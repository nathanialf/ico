#!/usr/bin/env python3
"""
postprocess_asm.py — apply R5900-specific fixups to splat-emitted asm.

Splat / spimdisasm sometimes emit mnemonics that the ps2dev binutils
assembler rejects, or that need a `.set noreorder` / `.set nomacro` wrap
to assemble cleanly. This script walks asm/*.s post-split and rewrites
them in place.

Empty at init — fixup rules will be added as splat output meets the
assembler. Entry-point logic is sketched so callers (Makefile,
agents) have a stable hook to extend.
"""

from __future__ import annotations

import sys
from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parent.parent
ASM_DIR = REPO_ROOT / "asm"


def fixup(content: str) -> str:
    """Apply R5900 fixups. Returns the (possibly unchanged) content.

    Add fixup rules here as splat output requires them. Each rule should
    be a small, well-commented transformation — prefer many narrow rules
    over one big regex.
    """
    # Placeholder — no fixups yet. Examples we expect to add later:
    # - re-encoding instructions that ps2dev as rejects as `.word ...`
    # - normalizing MMI mnemonic spelling (paddw / pmaddw / etc.)
    return content


def main() -> int:
    if not ASM_DIR.exists():
        print(f"postprocess_asm: {ASM_DIR} not found (skipping)")
        return 0
    changed = 0
    for s in ASM_DIR.rglob("*.s"):
        original = s.read_text(encoding="utf-8", errors="replace")
        new = fixup(original)
        if new != original:
            s.write_text(new, encoding="utf-8")
            changed += 1
    print(f"postprocess_asm: {changed} file(s) rewritten")
    return 0


if __name__ == "__main__":
    sys.exit(main())
