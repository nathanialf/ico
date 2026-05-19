#!/usr/bin/env python3
"""
postprocess_0AE420.py — specific rewrite for func_001AE420.

gcc emits (after early_body_swap that would swap sd ra and other ops):
    sd $17, 16($sp)
    sd $16, 0($sp)
    daddu $17, $6, $0    (s1 = a2)
    sd $31, 32($sp)
    daddu $16, $5, $0    (s0 = a1)
    jal func_001ADED8
    daddu $5, $7, $0
    daddu $3, $2, $0     (v1 = v0)
    sw $17, 52($3)
    sw $16, 48($3)
    ld $31, 32($sp)
    ld $17, 16($sp)
    ld $16, 0($sp)
    j $31
    addu $sp, $sp, 48

Rewrite to:
    sd $16, 0($sp)
    daddu $16, $5, $0    (s0 = a1)
    sd $17, 16($sp)
    daddu $17, $6, $0    (s1 = a2)
    sd $31, 32($sp)
    jal func_001ADED8
    daddu $5, $7, $0
    daddu $3, $2, $0     (v1 = v0)
    ld $31, 32($sp)
    sw $16, 48($3)
    sw $17, 52($3)
    ld $17, 16($sp)
    ld $16, 0($sp)
    j $31
    addu $sp, $sp, 48

Only triggers when the file is listed.
"""

from __future__ import annotations

import re
import sys
from pathlib import Path


def patch(path: Path) -> bool:
    text = path.read_text()

    # Prologue rewrite: swap sd $17/$16 and corresponding daddu/move
    prologue_pat = re.compile(
        r"([ \t]*sd[ \t]+\$17,[^\n]*\n)"
        r"([ \t]*sd[ \t]+\$16,[^\n]*\n)"
        r"([ \t]*(?:daddu|move)[ \t]+\$17,[^\n]*\n)"
        r"([ \t]*sd[ \t]+\$31,[^\n]*\n)"
        r"([ \t]*(?:daddu|move)[ \t]+\$16,[^\n]*\n)"
    )
    new = prologue_pat.sub(
        lambda m: m.group(2) + m.group(5) + m.group(1) + m.group(3) + m.group(4),
        text,
        count=1,
    )

    # Body rewrite: move ld $31 before sw $16/$17; swap sw $17/$16 to sw $16/$17
    body_pat = re.compile(
        r"([ \t]*sw[ \t]+\$17,[^\n]*\n)"
        r"([ \t]*sw[ \t]+\$16,[^\n]*\n)"
        r"([ \t]*ld[ \t]+\$31,[^\n]*\n)"
    )
    new2 = body_pat.sub(
        lambda m: m.group(3) + m.group(2) + m.group(1),
        new,
        count=1,
    )

    if new2 == text:
        return False
    path.write_text(new2)
    return True


def main(argv: list[str]) -> int:
    if len(argv) != 2:
        print("usage: postprocess_0AE420.py <path-to.s>", file=sys.stderr)
        return 2
    path = Path(argv[1])
    if not path.exists():
        return 1
    if patch(path):
        print(f"  0AE420: patched {path}")
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv))
