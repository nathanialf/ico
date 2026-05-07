#!/usr/bin/env python3
"""
postprocess_shared_sp_restore.py — strip the `addu $sp, $sp, N` (or
`subu $sp, $sp, -N`) that ee-gcc emits in the delay slot of the final
`j $31`, and wrap the j $31 in `.set noreorder` so gas leaves the
delay slot empty.

This matches the original ICO codegen pattern where a function ends
at `jr ra` with NO sp-restoring epilogue; the delay slot is filled by
the next adjacent function in the linked image, which is itself a
4-byte "shared sp restore" function (e.g. func_00194438 = just
`addiu sp, +0x20; endlabel`). Calling sites of the leading function
fall through into the shared restore, then jr ra unwinds to the caller.

Idempotent. Safe only when the next adjacent function in the linker
script is the appropriate `addiu sp, +N` shared-restore stub —
applying it elsewhere will leak stack.

Pattern matched in the .s emitted by ee-gcc 2.9-991111:

    .set noreorder
    .set nomacro
    j $31
    addu $sp, $sp, N
    .set macro
    .set reorder

    .end <FUNC>

Patched to:

    .set noreorder
    .set nomacro
    j $31
    .set macro
    .set reorder

    .end <FUNC>
"""

from __future__ import annotations

import re
import sys
from pathlib import Path

# Match the gcc-emitted closing block.
PATTERN = re.compile(
    r"([ \t]*\.set[ \t]+noreorder[ \t]*\n"
    r"[ \t]*\.set[ \t]+nomacro[ \t]*\n"
    r"[ \t]*j[ \t]+\$31[ \t]*\n)"
    r"[ \t]*(?:addu|subu)[ \t]+\$(?:sp|29),[ \t]*\$(?:sp|29),[ \t]*-?\d+[ \t]*\n"
    r"([ \t]*\.set[ \t]+macro[ \t]*\n"
    r"[ \t]*\.set[ \t]+reorder[ \t]*\n)",
    re.MULTILINE,
)


def patch(path: Path) -> bool:
    text = path.read_text()
    new = PATTERN.sub(lambda m: m.group(1) + m.group(2), text, count=1)
    if new == text:
        return False
    path.write_text(new)
    return True


def main(argv: list[str]) -> int:
    if len(argv) != 2:
        print("usage: postprocess_shared_sp_restore.py <path-to.s>", file=sys.stderr)
        return 2
    path = Path(argv[1])
    if not path.exists():
        print(f"file not found: {path}", file=sys.stderr)
        return 1
    if patch(path):
        print(f"  shared-sp-restore: patched {path}")
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv))
