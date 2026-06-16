#!/usr/bin/env python3
"""
tools/match_loop.py — the shared matching-loop CORE.

This is the state machine + plateau policy that BOTH front-ends drive:
  * the interactive /decomp-match skill (agent fills the reasoning slots), and
  * the autonomous auto_match.py batch runner (reasoning slots = heuristics).

It does NOT itself decide *which* C lever to apply (that's reasoning); it
tracks progress via tools/match_diff.py's reloc-normalized real_count and
answers ONE question on demand: given where we are, what's the next ACTION
(iterate / permute / park / commit)? The discipline is plateau-based:
keep iterating while real_count drops; escalate after STALL_LIMIT passes of
no progress, or sooner when every remaining diff tag is permuter-territory.

State lives in build/match_loop/<func>.json so a loop survives across agent
turns / process boundaries.

Subcommands
  diff   <TU> <func>            run match_diff, fold result into state, print JSON
  record <func> --lever <desc>  mark a distinct hypothesis as tried
  next   <func> [--stall-limit N] [--override keep-going|permute|park]
                                 print the policy decision JSON
  reset  <func>                 clear state (start a fresh attempt)
  show   <func>                 dump current state
The diff result and the next-decision are plain JSON for easy consumption.
"""
from __future__ import annotations
import argparse
import json
import re
import subprocess
import sys
import tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
STATE_DIR = ROOT / "build" / "match_loop"

sys.path.insert(0, str(Path(__file__).resolve().parent))
try:
    import _asmsig
except Exception:
    _asmsig = None

DEFAULT_STALL_LIMIT = 30   # distinct hand hypotheses with NO real_count progress
#                            (raised from 12 to match the 20-iter discipline with
#                             headroom — regalloc/branch tails crack late, so the
#                             loop must not bail to "permuter food" early.)

# How the matching loop resolves a TU name to its editable source file —
# mirrors tools/quick_diff.sh's own search order so the best-source snapshot
# (and `revert`) write back to the exact file quick_diff compiles.
_SRC_PATTERNS = ("{tu}.c",                              # tu already a repo-rel path (aug6 subseg name)
                 "src/{tu}.c", "tough_nuts/{tu}/{tu}.c",
                 "sound/{tu}.c", "ios/{tu}.c", "isys/{tu}.c",
                 # aug6 dev tree (mirror tools/quick_diff.sh CSRC roots)
                 "common/src/{tu}.c",
                 "fumi/src/{tu}.c", "fumi/ios/{tu}.c", "fumi/sound/{tu}.c", "fumi/isys/{tu}.c",
                 "sugipon/src/{tu}.c", "seki/src/{tu}.c", "omori/src/{tu}.c",
                 "script/src/{tu}.c", "ito/src/{tu}.c", "ito/mpeg/{tu}.c")


def resolve_tu_path(tu: str | None) -> Path | None:
    if not tu:
        return None
    for pat in _SRC_PATTERNS:
        p = ROOT / pat.format(tu=tu)
        if p.exists():
            return p
    return None


def best_src_path(func: str) -> Path:
    return STATE_DIR / f"{func}.best.c"

# HARD-WON LESSON (this project's history): the matches came from HAND
# REASONING — including on regalloc-swap / fp-licm / frame-size, which were all
# cracked by hand (sceneManager s5/s6 pin, fightSound s4 hoist). So the permuter
# is NOT an interactive escape hatch DURING iteration: the loop reasons by hand
# until a genuine stall-limit plateau. But the plateau is NOT the end —
# **park, then permute**: park the seed and fire ONE bounded permuter shot on it
# (decomp-match REFERENCE Step 4), then harvest by TRUE real_count and adopt any
# improvement. There is no "offline-only batch" deferral and no early-permute.
PERMUTER_SCHEDULING = {"3.3", "8.3", "delay-slot-occupant"}
LOW_COUNT_FOR_PERMUTE = 8

