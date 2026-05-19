#!/usr/bin/env python3
"""postprocess_00A3A0.py — func_0010A3A0 jal-delay swap.

gcc picks `addiu $16, $16, 32` (p += 8) for the jal delay slot and
emits `addiu $17, $17, -1` (i--) before the jal. Original has it
reversed: i-- is in the jal delay, p += 8 is before the jal.
"""

from __future__ import annotations

import re
import sys
from pathlib import Path


SRC = """\
\taddu\t$17,$17,-1
\t.set\tnoreorder
\t.set\tnomacro
\tjal\tfunc_0010D530
\taddu\t$16,$16,32
\t.set\tmacro
\t.set\treorder
"""

DST = """\
\taddu\t$16,$16,32
\t.set\tnoreorder
\t.set\tnomacro
\tjal\tfunc_0010D530
\taddu\t$17,$17,-1
\t.set\tmacro
\t.set\treorder
"""


def patch(path: Path) -> bool:
    text = path.read_text()
    if SRC not in text:
        return False
    new = text.replace(SRC, DST, 1)
    path.write_text(new)
    print(f"  00A3A0: jal-delay swap on {path}")
    return True


def main(argv):
    if len(argv) != 2:
        print("usage: postprocess_00A3A0.py <file.s>", file=sys.stderr)
        return 2
    path = Path(argv[1])
    if not path.exists():
        return 0
    patch(path)
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv))
