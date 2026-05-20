#!/usr/bin/env python3
"""postprocess_1356D0.py — func_002356D0 scheduling fix.

ee-gcc 2.9 emits the second `lw $v0, 0x15C($a1)` reload between
the first and last of four `mov.s` ops (filling load-use latency).
The original codegen emits all four `mov.s` first, then the reload
right before the `jal`.

The transform: move a `lw $v0, 0x15C($a1)` line down past any
`mov.s` lines that follow it, stopping at the next non-mov.s
instruction (the `jal`). Idempotent.
"""

from __future__ import annotations

import re
import sys
from pathlib import Path

LW_V0_OFF_REG = re.compile(r"^\s*lw\s+\$2\s*,\s*348\(\$5\)\s*$")
MOV_S = re.compile(r"^\s*mov\.s\s+\$f\d+\s*,\s*\$f\d+\s*$")
SKIP = re.compile(r"^\s*(#.*)?\s*$")


def patch(path: Path) -> bool:
    lines = path.read_text().splitlines(keepends=True)
    out = list(lines)
    changed = False

    # Find each `lw $2, 348($5)` line, scan forward through blank/comment
    # lines and any mov.s lines that follow, and move the lw to just after
    # the LAST consecutive mov.s. Idempotent because re-running finds the
    # lw already at the target position (no mov.s follow it).
    i = 0
    while i < len(out):
        if LW_V0_OFF_REG.match(out[i]):
            j = i + 1
            last_mov = -1
            saw_mov = False
            while j < len(out):
                if MOV_S.match(out[j]):
                    last_mov = j
                    saw_mov = True
                    j += 1
                elif SKIP.match(out[j]):
                    j += 1
                else:
                    break
            if saw_mov:
                lw_line = out.pop(i)
                out.insert(last_mov, lw_line)
                changed = True
                i = last_mov + 1
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
