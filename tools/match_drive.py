#!/usr/bin/env python3
"""match_drive.py — the decomp-match CONDUCTOR.

The model is a pure *iterate-only hypothesis oracle*. This driver OWNS the loop:
it churns through every mechanical transition (workspace setup, diff, next,
commit, park, permute, queue advance) and returns to the model at exactly ONE
point — verdict `iterate` (or a `compile-fail` flavor of it). Park / permute /
commit / clone / SHA-gate all run here, with no model involvement and no path
the model can reach to stop, ask, park, or permute.

`tools/match_loop.py` stays the *decision* oracle (diff/next/record/reset/clone);
this driver is the *executor* the skill used to be. One invocation runs until it
hits an `iterate`, empties the queue (`done`), or a script genuinely errors
(`blocker`).

Model-facing protocol (stdout, one JSON object per exit; dispatch on `protocol`):
  iterate    — the ONLY exit-to-model: recover dev intent + apply the Step-3
               playbook, Edit ONE distinct hypothesis, then `match_drive.py step`.
  re-demand  — the last edit produced NO novel codegen (cosmetic/no-op): it did
               not count; produce a genuinely DISTINCT shape. Escalates.
  done       — queue empty.
  blocker    — a tool errored / a file is missing (validated, not a judgment).

CLI:
  match_drive.py <set-spec>            # start (or resume if no spec) → first iterate
  match_drive.py step <func> [--lever "<desc>"]   # model re-entry after one edit
  match_drive.py status                # dump the driver queue + current state
  match_drive.py abort <func> "<reason>"          # drop current func (logged)

<set-spec>: a bare <func> (TU resolved by grepping its INCLUDE_ASM stub),
            `smallest:N` (across all author scopes), `scope:<dir>`, or a path to
            a newline-delimited func list.
"""
from __future__ import annotations
import argparse
import json
import os
import re
import signal
import subprocess
import sys
import time
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import match_loop as ML  # reuse ROOT, STATE_DIR, resolve_tu_path, load_state

ROOT = ML.ROOT
STATE_DIR = ML.STATE_DIR
QUEUE = STATE_DIR / "_drive_queue.json"
VERSION = os.environ.get("VERSION", "aug6")
PERMUTE_TIMEOUT = int(os.environ.get("PERMUTE_TIMEOUT", "600"))
# A stall=30 park now fires its permuter and BLOCKS to completion, harvesting it
# in-line so the step returns the real outcome (matched / exhausted) — see
# do_permute. This cap only bounds any LEGACY detached runs still pending from an
# older queue (drained before a new synchronous run); the synchronous path is
# serial by construction, so it never stacks background jobs.
MAX_CONCURRENT_PERMUTES = int(os.environ.get("MAX_PERMUTES", "2"))
# How many lowest-score candidate outputs to evaluate per harvest (diff --dry is
# not free; a long run can leave hundreds of output-*/ dirs).
HARVEST_TOPN = int(os.environ.get("HARVEST_TOPN", "12"))
NONNOVEL_LOUD = 3            # streak at which re-demand escalates to "reconsider"
SCOPES = ["fumi", "script", "common", "sugipon", "seki", "omori", "ito"]
PY = sys.executable


# ---------------------------------------------------------------- shell helpers
def _env():
    e = dict(os.environ)
    e["VERSION"] = VERSION
    return e


def run(cmd, timeout=None, capture=True):
    return subprocess.run([str(c) for c in cmd], cwd=str(ROOT), env=_env(),
                          capture_output=capture, text=True, timeout=timeout)


def ml(*args):
    """Invoke a match_loop.py subcommand; return (returncode, parsed|text)."""
    p = run([PY, ROOT / "tools" / "match_loop.py", *args])
    try:
        return p.returncode, json.loads(p.stdout)
    except Exception:
        return p.returncode, (p.stdout + p.stderr)


def ninja():
    nj = ROOT / ".venv" / "bin" / "ninja"
    exe = str(nj) if nj.exists() else "ninja"
    p = run([exe, "-C", str(ROOT)])
    return p.returncode, (p.stdout + p.stderr)


def now():
    return int(time.time())


def rel(p):
    return str(Path(p).relative_to(ROOT))


# ---------------------------------------------------------------- TU / asm glue
def inc_line(func):
    return re.compile(
        r'^[ \t]*INCLUDE_ASM(?:_NOAT)?\("[^"]*",\s*' + re.escape(func) + r'\s*\);[ \t]*$',
        re.M)


def is_stub(tu, func):
    cpath = ML.resolve_tu_path(tu)
    if not cpath or not cpath.exists():
        return False
    return bool(inc_line(func).search(cpath.read_text(errors="replace")))


