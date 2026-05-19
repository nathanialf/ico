#!/usr/bin/env python3
"""
postprocess_move_sw_v0_before_lds.py — for functions that store the
return value (in $v0) to a gp_rel symbol in the epilogue, gcc emits:

    ld   $31, OFF1($sp)
    ld   $16, OFF2($sp)
    sw   $0, SYM1
    sw   $V, SYM2          (<-- the return-value store)
    sw   $0, SYM3

while the original codegen interleaves the v0-store between the
epilogue restores:

    ld   $31, OFF1($sp)
    sw   $V, SYM2
    ld   $16, OFF2($sp)
    sw   $0, SYM1
    sw   $0, SYM3

This pass moves the `sw $V, SYM2` line earlier — between `ld $31` and
`ld $16` — when V is a non-zero register (the return value).

Per-file allowlist in config/move_sw_v0_before_lds.txt.
"""

from __future__ import annotations

import re
import sys
from pathlib import Path


PATTERN = re.compile(
    r"(?P<ld_ra>[ \t]*ld[ \t]+\$31,[^\n]*\n)"
    r"(?P<ld_sN>[ \t]*ld[ \t]+\$1[6-9],[^\n]*\n)"
    r"(?P<sw_zero>(?:[ \t]*sw[ \t]+\$0,[^\n]*\n)*?)"
    r"(?P<sw_v0>[ \t]*sw[ \t]+\$(?P<reg>[2-9]|1[0-5]),[^\n]*\n)"
    r"(?P<sw_rest>(?:[ \t]*sw[ \t]+\$0,[^\n]*\n)*)",
    re.MULTILINE,
)


def patch(path: Path) -> bool:
    text = path.read_text()

    def repl(m):
        return (
            m["ld_ra"]
            + m["sw_v0"]
            + m["ld_sN"]
            + m["sw_zero"]
            + m["sw_rest"]
        )

    new = PATTERN.sub(repl, text, count=1)
    if new == text:
        return False
    path.write_text(new)
    return True


def main(argv: list[str]) -> int:
    if len(argv) != 2:
        print("usage: postprocess_move_sw_v0_before_lds.py <path-to.s>", file=sys.stderr)
        return 2
    path = Path(argv[1])
    if not path.exists():
        return 1
    if patch(path):
        print(f"  move-sw-v0-before-lds: patched {path}")
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv))
