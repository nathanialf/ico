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
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
STATE_DIR = ROOT / "build" / "match_loop"

DEFAULT_STALL_LIMIT = 30   # distinct hand hypotheses with NO real_count progress
#                            (raised from 12 to match the 20-iter discipline with
#                             headroom — regalloc/branch tails crack late, so the
#                             loop must not bail to "permuter food" early.)

# How the matching loop resolves a TU name to its editable source file —
# mirrors tools/quick_diff.sh's own search order so the best-source snapshot
# (and `revert`) write back to the exact file quick_diff compiles.
_SRC_PATTERNS = ("src/{tu}.c", "tough_nuts/{tu}/{tu}.c",
                 "sound/{tu}.c", "ios/{tu}.c", "isys/{tu}.c")


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
# cracked by hand (sceneManager s5/s6 pin, fightSound s4 hoist). The permuter
# matched ONCE (after 40 hand iters got it to a 1-slot scheduling tail) and
# PLATEAUED on FP regalloc (motionManager2 1630->775, no match). It is also
# token-heavy. So the permuter is NOT an interactive escape hatch: it runs
# OFFLINE on PARKED seeds (tools/auto_permute.sh). The interactive loop reasons
# until a genuine plateau, then PARKS. There is no early-permute.
#
# These scheduling-tail tags are the ONLY shapes a permuter reliably nudges
# (and only once the count is already low). Even then, prefer park-for-batch.
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
        # Genuine plateau. The permuter is OFFLINE + unreliable, so the default
        # is PARK (auto_permute will attempt the seed in the unattended batch).
        # Only suggest an interactive permuter shot for a CLOSE pure-scheduling
        # tail — the one shape it has cracked here.
        if scheduling_tail and st["best"] is not None and st["best"] <= LOW_COUNT_FOR_PERMUTE:
            decision["action"] = "permute"
            decision["reason"] = (f"plateau at best={st['best']} (<= {LOW_COUNT_FOR_PERMUTE}) with a "
                                  f"pure scheduling-tail residual {sorted(tags)} — worth one "
                                  f"backgrounded permuter shot; else park")
        else:
            decision["action"] = "park"
            decision["reason"] = (f"plateau: {st['stall']} distinct hand hypotheses, no real_count "
                                  f"progress (best={st['best']}). Residual is regalloc/structural or "
                                  f"count is high — the permuter would plateau. PARK for the offline "
                                  f"batch (tools/auto_permute.sh); do NOT burn interactive tokens on it")
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

    args = ap.parse_args()
    return args.fn(args)


if __name__ == "__main__":
    sys.exit(main())