def resolve_tu_for(func):
    """Find the canonical SOURCE-TREE TU stem that DEFINES <func> — as an
    INCLUDE_ASM stub (unmatched) OR as an in-progress C body (near-miss seed).

    tough_nuts/ park snapshots are EXCLUDED: each is a whole-TU snapshot that
    carries INCLUDE_ASM stubs for its *sibling* funcs, so a plain stub search
    mis-resolves any func that is currently a body in its real TU to a
    non-compilable tough_nuts stem — the bug that froze func_00166D00 on an endless
    false compile-fail (its body lives in fumi/src/fuzio.c, but the stub survives in
    tough_nuts/func_00166BD8/...). Prefer a real stub site; fall back to a body
    site so an in-progress near-miss still resolves to its own TU."""
    pat = inc_line(func)
    files = run(["git", "ls-files", "*.c"]).stdout.split()
    body_hit = None
    for f in files:
        if f.startswith("tough_nuts/"):
            continue                       # snapshot seed, never the canonical TU
        try:
            txt = (ROOT / f).read_text(errors="replace")
        except OSError:
            continue
        if pat.search(txt):
            return f[:-2]                  # stub site — the canonical owner
        if body_hit is None and extract_func_def(txt, func) is not None:
            body_hit = f[:-2]              # in-progress body — fallback owner
    return body_hit


def replace_stub(cpath, func, body):
    txt = cpath.read_text()
    cpath.write_text(inc_line(func).sub(lambda m: body.rstrip() + "\n", txt, count=1))


def extract_func_def(text, func):
    """Pull the single definition of <func> out of a blob. The permuter seed and
    its candidate outputs are the WHOLE TU (park_tu snapshots the full coalesced
    file so the permuter keeps surrounding context). Splicing that whole blob into
    a single INCLUDE_ASM line would duplicate every sibling def → compile-fail.
    Return just <func>'s source span (signature .. matching '}'), or None if it is
    not present as a definition (only a call/declaration). Brace counting is naive
    about braces inside strings/comments, which the matched C here doesn't hit."""
    for m in re.finditer(r'\b' + re.escape(func) + r'\s*\(', text):
        depth, j = 0, m.end() - 1                     # at the '('
        while j < len(text):                          # find the matching ')'
            if text[j] == '(':
                depth += 1
            elif text[j] == ')':
                depth -= 1
                if depth == 0:
                    break
            j += 1
        else:
            continue
        k = j + 1
        while k < len(text) and text[k] in ' \t\r\n':
            k += 1
        if k >= len(text) or text[k] != '{':
            continue                                  # decl/call, not a definition
        depth, e = 0, k
        while e < len(text):                          # brace-match the body
            if text[e] == '{':
                depth += 1
            elif text[e] == '}':
                depth -= 1
                if depth == 0:
                    break
            e += 1
        else:
            continue
        start = text.rfind('\n', 0, m.start()) + 1    # back to start of sig line
        return text[start:e + 1]
    return None


def seed_func_body(body, func):
    """A whole-TU seed/candidate → just <func>'s definition (so a splice touches
    one function and leaves siblings pristine). Falls back to the blob unchanged
    if no definition is found (e.g. an already-single-func body)."""
    return extract_func_def(body, func) or body


def revert_tu(cpath):
    run(["git", "checkout", "--", rel(cpath)])


def gen_scaffold(func, tu):
    """Best-effort C scaffold (may compile-fail → handed back as an iterate). A
    bare stub still locks the model to the location."""
    spath = ROOT / "asm" / VERSION / "nonmatchings" / tu / (func + ".s")
    if spath.exists():
        p = run([PY, ROOT / "tools" / "classify_asm.py", "--scaffold", rel(spath)])
        out = p.stdout or ""
        m = out.find("--- scaffold")
        if m != -1:
            nl = out.find("\n", m)
            body = out[nl + 1:].strip()
            if body and "{" in body:
                return body + "\n"
    return f"void {func}(void) {{\n    /* TODO: scaffold unavailable — recover from asm */\n}}\n"


# ---------------------------------------------------------------- queue
def load_queue():
    if QUEUE.exists():
        return json.loads(QUEUE.read_text())
    return None


def save_queue(q):
    STATE_DIR.mkdir(parents=True, exist_ok=True)
    QUEUE.write_text(json.dumps(q, indent=2))


def sweep_rows(scope):
    scopes = [scope] if scope else SCOPES
    rows = []
    for sc in scopes:
        p = run([ROOT / "tools" / "sweep_targets.sh", sc])
        for line in p.stdout.splitlines():
            parts = line.split()
            if len(parts) >= 4 and parts[3] == ".":      # "." == fresh
                try:
                    rows.append((int(parts[0]), parts[1], parts[2]))
                except ValueError:
                    continue
    rows.sort(key=lambda r: r[0])
    seen, out = set(), []
    for _, tu, func in rows:
        if func not in seen:
            seen.add(func)
            out.append({"tu": tu, "func": func})
    return out


