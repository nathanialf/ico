#!/usr/bin/env python3
"""
postprocess_bne_to_bnel.py — convert specific `bne $X, $Y, $L` into
`bnel $X, $Y, $L` (branch likely) instructions.

ee-gcc 2.9 picks bne vs bnel via its own heuristic; flipping the C
condition (== vs !=) doesn't reliably change its choice (see
feedback_branch_likely_emission). Some original ICO functions use the
likely variant where our gcc emits the regular form. When the
delay-slot operation is safe to squash on the not-taken path (typical
"reload for next iteration"), a postprocess can simply convert bne to
bnel.

Per-file allowlist in config/bne_to_bnel.txt. Entries are
`<func_name>` or `<func_name>:<line_offset_within_func>` — one per
line; '#' starts a comment.

Idempotent: only fires on `bne ...` lines for listed funcs.
"""

from __future__ import annotations

import re
import sys
from pathlib import Path


# Match: glabel func_NNNN (splat-emitted) OR .ent func_NNNN (gcc-emitted)
FUNC_RE = re.compile(r"^\s*(?:glabel|\.ent)\s+(func_[0-9A-Fa-f]+)\b")
# Also detect end of function via .end func_NNNN
END_RE = re.compile(r"^\s*\.end\s+(func_[0-9A-Fa-f]+)\b")
# Match: bne ... (capture leading whitespace + 'bne' + the rest)
BNE_RE = re.compile(r"^(\s*)bne(\s+.*)$")
BEQ_RE = re.compile(r"^(\s*)beq(\s+.*)$")


def patch(path: Path, allowed: set[str]) -> int:
    """Convert bne→bnel and beq→beql for funcs in `allowed`.

    Each entry can be `<func>` (apply to ALL bne/beq in func) or
    `<func>:bne` / `<func>:beq` (only that mnemonic).
    """
    if not path.exists():
        return 0
    lines = path.read_text().splitlines(keepends=True)
    out: list[str] = []
    current_func: str | None = None
    fired = 0
    for line in lines:
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
        if current_func is not None and (
            current_func in allowed
            or f"{current_func}:bne" in allowed
            or f"{current_func}:beq" in allowed
        ):
            mb = BNE_RE.match(line)
            if mb and (current_func in allowed or f"{current_func}:bne" in allowed):
                out.append(f"{mb.group(1)}bnel{mb.group(2)}\n" if not mb.group(2).endswith("\n") else f"{mb.group(1)}bnel{mb.group(2)}")
                fired += 1
                continue
            mq = BEQ_RE.match(line)
            if mq and (current_func in allowed or f"{current_func}:beq" in allowed):
                out.append(f"{mq.group(1)}beql{mq.group(2)}\n" if not mq.group(2).endswith("\n") else f"{mq.group(1)}beql{mq.group(2)}")
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
        print("usage: postprocess_bne_to_bnel.py <path-to.s>", file=sys.stderr)
        return 2
    path = Path(argv[1])
    cfg = Path(__file__).resolve().parent.parent / "config" / "bne_to_bnel.txt"
    allowed = load_allowlist(cfg)
    if not allowed:
        return 0
    fired = patch(path, allowed)
    if fired:
        print(f"  bne→bnel: patched {path} ({fired} edits)")
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv))
