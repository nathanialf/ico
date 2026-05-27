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
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
STATE_DIR = ROOT / "build" / "match_loop"

DEFAULT_STALL_LIMIT = 12   # distinct hand hypotheses with NO real_count progress

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
    st = load_state(args.func)
    st["tu"] = args.tu
    st["iter"] += 1
    st["last_status"] = res["status"]
    st["last_tags"] = [t["id"] for t in res.get("tags", [])]
    rc = res["real_count"]
    st["history"].append(rc)
    if res["status"] == "compile-fail":
        # don't move the plateau counter on a build break; surface it
        pass
    elif st["best"] is None or rc < st["best"]:
        st["best"] = rc
        st["stall"] = 0
        st["tried_levers"] = []          # progress reopens the lever space
    else:
        st["stall"] += 1
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

    if args.override:
        decision["action"] = {"keep-going": "iterate", "permute": "permute",
                              "park": "park"}[args.override]
        decision["reason"] = f"override={args.override}"
        print(json.dumps(decision, indent=2)); return 0

    if st["best"] == 0:
        decision["action"] = "commit"
        decision["reason"] = "real_count == 0 — verify (ninja) and commit"
        print(json.dumps(decision, indent=2)); return 0

    if st["iter"] == 0:
        decision["action"] = "diff"
        decision["reason"] = "no diff yet — run `match_loop.py diff` first"
        print(json.dumps(decision, indent=2)); return 0

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
    print(json.dumps(decision, indent=2))
    return 0


def cmd_reset(args) -> int:
    p = state_path(args.func)
    if p.exists():
        p.unlink()
    print(json.dumps({"reset": args.func}))
    return 0


def cmd_show(args) -> int:
    print(json.dumps(load_state(args.func), indent=2))
    return 0


def main() -> int:
    ap = argparse.ArgumentParser(description="shared matching-loop core")
    sub = ap.add_subparsers(dest="cmd", required=True)

    d = sub.add_parser("diff"); d.add_argument("tu"); d.add_argument("func")
    d.set_defaults(fn=cmd_diff)

    r = sub.add_parser("record"); r.add_argument("func")
    r.add_argument("--lever", default=""); r.add_argument("--permuted", action="store_true")
    r.set_defaults(fn=cmd_record)

    n = sub.add_parser("next"); n.add_argument("func")
    n.add_argument("--stall-limit", type=int, default=DEFAULT_STALL_LIMIT)
    n.add_argument("--override", choices=["keep-going", "permute", "park"])
    n.set_defaults(fn=cmd_next)

    rs = sub.add_parser("reset"); rs.add_argument("func"); rs.set_defaults(fn=cmd_reset)
    sh = sub.add_parser("show"); sh.add_argument("func"); sh.set_defaults(fn=cmd_show)

    args = ap.parse_args()
    return args.fn(args)


if __name__ == "__main__":
    sys.exit(main())