def build_queue(spec):
    if spec.startswith("smallest:"):
        return sweep_rows(None)[:int(spec.split(":", 1)[1])]
    if spec.startswith("scope:"):
        return sweep_rows(spec.split(":", 1)[1])
    p = ROOT / spec
    if p.exists() and p.is_file():
        items = []
        for ln in p.read_text().splitlines():
            func = ln.strip()
            if not func or func.startswith("#"):
                continue
            tu = resolve_tu_for(func)
            if tu:
                items.append({"tu": tu, "func": func})
        return items
    # bare <func>
    tu = resolve_tu_for(spec)
    return [{"tu": tu, "func": spec}] if tu else []


def fresh_queue(spec, items):
    return {"set_spec": spec, "pending": items, "current": None, "done": {},
            "parked": [], "skipped": [], "nonnovel_streak": {},
            "workspace_ready": [], "lever": None,
            "permutes_pending": [], "permute_events": [],
            "last_protocol": None, "last_protocol_at": 0}


def engaged_unmatched(func):
    """True if the driver has ENGAGED <func> (it has a match_loop json) and it is
    NOT a completed match (best != 0): an in-progress near-miss (best > 0) OR a
    freshly-scaffolded pre-diff body (best == None). Such a non-stub body must be
    RESUMED, not skipped as out-of-band. A func with NO json (matched via a sibling's
    coalesced TU) or best == 0 (a real match) is genuinely done and is skipped.

    Without the best==None case, a scaffold a prior worker left un-diffed was wrongly
    skipped, forcing the worker to hand-restore the INCLUDE_ASM stub to re-engage."""
    try:
        st = json.loads((STATE_DIR / f"{func}.json").read_text())
    except Exception:
        return False
    return st.get("best") != 0


def advance(q):
    """Pick the next still-unmatched pending func. A func that is no longer an
    INCLUDE_ASM stub is normally an out-of-band match (matched via a sibling's
    coalesced TU) and drops out — EXCEPT a driver-engaged, unmatched body (an
    in-progress near-miss seed OR a freshly-scaffolded pre-diff body), which must be
    RESUMED, not skipped (the bug that silently dropped a sticky seed / a scaffold)."""
    while q["pending"]:
        nxt = q["pending"].pop(0)
        if is_stub(nxt["tu"], nxt["func"]) or engaged_unmatched(nxt["func"]):
            q["current"] = nxt
            save_queue(q)
            return nxt
        q["done"][nxt["func"]] = "skipped(out-of-band)"
        q["skipped"].append(nxt["func"])
    q["current"] = None
    save_queue(q)
    return None


# ---------------------------------------------------------------- emit
def _stamp(q, proto):
    q["last_protocol"] = proto
    q["last_protocol_at"] = now()
    save_queue(q)


def emit(obj, code=0):
    print(json.dumps(obj, indent=2))
    sys.exit(code)


def emit_blocker(q, func, detail, stage):
    _stamp(q, "blocker")
    emit({"protocol": "blocker", "func": func, "detail": detail, "stage": stage}, 1)


def iterate_obj(func, tu, d, kind):
    st = ML.load_state(func)
    extra = " The build does NOT compile — fix the C." if kind == "compile-fail" else ""
    return {
        "protocol": "iterate", "func": func, "tu": tu,
        "scaffold_at": rel(ML.resolve_tu_path(tu)),
        "real_count": d.get("real_count"), "diff_sites": d.get("diff_sites"),
        "tags": d.get("tags", []), "first_divergence": d.get("first_divergence"),
        "divergence_map": d.get("divergence_map", []),
        "stall": f'{st.get("stall", 0)}/30', "tried_levers": st.get("tried_levers", []),
        "kind": kind,
        "instructions": (
            f"Forming this hypothesis is the ONLY decision you own. You have NO "
            f"say in stopping, pausing, asking the user, reporting, or judging "
            f"this function hard / a floor / permuter-class — those do not exist "
            f"for you. Do not end the turn: produce the next edit and `step`, "
            f"every cycle, until the driver returns done/blocker. "
            f"ONE hypothesis. REFERENCE Step 1 (recover dev intent — run "
            f"`tools/classify_asm.py --bundle {func}` on demand) + Step 3 PLAYBOOK "
            f"(the row for the diff tag). Edit ONE genuinely distinct C shape into "
            f"{tu}.c (no crutches — diff rejects them), then call: "
            f"tools/match_drive.py step {func} --lever \"<what you tried>\"." + extra),
    }


