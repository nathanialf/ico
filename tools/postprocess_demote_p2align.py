#!/usr/bin/env python3
"""
postprocess_demote_p2align.py — demote `.p2align 3` to `.p2align 2`
inside specific function blocks listed in config/demote_p2align.txt.

ee-gcc 2.9 emits `.p2align 3` (8-byte) before loop/branch-target labels.
Most original ICO labels honour that, but a few if-merge labels in
coalesced TUs land at a VMA whose `mod 8 == 4`, so the 8-byte alignment
pads them with a stray nop (+4 bytes) that the original does NOT have.

The global cure is `-malign-loops=2` (emits `.p2align 2`), but that is a
*per-file* flag: a TU may hold one function whose if-merge needs the
demotion AND another whose real loop needs the 8-byte pad. This
postprocess demotes only the listed functions, leaving every other
`.p2align 3` (e.g. real loop tops) intact.

config/demote_p2align.txt: one function symbol per line (e.g.
`func_00131560`). Lines starting with `#` and blank lines are ignored.

Idempotent and a no-op when none of the listed functions are present.
"""

from __future__ import annotations

import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
CONFIG = ROOT / "config" / "demote_p2align.txt"

LABEL_RE = re.compile(r"^([A-Za-z_.$][\w.$]*):")
END_RE = re.compile(r"^\s*\.end\s+(\S+)")
P2ALIGN3_RE = re.compile(r"^(\s*)\.p2align\s+3\b(.*)$")


def listed_funcs() -> set[str]:
    if not CONFIG.is_file():
        return set()
    out = set()
    for line in CONFIG.read_text().splitlines():
        line = line.strip()
        if not line or line.startswith("#"):
            continue
        out.add(line.split()[0])
    return out


def patch(path: Path, funcs: set[str]) -> bool:
    if not funcs:
        return False
    lines = path.read_text().splitlines(keepends=True)
    cur = None  # current function symbol whose body we are inside
    changed = False
    for i, line in enumerate(lines):
        m = LABEL_RE.match(line)
        if m and not line.lstrip().startswith("$"):
            # A top-level (non-local) label starts a function body.
            cur = m.group(1)
        e = END_RE.match(line)
        if e:
            cur = None
            continue
        if cur in funcs:
            p = P2ALIGN3_RE.match(line)
            if p:
                lines[i] = f"{p.group(1)}.p2align 2{p.group(2)}\n"
                changed = True
    if changed:
        path.write_text("".join(lines))
    return changed


def main() -> int:
    if len(sys.argv) != 2:
        print("usage: postprocess_demote_p2align.py <asm_file>", file=sys.stderr)
        return 2
    patch(Path(sys.argv[1]), listed_funcs())
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
