#!/usr/bin/env python3
"""postprocess_105628.py — func_00205628 prologue reorder.

gcc emits the lui/addiu pair for D_004CC1E0 first; the original emits
D_004CAEC0 first. This script just rewrites the gcc-emit body to the
expected ordering.
"""

from __future__ import annotations

import re
import sys
from pathlib import Path


# Replacement keyed on the unique prologue (BEFORE the move→daddu sed).
SRC = """\
\tli\t$2,52\t\t\t# 0x34
\tlui\t$3,%hi(D_004CC1E0) # high
\tmult\t$4,$4,$2
\taddiu\t$3,$3,%lo(D_004CC1E0) # low
\tsll\t$5,$5,6
\tlui\t$6,%hi(D_004CAEC0) # high
\taddu\t$5,$5,$3
\taddiu\t$6,$6,%lo(D_004CAEC0) # low
\tsw\t$0,8($5)
\tmove\t$2,$0
\taddu\t$4,$4,$6
"""

DST = """\
\tli\t$2,52\t\t\t# 0x34
\tlui\t$6,%hi(D_004CAEC0) # high
\tmult\t$4,$4,$2
\tlui\t$3,%hi(D_004CC1E0) # high
\taddiu\t$6,$6,%lo(D_004CAEC0) # low
\taddiu\t$3,$3,%lo(D_004CC1E0) # low
\tsll\t$5,$5,6
\tmove\t$2,$0
\taddu\t$5,$5,$3
\taddu\t$4,$4,$6
\tsw\t$0,8($5)
"""


def patch(path: Path) -> bool:
    text = path.read_text()
    if SRC not in text:
        return False
    new = text.replace(SRC, DST, 1)
    path.write_text(new)
    print(f"  105628: reordered {path}")
    return True


def main(argv):
    if len(argv) != 2:
        print("usage: postprocess_105628.py <file.s>", file=sys.stderr)
        return 2
    path = Path(argv[1])
    if not path.exists():
        return 0
    patch(path)
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv))
