#!/usr/bin/env python3
"""
postprocess_lui_const_swap.py — swap register allocation between the
"address-load lui" and a nearby "const li" in functions where the lui
result is dead after one use.

Pattern (gcc-emitted, before any other postprocess):
    lui   $a, %hi(D)
    [optional intervening insns]
    lw    $b, %lo(D)($a)         <-- last use of $a
    li    $c, K
    [.set noreorder/.set nomacro]
    beq/bne $b, $c, LBL          <-- the only use of $c

Rewrite: rename $c (in `li`) and its sole use (in beq/bne) to $a.

Per-file allowlist in config/lui_const_swap.txt.
"""

from __future__ import annotations

import re
import sys
from pathlib import Path


PATTERN = re.compile(
    r"(?P<lui>[ \t]*lui[ \t]+\$(?P<rA>\d+),\s*%hi\([^)]+\))[ \t]*(?:#[^\n]*)?\n"
    r"(?P<inner>(?:[^\n]*\n){0,3}?)"
    r"(?P<lw>[ \t]*lw[ \t]+\$(?P<rB>\d+),\s*%lo\([^)]+\)\(\$(?P=rA)\))[ \t]*(?:#[^\n]*)?\n"
    r"(?P<between>(?:[^\n]*\n){0,2}?)"
    r"(?P<li>[ \t]*li[ \t]+\$(?P<rC>\d+),)(?P<lirest>[^\n]*)\n"
    r"(?P<setlines>(?:[ \t]*\.set[ \t]+\w+[ \t]*\n)*)"
    r"(?P<beq>[ \t]*(?:beq|bne)l?[ \t]+\$(?P=rB),)\$(?P=rC)(?P<beqrest>[^\n]*)\n",
    re.MULTILINE,
)


def patch(path: Path) -> bool:
    text = path.read_text()

    def repl(m):
        rA = m["rA"]
        rC = m["rC"]
        if rC == rA:
            return m.group(0)
        # Forbid if any intervening insn between lw and li/beq uses $rA
        if re.search(rf"\$\b{rA}\b", m["between"]):
            return m.group(0)
        return (
            m["lui"] + "\n"
            + m["inner"]
            + m["lw"] + "\n"
            + m["between"]
            + f"\tli\t${rA},{m['lirest']}\n"
            + m["setlines"]
            + m["beq"] + f"${rA}" + m["beqrest"] + "\n"
        )

    new = PATTERN.sub(repl, text, count=1)
    if new == text:
        return False
    path.write_text(new)
    return True


def main(argv: list[str]) -> int:
    if len(argv) != 2:
        print("usage: postprocess_lui_const_swap.py <path-to.s>", file=sys.stderr)
        return 2
    path = Path(argv[1])
    if not path.exists():
        return 1
    if patch(path):
        print(f"  lui-const-swap: patched {path}")
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv))
