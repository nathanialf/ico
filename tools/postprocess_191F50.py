#!/usr/bin/env python3
"""postprocess_191F50.py — for func_00191F50 in src/fightSound, lift
the `addiu $16, $16, %lo(D_0055AE88)` instructions from the `b` delay
slots (used by the 3-case switch's two default-jumps) to the merged
default-body label, and fill the b-delays with `li $5, 255` (the
func_00263FF0 line-number arg) which is needed downstream anyway.

Background: ee-gcc 2.9 first-pass scheduler keeps the lui+addiu pair
adjacent across the b's delay slot. The original ICO codegen split
them — the lui is hoisted into the preceding BEQ delay, the addiu is
lifted to the default body label, and the b's delay carries the
addiu of the line arg ($a1 = 0xFF). The net byte-effect is small but
the schedule differs.

This is a §13 one-off (per-function) postprocess; it only fires inside
src/fightSound.s and only when the exact pattern is present.

Per-file allowlist in config/191F50.txt.
"""

from __future__ import annotations

import re
import sys
from pathlib import Path


# Match the two b-delay sites:
#   b   $L<N>
#   addiu $16,$16,%lo(D_0055AE88) # low (optional comment)
B_DELAY_RE = re.compile(
    r"(\tb\t\$L\w+\n)\taddiu\t\$16,\$16,%lo\(D_0055AE88\)(?:[^\n]*)\n"
)

# Match the merged default-body label and the leading jal:
#   $L16:
#   $L18:
#       .set    noreorder
#       .set    nomacro
#       jal     func_001AD768
INSERT_RE = re.compile(
    r"(\$L\w+:\n\$L\w+:\n)"
    r"(\t\.set\tnoreorder\n\t\.set\tnomacro\n)"
    r"(\tjal\tfunc_001AD768\n)"
)


def patch(path: Path) -> bool:
    text = path.read_text()
    if "func_00191F50" not in text:
        return False
    if "D_0055AE88" not in text:
        return False

    new_text, n = B_DELAY_RE.subn(
        lambda m: m.group(1) + "\tli\t$5,255\n",
        text,
    )
    if n == 0:
        return False
    if n != 2:
        print(f"  191F50: expected 2 b-delay matches, got {n} in {path}",
              file=sys.stderr)
        return False

    new_text, n2 = INSERT_RE.subn(
        lambda m: m.group(1)
        + "\taddiu\t$16,$16,%lo(D_0055AE88)\n"
        + m.group(2)
        + m.group(3),
        new_text,
    )
    if n2 != 1:
        print(f"  191F50: insert pattern not found in {path}",
              file=sys.stderr)
        return False

    path.write_text(new_text)
    print(f"  191F50: patched {path}")
    return True


def main(argv: list[str]) -> int:
    if len(argv) != 2:
        return 2
    path = Path(argv[1])
    if not path.exists():
        return 1
    patch(path)
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv))
