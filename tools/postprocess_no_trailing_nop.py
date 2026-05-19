#!/usr/bin/env python3
"""
postprocess_no_trailing_nop.py — wrap the final `j $31` (jr ra) at
function end with `.set noreorder` so gas doesn't auto-fill the delay
slot with a nop.

Pattern: ee-gcc 2.9 emits the end-of-function return as
    $LN:
        j   $31
    .end FUNC

In default `.set reorder` mode, gas appends a nop in the delay slot,
growing the function by 4 bytes. The original ICO codegen leaves the
delay slot empty (filled at link time by the next function's first
instruction). Wrapping with noreorder suppresses the gas auto-fill.

Idempotent: only patches the LAST `j $31` immediately before `.end`,
and only if it's not already inside a `.set noreorder` block.
"""

from __future__ import annotations

import re
import sys
from pathlib import Path

# Match a label, then `j $31`, then `.end`, with no intervening insns.
PATTERN = re.compile(
    r"(\$L[0-9]+:[ \t]*\n)"
    r"([ \t]*)(j[ \t]+\$31)[ \t]*\n"
    r"([ \t]*\.end)",
    re.MULTILINE,
)

# Same but for inline-asm-terminated functions where the only thing
# before `j $31` is `#NO_APP` (no $L label).
PATTERN_NOAPP = re.compile(
    r"(#NO_APP[ \t]*\n)"
    r"([ \t]*)(j[ \t]+\$31)[ \t]*\n"
    r"([ \t]*\.end)",
    re.MULTILINE,
)


def patch(path: Path) -> bool:
    text = path.read_text()
    # Skip if already patched
    if ".set noreorder\n\tj\t$31" in text or ".set noreorder\n        j\t$31" in text:
        return False
    new = PATTERN.sub(
        lambda m: f"{m.group(1)}{m.group(2)}.set noreorder\n{m.group(2)}{m.group(3)}\n{m.group(2)}.set reorder\n{m.group(4)}",
        text,
        count=1,
    )
    if new == text:
        new = PATTERN_NOAPP.sub(
            lambda m: f"{m.group(1)}{m.group(2)}.set noreorder\n{m.group(2)}{m.group(3)}\n{m.group(2)}.set reorder\n{m.group(4)}",
            text,
            count=1,
        )
    if new == text:
        return False
    path.write_text(new)
    return True


def main(argv: list[str]) -> int:
    if len(argv) != 2:
        print("usage: postprocess_no_trailing_nop.py <path-to.s>", file=sys.stderr)
        return 2
    path = Path(argv[1])
    if not path.exists():
        print(f"file not found: {path}", file=sys.stderr)
        return 1
    patched = patch(path)
    if patched:
        print(f"  no-trailing-nop: patched {path}")
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv))