# Retired matching crutches. A `best` measured from a source carrying any of
# these is NOT a clean floor — recording it pollutes the discipline (a pinned
# permuter output once set best=8 and triggered a hand `reset`). `diff` refuses
# to fold a crutch-tainted source into `best` unless `--allow-crutch`. Narrow to
# the unambiguous retired tokens + register-string pins; sanctioned
# `TRAILING_PAD_NOP()` / `__asm__("D_real")` far-sdata aliases do NOT match (no
# `asm("$`), so byte/layout-parity uses stay allowed.
CRUTCH_RE = re.compile(
    r'\bREG\s*\(|\bANCHOR\s*\(|\bMEM_BARRIER\b|\bKEEP_LIVE|'
    r'\bMATERIALIZE\b|\bNOREORDER_BARRIER\b|asm\s*\(\s*"\$')


def func_body(src: str, func: str) -> str:
    """Return the brace-matched C text of `func`'s definition in `src`, or '' if
    it is still an INCLUDE_ASM stub / not found. Scopes the crutch scan to the
    measured function (the TU may hold sanctioned asm in siblings)."""
    start = -1
    for m in re.finditer(r'\b' + re.escape(func) + r'\s*\(', src):
        p = m.start()
        anchor = max(src.rfind(';', 0, p), src.rfind('}', 0, p)) + 1
        if 'INCLUDE_ASM' in src[anchor:p]:
            continue
        start = anchor
    if start < 0:
        return ''
    b = src.find('{', start)
    if b < 0:
        return ''
    depth = 0
    for i in range(b, len(src)):
        if src[i] == '{':
            depth += 1
        elif src[i] == '}':
            depth -= 1
            if depth == 0:
                return src[start:i + 1]
    return ''


def state_path(func: str) -> Path:
    return STATE_DIR / f"{func}.json"


def load_state(func: str) -> dict:
    p = state_path(func)
    if p.exists():
        return json.loads(p.read_text())
    return {"func": func, "tu": None, "iter": 0, "best": None, "stall": 0,
            "permuted": False, "tried_levers": [], "history": [],
            "last_tags": [], "last_status": None}


def save_state(st: dict) -> None:
    STATE_DIR.mkdir(parents=True, exist_ok=True)
    state_path(st["func"]).write_text(json.dumps(st, indent=2))


