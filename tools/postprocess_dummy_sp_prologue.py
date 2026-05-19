#!/usr/bin/env python3
"""postprocess_dummy_sp_prologue.py — inject a dummy `addiu $sp, $sp, 16`
right BEFORE the real `subu $sp, $sp, K` (or `addiu $sp, $sp, -K`) prologue.

ee-gcc 2.9 sometimes left a no-op stack adjust at the function head
(e.g. func_0023C17C). This postprocess inserts it.

Gated by config/dummy_sp_prologue.txt (basename allowlist).
"""

from __future__ import annotations

import re
import sys
from pathlib import Path


def patch(path: Path) -> bool:
    text = path.read_text()
    # Match either form of the gcc prologue stack-alloc.
    pat = re.compile(
        r"(\.fmask[^\n]*\n)"
        r"(\t(?:subu[ \t]+\$(?:sp|29),\$(?:sp|29),(\d+)|addiu[ \t]+\$(?:sp|29),\$(?:sp|29),-(\d+)))",
    )
    m = pat.search(text)
    if not m:
        return False
    inject = "\taddiu\t$sp,$sp,16\n"
    new = text[: m.end(1)] + inject + text[m.end(1):]
    # Lower function alignment so the (sub)section can land at a 4-aligned
    # address — the original ELF's func_0023C17C symbol is at 0x23C17C
    # which is mod-8 = 4, not 8-aligned.
    new = re.sub(r"\.p2align\s+3\b", ".p2align 2", new, count=1)
    path.write_text(new)
    print(f"  dummy_sp_prologue: injected into {path}")
    return True


def main(argv):
    if len(argv) != 2:
        print("usage: postprocess_dummy_sp_prologue.py <file.s>", file=sys.stderr)
        return 2
    path = Path(argv[1])
    if not path.exists():
        return 0
    patch(path)
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv))
