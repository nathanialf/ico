#!/usr/bin/env python3
"""postprocess_07ACD8.py — for func_0017ACD8 (way_util).

Two ee-gcc-2.9 codegen quirks left after the C is otherwise exact
(matched siblings are unaffected — both patterns are unique to this fn):

1. lui-order: gcc materialises %hi(D_004CC1E0) before %hi(D_004CAEC0)
   (same quirk func_00205628 needed postprocess_105628 for), so the two
   table bases land swapped and the f0 read folds %lo onto the %hi reg
   instead of reading via the iterator. Source decl-reorder / inlining
   don't move it. Swap the prologue to a-first and read f0 via $6.

2. back-edge branch-likely: the `a < end` loop test emits the inverted
   `beq $2,$0,$Lexit ; b $Lloop ; lw(delay)` instead of the original
   `bnel $2,$0,$Lloop ; lw(delay)` (position-dependent heuristic, see
   [[branch_likely_emission]]; empty-label/structure tweaks don't move
   it). Collapse it back to bnel.

Pure deterministic rewrites → COOKBOOK.md §13. Idempotent.
"""

from __future__ import annotations

import re
import sys
from pathlib import Path


def patch(path: Path) -> bool:
    text = path.read_text()
    changed = False

    # (1) prologue lui-order: D_004CC1E0-first -> D_004CAEC0-first.
    pro = re.compile(
        r"\tlui\t\$2,%hi\(D_004CC1E0\)[^\n]*\n"
        r"\tlui\t\$3,%hi\(D_004CAEC0\)[^\n]*\n"
        r"\taddiu\t\$7,\$2,%lo\(D_004CC1E0\)[^\n]*\n"
        r"\taddiu\t\$6,\$3,%lo\(D_004CAEC0\)[^\n]*\n"
        r"\tlw\t\$2,%lo\(D_004CAEC0\)\(\$3\)\n"
        r"\taddu\t\$8,\$6,4888\n"
    )
    pro_repl = (
        "\tlui\t$2,%hi(D_004CAEC0) # high\n"
        "\tlui\t$3,%hi(D_004CC1E0) # high\n"
        "\taddiu\t$6,$2,%lo(D_004CAEC0) # low\n"
        "\taddiu\t$7,$3,%lo(D_004CC1E0) # low\n"
        "\taddu\t$8,$6,4888\n"
        "\tlw\t$2,0($6)\n"
    )
    text, n = pro.subn(pro_repl, text, count=1)
    changed = changed or n > 0

    # (2) back-edge: beq-to-exit + b-to-loop -> bnel-to-loop (lw stays delay).
    be = re.compile(
        r"\tbeq\t\$2,\$0,\$L\d+\n"
        r"(\t\.set\tnoreorder\n\t\.set\tnomacro\n)"
        r"\tb\t(\$L\d+)\n"
        r"(\tlw\t\$2,0\(\$6\)\n)"
    )
    text, n = be.subn(lambda m: m.group(1) + "\tbnel\t$2,$0," + m.group(2) + "\n" + m.group(3), text, count=1)
    changed = changed or n > 0

    if not changed:
        return False
    path.write_text(text)
    print(f"  07ACD8: fixed lui-order + back-edge bnel in {path}")
    return True


def main(argv):
    if len(argv) != 2:
        return 2
    path = Path(argv[1])
    if not path.exists():
        return 1
    patch(path)
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv))
