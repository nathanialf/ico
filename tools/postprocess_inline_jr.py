#!/usr/bin/env python3
"""
postprocess_inline_jr.py — strip compiler-added `j $31` epilogue when
an inline-asm block already returned via `jr $31`.

Why: ee-gcc 2.96 doesn't honour __attribute__((naked)). For the
la-macro-with-jr-delay-slot family (FE08, B748, 14B358, 244738, …)
we need the function body to end with `jr $31; <something>` where
the something fills the delay slot. We can write this in inline asm,
but the compiler always appends its own `j $31` (and possibly stack
restore) afterwards, inflating the function size.

When the inline-asm block ends with `jr $31` and the function has
no stack frame (`.frame $sp,0,$31`), the compiler-emitted epilogue
is unreachable code that still occupies bytes. Strip it.

Pattern detected:
    .frame $sp,0,$31  ...   ← no-frame marker
    ...
    #APP
    ...
    jr $31            ← inline-asm return
    <delay slot>
    #NO_APP
    j $31             ← compiler's redundant return
    .end <funcname>

Action: remove the `j $31` line. The assembler would otherwise add
a nop in its delay slot (`.set reorder` default) — and that nop is
also unwanted, but since it's implicit it disappears with the `j $31`
removal.

Idempotent. Does nothing on .s files that don't match the pattern.
"""

from __future__ import annotations

import re
import sys
from pathlib import Path

# Match a complete function body in the .s file. Functions look like:
#   .ent <name>
#   <name>:
#       ...
#   .end <name>
FUNC_RE = re.compile(
    r"(\t\.ent\t(?P<name>\S+)\n.*?\t\.end\t(?P=name)\n)",
    re.DOTALL,
)

# Inside a function body, detect the no-frame + inline-asm-return + redundant-j shape.
NO_FRAME_RE = re.compile(r"^\s*\.frame\s+\$sp,0,\$31", re.MULTILINE)

# Detect the inline-asm block ending with a terminating jump — either
# `jr $31` (return), `jr $reg` (computed jump), or `j label` (tail
# call). We look for it inside an #APP/#NO_APP pair, optionally
# followed by a delay-slot instruction. If the block terminates this
# way, the compiler's appended `j $31` is unreachable and safe to
# strip from a no-frame function.
INLINE_TERMINATING_RE = re.compile(
    r"\s\#APP\s*\n(?:.*\n)*?\s*(?:jr\s+\$\w+|j\s+\w+)\b[^\n]*\n(?:[^#]*\n)?\s\#NO_APP\s*\n",
)

# The compiler-emitted j $31 (with optional `.set noreorder/.set nomacro`
# wrappers and optional delay slot) right after #NO_APP. Strip the line
# if it's a bare `j $31` at the function's end (just before `.end`).
TRAILING_J_RE = re.compile(
    r"(\s\#NO_APP\s*\n)"           # group 1: the NO_APP marker
    r"\tj\t\$31\s*\n"               # the redundant unconditional jump
    r"(\t\.end\t\S+\s*\n)"          # group 2: the .end directive
)


def fix_function(body: str) -> tuple[str, bool]:
    """Return (new_body, changed). Only patches no-frame functions whose
    inline-asm block returns via `jr $31`."""
    if not NO_FRAME_RE.search(body):
        return body, False
    if not INLINE_TERMINATING_RE.search(body):
        return body, False
    new = TRAILING_J_RE.sub(r"\1\2", body)
    return new, new != body


def patch_file(path: Path) -> bool:
    text = path.read_text()
    out_parts: list[str] = []
    last = 0
    changed_any = False
    for m in FUNC_RE.finditer(text):
        out_parts.append(text[last : m.start()])
        body, ch = fix_function(m.group(1))
        out_parts.append(body)
        last = m.end()
        if ch:
            changed_any = True
    out_parts.append(text[last:])
    if changed_any:
        path.write_text("".join(out_parts))
    return changed_any


def main(argv: list[str]) -> int:
    if len(argv) != 2:
        print("usage: postprocess_inline_jr.py <src.s>", file=sys.stderr)
        return 2
    p = Path(argv[1])
    if not p.exists():
        print(f"postprocess_inline_jr: no such file: {p}", file=sys.stderr)
        return 3
    patch_file(p)
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv))
