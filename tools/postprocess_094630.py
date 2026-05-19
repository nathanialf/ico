#!/usr/bin/env python3
"""postprocess_094630.py — for func_00194630, move `sd $31; daddu $4,$sp,$0`
before `sw $0, 4($sp)`."""

from __future__ import annotations

import re
import sys
from pathlib import Path


def patch(path: Path) -> bool:
    text = path.read_text()
    pat = re.compile(
        r"([ \t]*sw[ \t]+\$0,[ \t]*4\(\$(?:sp|29)\)[ \t]*\n)"
        r"((?:[ \t]*(?:daddu|move)[ \t]+\$4,[ \t]*\$(?:sp|29)[^\n]*\n)?)"
        r"([ \t]*sd[ \t]+\$31,[^\n]*\n)"
    )

    def repl(m):
        return m.group(3) + m.group(2) + m.group(1)

    # Also pattern where order is sw $0; sd $31; daddu $4 — find the daddu later
    pat2 = re.compile(
        r"([ \t]*sw[ \t]+\$0,[ \t]*4\(\$(?:sp|29)\)[ \t]*\n)"
        r"([ \t]*(?:daddu|move)[ \t]+\$4,[ \t]*\$(?:sp|29)[^\n]*\n)"
        r"([ \t]*sd[ \t]+\$31,[^\n]*\n)"
    )

    def repl2(m):
        return m.group(3) + m.group(2) + m.group(1)

    new = pat2.sub(repl2, text, count=1)
    if new == text:
        new = pat.sub(repl, text, count=1)
    if new == text:
        return False
    path.write_text(new)
    print(f"  094630: patched {path}")
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
