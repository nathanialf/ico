#!/usr/bin/env python3
"""postprocess_0EF9E0.py — func_001EF9E0 scheduling fix.

For two identical func_0011C028 calls (4 int + 1 FP arg), ee-gcc 2.9
emits the FIRST call's `mov.s $f12, $f20` before `daddu $a1, $s0, $0`
but the SECOND call's `daddu $a1, $s0, $0` before `mov.s $f12, $f20`.
The original codegen emits `mov.s` first in both.

The transform: find pairs of consecutive `daddu $5, $16, $0` followed by
`mov.s $f12, $f20` (in the .s before move→daddu translation: actually
gcc emits `move $5, $16; mov.s ...`) and swap them. Idempotent (won't
re-fire on the already-swapped pair because the order is reversed).
"""

from __future__ import annotations

import re
import sys
from pathlib import Path

DADDU_A1 = re.compile(r"^\s*(?:move\s+\$5\s*,\s*\$16|daddu\s+\$5\s*,\s*\$16\s*,\s*\$(?:0|zero))\s*$")
MOV_S_F12 = re.compile(r"^\s*mov\.s\s+\$f12\s*,\s*\$f20\s*$")


def patch(path: Path) -> bool:
    lines = path.read_text().splitlines(keepends=True)
    out = list(lines)
    changed = False

    i = 0
    while i < len(out) - 1:
        if DADDU_A1.match(out[i]) and MOV_S_F12.match(out[i + 1]):
            out[i], out[i + 1] = out[i + 1], out[i]
            changed = True
            i += 2
            continue
        i += 1

    if changed:
        path.write_text("".join(out))
    return changed


def main(argv):
    if len(argv) != 2:
        print(f"usage: {argv[0]} <file.s>", file=sys.stderr)
        return 2
    p = Path(argv[1])
    patch(p)
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv))
