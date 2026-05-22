#!/usr/bin/env python3
"""
postprocess_fcc_nop.py — promote `#nop` (gcc-emitted comment) to a real
`nop` after FCC compare instructions on R5900.

ee-gcc 2.9 emits `c.lt.s`/`c.le.s`/`c.eq.s` (and the .d variants) and
follows them with a `\\t#nop` comment line, expecting the assembler to
fill the FCC hazard slot. ee-as 2.10 ignores the comment, so the nop
is missing in the encoded output. mips-linux-gnu-as in reorder mode
DOES insert the nop, but switches the `move`/`daddu` macro expansion
to `or` — so we want ee-as for the macros and a manual nop after FCC
compares.

Pattern: line N has `\tc.{lt,le,eq}.{s,d}\t...`, line N+1 is `\t#nop`.
Replace the `#nop` line with a real `nop`.

Idempotent.
"""

from __future__ import annotations

import re
import sys
from pathlib import Path

FCC_RE = re.compile(r"^\s*c\.(lt|le|eq)\.[sd]\b")
NOP_COMMENT_RE = re.compile(r"^\s*#nop\s*$")
NOREORDER_RE = re.compile(r"^\s*\.set\s+noreorder\b")
COMMENT_OR_BLANK_RE = re.compile(r"^\s*(#|$)")


def transform(text: str) -> str:
    lines = text.splitlines(keepends=True)
    out = []
    i = 0
    while i < len(lines):
        out.append(lines[i])
        if FCC_RE.match(lines[i]) and i + 1 < len(lines) and NOP_COMMENT_RE.match(lines[i + 1]):
            # Only promote `#nop` -> `nop` when gcc explicitly emitted a
            # `.set noreorder` block around the following bc1[ft]l? — that's
            # the case where the delay slot is filled and the FCC-update
            # hazard nop must be inserted by hand. Otherwise (delay slot is
            # nop / handled by gas), promoting adds a spurious nop.
            j = i + 2
            while j < len(lines) and COMMENT_OR_BLANK_RE.match(lines[j]):
                j += 1
            if j < len(lines) and NOREORDER_RE.match(lines[j]):
                out.append("\tnop\n")
                i += 2
                continue
        i += 1
    return "".join(out)


def main(argv: list[str]) -> int:
    if len(argv) != 2:
        print("usage: postprocess_fcc_nop.py <path.s>", file=sys.stderr)
        return 2
    p = Path(argv[1])
    src = p.read_text()
    out = transform(src)
    if out != src:
        p.write_text(out)
    return 0


if __name__ == "__main__":
    raise SystemExit(main(sys.argv))
