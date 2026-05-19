#!/usr/bin/env python3
"""
postprocess_jal_daddu_lw_loop.py — rewrite the gcc-emitted

    .L_LBL:
        .set noreorder
        .set nomacro
        jal SYM
        daddu $rA, $rS, $0
        .set macro
        .set reorder

        lw $rS, OFF($rS)
        #nop
        bne $rS, $0, .L_LBL

loop into the more compact "useful delay slot" form

    .L_LBL:
        .set noreorder
        .set nomacro
        jal SYM
        lw $rS, OFF($rS)
        .set macro
        .set reorder

        bne $rS, $0, .L_LBL
        daddu $rA, $rS, $0

— matching the original ICO codegen where the linked-list-walk delay
slots are fully utilized (jal's slot for the next-pointer load, bne's
slot for setting the call argument).

Gated by per-file allowlist in config/jal_daddu_lw_loop.txt.

Idempotent: only rewrites the first matching block per file.
"""

from __future__ import annotations

import re
import sys
from pathlib import Path


PATTERN = re.compile(
    r"(?P<lbl>\$L\d+:[ \t]*\n)"
    r"(?P<nr1>[ \t]*\.set[ \t]+noreorder[ \t]*\n[ \t]*\.set[ \t]+nomacro[ \t]*\n)"
    r"(?P<jal>[ \t]*jal[ \t]+\w+[ \t]*\n)"
    r"(?P<daddu>[ \t]*(?:daddu[ \t]+\$\d+,[ \t]*\$(?P<rS>\d+),[ \t]*\$0|move[ \t]+\$\d+,[ \t]*\$(?P<rS2>\d+))[ \t]*\n)"
    r"(?P<mr1>[ \t]*\.set[ \t]+macro[ \t]*\n[ \t]*\.set[ \t]+reorder[ \t]*\n)"
    r"(?P<blank>\s*\n)"
    r"(?P<lw>[ \t]*lw[ \t]+\$(?P<rL>\d+),[ \t]*\d+\(\$(?P=rL)\)[ \t]*\n)"
    r"(?P<comment>[ \t]*#nop[ \t]*\n)?"
    r"(?P<bne>[ \t]*bne[ \t]+\$(?P=rL),[ \t]*\$0,[ \t]*(?P<bnelbl>\$L\d+)[ \t]*\n)",
    re.MULTILINE,
)


def patch(path: Path) -> bool:
    text = path.read_text()

    def repl(m):
        # The bne target should equal the loop label
        lbl_name = m["lbl"].strip().rstrip(":")
        if m["bnelbl"] != lbl_name:
            return m.group(0)
        # Emit a pre-loop daddu (initial a0 setup) + nop, then rewrite
        # the loop to use both delay slots usefully.
        daddu = m["daddu"]
        return (
            daddu
            + "\tnop\n"
            + m["lbl"]
            + m["nr1"]
            + m["jal"]
            + m["lw"]
            + m["bne"]
            + daddu
            + m["mr1"]
            + m["blank"]
        )

    new = PATTERN.sub(repl, text, count=1)
    if new == text:
        return False
    path.write_text(new)
    return True


def main(argv: list[str]) -> int:
    if len(argv) != 2:
        print("usage: postprocess_jal_daddu_lw_loop.py <path-to.s>", file=sys.stderr)
        return 2
    path = Path(argv[1])
    if not path.exists():
        return 1
    if patch(path):
        print(f"  jal-daddu-lw-loop: patched {path}")
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv))
