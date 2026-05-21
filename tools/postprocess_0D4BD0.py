#!/usr/bin/env python3
"""postprocess_0D4BD0.py — reorder func_001D4BD0 prologue saves.

ee-gcc 2.9 emits the saves in batch:
    sd $18, 32($sp)
    sd $16, 0($sp)
    sd $31, 48($sp)
    move $16, $4
    sd $17, 16($sp)
    lw $6, 0($16)
    beq $6, $0, $Lend
    move $18, $5  (delay)
    move $17, $0

Reorder to interleave to match the original ICO codegen:
    sd $18, 32($sp)
    sd $17, 16($sp)
    move $18, $5
    sd $16, 0($sp)
    sd $31, 48($sp)
    move $16, $4
    lw $6, 0($16)
    beq $6, $0, $Lend
    move $17, $0  (delay)

NOTE: runs BEFORE the canonicalization sed (move→daddu, $sp→$29), so
match against the raw gcc form with `move` and `$sp`.
"""

from __future__ import annotations

import re
import sys
from pathlib import Path


def main():
    if len(sys.argv) != 2:
        sys.exit("usage: postprocess_0D4BD0.py <file.s>")
    path = Path(sys.argv[1])
    text = path.read_text()

    pat = re.compile(
        r"(\.ent\s+func_001D4BD0\b[^\n]*\nfunc_001D4BD0:[^\n]*\n"
        r"(?:[ \t]*\.[a-z][^\n]*\n)*"
        r"[ \t]*subu\s+\$sp,\$sp,64[^\n]*\n)"
        r"([ \t]*sd\s+\$18,32\(\$sp\)[^\n]*\n)"
        r"([ \t]*sd\s+\$16,0\(\$sp\)[^\n]*\n)"
        r"([ \t]*sd\s+\$31,48\(\$sp\)[^\n]*\n)"
        r"([ \t]*move\s+\$16,\$4[^\n]*\n)"
        r"([ \t]*sd\s+\$17,16\(\$sp\)[^\n]*\n)"
        r"([ \t]*lw\s+\$6,0\(\$16\)[^\n]*\n)"
        r"((?:[ \t]*#nop[^\n]*\n)?"
        r"(?:[ \t]*\.set\s+noreorder[^\n]*\n)?"
        r"(?:[ \t]*\.set\s+nomacro[^\n]*\n)?)"
        r"([ \t]*beq\s+\$6,\$0,\$L\d+[^\n]*\n)"
        r"([ \t]*move\s+\$18,\$5[^\n]*\n)"
        r"((?:[ \t]*\.set\s+macro[^\n]*\n)?"
        r"(?:[ \t]*\.set\s+reorder[^\n]*\n)?"
        r"(?:[ \t]*\n)*)"
        r"([ \t]*move\s+\$17,\$0[^\n]*\n)"
    )
    m = pat.search(text)
    if not m:
        return
    (head, sd_s2, sd_s0, sd_ra, mv_s0, sd_s1, lw, set_noreorder,
     beq, dl_move_s2, set_macro, mv_s1) = m.groups()
    # Strip leading whitespace from instrs we're relocating so they're
    # consistent. Use a single tab as canonical indent.
    def reindent(line: str) -> str:
        stripped = line.lstrip()
        return "\t" + stripped if stripped else line
    new_block = (
        head
        + sd_s2
        + sd_s1
        + reindent(dl_move_s2)
        + sd_s0
        + sd_ra
        + mv_s0
        + lw
        + set_noreorder
        + beq
        + reindent(mv_s1)
        + set_macro
    )
    text = text[:m.start()] + new_block + text[m.end():]
    path.write_text(text)


if __name__ == "__main__":
    main()
