#!/usr/bin/env python3
"""
postprocess_fcc_noreorder.py — wrap `c.{eq,lt,le}.{s,d}` + `bc1[ft]l?`
pair in `.set noreorder` to suppress gas auto-insertion of the FCC
hazard nop between them.

When ee-as 2.10 is in reorder mode and sees an FCC compare followed
immediately by a branch (with only a `#nop` comment between), it
auto-inserts a real `nop` for the FCC hazard. Our matched original
has NO such nop — it was assembled with a (different) ee-as that
did not enforce the hazard at this site.

Wrapping the pair in `.set noreorder` prevents the auto-fill. We
must also add an explicit `nop` for the bc1[ft]'s delay slot, since
gcc immediately follows bc1f with `.set noreorder; .set nomacro; jal`
— under noreorder gas does not fill the delay slot either, and jal
in a branch delay slot is illegal.

Pattern transformed (in order):
    [\t]c.{eq,lt,le}.{s,d}\t...
    [\t]#nop
    [\t]bc1[ft]l?\t...
    [\t].set noreorder       <- already there, indicates gcc's call block
becomes:
    [\t].set noreorder
    [\t]c.{eq,lt,le}.{s,d}\t...
    [\t]bc1[ft]l?\t...
    [\t]nop
    [\t].set noreorder       <- existing line, unchanged

Idempotent: the inserted `.set noreorder` is skipped if already there.
"""

from __future__ import annotations

import re
import sys
from pathlib import Path

FCC_RE = re.compile(r"^(\s*)c\.(lt|le|eq)\.[sd]\b")
NOP_COMMENT_RE = re.compile(r"^\s*#nop\s*$")
BC1_RE = re.compile(r"^\s*bc1[ft]l?\b")
NOREORDER_RE = re.compile(r"^\s*\.set\s+noreorder\b")


def transform(text: str) -> str:
    lines = text.splitlines(keepends=True)
    out = []
    i = 0
    while i < len(lines):
        m = FCC_RE.match(lines[i])
        if (
            m
            and i + 3 < len(lines)
            and NOP_COMMENT_RE.match(lines[i + 1])
            and BC1_RE.match(lines[i + 2])
            and NOREORDER_RE.match(lines[i + 3])
        ):
            indent = m.group(1)
            # Idempotency: don't re-wrap if previous emitted line already
            # set noreorder for this site.
            if not (out and NOREORDER_RE.match(out[-1])):
                out.append(f"{indent}.set noreorder\n")
            out.append(lines[i])        # c.eq.s
            # drop lines[i+1] (#nop comment)
            out.append(lines[i + 2])    # bc1f
            out.append(f"{indent}nop\n")  # explicit delay-slot nop
            # keep lines[i+3] (.set noreorder) — needed for the jal block
            out.append(lines[i + 3])
            i += 4
            continue
        out.append(lines[i])
        i += 1
    return "".join(out)


def main(argv: list[str]) -> int:
    if len(argv) != 2:
        print("usage: postprocess_fcc_noreorder.py <path.s>", file=sys.stderr)
        return 2
    p = Path(argv[1])
    src = p.read_text()
    out = transform(src)
    if out != src:
        p.write_text(out)
    return 0


if __name__ == "__main__":
    raise SystemExit(main(sys.argv))
