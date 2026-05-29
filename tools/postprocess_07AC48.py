#!/usr/bin/env python3
"""postprocess_07AC48.py — for func_0017AC48 (way_util).

The table-walk has two identical "skip this entry on a zero field" guards
(`*(a+0x0)==0` and `*(a+0x18)==0`). ee-gcc 2.9 emits the FIRST as a clean
`beql ...,$L_check` (advance in the delay) but the SECOND as the inverted
`bne ...,$L_body ; b $L_check ; addu a,a,52(delay)` — a per-branch
branch-likely heuristic that depends on the guard's position, not the C
(see [[branch_likely_emission]]; flipping ==/!=, a memory barrier,
removing the barrier, and restructuring all leave the 2nd guard as
bne+b). Pure branch-mnemonic diff that no source form reproduced →
one-off postprocess per COOKBOOK.md §13.

Collapses the 2nd guard's `bne $2,$0,$Lbody ; b $Lcheck ; addu $8,$8,52`
back to `beql $2,$0,$Lcheck ; addu $8,$8,52`. The `addu $8,$8,52`
(iterator += 0x34, a in $8/t0) plus the bne/b pair makes the match
unambiguous; the dropped `$Lbody` target is the fall-through body, which
is emitted immediately after. Idempotent (no bne/b pair → no-op).
"""

from __future__ import annotations

import re
import sys
from pathlib import Path


def patch(path: Path) -> bool:
    text = path.read_text()
    pat = re.compile(
        r"\t#nop\n"
        r"\tbne\t\$2,\$0,\$L\d+\n"
        r"(\t\.set\tnoreorder\n\t\.set\tnomacro\n)"
        r"\tb\t(\$L\d+)\n"
        r"(\taddu\t\$8,\$8,52\n)"
    )

    def repl(m):
        return m.group(1) + "\tbeql\t$2,$0," + m.group(2) + "\n" + m.group(3)

    new, n = pat.subn(repl, text, count=1)
    if n == 0:
        return False
    path.write_text(new)
    print(f"  07AC48: collapsed bne+b 2nd guard to beql in {path}")
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
