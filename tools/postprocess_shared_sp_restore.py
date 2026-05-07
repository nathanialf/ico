#!/usr/bin/env python3
"""
postprocess_shared_sp_restore.py — strip the function epilogue that
ee-gcc emits before `.end`, leaving the function to fall through into
the next adjacent function (a "shared epilogue stub") that provides
the missing instructions.

Two modes (controlled by the second arg):

  --sp-only     : strip just the `addu/subu $sp, $sp, N` from the
                  delay slot of the final `j $31`. Function ends at
                  `j $31` with empty delay slot. Next adjacent
                  function must be a 4-byte `addiu sp, +N; endlabel`
                  stub (e.g. func_00194438).

  --jr-and-sp   : strip the entire `j $31 ; addu $sp, $sp, N` (both
                  the jr and the sp restore). Function ends at the
                  preceding instruction (typically `ld $31, N($sp)`).
                  Next adjacent function must be an 8-byte
                  `jr ra; addiu sp, +N; endlabel` stub (e.g.
                  func_001943C0).

Default is `--sp-only` for backwards compatibility.

Idempotent. Per-file opt-in via config files.
"""

from __future__ import annotations

import re
import sys
from pathlib import Path

# --sp-only: strip the addu/subu $sp from delay slot of j $31.
SP_ONLY_PATTERN = re.compile(
    r"([ \t]*\.set[ \t]+noreorder[ \t]*\n"
    r"[ \t]*\.set[ \t]+nomacro[ \t]*\n"
    r"[ \t]*j[ \t]+\$31[ \t]*\n)"
    r"[ \t]*(?:addu|subu)[ \t]+\$(?:sp|29),[ \t]*\$(?:sp|29),[ \t]*-?\d+[ \t]*\n"
    r"([ \t]*\.set[ \t]+macro[ \t]*\n"
    r"[ \t]*\.set[ \t]+reorder[ \t]*\n)",
    re.MULTILINE,
)

# --jr-and-sp: strip the whole `.set noreorder ... j $31 ... addu sp ... .set reorder` block.
JR_AND_SP_PATTERN = re.compile(
    r"[ \t]*\.set[ \t]+noreorder[ \t]*\n"
    r"[ \t]*\.set[ \t]+nomacro[ \t]*\n"
    r"[ \t]*j[ \t]+\$31[ \t]*\n"
    r"[ \t]*(?:addu|subu)[ \t]+\$(?:sp|29),[ \t]*\$(?:sp|29),[ \t]*-?\d+[ \t]*\n"
    r"[ \t]*\.set[ \t]+macro[ \t]*\n"
    r"[ \t]*\.set[ \t]+reorder[ \t]*\n",
    re.MULTILINE,
)


def patch(path: Path, mode: str) -> bool:
    text = path.read_text()
    if mode == "--sp-only":
        new = SP_ONLY_PATTERN.sub(lambda m: m.group(1) + m.group(2), text, count=1)
    elif mode == "--jr-and-sp":
        new = JR_AND_SP_PATTERN.sub("", text, count=1)
    else:
        print(f"unknown mode: {mode}", file=sys.stderr)
        return False
    if new == text:
        return False
    path.write_text(new)
    return True


def main(argv: list[str]) -> int:
    mode = "--sp-only"
    args = argv[1:]
    if args and args[0] in ("--sp-only", "--jr-and-sp"):
        mode = args[0]
        args = args[1:]
    if len(args) != 1:
        print("usage: postprocess_shared_sp_restore.py [--sp-only|--jr-and-sp] <path-to.s>", file=sys.stderr)
        return 2
    path = Path(args[0])
    if not path.exists():
        print(f"file not found: {path}", file=sys.stderr)
        return 1
    if patch(path, mode):
        print(f"  shared-sp-restore ({mode}): patched {path}")
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv))