def redemand_obj(func, tu, d, streak):
    if streak < NONNOVEL_LOUD:
        reason = ("Your edit produced NO codegen change vs a prior attempt "
                  "(cosmetic/no-op, or you did not change the build). It did NOT "
                  "count toward the stall. Edit a genuinely DISTINCT C shape.")
    else:
        reason = (
            f"{streak} non-novel edits in a row — you are re-spelling, not "
            f"reconsidering. STOP. Re-read the asm and run "
            f"`tools/classify_asm.py --bundle {func}`, reconstruct the developer's "
            f"data model and the function's ACTUAL semantics, then change the "
            f"MEANING (type / aliasing / liveness / factoring / CFG / algorithm) — "
            f"not the syntax. There is no batching and no escape; only a distinct "
            f"codegen moves this forward.")
    st = ML.load_state(func)
    return {"protocol": "re-demand", "func": func, "tu": tu,
            "nonnovel_streak": str(streak), "reason": reason,
            "real_count": d.get("real_count"), "diff_sites": d.get("diff_sites"),
            "stall": f'{st.get("stall", 0)}/30',
            "first_divergence": d.get("first_divergence"),
            "instructions": (f"After a DISTINCT edit: tools/match_drive.py step "
                             f"{func} --lever \"<what you tried>\".")}


# ---------------------------------------------------------------- executors
def commit_msg(func, tu):
    st = ML.load_state(func)
    levers = "; ".join(st.get("tried_levers", [])) or "direct"
    return f"match {func} ({tu})\n\nlevers: {levers}\nrc 0 in {st.get('iter', '?')} iters"


def clone_and_commit(func):
    run([PY, ROOT / "tools" / "match_loop.py", "clone", "--from", func])
    if run(["git", "status", "--porcelain"]).stdout.strip():
        run(["git", "add", "-A"])
        run(["git", "commit", "-m", f"clone byte-identical twins of {func}"])


def commit_seq(func, tu, msg):
    """ninja SHA gate → check_no_rom → git add -A → commit → clone. (ok, errmsg)."""
    rc, out = ninja()
    if rc != 0:
        return False, "ninja/verify_elf failed:\n" + out[-600:]
    cr = run([ROOT / "tools" / "check_no_rom.sh"])
    if cr.returncode != 0:
        return False, "check_no_rom failed:\n" + (cr.stdout + cr.stderr)[-300:]
    run(["git", "add", "-A"])
    gc = run(["git", "commit", "-m", msg])
    if gc.returncode != 0:
        return False, "git commit failed:\n" + (gc.stdout + gc.stderr)[-500:]
    clone_and_commit(func)
    return True, ""


def _warn_volatile_commit(q, func, tu):
    """§2.7 (decomp/COOKBOOK.md): `volatile` is a do-not-ship home-spill diagnostic
    crutch — the clean home-forcing construct is the real source. User policy is
    WARN-BUT-ALLOW: a match whose committed body contains `volatile` IS committed
    (its bytes are byte-identical), but it is flagged for review — recorded to the
    queue's events (surfaced in the driver's `done` payload) and to a warnings log
    the supervisor reads. NOT a block. Only matters at commit (a match keeps its C
    body in the ELF build); a park keeps the INCLUDE_ASM stub, so park seeds don't
    ship and aren't flagged here."""
    cpath = ML.resolve_tu_path(tu)
    try:
        body = extract_func_def(cpath.read_text(errors="replace"), func) or ""
    except Exception:
        return
    if re.search(r"\bvolatile\b", body):
        msg = (f"[VOLATILE-WARN] {func} ({tu}) committed WITH `volatile` in its body "
               f"— §2.7 do-not-ship crutch; review and re-derive the clean shape.")
        _plog(q, func, msg)
        try:
            with open(STATE_DIR / "_volatile_warnings.log", "a") as fh:
                fh.write(f"{func}\t{tu}\n")
        except OSError:
            pass
        sys.stderr.write(msg + "\n")


def do_commit(q, func, tu, v):
    ok, err = commit_seq(func, tu, commit_msg(func, tu))
    if not ok:
        return emit_blocker(q, func, err, "commit")
    _warn_volatile_commit(q, func, tu)
    q["done"][func] = "matched"
    q["current"] = None
    save_queue(q)
    return None


def do_park(q, func, tu, v):
    cpath = ML.resolve_tu_path(tu)
    reason = v.get("reason", "parked by driver")
    pr = run([PY, ROOT / "tools" / "park_tu.py", func, rel(cpath), reason])
    if pr.returncode != 0:
        return emit_blocker(q, func, "park_tu failed:\n" + (pr.stdout + pr.stderr)[-400:], "park")
    rc, out = ninja()
    if rc != 0:
        return emit_blocker(q, func, "ninja after park failed:\n" + out[-400:], "park")
    run(["git", "add", "-A"])
    run(["git", "commit", "-m", f"park {func} ({tu})"])
    q["done"][func] = "parked"
    q["parked"].append(func)
    q["current"] = None
    save_queue(q)
    return None


