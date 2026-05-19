#!/usr/bin/env python3
"""postprocess_01BF60.py — func_0011BF60 loop schedule rewrite.

gcc's chosen schedule (loop body):
    daddu $4,$17,$0          # a0 = p
    jal func_00118FD8
    li    $5,4               # delay
    addu  $16,$16,-1
    bne   $16,$0, LOOP
    addu  $17,$17,16         # delay

Original schedule (loop body):
    LOOP:
    li    $5,4
    jal func_00118FD8
    addu  $17,$17,16         # delay (p += 16)
    addu  $16,$16,-1
    bne   $16,$0, LOOP
    daddu $4,$17,$0          # delay (a0 = p for next iter)

Plus prologue reorder: sd $17 before sd $31; daddu $17,$4,$0 before
blez; and an `addu $4,$17,$0` pre-loop instruction.
"""

from __future__ import annotations

import re
import sys
from pathlib import Path


SRC = """\
\tsubu\t$sp,$sp,48
\tsra\t$5,$5,4
\tsd\t$31,32($sp)
\tsd\t$17,16($sp)
\t.set\tnoreorder
\t.set\tnomacro
\tblez\t$5,$L2
\tsd\t$16,0($sp)
\t.set\tmacro
\t.set\treorder

\tmove\t$17,$4
\tmove\t$16,$5
\t.p2align 3
$L7:
\tmove\t$4,$17
\t.set\tnoreorder
\t.set\tnomacro
\tjal\tfunc_00118FD8
\tli\t$5,4\t\t\t# 0x4
\t.set\tmacro
\t.set\treorder

\taddu\t$16,$16,-1
\t.set\tnoreorder
\t.set\tnomacro
\tbne\t$16,$0,$L7
\taddu\t$17,$17,16
\t.set\tmacro
\t.set\treorder
"""

DST = """\
\tsubu\t$sp,$sp,48
\tsra\t$5,$5,4
\tsd\t$17,16($sp)
\tsd\t$31,32($sp)
\tmove\t$17,$4
\t.set\tnoreorder
\t.set\tnomacro
\tblez\t$5,$L2
\tsd\t$16,0($sp)
\t.set\tmacro
\t.set\treorder

\tmove\t$16,$5
\tmove\t$4,$17
\t.p2align 3
$L7:
\t.set\tnoreorder
\t.set\tnomacro
\tli\t$5,4\t\t\t# 0x4
\tjal\tfunc_00118FD8
\taddu\t$17,$17,16
\t.set\tmacro
\t.set\treorder

\taddu\t$16,$16,-1
\t.set\tnoreorder
\t.set\tnomacro
\tbne\t$16,$0,$L7
\tmove\t$4,$17
\t.set\tmacro
\t.set\treorder
"""


def patch(path: Path) -> bool:
    text = path.read_text()
    if SRC not in text:
        return False
    new = text.replace(SRC, DST, 1)
    path.write_text(new)
    print(f"  01BF60: rescheduled {path}")
    return True


def main(argv):
    if len(argv) != 2:
        print("usage: postprocess_01BF60.py <file.s>", file=sys.stderr)
        return 2
    path = Path(argv[1])
    if not path.exists():
        return 0
    patch(path)
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv))
