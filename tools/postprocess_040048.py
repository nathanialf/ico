#!/usr/bin/env python3
"""postprocess_040048.py — reorder func_00140048 prologue saves.

ee-gcc 2.9 emits:
    sd $17,16($sp)
    lw $17,D_006321DC
    sd $20,64($sp)
    sd $16,0($sp)
    sd $31,80($sp)
    addu $16,$17,84
    sd $19,48($sp)
    sd $18,32($sp)
    lw $6,4($16)
    blez $6, $Lend
    move $20,$4              ; delay slot (s4 = a0)
    move $18,$0              ; i = 0

Original ICO codegen interleaves the move-s4 between sd-s2 and sd-s0,
and places i=0 in the blez delay slot:
    sd $17,16($sp)
    lw $17,D_006321DC
    sd $20,64($sp)
    sd $18,32($sp)
    move $20,$4
    sd $16,0($sp)
    sd $31,80($sp)
    addu $16,$17,84
    sd $19,48($sp)
    lw $6,4($16)
    blez $6, $Lend
    move $18,$0              ; delay slot
"""

from __future__ import annotations

import re
import sys
from pathlib import Path


def main():
    if len(sys.argv) != 2:
        sys.exit("usage: postprocess_040048.py <file.s>")
    path = Path(sys.argv[1])
    text = path.read_text()

    pat = re.compile(
        r"(\.ent\s+func_00140048\b[^\n]*\nfunc_00140048:[^\n]*\n"
        r"(?:[ \t]*\.[a-z][^\n]*\n)*"
        r"[ \t]*subu\s+\$sp,\$sp,96[^\n]*\n)"
        r"([ \t]*sd\s+\$17,16\(\$sp\)[^\n]*\n)"
        r"([ \t]*lw\s+\$17,D_006321DC[^\n]*\n)"
        r"([ \t]*sd\s+\$20,64\(\$sp\)[^\n]*\n)"
        r"([ \t]*sd\s+\$16,0\(\$sp\)[^\n]*\n)"
        r"([ \t]*sd\s+\$31,80\(\$sp\)[^\n]*\n)"
        r"([ \t]*addu\s+\$16,\$17,84[^\n]*\n)"
        r"([ \t]*sd\s+\$19,48\(\$sp\)[^\n]*\n)"
        r"([ \t]*sd\s+\$18,32\(\$sp\)[^\n]*\n)"
        r"([ \t]*lw\s+\$6,4\(\$16\)[^\n]*\n)"
        r"((?:[ \t]*#nop[^\n]*\n)?"
        r"(?:[ \t]*\.set\s+noreorder[^\n]*\n)?"
        r"(?:[ \t]*\.set\s+nomacro[^\n]*\n)?)"
        r"([ \t]*blez\s+\$6,\$L\d+[^\n]*\n)"
        r"([ \t]*move\s+\$20,\$4[^\n]*\n)"
        r"((?:[ \t]*\.set\s+macro[^\n]*\n)?"
        r"(?:[ \t]*\.set\s+reorder[^\n]*\n)?"
        r"(?:[ \t]*\n)*)"
        r"([ \t]*move\s+\$18,\$0[^\n]*\n)"
    )
    m = pat.search(text)
    if not m:
        return
    (head, sd_s1, lw_s1, sd_s4, sd_s0, sd_ra, addu_s0, sd_s3, sd_s2,
     lw_a2, set_noreorder, blez, mv_s4, set_macro, mv_s2_zero) = m.groups()

    def reindent(line: str) -> str:
        stripped = line.lstrip()
        return "\t" + stripped if stripped else line

    new_block = (
        head
        + sd_s1
        + lw_s1
        + sd_s4
        + sd_s2          # was after, promote
        + reindent(mv_s4)  # was delay slot, promote
        + sd_s0
        + sd_ra
        + addu_s0
        + sd_s3
        + lw_a2
        + set_noreorder
        + blez
        + reindent(mv_s2_zero)  # i=0 to delay slot
        + set_macro
    )
    text = text[:m.start()] + new_block + text[m.end():]
    path.write_text(text)


if __name__ == "__main__":
    main()