def _plog(q, func, msg):
    """Record a permuter lifecycle event for later surfacing (status/done). The
    driver only prints one JSON per exit, so drain/launch progress is buffered
    here rather than written to stdout mid-churn."""
    ev = q.setdefault("permute_events", [])
    ev.append({"func": func, "msg": msg, "at": now()})
    del ev[:-40]                                  # keep the tail bounded


def _cand_score(src):
    """output-<score>-<n>/source.c → <score> (for cheapest-first harvest)."""
    try:
        return int(src.parent.name.split("-")[1])
    except (IndexError, ValueError):
        return 1 << 30


def launch_permute(func, tu):
    """Fire the permuter DETACHED and time-BOUNDED, return a pending record.

    `timeout` caps wall-clock (hard SIGKILL escalation) so a run can never leak
    the way the old background `&` jobs did; `start_new_session` puts it in its
    own process group so (a) it survives this short-lived driver invocation to be
    harvested later, and (b) it is killable as a group by pgid if it overruns."""
    seed = ROOT / "tough_nuts" / func / (func + ".c")
    seedarg = [rel(seed)] if seed.exists() else []
    STATE_DIR.mkdir(parents=True, exist_ok=True)   # ninja can wipe build/ mid-run
    logp = STATE_DIR / f"permute_{func}.log"
    cmd = ["timeout", "-k", "15", str(PERMUTE_TIMEOUT),
           str(ROOT / "tools" / "permute_run.sh"), func, *seedarg,
           "--", "--stop-on-zero", "-j", "4"]
    lf = open(logp, "wb")
    p = subprocess.Popen([str(c) for c in cmd], cwd=str(ROOT), env=_env(),
                         stdout=lf, stderr=subprocess.STDOUT,
                         stdin=subprocess.DEVNULL, start_new_session=True)
    lf.close()
    return {"func": func, "tu": tu, "pgid": p.pid, "log": rel(logp),
            "started": now(), "deadline": now() + PERMUTE_TIMEOUT + 30}


def _pg_alive(pgid):
    try:
        os.killpg(pgid, 0)
        return True
    except ProcessLookupError:
        return False
    except PermissionError:
        return True


def eval_best(func, tu, cpath):
    """Cheapest-score-first, apply each candidate + diff --dry for its TRUE
    real_count (the permuter's own score can be anti-correlated). Always leaves
    the TU reverted to its committed state. Returns (best_rc, best_cand)."""
    rundir = ROOT / "lib" / "decomp-permuter" / "runs" / func
    outs = sorted(rundir.glob("output-*/source.c"), key=_cand_score) if rundir.is_dir() else []
    best_rc, best_cand = None, None
    for src in outs[:HARVEST_TOPN]:
        try:
            cand = src.read_text(errors="replace")
        except OSError:
            continue
        replace_stub(cpath, func, seed_func_body(cand, func))
        rc, d = ml("diff", tu, func, "--dry")
        revert_tu(cpath)                          # restore the committed stub
        cc = d.get("real_count") if isinstance(d, dict) else None
        if cc is None or cc < 0:
            continue
        if best_rc is None or cc < best_rc:
            best_rc, best_cand = cc, cand
    return best_rc, best_cand


def harvest_pending(q, rec, active=False):
    """Evaluate a finished permuter's outputs. Commits a rc0 match; on a sub-best
    (non-zero) improvement the behaviour forks on `active`:
      - active=False (background drain, NO live session): reseed tough_nuts and
        stay parked — re-found on a future resume. DO NOT re-activate the loop.
      - active=True (blocking stall=30 path, model IS in the loop): install the
        improved shape live, re-baseline (stall->0, best->the lower rc), un-park,
        and hand it back so churn re-emits `iterate` on the lower-count diff.
    Otherwise marks it permuter-exhausted. Leaves the tree clean except on the
    active improved-handback (which installs the lower-floor C for the model to
    iterate on, exactly as a normal iterating step would).
    Returns one of: 'matched' | 'improved' | 'exhausted' | 'none' | 'skipped'."""
    func, tu = rec["func"], rec["tu"]
    cpath = ML.resolve_tu_path(tu)
    if cpath is None:
        _plog(q, func, "harvest skipped — TU unresolved")
        return "skipped"
    best_rc, best_cand = eval_best(func, tu, cpath)
    if best_cand is None:
        _plog(q, func, "permuter produced no usable candidate")
        return "none"
    if best_rc == 0:
        replace_stub(cpath, func, seed_func_body(best_cand, func))
        ok, err = commit_seq(func, tu, commit_msg(func, tu))
        if ok:
            q["done"][func] = "matched"
            if func in q.get("parked", []):
                q["parked"].remove(func)
            _plog(q, func, "permuter MATCH rc0 — committed")
            return "matched"
        revert_tu(cpath)
        _plog(q, func, f"permuter rc0 but commit failed: {err[:120]}")
        return "exhausted"
    best = (ML.load_state(func) or {}).get("best")
    if best is not None and best_rc < best:
        # A STRICT improvement on the parked floor: always reseed tough_nuts so a
        # future resume starts from the lower floor.
        seed = ROOT / "tough_nuts" / func / (func + ".c")
        seed.parent.mkdir(parents=True, exist_ok=True)
        seed.write_text(best_cand)
        if active:
            # Live stall=30 path: hand the lower floor back as a fresh `iterate`.
            # Install it as the working scaffold, re-baseline (`ml reset` wipes
            # best/stall so the model gets a clean 30-budget from the lower rc),
            # un-park, and restore `current` so churn re-emits iterate. Re-activating
            # the loop here is correct (unlike the drain path) because the model is
            # actively grinding this func in THIS call.
            replace_stub(cpath, func, seed_func_body(best_cand, func))
            ml("reset", func, "--reason", f"permuter improved rc{best}->rc{best_rc}")
            if func in q.get("parked", []):
                q["parked"].remove(func)
            q["done"].pop(func, None)
            q["current"] = {"func": func, "tu": tu}
            if func not in q["workspace_ready"]:
                q["workspace_ready"].append(func)
            _plog(q, func, f"permuter improved rc{best}->rc{best_rc}; handed back as iterate")
        else:
            _plog(q, func, f"permuter improved seed rc{best}->rc{best_rc}; reseeded, stays parked")
        return "improved"
    ml("record", func, "--permuted")
    bs = f"rc{best}" if best is not None else "?"
    _plog(q, func, f"permuter exhausted (best rc{best_rc} >= parked {bs})")
    return "exhausted"