def cmd_diff(args) -> int:
    py = sys.executable
    proc = subprocess.run(
        [py, str(ROOT / "tools" / "match_diff.py"), args.tu, args.func],
        capture_output=True, text=True, cwd=str(ROOT),
    )
    try:
        res = json.loads(proc.stdout)
    except json.JSONDecodeError:
        print(proc.stdout or proc.stderr, file=sys.stderr)
        return 2

    # Crutch guard: a clean floor cannot contain a retired matching crutch.
    # Scope the scan to the measured function (siblings may carry sanctioned
    # asm). A tainted source is flagged `crutch` and (unless --allow-crutch) is
    # NOT allowed to set `best` — exactly like a compile-fail, so a pinned
    # permuter output can never silently pollute the discipline.
    tp0 = resolve_tu_path(args.tu)
    body = func_body(tp0.read_text(), args.func) if tp0 else ''
    crutch = bool(body) and bool(CRUTCH_RE.search(body))
    res["crutch"] = crutch
    if crutch and not args.allow_crutch:
        res["crutch_warning"] = (
            "CRUTCH DETECTED (REG/ANCHOR/MEM_BARRIER/KEEP_LIVE/asm-pin) — NOT "
            "counted toward best/stall. A clean floor must be crutch-free; "
            "re-derive the shape. (--allow-crutch measures anyway but it still "
            "cannot become a committable match.)")

    # --dry: measure and print but never touch persisted state. Use when
    # harvesting permuter outputs so a stray measurement can't move best.
    if args.dry:
        res["dry"] = True
        print(json.dumps(res, indent=2))
        return 0 if res["status"] in ("match", "diffs") else 2

    st = load_state(args.func)
    st["tu"] = args.tu
    st["iter"] += 1
    st["last_status"] = res["status"]
    st["last_tags"] = [t["id"] for t in res.get("tags", [])]
    rc = res["real_count"]
    st["history"].append(rc)
    prev_best = st["best"]
    if res["status"] == "compile-fail":
        # don't move the plateau counter on a build break; surface it
        pass
    elif crutch and not args.allow_crutch:
        # tainted: count as a non-improving iteration (stall advances) but
        # NEVER let it set the clean best.
        st["stall"] += 1
    elif prev_best is None or rc < prev_best:
        st["best"] = rc
        st["stall"] = 0
        st["tried_levers"] = []          # progress reopens the lever space
        # Snapshot the WINNING source so a later regression can be undone.
        # (Encodes feedback_revert_to_best_count_not_thrash into the tool:
        #  the lowest-count state already has the right regalloc — never
        #  keep iterating from a worse one.)
        tp = resolve_tu_path(args.tu)
        if tp:
            STATE_DIR.mkdir(parents=True, exist_ok=True)
            best_src_path(args.func).write_text(tp.read_text())
            st["best_src"] = str(tp.relative_to(ROOT))
    else:
        st["stall"] += 1
        # Regression guard: the edit made things WORSE than the best so far.
        if prev_best is not None and rc > prev_best and res["status"] == "diffs":
            res["warning"] = (
                f"REGRESSED to {rc} (best={prev_best}). Don't iterate from a worse "
                f"state — the best-count source already has the right regalloc. "
                f"Restore it first: `tools/match_loop.py revert {args.func}`, then "
                f"apply ONE surgical change.")
    save_state(st)
    res["state"] = {k: st[k] for k in ("iter", "best", "stall", "permuted")}
    print(json.dumps(res, indent=2))
    return 0 if res["status"] in ("match", "diffs") else 2


def cmd_record(args) -> int:
    st = load_state(args.func)
    if args.lever and args.lever not in st["tried_levers"]:
        st["tried_levers"].append(args.lever)
    if args.permuted:
        st["permuted"] = True
    save_state(st)
    print(json.dumps({"tried_levers": st["tried_levers"], "permuted": st["permuted"]}))
    return 0


def cmd_next(args) -> int:
    st = load_state(args.func)
    limit = args.stall_limit
    decision = {"func": args.func, "iter": st["iter"], "best": st["best"],
                "stall": st["stall"], "tried_levers": st["tried_levers"]}
    if st.get("reset_log"):
        decision["reset_log"] = st["reset_log"]
        decision["reset_warning"] = ("⚠ stall was hand-RESET — the counter "
                                     "is not continuous; treat this plateau with "
                                     "suspicion")

    def _authorize(d):
        # Stamp the verdict so park/permute tools can require it be FRESH (run
        # `next` immediately before a terminal action). Kills hand-counting.
        st["auth"] = {"iter": st["iter"], "action": d["action"]}
        save_state(st)
        print(json.dumps(d, indent=2))
        return 0

    if args.override:
        decision["action"] = {"keep-going": "iterate", "permute": "permute",
                              "park": "park"}[args.override]
        decision["reason"] = f"override={args.override}"
        return _authorize(decision)

    if st["best"] == 0:
        decision["action"] = "commit"
        decision["reason"] = "real_count == 0 — verify (ninja) and commit"
        return _authorize(decision)

    if st["iter"] == 0:
        decision["action"] = "diff"
        decision["reason"] = "no diff yet — run `match_loop.py diff` first"
        return _authorize(decision)

    tags = set(st["last_tags"])
    scheduling_tail = bool(tags) and tags <= PERMUTER_SCHEDULING

    if st["permuted"]:
        decision["action"] = "park"
        decision["reason"] = "permuter already attempted without a 0 — park the seed and move on"
    elif st["stall"] >= limit:
        # Genuine plateau. PARK the seed, THEN fire ONE bounded permuter shot on
        # it (decomp-match REFERENCE Step 4): park, then permute. This is an
        # interactive turn action, not an offline-only batch — the permuter runs
        # on the parked seed now and the harvest is read by TRUE real_count.
        decision["action"] = "permute"
        decision["reason"] = (f"plateau: {st['stall']} distinct hand hypotheses, no real_count "
                              f"progress (best={st['best']}). PARK the seed, then fire ONE bounded "
                              f"permuter shot on it (REFERENCE Step 4); harvest by true real_count and "
                              f"adopt any improvement (resolution b only if nothing beats best).")
    else:
        decision["action"] = "iterate"
        untried = [t for t in st["last_tags"] if t not in st["tried_levers"]]
        decision["reason"] = (f"KEEP REASONING (best={st['best']}, stall={st['stall']}/{limit}). "
                              f"A high count is usually ONE root cascade — fix the root.")
        decision["suggested_tags"] = untried or st["last_tags"]
        decision["note"] = ("pick a DISTINCT untried tag; apply its PLAYBOOK lever from the "
                            "decomp-match skill (regalloc-swap/fp-licm/frame-size are HAND-FIXABLE "
                            "here, not permuter food), then `record --lever`. Override with "
                            "`next --override park|permute|keep-going` when your judgment is firmer "
                            "than the counter.")
    return _authorize(decision)


