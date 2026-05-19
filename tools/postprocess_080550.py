#!/usr/bin/env python3
"""postprocess_080550.py — for func_00180550, swap `li $5, 1` and the
move.s $f16 sequence so the addiu a1,$0,1 lands in the j-tail-call's
delay slot."""

from __future__ import annotations

import re
import sys
from pathlib import Path


def patch(path: Path) -> bool:
    text = path.read_text()
    # Pattern: li $5, 1; mov.s f13; mov.s f14; .set noreorder/nomacro; j SYM; mov.s f16
    # Want:    mov.s f13; mov.s f14; mov.s f16; .set noreorder; j SYM; li $5, 1
    pat = re.compile(
        r"([ \t]*li[ \t]+\$5,[^\n]*\n)"
        r"([ \t]*mov\.s[ \t]+\$f13,[^\n]*\n)"
        r"([ \t]*mov\.s[ \t]+\$f14,[^\n]*\n)"
        r"([ \t]*\.set[ \t]+noreorder[ \t]*\n[ \t]*\.set[ \t]+nomacro[ \t]*\n)"
        r"([ \t]*j[ \t]+\w+[ \t]*\n)"
        r"([ \t]*mov\.s[ \t]+\$f16,[^\n]*\n)"
    )

    def repl(m):
        return (
            m.group(2)
            + m.group(3)
            + m.group(6)
            + m.group(4)
            + m.group(5)
            + m.group(1)
        )

    new = pat.sub(repl, text, count=1)
    if new == text:
        return False
    path.write_text(new)
    print(f"  080550: patched {path}")
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
