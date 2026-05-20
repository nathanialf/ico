#!/usr/bin/env python3
"""
postprocess_itou_boss.py — collapse three-step address materialization
into the two-step shape the original ICO codegen used.

ee-gcc 2.9 emits:
    lui   $3, %hi(D_006D35F0)
    lui   $4, %hi(D_0055B030)
    lui   $2, %hi(D_0055BD40)
    addiu $3, $3, %lo(D_006D35F0)
    addiu $4, $4, %lo(D_0055B030)
    addiu $2, $2, %lo(D_0055BD40)
    addu  $17, $3, 32
    daddu $18, $4, $0
    daddu $19, $2, $0
    daddu $16, $3, $0

Original ICO codegen emits one fewer insn each for the $tN-only-used-once
constants (s2, s3) by folding `addiu $tN, $tN, lo` + `daddu $sM, $tN, $0`
into a single `addiu $sM, $tN, lo`. The $3 chain stays as-is because the
temp is reused (both as the `daddu $16, $3, $0` source and as the
`addu $17, $3, 32` source — keeping the temp's full value alive).

This pass implements that fold for src/itou_boss.c (func_00198218). Wired
into both tools/quick_diff.sh and tools/compile_c.sh on `BASE=itou_boss`.
"""

from __future__ import annotations

import re
import sys
from pathlib import Path

ADDIU_SELF_LO = re.compile(
    r"^(?P<indent>\s*)addiu\s+\$(?P<dst>\d+|\w+)\s*,\s*\$(?P=dst)\s*,\s*(?P<imm>%lo\([^)]+\))\s*(?:#.*)?$"
)

DADDU_MOVE = re.compile(
    r"^(?P<indent>\s*)(?:daddu\s+\$(?P<dst>\d+|\w+)\s*,\s*\$(?P<src>\d+|\w+)\s*,\s*\$(?:0|zero)"
    r"|move\s+\$(?P<dst2>\d+|\w+)\s*,\s*\$(?P<src2>\d+|\w+))\s*(?:#.*)?$"
)

ADDU_IMM = re.compile(
    r"^(?P<indent>\s*)addu\s+\$(?P<dst>\d+|\w+)\s*,\s*\$(?P<src>\d+|\w+)\s*,\s*(?P<k>\d+|0x[0-9a-fA-F]+)\s*(?:#.*)?$"
)


def line_uses(line: str, reg: str) -> bool:
    return f"${reg}" in line


def collapse(path: Path) -> bool:
    lines = path.read_text().splitlines(keepends=True)
    out: list[str] = []
    consumed: set[int] = set()
    changed = False

    # Pass 1: collapse `addiu $tN, $tN, %lo(SYM)` + later `daddu $sM, $tN, $0`
    # (when $tN is used nowhere else) into `addiu $sM, $tN, %lo(SYM)`.
    for i, line in enumerate(lines):
        if i in consumed:
            continue
        m_a = ADDIU_SELF_LO.match(line)
        if not m_a:
            out.append(line)
            continue
        tmp_reg = m_a.group("dst")
        imm = m_a.group("imm")
        indent = m_a.group("indent")
        j = i + 1
        collapse_target = None
        while j < len(lines):
            l2 = lines[j]
            stripped = l2.strip()
            if not stripped or stripped.startswith("#") or stripped.startswith(".set"):
                j += 1
                continue
            m_d = DADDU_MOVE.match(l2)
            if m_d:
                src = m_d.group("src") or m_d.group("src2")
                dst = m_d.group("dst") or m_d.group("dst2")
                if src == tmp_reg:
                    collapse_target = (j, dst)
                    break
            if line_uses(l2, tmp_reg):
                break
            j += 1
        if collapse_target is None:
            out.append(line)
            continue
        j_idx, dst_reg = collapse_target
        out.append(f"{indent}addiu\t${dst_reg},${tmp_reg},{imm}\n")
        consumed.add(j_idx)
        changed = True

    # Pass 2: swap `addu $sN, $tM, K ; daddu $sP, $tM, $0` (both use same
    # $tM) so the daddu emits first, then the offset add. Also rewrite
    # `addu $sN, $tM, K` (with K immediate) to `addiu $sN, $tM, 0xK` to
    # match the original .s style.
    lines = out
    out2: list[str] = []
    i = 0
    while i < len(lines):
        line = lines[i]
        m = ADDU_IMM.match(line)
        if m and i + 1 < len(lines):
            m2 = DADDU_MOVE.match(lines[i + 1])
            if m2:
                m2_src = m2.group("src") or m2.group("src2")
                m2_dst = m2.group("dst") or m2.group("dst2")
                if m2_src == m.group("src") and m.group("dst") != m2_dst:
                    k_val = int(m.group("k"), 0)
                    out2.append(
                        f"{m2.group('indent')}daddu ${m2_dst},${m2_src},$0\n"
                    )
                    out2.append(
                        f"{m.group('indent')}addiu\t${m.group('dst')},${m.group('src')},0x{k_val:X}\n"
                    )
                    i += 2
                    changed = True
                    continue
        out2.append(line)
        i += 1

    if changed:
        path.write_text("".join(out2))
    return changed


def main(argv: list[str]) -> int:
    if len(argv) != 2:
        print(f"usage: {argv[0]} <file.s>", file=sys.stderr)
        return 2
    p = Path(argv[1])
    collapse(p)
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv))
