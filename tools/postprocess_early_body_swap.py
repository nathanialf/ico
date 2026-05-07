#!/usr/bin/env python3
"""
postprocess_early_body_swap.py — swap the first body instruction with
the prologue's `sd $31, OFF($sp)` save.

ee-gcc 2.9 emits its prologue (sp-adjust + ra-save) then the function
body.  Some original ICO functions have a single body instruction
SCHEDULED BETWEEN the sp-adjust and the ra-save, e.g.

    addiu  $sp, $sp, -0x10
    daddu  $3, $4, $0          ; body op (copy a0 to v1)
    sd     $31, 0($sp)
    ...

ee-gcc 2.9 always emits sd $31 immediately after the sp-adjust.  This
postprocess swaps the `sd $31` with the *immediately-following*
instruction emitted by an `#APP` inline-asm block, when the inline-asm
block contains a single instruction.

Idempotent: only applies when the input matches the unswapped pattern.
"""

from __future__ import annotations

import re
import sys
from pathlib import Path

# Match the gcc-emitted prologue + opening of an #APP block:
#   <ws>sd  $31, OFFSET($sp)
#   <ws>#APP
#   <ws>FIRST_INSTR
PATTERN = re.compile(
    r"([ \t]*)(sd[ \t]+\$31,\s*\d+\(\$sp\))[ \t]*\n"
    r"([ \t]*\#APP[^\n]*\n)"
    r"([ \t]*)([^\n#]+)\n",
    re.MULTILINE,
)


def patch(path: Path) -> bool:
    text = path.read_text()
    new = PATTERN.sub(
        lambda m: (
            f"{m.group(3)}"             # #APP marker first
            f"{m.group(4)}{m.group(5)}\n"  # first body instr
            f"{m.group(1)}{m.group(2)}\n"  # then sd $31
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
        print("usage: postprocess_early_body_swap.py <path-to.s>", file=sys.stderr)
        return 2
    path = Path(argv[1])
    if not path.exists():
        print(f"file not found: {path}", file=sys.stderr)
        return 1
    patched = patch(path)
    if patched:
        print(f"  early-body-swap: patched {path}")
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv))
