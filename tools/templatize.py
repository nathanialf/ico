#!/usr/bin/env python3
"""tools/templatize.py — find FAMILIES: groups of functions that share a shape
modulo relocations AND numeric immediates (offsets/shifts/pool constants), so
cracking ONE member templatizes the rest.

This is the *targeting* half of the clone/propagate idea (the banking half is
`tools/match_loop.py clone`, which handles the exact-signature subset — same
shape, same immediates — by retargeting symbols and oracle-gating each bank).
templatize widens the lens to immediate-different near-siblings, which a single
symbol-retarget will NOT byte-match, but which become a force-multiplier once a
representative is cracked by hand: crack one, then `clone --from` banks the exact
twins and the remaining near-siblings each get the cracked shape applied.

Faithful to sm64ds-decomp's recurring.py / cluster_shapes.py: pure analysis, no
mutation. It tells you WHERE to spend a crack for maximum propagation.

Usage:
  tools/templatize.py --recurring [--scope STR] [--min N] [--top K]
        Rank families that have >=1 matched member and >=N unmatched siblings
        (default N=2), by propagation value (unmatched x insns). These are the
        highest-leverage crack targets.
  tools/templatize.py --family <func>
        Show the imm-masked family of one function: every member, matched or not,
        and whether `clone --from` can bank it directly (exact signature) or it
        needs the cracked shape applied (immediate-different).
"""
from __future__ import annotations

import argparse
import sys
from collections import defaultdict
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import _asmsig
import match_loop   # reuse _matched_body / _is_stub (authoritative matched-status)


def _classify(name: str, tu: str | None):
    """matched | stub | other (library / pure-asm TU with no .c)."""
    if not tu:
        return "other"
    if match_loop._matched_body(tu, name):
        return "matched"
    if match_loop._is_stub(tu, name):
        return "stub"
    return "other"


def _families(scope: str | None):
    """Yield (members, exact_subgroups) for each imm-masked family.

    members: [(name, s_path, tu, status, n_insns)]
    exact_subgroups: {exact_signature: [names]} — the clone-bankable clusters
    within the immediate-masked family.
    """
    imm_idx = _asmsig.signature_index(imm_masked=True)
    for sig, mem in imm_idx.items():
        rows = []
        for name, s, tu in mem:
            if scope and (not tu or scope not in tu):
                continue
            rows.append((name, s, tu, _classify(name, tu),
                         len(_asmsig.parse_s(s))))
        if len(rows) < 2:
            continue
        exact = defaultdict(list)
        for name, s, tu, status, n in rows:
            exact[_asmsig.signature(s)].append(name)
        yield rows, exact


def cmd_recurring(args) -> int:
    fams = []
    for rows, exact in _families(args.scope):
        matched = [r for r in rows if r[3] == "matched"]
        stubs = [r for r in rows if r[3] == "stub"]
        if not matched or len(stubs) < args.min:
            continue
        n = rows[0][4]
        fams.append({
            "rep": matched[0][0], "rep_tu": matched[0][2], "insns": n,
            "matched": len(matched), "unmatched": len(stubs),
            "value": len(stubs) * n,
            "exact_bankable": sum(len(v) for k, v in exact.items()
                                  if any(m[0] in v for m in matched)) - len(matched),
            "stubs": [s[0] for s in stubs][:8],
        })
    fams.sort(key=lambda f: -f["value"])
    print(f"{'value':>6}  {'n':>4}  {'+stub':>5} {'+exact':>6}  representative (matched)  -> sample unmatched siblings")
    for f in fams[:args.top]:
        print(f"{f['value']:>6}  {f['insns']:>4}  {f['unmatched']:>5} "
              f"{f['exact_bankable']:>6}  {f['rep']:<26} -> {', '.join(f['stubs'])}")
    print(f"\n{len(fams)} families with a matched rep + >={args.min} unmatched siblings.")
    print("crack the representative (decomp-match), then `match_loop.py clone "
          "--from <rep>` to bank exact twins; apply the cracked shape to the rest.")
    return 0


def cmd_family(args) -> int:
    func = args.family
    s = _asmsig.find_s(func)
    if s is None:
        print(f"no .s for {func}", file=sys.stderr)
        return 1
    target_imm = tuple(_asmsig.imm_masked_signature(s))
    exact_sig = _asmsig.signature(s)
    idx = _asmsig.signature_index(imm_masked=True)
    members = idx.get(target_imm, [])
    if len(members) < 2:
        print(f"{func}: no family (unique imm-masked shape).")
        return 0
    print(f"{func}: family of {len(members)} (n={len(_asmsig.parse_s(s))} insns)")
    for name, ms, tu in sorted(members):
        status = _classify(name, tu)
        exact = "exact" if _asmsig.signature(ms) == exact_sig else "imm-diff"
        bankable = " (clone --from bankable)" if exact == "exact" and status == "stub" else ""
        print(f"  {name:<28} {status:<8} {exact}{bankable}  [{tu}]")
    return 0


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--recurring", action="store_true",
                    help="rank high-leverage families (matched rep + unmatched siblings)")
    ap.add_argument("--family", metavar="FUNC", help="show one function's family")
    ap.add_argument("--scope", help="restrict to TUs containing this substring")
    ap.add_argument("--min", type=int, default=2, help="min unmatched siblings (default 2)")
    ap.add_argument("--top", type=int, default=25, help="rows to show (default 25)")
    args = ap.parse_args()
    if args.family:
        return cmd_family(args)
    if args.recurring:
        return cmd_recurring(args)
    ap.print_help()
    return 2


if __name__ == "__main__":
    sys.exit(main())
