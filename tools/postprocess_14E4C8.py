#!/usr/bin/env python3
"""postprocess_14E4C8.py — move mult1 inline-asm before subu $sp.

gcc emits:
    mult  $5,$5,$2
    subu  $29,$29,32
 #APP
    mult1 $4, $4, $3
 #NO_APP

Original has the mult1 before the stack-alloc:
    mult  $5,$5,$2
    mult1 $4, $4, $3
    subu  $29,$29,32
"""

from __future__ import annotations

import sys
from pathlib import Path


SRC = """\
\tmult\t$5,$5,$2
\tsubu\t$sp,$sp,32
 #APP
\tmult1 $4, $4, $3
 #NO_APP
"""

DST = """\
\tmult\t$5,$5,$2
 #APP
\tmult1 $4, $4, $3
 #NO_APP
\tsubu\t$sp,$sp,32
"""


def patch(path: Path) -> bool:
    text = path.read_text()
    if SRC not in text:
        return False
    new = text.replace(SRC, DST, 1)
    path.write_text(new)
    print(f"  14E4C8: moved mult1 before subu on {path}")
    return True


def main(argv):
    if len(argv) != 2:
        print("usage: postprocess_14E4C8.py <file.s>", file=sys.stderr)
        return 2
    path = Path(argv[1])
    if not path.exists():
        return 0
    patch(path)
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv))