def drain_permutes(q, wait=False):
    """Harvest finished background permuters. Call ONLY when no func edit is in
    flight (tree at committed state) — harvest_pending commits/reverts the TU.
    `wait=True` blocks (bounded by each run's deadline) for still-running ones;
    the default non-blocking pass leaves them pending for the next invocation."""
    pend = q.get("permutes_pending") or []
    if not pend:
        return
    # Never harvest a run whose TU is the one a func edit is currently in flight
    # in — harvest_pending commits/reverts that TU and would clobber the edit.
    cur_tu = (q.get("current") or {}).get("tu")
    still = []
    for rec in pend:
        if rec.get("tu") == cur_tu and cur_tu is not None:
            still.append(rec)
            continue
        alive = _pg_alive(rec["pgid"])
        overdue = now() >= rec.get("deadline", 0)
        if alive and not overdue and not wait:
            still.append(rec)                     # let it keep cooking
            continue
        if alive and wait and not overdue:
            while _pg_alive(rec["pgid"]) and now() < rec.get("deadline", 0):
                time.sleep(5)
            alive = _pg_alive(rec["pgid"])
            overdue = now() >= rec.get("deadline", 0)
        if alive and overdue:                     # bound exceeded — reap the group
            try:
                os.killpg(rec["pgid"], signal.SIGKILL)
            except (ProcessLookupError, PermissionError):
                pass
        harvest_pending(q, rec)
    q["permutes_pending"] = still
    save_queue(q)


def do_permute(q, func, tu, v):
    """Park the seed (commit it green), fire the permuter, and BLOCK until it
    finishes (bounded by PERMUTE_TIMEOUT), then harvest it IN-LINE so the verdict
    reflects the real outcome. The stall=30 step must not escape with the run
    still cooking: the model has to learn, from this one call, the real result —
    one of three: MATCHED (rc0, committed — func resolved → churn emits `done`);
    IMPROVED (a lower non-zero floor — installed live, stall reset, un-parked, so
    churn re-emits `iterate` on the lower-count diff to re-attack by hand); or
    EXHAUSTED (no improvement — func stays parked). No 'harvest deferred' limbo."""
    cpath = ML.resolve_tu_path(tu)
    reason = v.get("reason", "stall>=30")
    # Seed the permuter from the BEST-count shape, not the live file. The stall=30
    # gate is tripped by a NOVEL (usually divergent) final edit, so the live TU at
    # this moment is typically NOT the lowest-count source. Restore the best
    # snapshot into the TU first so park_tu hands the permuter the best regalloc
    # to perturb from (best-effort: a no-op if no snapshot was recorded yet).
    snap = ML.best_src_path(func)
    if cpath and snap.exists():
        try:
            cpath.write_text(snap.read_text())
        except OSError:
            pass
    pr = run([PY, ROOT / "tools" / "park_tu.py", func, rel(cpath), reason])
    if pr.returncode != 0:
        return emit_blocker(q, func, "park_tu(permute) failed:\n" + (pr.stdout + pr.stderr)[-400:], "permute")
    rc, out = ninja()
    if rc != 0:
        return emit_blocker(q, func, "ninja after park(permute) failed:\n" + out[-400:], "permute")
    run(["git", "add", "-A"])
    run(["git", "commit", "-m", f"park {func} ({tu}) — pre-permute seed"])
    # Reap any older background runs first (they may have finished while the human
    # was grinding), so they don't collide with this synchronous run's harvest.
    drain_permutes(q)
    # Mark parked BEFORE harvesting: harvest_pending's rc0 path removes the func
    # from q["parked"] and flips it to "matched", so the state must be set first.
    q["done"][func] = "parked"
    if func not in q["parked"]:
        q["parked"].append(func)
    q["current"] = None
    save_queue(q)
    # Fire and BLOCK to completion (bounded). The run exits on its own when it has
    # found rc0 or exhausted its search; the deadline is only the hard ceiling.
    rec = launch_permute(func, tu)
    _plog(q, func, f"permuter launched (bounded {PERMUTE_TIMEOUT}s, BLOCKING to completion)")
    save_queue(q)
    while _pg_alive(rec["pgid"]) and now() < rec.get("deadline", 0):
        time.sleep(5)
    if _pg_alive(rec["pgid"]):                       # overran the bound — reap it
        try:
            os.killpg(rec["pgid"], signal.SIGKILL)
        except (ProcessLookupError, PermissionError):
            pass
    # Harvest IN-LINE (tree is at the committed park, no edit in flight). active=True:
    # rc0 -> commit + matched; a lower non-zero floor -> install live, reset, un-park,
    # restore `current` so churn re-emits iterate; else stays parked. (drain_permutes
    # harvests background runs with active=False -> reseed-and-stay-parked.)
    harvest_pending(q, rec, active=True)
    save_queue(q)
    return None


