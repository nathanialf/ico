#!/usr/bin/env python3
"""postprocess_0FBBE0.py — func_001FBBE0 register rename.

gcc emits the lui+lw+addiu+sw prologue using $v0 as the HI base; the
original ELF uses $a0. Rename only those four occurrences (where
$v0 ↔ HI of D_004C7710) to $a0. Later uses of $v0 (for offset/ptr)
remain unchanged.
"""

from __future__ import annotations

import re
import sys
from pathlib import Path


SRC = """\
\tlui\t$2,%hi(D_004C7710) # high
\tlw\t$3,%lo(D_004C7710)($2)
\taddiu\t$5,$2,%lo(D_004C7710) # low
\txori\t$3,$3,0x1
\tsw\t$3,%lo(D_004C7710)($2)
\tsll\t$2,$3,2
"""

DST = """\
\tlui\t$4,%hi(D_004C7710) # high
\tlw\t$3,%lo(D_004C7710)($4)
\taddiu\t$5,$4,%lo(D_004C7710) # low
\txori\t$3,$3,0x1
\tsll\t$2,$3,2
\tsw\t$3,%lo(D_004C7710)($4)
"""


def patch(path: Path) -> bool:
    text = path.read_text()
    if SRC not in text:
        return False
    new = text.replace(SRC, DST, 1)
    path.write_text(new)
    print(f"  0FBBE0: renamed v0→a0 in prologue of {path}")
    return True


def main(argv):
    if len(argv) != 2:
        print("usage: postprocess_0FBBE0.py <file.s>", file=sys.stderr)
        return 2
    path = Path(argv[1])
    if not path.exists():
        return 0
    patch(path)
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv))
