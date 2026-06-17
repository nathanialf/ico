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
    """Find the TU stem whose .c still carries an INCLUDE_ASM stub for <func>."""
    pat = inc_line(func)
    files = run(["git", "ls-files", "*.c"]).stdout.split()
    for f in files:
        try:
            if pat.search((ROOT / f).read_text(errors="replace")):
                return f[:-2]          # strip ".c" → repo-relative stem
        except OSError:
            continue
    return None


def replace_stub(cpath, func, body):
    txt = cpath.read_text()
    cpath.write_text(inc_line(func).sub(lambda m: body.rstrip() + "\n", txt, count=1))


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
            "last_protocol": None, "last_protocol_at": 0}


def advance(q):
    """Pick the next still-unmatched pending func (out-of-band matches drop out)."""
    while q["pending"]:
        nxt = q["pending"].pop(0)
        if is_stub(nxt["tu"], nxt["func"]):
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


def do_commit(q, func, tu, v):
    ok, err = commit_seq(func, tu, commit_msg(func, tu))
    if not ok:
        return emit_blocker(q, func, err, "commit")
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


def harvest(q, func, tu):
    """Apply each permuter output (lowest real_count first via diff --dry).
    Returns: 'committed' | 'improved' | 'none'. Leaves the TU reverted to its
    parked stub on 'none'."""
    rundir = ROOT / "lib" / "decomp-permuter" / "runs" / func
    outs = sorted(rundir.glob("output-*/source.c")) if rundir.is_dir() else []
    if not outs:
        return "none"
    cpath = ML.resolve_tu_path(tu)
    best = (ML.load_state(func) or {}).get("best")
    best_rc, best_cand = None, None
    for src in outs:
        try:
            cand = src.read_text(errors="replace")
        except OSError:
            continue
        replace_stub(cpath, func, cand)
        rc, d = ml("diff", tu, func, "--dry")
        revert_tu(cpath)                          # restore the committed stub
        cc = d.get("real_count") if isinstance(d, dict) else None
        if cc is None or cc < 0:
            continue
        if best_rc is None or cc < best_rc:
            best_rc, best_cand = cc, cand
    if best_cand is None:
        return "none"
    if best_rc == 0:
        replace_stub(cpath, func, best_cand)
        ok, _ = commit_seq(func, tu, commit_msg(func, tu))
        if ok:
            return "committed"
        revert_tu(cpath)
        return "none"
    if best is not None and best_rc < best:
        replace_stub(cpath, func, best_cand)
        seed = ROOT / "tough_nuts" / func / (func + ".c")
        seed.parent.mkdir(parents=True, exist_ok=True)
        seed.write_text(best_cand)
        ml("reset", func, "--reason", f"permuter harvest: rc{best_rc}")
        return "improved"
    return "none"


def do_permute(q, func, tu, v):
    cpath = ML.resolve_tu_path(tu)
    reason = v.get("reason", "stall>=30")
    pr = run([PY, ROOT / "tools" / "park_tu.py", func, rel(cpath), reason])
    if pr.returncode != 0:
        return emit_blocker(q, func, "park_tu(permute) failed:\n" + (pr.stdout + pr.stderr)[-400:], "permute")
    rc, out = ninja()
    if rc != 0:
        return emit_blocker(q, func, "ninja after park(permute) failed:\n" + out[-400:], "permute")
    run(["git", "add", "-A"])
    run(["git", "commit", "-m", f"park {func} ({tu}) — pre-permute seed"])
    # fire the bounded permuter (self-gated at stall>=30; runs foreground)
    seed = ROOT / "tough_nuts" / func / (func + ".c")
    seedarg = [rel(seed)] if seed.exists() else []
    try:
        run([ROOT / "tools" / "permute_run.sh", func, *seedarg,
             "--", "--stop-on-zero", "-j", "4"], timeout=PERMUTE_TIMEOUT)
    except subprocess.TimeoutExpired:
        pass
    outcome = harvest(q, func, tu)
    if outcome == "committed":
        q["done"][func] = "matched"
        q["current"] = None
        save_queue(q)
        return None
    if outcome == "improved":
        # re-attack from the lower floor: keep workspace, re-diff → iterate
        save_queue(q)
        return None                              # current stays; churn re-diffs
    ml("record", func, "--permuted")             # resolution (b): exhausted
    q["done"][func] = "parked"
    q["parked"].append(func)
    q["current"] = None
    save_queue(q)
    return None


# ---------------------------------------------------------------- the churn
def churn(q, just_edited=False, lever=None):
    while True:
        cur = q.get("current") or advance(q)
        if not cur:
            _stamp(q, "done")
            emit({"protocol": "done",
                  "matched": [f for f, s in q["done"].items() if s == "matched"],
                  "parked": q["parked"], "skipped": q["skipped"]})
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
            replace_stub(cpath, func, seed.read_text(errors="replace"))
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
                      "last_protocol": q.get("last_protocol"),
                      "current_state": ({k: st.get(k) for k in
                                         ("best", "stall", "nonnovel", "iter")}
                                        if st else None)}, indent=2))


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
    KNOWN = {"step", "status", "abort", "start"}
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
    if args.cmd == "abort":
        return cmd_abort(args.func, " ".join(args.reason))
    return cmd_start(getattr(args, "set_spec", None))


if __name__ == "__main__":
    main()