def cmd_revert(args) -> int:
    """Restore the TU source to the best-count snapshot taken by `diff`."""
    st = load_state(args.func)
    snap = best_src_path(args.func)
    if not snap.exists():
        print(json.dumps({"error": "no snapshot yet — run `diff` until it records "
                          "a best", "func": args.func}))
        return 2
    dst_rel = st.get("best_src")
    dst = (ROOT / dst_rel) if dst_rel else resolve_tu_path(st.get("tu"))
    if dst is None:
        print(json.dumps({"error": "cannot resolve TU source path", "func": args.func}))
        return 2
    dst.write_text(snap.read_text())
    print(json.dumps({"reverted": args.func, "to": str(Path(dst).relative_to(ROOT)),
                      "best": st["best"],
                      "note": "TU restored to best-count source; apply ONE surgical change"}))
    return 0


def cmd_reset(args) -> int:
    # reset clears the stall the tool tracks for you — a discipline OVERRIDE,
    # sanctioned only when resuming a parked seed (skill Step 0). Require a
    # reason and leave a permanent audit breadcrumb (state.reset_log) that
    # `next` surfaces forever after, so a mid-loop reset can't be silent.
    st = load_state(args.func)
    prev = {"iter": st.get("iter"), "best": st.get("best"), "stall": st.get("stall")}
    log = st.get("reset_log", []) + [{"at": prev, "reason": args.reason}]
    p = state_path(args.func)
    if p.exists():
        p.unlink()
    fresh = load_state(args.func)
    fresh["reset_log"] = log
    save_state(fresh)
    print(json.dumps({"reset": args.func, "cleared": prev, "reason": args.reason,
                      "note": "reset is for resume Step 0 only; logged in "
                              "state.reset_log and surfaced by `next`"}))
    return 0


def cmd_show(args) -> int:
    print(json.dumps(load_state(args.func), indent=2))
    return 0


# ---------------------------------------------------------------------------
# clone — bank a function that is byte-identical *modulo relocations* to an
# already-matched one, by retargeting the matched C. Two entry points:
#   * post-commit propagation:  match_loop.py clone --from <just-matched>
#   * sweep pre-pass / one-off:  match_loop.py clone <func> | --scope <scope>
# The oracle (tools/sweep_try.sh) is always the final gate — a wrong retarget
# just COMPILE-FAILs or MISSes and is surgically reverted; no false bank.
# ---------------------------------------------------------------------------

def _tu_c(tu_stem: str) -> Path:
    return ROOT / f"{tu_stem}.c"


