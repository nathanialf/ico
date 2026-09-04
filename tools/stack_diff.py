#!/usr/bin/env python3
"""
tools/stack_diff.py — frame-slot pairing diagnostic for a near-miss function.

Adapted from the LEGO Island decomp toolchain (isledecomp/reccmp,
reccmp/tools/stackcmp.py): extract every stack-relative memory reference
(`ebp±off`/`esp±off` there; `N(sp)` / `N(s8)` / `N(fp)` in our canonical MIPS
stream) from BOTH sides of the diff, build the implied expected→built
slot pairing, and flag when that map is not a bijection. reccmp resolves the
recomp side against PDB debug symbols; we have no debug info, so the report is
offset↔offset with the access mnemonics per slot as the identification aid.

Why a separate tool (not a --stack mode on match_diff): match_diff's JSON is a
driver contract (match_loop/match_drive consume it) — keeping this out of it
keeps that contract untouched, and mirrors how tools/sched_diff.py already
works as a focused post-hoc diagnostic over the same quick_diff streams.

What it localizes: frame-layout / spill-slot residuals. A function whose code
is structurally right but whose frame is laid out differently shows up in
match_diff as dozens of offset diffs; here it collapses to "slot map is a
consistent shift" (fix: the decl/spill that moved) or "slot X on the expected
side pairs with two built slots" (fix: two locals coalesced/split — the
non-bijective case). sched_diff and the greg dumps show this only indirectly.

Usage:
    tools/stack_diff.py <TU> [func]          # human report
    tools/stack_diff.py --json <TU> [func]   # machine-readable
Exit: 0 = clean bijection (or no stack refs), 1 = non-bijective / unpaired,
      2 = compile-fail / usage.
"""
from __future__ import annotations
import argparse
import difflib
import json
import re
import sys
from collections import defaultdict
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import match_diff as md  # reuse the quick_diff plumbing + canonical stream

# `off(sp)` / `off(s8)` / `off(fp)` in a canonical `mnem\top1,op2,...` line.
# Offsets are signed decimal in objdump's rendering. sp-relative and
# frame-pointer-relative references are tracked as separate registers, exactly
# as reccmp keeps esp and ebp apart.
_STACK_REF = re.compile(r"(-?\d+)\((sp|s8|fp)\)")
# address-of-slot: `addiu rX,sp,N` (rX != sp — dest sp is the frame adjust).
# The MIPS analogue of reccmp catching `lea eax,[esp+0x10]`.
_STACK_LEA = re.compile(r"^(?:addiu|daddiu)\t(?!sp,)\w+,(sp|s8|fp),(-?\d+)$")
_FRAME_ADJ = re.compile(r"^(?:addiu|daddiu)\tsp,sp,(-\d+)$")


def stack_ref(line: str):
    """(register, offset, mnemonic) of the line's stack reference, or None."""
    m = _STACK_REF.search(line)
    if m:
        return (m.group(2), int(m.group(1)), md._mnem(line))
    m = _STACK_LEA.match(line)
    if m:
        return (m.group(1), int(m.group(2)), md._mnem(line))
    return None


def frame_size(lines: list[str]):
    """Frame size from the prologue `addiu sp,sp,-N`, or None (leaf)."""
    for l in lines[:8]:
        m = _FRAME_ADJ.match(l)
        if m:
            return -int(m.group(1))
    return None


def collect_pairs(exp: list[str], blt: list[str]):
    """Walk the aligned diff and collect (expected_slot, built_slot) pairs.

    * equal lines: any stack ref pairs with itself.
    * replace blocks of EQUAL length: pair line-by-line (reccmp's orig/recomp
      zip); a line pair where exactly one side has a stack ref is a structural
      mismatch — the pairing for that block cannot be trusted.
    * insert/delete or unequal replace blocks: structural mismatch, skipped.

    Returns (pairs, mnems, structural_blocks) where pairs is a set of
    ((reg, exp_off), (reg, blt_off)), mnems maps each side's slot to the
    mnemonics seen touching it, and structural_blocks counts skipped blocks.
    """
    sm = difflib.SequenceMatcher(None, exp, blt, autojunk=False)
    pairs = set()
    mnems = {"expected": defaultdict(set), "built": defaultdict(set)}
    structural = 0
    for op, i1, i2, j1, j2 in sm.get_opcodes():
        if op == "equal":
            for k in range(i2 - i1):
                r = stack_ref(exp[i1 + k])
                if r:
                    reg, off, mn = r
                    pairs.add(((reg, off), (reg, off)))
                    mnems["expected"][(reg, off)].add(mn)
                    mnems["built"][(reg, off)].add(mn)
            continue
        if op != "replace" or (i2 - i1) != (j2 - j1):
            # inserted/removed instructions: no positional correspondence
            if any(stack_ref(l) for l in exp[i1:i2]) or \
               any(stack_ref(l) for l in blt[j1:j2]):
                structural += 1
            continue
        for le, lb in zip(exp[i1:i2], blt[j1:j2]):
            re_, rb_ = stack_ref(le), stack_ref(lb)
            if re_ and rb_:
                ereg, eoff, emn = re_
                breg, boff, bmn = rb_
                pairs.add(((ereg, eoff), (breg, boff)))
                mnems["expected"][(ereg, eoff)].add(emn)
                mnems["built"][(breg, boff)].add(bmn)
            elif re_ or rb_:
                structural += 1     # one-sided stack ref in a paired line
    return pairs, mnems, structural


