#!/usr/bin/env python3
"""
postprocess_swap_zero_ret_ld_ra.py — swap `daddu $2,$0,$0` and the
immediately-following `ld $31, OFF($sp)` so the ld-ra runs first.

ee-gcc 2.9 sometimes places the return-value zeroing instruction BEFORE
the `ld $31` epilogue restore. The original ICO codegen swaps this
order. Both are byte-different forms of the same epilogue.

Pattern (before):
    daddu $2,$0,$0
    ld $31, OFF($sp)
becomes:
    ld $31, OFF($sp)
    daddu $2,$0,$0

Gated by config/swap_zero_ret_ld_ra.txt.
Idempotent (idempotent over the inverse swap, so re-running has no effect
once the line pair is in the desired order).
"""

from __future__ import annotations

import re
import sys
from pathlib import Path


DADDU_ZERO = re.compile(
    r"^(?P<lead>[ \t]*)"
    r"(daddu[ \t]+\$2,\$0,\$0|move[ \t]+\$2,\$0|move[ \t]+\$v0,\$zero)"
    r"[ \t]*$"
)
LD_RA = re.compile(
    r"^(?P<lead>[ \t]*)ld[ \t]+(?:\$31|\$ra),\s*\d+\((?:\$sp|\$29)\)[ \t]*$"
)


def patch(path: Path) -> bool:
    lines = path.read_text().splitlines(keepends=True)
    out = list(lines)
    changed = False

    i = 0
    n = len(out)
    while i < n - 1:
        if DADDU_ZERO.match(out[i]) and LD_RA.match(out[i + 1]):
            out[i], out[i + 1] = out[i + 1], out[i]
            changed = True
            i += 2
            continue
        i += 1

    if changed:
        path.write_text("".join(out))
    return changed


def main():
    if len(sys.argv) != 2:
        sys.exit("usage: postprocess_swap_zero_ret_ld_ra.py <file.s>")
    patch(Path(sys.argv[1]))


if __name__ == "__main__":
    main()