# ---------------------------------------------------------------- the churn
def churn(q, just_edited=False, lever=None):
    while True:
        cur = q.get("current")
        if not cur:
            # No func edit in flight → safe point to harvest finished permuters
            # (harvest_pending commits/reverts TUs) before picking the next func.
            drain_permutes(q)
            cur = advance(q)
        if not cur:
            drain_permutes(q)                     # last reap before reporting done
            _stamp(q, "done")
            emit({"protocol": "done",
                  "matched": [f for f, s in q["done"].items() if s == "matched"],
                  "parked": q["parked"], "skipped": q["skipped"],
                  "permutes_running": [r["func"] for r in q.get("permutes_pending", [])],
                  "permute_events": q.get("permute_events", [])[-10:]})
        func, tu = cur["func"], cur["tu"]
        if ML.resolve_tu_path(tu) is None:
            return emit_blocker(q, func, f"cannot resolve TU source for {tu}", "resolve")

        # one-time workspace setup (scaffold a fresh func; apply seed + reset a resume)
        if func not in q["workspace_ready"]:
            status, detail = setup_workspace(func, tu)
            if status == "blocker":
                return emit_blocker(q, func, detail, "setup")
            q["workspace_ready"].append(func)
            save_queue(q)

        rc, d = ml("diff", tu, func)
        if not isinstance(d, dict):
            return emit_blocker(q, func, f"diff failed:\n{str(d)[-400:]}", "diff")
        if d.get("status") == "compile-fail":
            _stamp(q, "iterate")
            emit(iterate_obj(func, tu, d, kind="compile-fail"))

        if just_edited:
            just_edited = False                  # applies only to this re-entry's diff
            if d.get("status") != "match" and not d.get("novel", True):
                streak = q["nonnovel_streak"].get(func, 0) + 1
                q["nonnovel_streak"][func] = streak
                _stamp(q, "re-demand")
                emit(redemand_obj(func, tu, d, streak))
            q["nonnovel_streak"][func] = 0
            if lever:
                ml("record", func, "--lever", lever)

        rc, vd = ml("next", func)
        if not isinstance(vd, dict):
            return emit_blocker(q, func, f"next failed:\n{str(vd)[-400:]}", "next")
        act = vd.get("action")
        if act == "iterate":
            _stamp(q, "iterate")
            emit(iterate_obj(func, tu, d, kind="iterate"))
        elif act == "commit":
            if do_commit(q, func, tu, vd):
                return
        elif act == "park":
            if do_park(q, func, tu, vd):
                return
        elif act == "permute":
            if do_permute(q, func, tu, vd):
                return
        elif act == "diff":
            continue
        else:
            return emit_blocker(q, func, f"unknown verdict {act!r}", "next")


def setup_workspace(func, tu):
    cpath = ML.resolve_tu_path(tu)
    if cpath is None:
        return "blocker", f"cannot resolve TU source for {tu}"
    seed = ROOT / "tough_nuts" / func / (func + ".c")
    is_resume = (ROOT / "tough_nuts" / func).is_dir() and seed.exists()
    if is_resume:
        if inc_line(func).search(cpath.read_text(errors="replace")):
            replace_stub(cpath, func, seed_func_body(seed.read_text(errors="replace"), func))
        ml("reset", func, "--reason", "resume via match_drive")   # MANDATORY re-baseline
        return "ok", "resume seed applied + reset"
    txt = cpath.read_text(errors="replace")
    if not inc_line(func).search(txt):
        return "ok", "no INCLUDE_ASM stub (already C) — left as-is"
    replace_stub(cpath, func, gen_scaffold(func, tu))
    return "ok", "scaffold installed"


