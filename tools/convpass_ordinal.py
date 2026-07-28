#!/usr/bin/env python3
"""convpass wave-2 helper (worker 3): audit `provisional-ordinal` names.

Wave 1 assigned the unnamed retail functions of a TU by *ordinal* alignment
against the aug6 twin (named anchors, then function size).  Wherever retail
inserted, deleted or moved a function inside a TU, that alignment slips and
every later name in the TU is off by one — which then shows up as a batch of
`divergent` port candidates whose aug6/retail instruction counts do not
match.

This re-derives the mapping from the *code* instead of the ordinal: it
normalizes both instruction streams (blanking every reloc-bearing immediate:
j/jal targets, lui immediates, and the imm16 of loads/stores/addiu) and
scores each retail function against every matched aug6 function in the twin
TU — plus, with --extra, any other aug6 stems worth considering, since
retail also moved functions between TUs.

    tools/convpass_ordinal.py src/st18a.c script/src/st18a [--extra script/src/st19a]

Prints, per retail function, the current symbol name and the best-scoring
aug6 bodies.  A score near 1.0 on a name other than the current one is a
mis-assignment; act on it only when the reloc evidence agrees.
"""
import argparse
import difflib
import os
import re
import struct
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
AUG6 = os.environ.get("PORT_AUG6_ROOT", "/primary/dev/ico")
# opcodes whose imm16 is a reloc slot (%lo / gp_rel) or otherwise link-dependent
IMM_OPS = {9, 0x20, 0x21, 0x23, 0x24, 0x25, 0x28, 0x29, 0x2B,
           0x31, 0x35, 0x37, 0x39, 0x3D, 0x3F}


def norm(w):
    op = w >> 26
    if op in (2, 3):
        return "j"                                  # j / jal target
    if op == 0x0F:
        return "lui%d" % ((w >> 16) & 0x1F)          # %hi
    if op in IMM_OPS:
        return "i%d" % (w >> 16)                     # drop imm16
    return "%08x" % w


def aug6_stream(path):
    out = []
    for ln in open(path):
        m = re.search(r"/\* [0-9A-F]+ [0-9A-F]+ ([0-9A-F]{8}) \*/", ln)
        if m:
            out.append(norm(struct.unpack("<I", bytes.fromhex(m.group(1)))[0]))
    return out


def retail_syms(tu):
    """(name, vma, size_in_insns) for every type:func symbol tagged with `tu`."""
    rows = []
    pat = re.compile(r"^(\S+)\s*=\s*(0x[0-9A-Fa-f]+);.*type:func")
    allrows = []
    for ln in open(os.path.join(ROOT, "config/symbol_addrs.us.txt")):
        m = pat.match(ln.strip())
        if m:
            allrows.append((int(m.group(2), 16), m.group(1), ln))
    allrows.sort()
    for i, (vma, name, ln) in enumerate(allrows):
        if ("// " + tu) in ln or (" " + tu) in ln:
            nxt = allrows[i + 1][0] if i + 1 < len(allrows) else vma + 4
            rows.append((name, vma, (nxt - vma) // 4))
    return rows


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("tu")
    ap.add_argument("aug6_stem")
    ap.add_argument("--extra", nargs="*", default=[])
    ap.add_argument("--top", type=int, default=3)
    a = ap.parse_args()

    base = open(os.path.join(ROOT, "baserom/baseelf.rom"), "rb").read()
    pool = []
    for stem in [a.aug6_stem] + a.extra:
        d = os.path.join(AUG6, "asm/aug6/matchings", stem)
        if not os.path.isdir(d):
            print("no such aug6 stem: %s" % d, file=sys.stderr)
            continue
        for f in sorted(os.listdir(d)):
            s = aug6_stream(os.path.join(d, f))
            if s:
                pool.append((os.path.basename(stem) + "/" + f[:-2], s))

    for name, vma, n in retail_syms(a.tu):
        off = vma - 0x100000
        r = [norm(struct.unpack_from("<I", base, off + 4 * i)[0]) for i in range(n)]
        sc = sorted(((difflib.SequenceMatcher(None, s, r, autojunk=False).ratio(), nm, len(s))
                     for nm, s in pool), reverse=True)
        head = "%-32s 0x%08X %3d" % (name, vma, n)
        print("%s  %s" % (head, "  ".join("%s=%.2f(%d)" % (x[1], x[0], x[2])
                                          for x in sc[:a.top])))
    return 0


if __name__ == "__main__":
    sys.exit(main())