def _is_stub(tu_stem: str, func: str) -> bool:
    """True iff <func> is still an INCLUDE_ASM stub in its TU (i.e. unmatched)."""
    c = _tu_c(tu_stem)
    if not c.exists():
        return False
    return bool(re.search(r'INCLUDE_ASM\("[^"]+",\s*' + re.escape(func) + r'\)',
                          c.read_text(errors="replace")))


def _definition_of(src: str, name: str) -> str:
    """The brace-matched C of a real top-level DEFINITION of exactly `name`
    (`<type> name(...) {`), or '' if absent. Unlike func_body this rejects
    `extern` decls, calls, and self-references — so a twin the dev renamed in C
    (asm symbol func_XXXX defined as e.g. `fzShowV`) yields '' and is skipped,
    never a garbage retarget. Clone source must be named as its asm symbol."""
    m = re.search(r"(?m)^[A-Za-z_][\w \t\*]*\b" + re.escape(name) + r"\s*\([^;{]*\)\s*\{",
                  src)
    if not m:
        return ""
    b = src.find("{", m.start())
    depth = 0
    for i in range(b, len(src)):
        if src[i] == "{":
            depth += 1
        elif src[i] == "}":
            depth -= 1
            if depth == 0:
                return src[m.start():i + 1]
    return ""


def _matched_body(tu_stem: str, func: str) -> str:
    """The brace-matched C of <func> if it is matched (a real definition under
    its own asm-symbol name, not a stub and not a dev-renamed twin)."""
    c = _tu_c(tu_stem)
    if not c.exists():
        return ""
    return _definition_of(c.read_text(errors="replace"), func)


def _retarget(body: str, name_a: str, name_b: str,
              slots_a: list[tuple[str, str]],
              slots_b: list[tuple[str, str]]) -> tuple[str, dict]:
    """Turn twin A's C into B's candidate: rename A->B and remap each symbol
    slot positionally (equal signatures guarantee aligned slot lists)."""
    out = re.sub(r"\b" + re.escape(name_a) + r"\b", name_b, body)
    renames: dict[str, str] = {}
    for (_ka, sa), (_kb, sb) in zip(slots_a, slots_b):
        if sa != sb and sa != ".L" and sb != ".L":
            renames[sa] = sb
    for sa, sb in renames.items():
        out = re.sub(r"\b" + re.escape(sa) + r"\b", sb, out)
    return out, renames


def _decl_lines(src: str) -> list[str]:
    """Top-level declaration lines (col-0, end in ';', no brace) from a TU — the
    externs/globals a clone candidate may need carried over to its new TU."""
    out = []
    for ln in src.splitlines():
        if not ln or ln[0] in " \t#":
            continue
        s = ln.strip()
        if s.endswith(";") and "{" not in s and "(" != s[:1] and "=" not in s.split("//")[0]:
            out.append(s)
        elif s.startswith("extern ") and s.endswith(";"):
            out.append(s)
    return out


def _harvest_decls(tu_a: str, tu_b: str, symbols: list[str],
                   renames: dict) -> list[str]:
    """For each referenced symbol the candidate needs, lift its declaration from
    twin A's TU, retarget it, and keep it only if B's TU lacks that decl. The
    oracle still gates — a wrong/missing type just COMPILE-FAILs and reverts."""
    src_a = _tu_c(tu_a).read_text(errors="replace") if _tu_c(tu_a).exists() else ""
    src_b = _tu_c(tu_b).read_text(errors="replace") if _tu_c(tu_b).exists() else ""
    a_decls = _decl_lines(src_a)
    inv = {v: k for k, v in renames.items()}
    carried, seen = [], set()
    for q in symbols:
        if q in seen or re.search(r"\b" + re.escape(q) + r"\b\s*[;\(\[]", src_b):
            continue
        pre = inv.get(q, q)
        for d in a_decls:
            if re.search(r"\b" + re.escape(pre) + r"\b", d):
                line = d
                for sa, sb in renames.items():
                    line = re.sub(r"\b" + re.escape(sa) + r"\b", sb, line)
                carried.append(line)
                seen.add(q)
                break
    return carried