def slot_map(pairs):
    """Forward and reverse multimaps of the slot pairing."""
    fwd, rev = defaultdict(set), defaultdict(set)
    for e, b in pairs:
        fwd[e].add(b)
        rev[b].add(e)
    return fwd, rev


def analyze_streams(exp: list[str], blt: list[str]) -> dict:
    pairs, mnems, structural = collect_pairs(exp, blt)
    fwd, rev = slot_map(pairs)
    nb_expected = sorted(k for k, v in fwd.items() if len(v) > 1)
    nb_built = sorted(k for k, v in rev.items() if len(v) > 1)
    non_bijective = sorted(set(nb_expected) | set(nb_built))
    # slots referenced only inside structural blocks never enter the pairing;
    # report the offsets each side touches that got no pairing at all.
    def all_slots(lines):
        out = set()
        for l in lines:
            r = stack_ref(l)
            if r:
                out.add((r[0], r[1]))
        return out
    exp_unpaired = sorted(all_slots(exp) - set(fwd.keys()))
    blt_unpaired = sorted(all_slots(blt) - set(rev.keys()))
    bijective = (not non_bijective) and not exp_unpaired and not blt_unpaired
    return {
        "frame_expected": frame_size(exp),
        "frame_built": frame_size(blt),
        "pairs": sorted(pairs),
        "mnems": mnems,
        "bijective": bijective,
        "non_bijective_slots": non_bijective,
        "non_bijective_expected": nb_expected,
        "non_bijective_built": nb_built,
        "expected_unpaired": exp_unpaired,
        "built_unpaired": blt_unpaired,
        "structural_blocks": structural,
    }


def _fmt_slot(slot) -> str:
    reg, off = slot
    return f"{off}({reg})"


def render(r: dict, out=sys.stdout):
    fe, fb = r["frame_expected"], r["frame_built"]
    if fe != fb:
        print(f"FRAME SIZE differs: expected {fe} vs built {fb}", file=out)
    else:
        print(f"frame size: {fe}", file=out)
    fwd, _ = slot_map({(tuple(e), tuple(b)) for e, b in r["pairs"]})
    print("\nexpected slot -> built slot   (mnemonics seen)", file=out)
    for e in sorted(fwd):
        bs = sorted(fwd[e])
        mn = ",".join(sorted(r["mnems"]["expected"].get(tuple(e), set())))
        exact = len(bs) == 1 and bs[0] == e
        mark = " " if exact else ("!" if len(bs) > 1 else "~")
        print(f"  {mark} {_fmt_slot(e):>10} -> "
              f"{', '.join(_fmt_slot(b) for b in bs):<22} ({mn})", file=out)
    if r["expected_unpaired"]:
        print("\nexpected-only slots (structural region, no pairing):", file=out)
        for s in r["expected_unpaired"]:
            print(f"    {_fmt_slot(s)}", file=out)
    if r["built_unpaired"]:
        print("\nbuilt-only slots (structural region, no pairing):", file=out)
        for s in r["built_unpaired"]:
            print(f"    {_fmt_slot(s)}", file=out)
    if r["non_bijective_slots"]:
        print("\nNON-BIJECTIVE: these slots pair with multiple slots on the "
              "other side —\ntwo locals coalesced/split, or the frame layout "
              "genuinely differs:", file=out)
        for s in r["non_bijective_slots"]:
            print(f"    {_fmt_slot(s)}", file=out)
    if r["structural_blocks"]:
        print(f"\nnote: {r['structural_blocks']} diff block(s) with stack refs "
              "had no positional correspondence (insert/delete); the map may "
              "be incomplete — fix the structural diff first.", file=out)
    print("\nverdict: " + ("slot map is a clean bijection"
                           if r["bijective"] else
                           "slot map is NOT a clean bijection"), file=out)


def analyze(tu: str, func: str | None) -> dict | None:
    out = md.run_quick_diff(tu, func)
    exp, blt = md.parse_blocks(out)
    if exp is None or blt is None:
        print(out.strip().splitlines()[-1] if out.strip() else "no output",
              file=sys.stderr)
        return None
    exp, blt = md.strip_trailing_align_nops(exp, blt)
    # NO reloc normalization here: stack offsets are literal text and the
    # lui/addiu folding would only obscure lines; jump-target normalization is
    # irrelevant to `N(sp)` extraction. Raw canonical stream is what we parse.
    return analyze_streams(exp, blt)


def main() -> int:
    ap = argparse.ArgumentParser(description="frame-slot pairing diagnostic "
                                             "(reccmp stackcmp port)")
    ap.add_argument("tu")
    ap.add_argument("func", nargs="?", default=None)
    ap.add_argument("--json", action="store_true")
    args = ap.parse_args()
    r = analyze(args.tu, args.func)
    if r is None:
        return 2
    if args.json:
        r2 = dict(r)
        r2["pairs"] = [[list(e), list(b)] for e, b in r["pairs"]]
        r2["mnems"] = {side: {f"{off}({reg})": sorted(v)
                              for (reg, off), v in m.items()}
                       for side, m in r["mnems"].items()}
        r2["non_bijective_slots"] = [list(s) for s in r["non_bijective_slots"]]
        r2["non_bijective_expected"] = [list(s) for s in r["non_bijective_expected"]]
        r2["non_bijective_built"] = [list(s) for s in r["non_bijective_built"]]
        r2["expected_unpaired"] = [list(s) for s in r["expected_unpaired"]]
        r2["built_unpaired"] = [list(s) for s in r["built_unpaired"]]
        print(json.dumps(r2, indent=2))
    else:
        render(r)
    return 0 if r["bijective"] else 1


if __name__ == "__main__":
    sys.exit(main())
