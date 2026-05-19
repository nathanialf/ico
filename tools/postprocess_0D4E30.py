#!/usr/bin/env python3
"""postprocess_0D4E30.py — func_001D4E30 loop body rewrite.

gcc emits the inner loop with bne+nondelay-store; original uses
beql+delay-store (branch-likely).

gcc:
    lw    $2, 0($6)
    addu  $5, $5, -1
    bne   $2, $4, $L6
    addu  $6, $6, 400    # delay
    sw    $0, 0($3)
$L6:
    bgez  $5, $L7
    addu  $3, $3, 4      # delay

original:
$L7:
    lw    $2, 0($6)
    beql  $2, $4, $L6
    sw    $0, 0($3)      # delay (squashed if not equal)
$L6:
    addu  $3, $3, 4
    addu  $5, $5, -1
    bgez  $5, $L7
    addu  $6, $6, 400    # delay
"""

from __future__ import annotations

import sys
from pathlib import Path


SRC = """\
$L7:
\tlw\t$2,0($6)
\taddu\t$5,$5,-1
\t.set\tnoreorder
\t.set\tnomacro
\tbne\t$2,$4,$L6
\taddu\t$6,$6,400
\t.set\tmacro
\t.set\treorder

\tsw\t$0,0($3)
$L6:
\t.set\tnoreorder
\t.set\tnomacro
\tbgez\t$5,$L7
\taddu\t$3,$3,4
\t.set\tmacro
\t.set\treorder
"""

DST = """\
$L7:
\tlw\t$2,0($6)
\t.set\tnoreorder
\t.set\tnomacro
\tbeql\t$2,$4,$L6
\tsw\t$0,0($3)
\t.set\tmacro
\t.set\treorder

$L6:
\taddu\t$3,$3,4
\taddu\t$5,$5,-1
\t.set\tnoreorder
\t.set\tnomacro
\tbgez\t$5,$L7
\taddu\t$6,$6,400
\t.set\tmacro
\t.set\treorder
"""


def patch(path: Path) -> bool:
    text = path.read_text()
    if SRC not in text:
        return False
    new = text.replace(SRC, DST, 1)
    path.write_text(new)
    print(f"  0D4E30: bne→beql loop rewrite on {path}")
    return True


def main(argv):
    if len(argv) != 2:
        print("usage: postprocess_0D4E30.py <file.s>", file=sys.stderr)
        return 2
    path = Path(argv[1])
    if not path.exists():
        return 0
    patch(path)
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv))
