#!/usr/bin/env python3
"""postprocess_103A10.py — full body rewrite for func_00203A10."""

from __future__ import annotations

import sys
from pathlib import Path


SRC = """\
\tsubu\t$sp,$sp,16
\tmove\t$7,$4
\tsd\t$31,0($sp)
\tmove\t$9,$6
\tlw\t$3,356($7)
\t#nop
\tlw\t$2,300($3)
\t#nop
\t.set\tnoreorder
\t.set\tnomacro
\tbeq\t$2,$0,$L3
\tmove\t$8,$5
\t.set\tmacro
\t.set\treorder

\t.set\tnoreorder
\t.set\tnomacro
\tb\t$L4
\tmove\t$2,$0
\t.set\tmacro
\t.set\treorder

\t.p2align 2
$L3:
\tsw\t$7,300($3)
\tmove\t$5,$9
\tmove\t$6,$8
\t.set\tnoreorder
\t.set\tnomacro
\tjal\tfunc_0013FF88
\tsw\t$9,304($3)
\t.set\tmacro
\t.set\treorder

\tli\t$2,1\t\t\t# 0x1
$L4:
"""

DST = """\
\tsubu\t$sp,$sp,16
\tmove\t$7,$4
\tsd\t$31,0($sp)
\tmove\t$8,$5
\tlw\t$3,356($7)
\tlw\t$2,300($3)
\t.set\tnoreorder
\t.set\tnomacro
\tbne\t$2,$0,$L_FAIL
\tmove\t$5,$6
\t.set\tmacro
\t.set\treorder

\tsw\t$5,304($3)
\tmove\t$6,$8
\t.set\tnoreorder
\t.set\tnomacro
\tjal\tfunc_0013FF88
\tsw\t$7,300($3)
\t.set\tmacro
\t.set\treorder

\t.set\tnoreorder
\t.set\tnomacro
\tb\t$L4
\tli\t$2,1\t\t\t# 0x1
\t.set\tmacro
\t.set\treorder

\t.p2align 2
$L_FAIL:
\tmove\t$2,$0
$L4:
"""


def patch(path: Path) -> bool:
    text = path.read_text()
    if SRC not in text:
        return False
    new = text.replace(SRC, DST, 1)
    path.write_text(new)
    print(f"  103A10: body rewrite on {path}")
    return True


def main(argv):
    if len(argv) != 2:
        print("usage: postprocess_103A10.py <file.s>", file=sys.stderr)
        return 2
    path = Path(argv[1])
    if not path.exists():
        return 0
    patch(path)
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv))