def _referenced_symbols(slots_b: list[tuple[str, str]]) -> list[str]:
    """Distinct post-retarget symbols a candidate needs declared (globals +
    real callees; internal `.L` labels excluded)."""
    out, seen = [], set()
    for kind, sym in slots_b:
        if sym == ".L" or sym in seen:
            continue
        seen.add(sym)
        out.append(sym)
    return out


def _find_twin(func: str, s_path: Path):
    """A matched func with an identical reloc-normalized signature to <func>."""
    sig = _asmsig.signature(s_path)
    for cand, cs, ctu in _asmsig.signature_index().get(sig, []):
        if cand == func or ctu is None:
            continue
        if _matched_body(ctu, cand):
            return cand, cs, ctu
    return None


def _try_clone(func: str, s_path: Path, tu_stem: str,
               src: tuple | None, dry: bool, keep: bool = True) -> dict:
    """Attempt to bank <func> from a matched twin (or the explicit `src`).
    dry=True: report the retarget only. keep=False (--check): compile+measure
    through the oracle but ALWAYS revert (validates without mutating the tree)."""
    if not tu_stem or not _is_stub(tu_stem, func):
        return {"func": func, "result": "skip", "reason": "not an unmatched stub"}
    if src is None:
        twin = _find_twin(func, s_path)
        if twin is None:
            return {"func": func, "result": "no-twin"}
        name_a, s_a, tu_a = twin
    else:
        name_a, s_a, tu_a = src
    body = _matched_body(tu_a, name_a)
    if not body:
        return {"func": func, "result": "skip", "reason": f"twin {name_a} has no C body"}
    slots_a = _asmsig.symbol_slots(s_a)
    slots_b = _asmsig.symbol_slots(s_path)
    if len(slots_a) != len(slots_b):
        return {"func": func, "result": "skip",
                "reason": "slot-count mismatch (not a true clone)", "twin": name_a}
    cand, renames = _retarget(body, name_a, func, slots_a, slots_b)
    decls = _harvest_decls(tu_a, tu_stem, _referenced_symbols(slots_b), renames)
    if decls:
        cand = "\n".join(decls) + "\n\n" + cand
    info = {"func": func, "twin": name_a, "tu": tu_stem, "renames": renames,
            "carried_decls": len(decls)}
    if dry:
        info["result"] = "dry"
        info["candidate"] = cand
        return info
    with tempfile.NamedTemporaryFile("w", suffix=".c", delete=False) as f:
        f.write(cand + "\n")
        cf = f.name
    try:
        out = subprocess.run(
            ["bash", str(ROOT / "tools" / "sweep_try.sh"), tu_stem, func, cf],
            capture_output=True, text=True, cwd=str(ROOT)).stdout.strip()
    finally:
        Path(cf).unlink(missing_ok=True)
    verdict = out.splitlines()[-1] if out else ""
    if verdict == "CANDIDATE":
        if keep:
            subprocess.run(["python3", str(ROOT / "tools" / "sweep.py"),
                            "keep", tu_stem, func], cwd=str(ROOT))
            info["result"] = "banked"
        else:
            # --check: undo the still-applied sentinel block, leave tree clean
            subprocess.run(["python3", str(ROOT / "tools" / "sweep.py"),
                            "revert", tu_stem, func], cwd=str(ROOT))
            info["result"] = "would-bank"
    else:
        info["result"] = "miss"
        info["verdict"] = verdict
    return info