# ---------------------------------------------------------------- CLI
def cmd_start(spec):
    q = load_queue()
    if spec is None:
        if q is None:
            emit({"protocol": "blocker", "detail": "no drive queue to resume — "
                  "pass a set-spec (<func> | smallest:N | scope:<dir> | <file>)"}, 1)
    else:
        items = build_queue(spec)
        if not items:
            emit({"protocol": "done", "matched": [], "parked": [], "skipped": [],
                  "note": f"no fresh targets for set-spec {spec!r}"})
        q = fresh_queue(spec, items)
        save_queue(q)
    churn(q, just_edited=False)


def cmd_step(func, lever):
    q = load_queue()
    if q is None:
        emit({"protocol": "blocker", "detail": "no active drive queue"}, 1)
    cur = q.get("current")
    if not cur or cur.get("func") != func:
        emit({"protocol": "blocker", "func": func,
              "detail": f"{func} is not the current driver func ({cur})"}, 1)
    churn(q, just_edited=True, lever=lever)


def cmd_status():
    q = load_queue()
    if q is None:
        print(json.dumps({"queue": None}))
        return
    cur = q.get("current")
    st = ML.load_state(cur["func"]) if cur else None
    print(json.dumps({"set_spec": q["set_spec"], "current": cur,
                      "pending": [i["func"] for i in q["pending"]],
                      "done": q["done"], "parked": q["parked"],
                      "permutes_running": [{"func": r["func"], "log": r.get("log"),
                                            "alive": _pg_alive(r["pgid"])}
                                           for r in q.get("permutes_pending", [])],
                      "permute_events": q.get("permute_events", [])[-10:],
                      "last_protocol": q.get("last_protocol"),
                      "current_state": ({k: st.get(k) for k in
                                         ("best", "stall", "nonnovel", "iter")}
                                        if st else None)}, indent=2))


def cmd_drain(wait):
    """Harvest finished (or, with --wait, still-running) background permuters
    out-of-band. Safe to run between match_drive steps; never call mid-func."""
    q = load_queue()
    if q is None:
        emit({"protocol": "blocker", "detail": "no active drive queue"}, 1)
    if q.get("current"):
        emit({"protocol": "blocker", "detail": "a func edit is in flight "
              f"({q['current'].get('func')}); drain only between funcs"}, 1)
    drain_permutes(q, wait=wait)
    emit({"protocol": "drained",
          "permutes_running": [r["func"] for r in q.get("permutes_pending", [])],
          "permute_events": q.get("permute_events", [])[-20:]})


def cmd_abort(func, reason):
    q = load_queue()
    if q is None:
        emit({"error": "no queue"}, 1)
    q.setdefault("aborted", []).append({"func": func, "reason": reason, "at": now()})
    if q.get("current", {}) and q["current"].get("func") == func:
        q["current"] = None
    q["done"][func] = f"aborted: {reason}"
    save_queue(q)
    churn(q, just_edited=False)


def main():
    KNOWN = {"step", "status", "abort", "start", "drain"}
    argv = sys.argv[1:]
    # No args → resume an active queue. A first token that is NOT a subcommand
    # (and not a help flag) is a bare <set-spec> → start. Both bypass argparse,
    # which would otherwise reject the bare spec as an "invalid choice".
    if not argv:
        return cmd_start(None)
    if argv[0] not in KNOWN and argv[0] not in ("-h", "--help"):
        return cmd_start(argv[0])

    ap = argparse.ArgumentParser(description="decomp-match conductor")
    sub = ap.add_subparsers(dest="cmd")
    p_step = sub.add_parser("step")
    p_step.add_argument("func")
    p_step.add_argument("--lever", default=None)
    sub.add_parser("status")
    p_dr = sub.add_parser("drain")
    p_dr.add_argument("--wait", action="store_true")
    p_ab = sub.add_parser("abort")
    p_ab.add_argument("func")
    p_ab.add_argument("reason", nargs="+")
    p_start = sub.add_parser("start")
    p_start.add_argument("set_spec", nargs="?", default=None)
    args = ap.parse_args(argv)

    if args.cmd == "step":
        return cmd_step(args.func, args.lever)
    if args.cmd == "status":
        return cmd_status()
    if args.cmd == "drain":
        return cmd_drain(args.wait)
    if args.cmd == "abort":
        return cmd_abort(args.func, " ".join(args.reason))
    return cmd_start(getattr(args, "set_spec", None))


if __name__ == "__main__":
    main()
