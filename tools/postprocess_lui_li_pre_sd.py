#!/usr/bin/env python3
"""postprocess_lui_li_pre_sd.py — reorder gcc-emit pattern:

    subu  $29, $29, K
    daddu $8, $5, $0       <-- 5th-arg setup
    sd    $31, OFF($29)
    lui   $H, %hi(SYM)
    li    $L, IMM
    sw    $L, %lo(SYM)($H)
    daddu $5, $0, $0
    daddu $6, $0, $0

into

    subu  $29, $29, K
    lui   $H, %hi(SYM)
    li    $L, IMM
    daddu $8, $5, $0
    sd    $31, OFF($29)
    daddu $5, $0, $0
    sw    $L, %lo(SYM)($H)
    daddu $6, $0, $0

Gated by config/lui_li_pre_sd.txt per-function allowlist (one func name per line).
"""

from __future__ import annotations

import re
import sys
from pathlib import Path


def patch(path: Path) -> bool:
    text = path.read_text()
    # Match both gcc-emit forms: `move $8,$5` (pre move→daddu sed) and
    # `daddu $8,$5,$0` (post-sed). Same for the $5,$0,$0 / $6,$0,$0 zeroes.
    MOVE = r"(?:move[ \t]+\$8,\$5|daddu[ \t]+\$8,\$5,\$0)"
    Z5 = r"(?:move[ \t]+\$5,\$0|daddu[ \t]+\$5,\$0,\$0)"
    Z6 = r"(?:move[ \t]+\$6,\$0|daddu[ \t]+\$6,\$0,\$0)"
    SP = r"(?:\$29|\$sp)"
    pat = re.compile(
        rf"([ \t]*subu[ \t]+{SP},{SP},\d+\n)"
        rf"([ \t]*{MOVE}\n)"
        rf"([ \t]*sd[ \t]+\$31,\d+\({SP}\)\n)"
        r"((?:[ \t]*\#APP\s*\n[ \t]*\#NO_APP\s*\n)?)"
        r"([ \t]*lui[ \t]+\$\d+,%hi\([^)]+\)[^\n]*\n)"
        r"([ \t]*li[ \t]+\$\d+,\d+[^\n]*\n)"
        r"([ \t]*sw[ \t]+\$\d+,%lo\([^)]+\)\(\$\d+\)[^\n]*\n)"
        rf"([ \t]*{Z5}\n)"
        rf"([ \t]*{Z6}\n)"
    )

    def repl(m):
        return (
            m.group(1)
            + m.group(4)  # APP/NO_APP block
            + m.group(5)  # lui
            + m.group(6)  # li
            + m.group(2)  # move/daddu $8
            + m.group(3)  # sd
            + m.group(8)  # move/daddu $5
            + m.group(7)  # sw
            + m.group(9)  # move/daddu $6
        )

    new = pat.sub(repl, text, count=1)

    # Sibling shape (func_0024DA80): a zero-store + dead-la-in-$8 prologue where
    # ee-gcc schedules `sd $31` AFTER the store and la-%lo; the original keeps it
    # right after the two lui's. Move `sd $31` up before them. Same family as the
    # primary pattern above (func_0024DD30 wrappers), same prologue-order fixup.
    SP = r"(?:\$29|\$sp)"
    pat2 = re.compile(
        r"([ \t]*lui[ \t]+\$8,%hi\([^)]+\)[^\n]*\n)"
        r"([ \t]*sw[ \t]+\$0,%lo\([^)]+\)\(\$\d+\)[^\n]*\n)"
        r"([ \t]*addiu[ \t]+\$8,\$8,%lo\([^)]+\)[^\n]*\n)"
        rf"([ \t]*sd[ \t]+\$31,\d+\({SP}\)\n)"
    )
    new = pat2.sub(lambda m: m.group(1) + m.group(4) + m.group(2) + m.group(3),
                   new, count=1)

    if new == text:
        return False
    path.write_text(new)
    print(f"  lui_li_pre_sd: reordered {path}")
    return True


def main(argv):
    if len(argv) != 2:
        print("usage: postprocess_lui_li_pre_sd.py <file.s>", file=sys.stderr)
        return 2
    path = Path(argv[1])
    if not path.exists():
        return 0
    patch(path)
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv))
