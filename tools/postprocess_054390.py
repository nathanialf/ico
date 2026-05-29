#!/usr/bin/env python3
"""postprocess_054390.py — for func_00154390 (boyact).

ee-gcc 2.9 fills `jal func_00104360`'s delay slot with the trailing
`s.s $f0,0($29)` buf-store (a "free" movable store) and hoists the
`lw $4,320($16)` arg0 reload AHEAD of the jal. The original codegen
does the opposite: the buf-store is emitted before the call and the
arg0 reload fills the delay slot.

This is a §8.22-shaped diff (store landing in a jal delay), but the
*load-in-delay* variant — the cookbook barrier (and `volatile` cast)
only relocates the store; they cannot pull the arg-LOAD into the slot
(gcc fills the freed slot with the a1 setup instead). 10+ source-level
attempts (memory barrier, volatile store, volatile arg0 read, buf via
pointer, arg0 temp, KEEP_LIVE(buf), barrier+pointer, ...) all stalled
at the same single ordering diff. Pure deterministic instruction-order
swap → one-off postprocess per COOKBOOK.md §13.

func_00104360 is called from exactly one site in the boyact TU, so the
pattern (the buf-store + that jal + the 0x140 reload) is unambiguous.
Idempotent: re-running on already-swapped output is a no-op.
"""

from __future__ import annotations

import re
import sys
from pathlib import Path


def patch(path: Path) -> bool:
    text = path.read_text()
    # built:  lw $4,320($16) ; .set noreorder/nomacro ; jal func_00104360 ; s.s $f0,0($29)
    # want:   s.s $f0,0($29) ; .set noreorder/nomacro ; jal func_00104360 ; lw $4,320($16)
    # Runs in compile_c.sh/quick_diff.sh BEFORE canon_regnames, so the stack
    # pointer is still the named `$sp` (not yet `$29`); $16/$4/$f0 are numbered.
    pat = re.compile(
        r"(\tlw\t\$4,320\(\$16\)\n)"
        r"(\t\.set\tnoreorder\n\t\.set\tnomacro\n\tjal\tfunc_00104360\n)"
        r"(\ts\.s\t\$f0,0\(\$(?:sp|29)\)\n)"
    )

    def repl(m):
        return m.group(3) + m.group(2) + m.group(1)

    new, n = pat.subn(repl, text, count=1)
    if n == 0:
        return False
    path.write_text(new)
    print(f"  054390: swapped buf-store/arg0-reload around jal func_00104360 in {path}")
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
