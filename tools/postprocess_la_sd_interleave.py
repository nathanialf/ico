#!/usr/bin/env python3
"""
postprocess_la_sd_interleave.py — interleave `sd $31` between the `lui`
and `addiu` halves of an la-macro emission.

ee-gcc 2.9 emits a la-style address load as a back-to-back lui+addiu pair
followed by the prologue `sd $31, OFFSET($sp)` save:

    subu  $sp, $sp, N
    lui   $rX, %hi(SYM)
    addiu $rX, $rX, %lo(SYM)
    sd    $31, OFFSET($sp)

Some original ICO functions (e.g., func_0024DA50, func_0024DA20) instead
have the prologue ra-save scheduled BETWEEN the lui and addiu of the
la macro:

    addiu $sp, $sp, -N
    lui   $rX, %hi(SYM)
    sd    $31, OFFSET($sp)
    addiu $rX, $rX, %lo(SYM)

Idempotent: only runs when the input contains the unswapped sequence,
and only swaps the first occurrence (which is what gcc emits — these
sites are leaf-prologue 5-arg-via-$tN wrappers).
"""

from __future__ import annotations

import re
import sys
from pathlib import Path

# Match the gcc-emitted sequence:
#   <ws>lui   $rX, %hi(SYM)
#   <ws>addiu $rX, $rX, %lo(SYM)
#   <ws>sd    $31, OFFSET($sp)
#
# Captures: ws, lui-line body, addiu-line body, sd-line body.
PATTERN = re.compile(
    r"([ \t]*)(lui[ \t]+\$\d+,\s*%hi\(\w+\))[ \t]*(?:#[^\n]*)?\n"
    r"[ \t]*(addiu[ \t]+\$\d+,\s*\$\d+,\s*%lo\(\w+\))[ \t]*(?:#[^\n]*)?\n"
    r"[ \t]*(sd[ \t]+\$31,[^\n]+)\n",
    re.MULTILINE,
)


def patch(path: Path) -> bool:
    text = path.read_text()
    new = PATTERN.sub(
        lambda m: (
            f"{m.group(1)}{m.group(2)}\n"
            f"{m.group(1)}{m.group(4)}\n"
            f"{m.group(1)}{m.group(3)}\n"
        ),
        text,
        count=1,
    )
    if new == text:
        return False
    path.write_text(new)
    return True


def main(argv: list[str]) -> int:
    if len(argv) != 2:
        print("usage: postprocess_la_sd_interleave.py <path-to.s>", file=sys.stderr)
        return 2
    path = Path(argv[1])
    if not path.exists():
        print(f"file not found: {path}", file=sys.stderr)
        return 1
    patched = patch(path)
    if patched:
        print(f"  la-sd-interleave: patched {path}")
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv))
