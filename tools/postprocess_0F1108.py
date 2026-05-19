#!/usr/bin/env python3
"""postprocess_0F1108.py — rewrite tail of func_001F1108 to use the
movn idiom and a single-merge structure."""

from __future__ import annotations

import sys
from pathlib import Path


SRC = """\
\tsltu\t$2,$3,$4
\t.set\tnoreorder
\t.set\tnomacro
\tbeq\t$2,$0,$L3
\taddu\t$5,$4,4096
\t.set\tmacro
\t.set\treorder

\tli\t$2,131072\t\t\t# 0x20000
\tori\t$2,$2,0x8000
\taddu\t$3,$3,$2
\tsltu\t$4,$3,$4
\t.set\tnoreorder
\t.set\tnomacro
\tbeq\t$4,$0,$L6
\tslt\t$2,$3,$5
\t.set\tmacro
\t.set\treorder

\t.set\tnoreorder
\t.set\tnomacro
\tj\t$31
\tli\t$2,1\t\t\t# 0x1
\t.set\tmacro
\t.set\treorder

\t.p2align 2
$L3:
\tslt\t$2,$3,$5
$L6:
\t.set\tnoreorder
\t.set\tnomacro
\tj\t$31
\txori\t$2,$2,0x1
\t.set\tmacro
\t.set\treorder
"""

DST = """\
\tsltu\t$2,$3,$4
\t.set\tnoreorder
\t.set\tnomacro
\tbeq\t$2,$0,$L3
\taddu\t$5,$4,4096
\t.set\tmacro
\t.set\treorder

\tli\t$2,131072\t\t\t# 0x20000
\tori\t$2,$2,0x8000
\taddu\t$3,$3,$2
\tsltu\t$2,$3,$4
$L3:
\t.set\tnoreorder
\t.set\tnomacro
\tbne\t$2,$0,$L6
\taddiu\t$4,$0,1
\t.set\tmacro
\t.set\treorder

\tslt\t$2,$3,$5
\tmovn\t$4,$0,$2
$L6:
\t.set\tnoreorder
\t.set\tnomacro
\tj\t$31
\tdaddu\t$2,$4,$0
\t.set\tmacro
\t.set\treorder
"""


def patch(path: Path) -> bool:
    text = path.read_text()
    if SRC not in text:
        return False
    new = text.replace(SRC, DST, 1)
    path.write_text(new)
    print(f"  0F1108: tail rewrite on {path}")
    return True


def main(argv):
    if len(argv) != 2:
        print("usage: postprocess_0F1108.py <file.s>", file=sys.stderr)
        return 2
    path = Path(argv[1])
    if not path.exists():
        return 0
    patch(path)
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv))
