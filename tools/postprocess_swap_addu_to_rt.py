#!/usr/bin/env python3
"""
postprocess_swap_addu_to_rt.py — swap the operand pair on a commutative
`addu` so its rd-register lands in the `rt` slot rather than `rs`.

Inverse of postprocess_swap_addu_operands (which moves rd to rs).
Some ICO functions have the rd==rt form natively but ee-gcc 2.9 emits
the rd==rs form for the same operation. Both compute `dst = a + b`
correctly but differ in encoded bytes.

Pattern (gas asm syntax):

    addu $X, $X, $Y           # rd=X, rs=X, rt=Y (gcc's natural form)

becomes:

    addu $X, $Y, $X           # rd=X, rs=Y, rt=X (target form)

Per-function allowlist in config/swap_addu_to_rt.txt.

Idempotent: only fires on the rd==rs pattern.
"""

from __future__ import annotations

import re
import sys
from pathlib import Path


FUNC_RE = re.compile(r"^\s*(?:glabel|\.ent)\s+(func_[0-9A-Fa-f]+)\b")
END_RE = re.compile(r"^\s*\.end\s+(func_[0-9A-Fa-f]+)\b")
# Match `addu $X, $X, $Y` (rd == rs, rt != rs)
ADDU_RE = re.compile(r"^(\s*)addu\s+\$(\d+),\s*\$(\d+),\s*\$(\d+)\s*$")


def patch(path: Path, allowed: set[str]) -> int:
    if not path.exists():
        return 0
    lines = path.read_text().splitlines(keepends=True)
    out: list[str] = []
    current_func: str | None = None
    fired = 0
    for raw in lines:
        line = raw
        m = FUNC_RE.match(line)
        if m:
            current_func = m.group(1)
            out.append(line)
            continue
        e = END_RE.match(line)
        if e:
            current_func = None
            out.append(line)
            continue
        if current_func is not None and current_func in allowed:
            # Strip trailing newline for regex
            stripped = line.rstrip("\n")
            ma = ADDU_RE.match(stripped)
            if ma and ma.group(2) == ma.group(3) and ma.group(2) != ma.group(4):
                ws, rd, _, rt = ma.group(1), ma.group(2), ma.group(3), ma.group(4)
                new_line = f"{ws}addu\t${rd},${rt},${rd}"
                if line.endswith("\n"):
                    new_line += "\n"
                out.append(new_line)
                fired += 1
                continue
        out.append(line)
    if fired:
        path.write_text("".join(out))
    return fired


def load_allowlist(cfg: Path) -> set[str]:
    allowed: set[str] = set()
    if not cfg.exists():
        return allowed
    for raw in cfg.read_text().splitlines():
        s = raw.split("#", 1)[0].strip()
        if s:
            allowed.add(s)
    return allowed


def main(argv: list[str]) -> int:
    if len(argv) != 2:
        print("usage: postprocess_swap_addu_to_rt.py <path-to.s>", file=sys.stderr)
        return 2
    path = Path(argv[1])
    cfg = Path(__file__).resolve().parent.parent / "config" / "swap_addu_to_rt.txt"
    allowed = load_allowlist(cfg)
    if not allowed:
        return 0
    fired = patch(path, allowed)
    if fired:
        print(f"  swap-addu-to-rt: patched {path} ({fired} edits)")
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv))