def cmd_clone(args) -> int:
    if _asmsig is None:
        print(json.dumps({"error": "tools/_asmsig.py not importable"}))
        return 2
    results = []

    if args.from_func:
        # propagation: bank every unmatched stub identical to a just-matched func
        s_a = _asmsig.find_s(args.from_func)
        if s_a is None:
            print(json.dumps({"error": f"no .s for {args.from_func}"}))
            return 2
        tu_a = _asmsig.tu_stem_of(s_a)
        src = (args.from_func, s_a, tu_a)
        sig = _asmsig.signature(s_a)
        for cand, cs, ctu in _asmsig.signature_index().get(sig, []):
            if cand == args.from_func:
                continue
            results.append(_try_clone(cand, cs, ctu, src, args.dry, keep=not args.check))
    elif args.func:
        s_b = _asmsig.find_s(args.func)
        if s_b is None:
            print(json.dumps({"error": f"no .s for {args.func}"}))
            return 2
        results.append(_try_clone(args.func, s_b, _asmsig.tu_stem_of(s_b),
                                  None, args.dry, keep=not args.check))
    else:
        # scope pre-pass: every sig-group with a matched twin + unmatched stubs
        idx = _asmsig.signature_index()
        for sig, members in idx.items():
            if len(members) < 2:
                continue
            matched = [(n, s, t) for n, s, t in members if t and _matched_body(t, n)]
            if not matched:
                continue
            src = matched[0]
            for n, s, t in members:
                if n == src[0] or not t:
                    continue
                if args.scope and (not t or args.scope not in t):
                    continue
                if not _is_stub(t, n):
                    continue
                results.append(_try_clone(n, s, t, src, args.dry))

    banked = [r for r in results if r.get("result") in ("banked", "would-bank")]
    summary = {"attempted": len(results), "banked": len(banked),
               "results": results if args.verbose else
               [r for r in results
                if r.get("result") in ("banked", "would-bank", "dry", "miss")]}
    print(json.dumps(summary, indent=2))
    return 0


def main() -> int:
    ap = argparse.ArgumentParser(description="shared matching-loop core")
    sub = ap.add_subparsers(dest="cmd", required=True)

    d = sub.add_parser("diff"); d.add_argument("tu"); d.add_argument("func")
    d.add_argument("--dry", action="store_true",
                   help="measure only; never mutate loop state (use for harvest)")
    d.add_argument("--allow-crutch", action="store_true",
                   help="count a crutch-tainted source toward best (discouraged)")
    d.set_defaults(fn=cmd_diff)

    r = sub.add_parser("record"); r.add_argument("func")
    r.add_argument("--lever", default=""); r.add_argument("--permuted", action="store_true")
    r.set_defaults(fn=cmd_record)

    n = sub.add_parser("next"); n.add_argument("func")
    n.add_argument("--stall-limit", type=int, default=DEFAULT_STALL_LIMIT)
    n.add_argument("--override", choices=["keep-going", "permute", "park"])
    n.set_defaults(fn=cmd_next)

    rv = sub.add_parser("revert"); rv.add_argument("func"); rv.set_defaults(fn=cmd_revert)
    rs = sub.add_parser("reset"); rs.add_argument("func")
    rs.add_argument("--reason", required=True,
                    help="why (reset is a discipline override — resume Step 0 only)")
    rs.set_defaults(fn=cmd_reset)
    sh = sub.add_parser("show"); sh.add_argument("func"); sh.set_defaults(fn=cmd_show)

    cl = sub.add_parser("clone", help="bank funcs byte-identical modulo relocs "
                                      "to a matched twin (retarget + oracle-gate)")
    cl.add_argument("func", nargs="?", help="single target to bank")
    cl.add_argument("--from", dest="from_func", metavar="FUNC",
                    help="propagate: bank every unmatched twin of this matched func")
    cl.add_argument("--scope", metavar="STR",
                    help="pre-pass: bank all clones whose TU contains STR")
    cl.add_argument("--dry", action="store_true",
                    help="report twin + retarget renames; do not apply/keep")
    cl.add_argument("--check", action="store_true",
                    help="compile+measure through the oracle but ALWAYS revert "
                         "(validate without mutating the tree)")
    cl.add_argument("--verbose", action="store_true",
                    help="include skip/no-twin rows in the report")
    cl.set_defaults(fn=cmd_clone)

    args = ap.parse_args()
    return args.fn(args)


if __name__ == "__main__":
    sys.exit(main())
