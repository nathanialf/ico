#!/usr/bin/env python3
"""
postprocess_asm.py — apply post-split fixups to splat-emitted asm.

Splat 0.40.0 has a few known mis-emissions on the ICO ELF that we patch
here so the round-trip is byte-identical:

  1. .sdata ends mid-string. The .sdata section size is 0x22C6 (not 4-byte
     aligned), and splat rounds the last data symbol down to a .word, so
     the trailing two bytes ("E\0", completing the asciz "FALSE\0") at
     0x00633BC4 are dropped. We patch the .sdata.s tail to emit those
     two bytes.

Future R5900-mnemonic / VU-asm fixups would also live here.

Idempotent — run as part of `make setup` after `splat split`.
"""

from __future__ import annotations

import re
import sys
from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parent.parent

# (path, sentinel, replacement, reason)
SDATA_TAIL_FIX = (
    REPO_ROOT / "asm" / "data" / "cod" / "531900.sdata.s",
    re.compile(
        r"^(?P<head>dlabel D_00633BC0\n"
        r"\s*/\*\s*533BC0\s+00633BC0\s+46414C53\s*\*/\s*\.word\s+0x534C4146)\s*\n"
        r"(?P<tail>enddlabel D_00633BC0\b)",
        re.MULTILINE,
    ),
    # Replace the lone .word with: .word + 2-byte tail (".byte 0x45, 0x00").
    # GNU as accepts that combination cleanly inside a section.
    "{head}\n    /* 533BC4 00633BC4 4500     */ .byte 0x45, 0x00\n{tail}",
    "splat sdata-tail truncation (0x22C6 size, last 2 bytes dropped)",
)


def patch_sdata_tail() -> int:
    path, pat, repl, reason = SDATA_TAIL_FIX
    if not path.exists():
        return 0
    text = path.read_text()
    if "/* 533BC4 00633BC4" in text:
        return 0  # already patched
    m = pat.search(text)
    if m is None:
        # Splat output may have changed shape — surface this as a failure
        # so the round-trip mismatch doesn't get silently re-introduced.
        print(
            f"postprocess_asm: WARN — could not locate the splat-truncated "
            f"D_00633BC0 .word in {path.relative_to(REPO_ROOT)} "
            f"({reason!r}); .rom may not round-trip.",
            file=sys.stderr,
        )
        return 0
    new = text[: m.start()] + repl.format(head=m.group("head"), tail=m.group("tail")) + text[m.end():]
    path.write_text(new)
    return 1


def main() -> int:
    changed = 0
    changed += patch_sdata_tail()
    print(f"postprocess_asm: {changed} file(s) rewritten")
    return 0


if __name__ == "__main__":
    sys.exit(main())
