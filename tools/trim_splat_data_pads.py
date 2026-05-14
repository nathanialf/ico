#!/usr/bin/env python3
"""
Trim trailing "Automatically generated and unreferenced pad" sections
from splat's per-segment data .s files. Splat emits zero-byte/zero-float
sections claiming VMAs past each baseelf data section's actual end —
e.g. .data ends at 0x5536B8 but splat emits zero `.word`s up to 0x553700
to fill the inter-section padding. These spurious sections accumulate
into cod_DATA_END/RODATA_END/LIT4_END, displacing every subsequent
section's VMA and breaking byte-identical link.

Baseelf section boundaries (from `readelf -S baseelf.elf`):
  .data   ends at 0x5536B8
  .rodata ends at 0x6308A8
  .lit4   ends at 0x6318D0
  .sdata  ends at 0x633BC6
The 0x100-aligned `. = ALIGN(.,0x100)` between sections (see
postprocess_ld.py:bump_inter_section_aligns) reproduces the original
linker's padding behavior — but only when splat's spurious pads aren't
already padding the section bigger than baseelf.

Idempotent. Trims:
  asm/data/cod/174700.data.s   past 0x5536B8
  asm/data/cod/453700.rodata.s past 0x6308A8
  asm/data/cod/530900.lit4.s   past 0x6318D0
"""
from __future__ import annotations
import re
import sys
from pathlib import Path

REPO = Path(__file__).resolve().parent.parent

# (file, cutoff_vma_exclusive) — drop everything at or beyond cutoff
TRIMS = [
    (REPO / "asm/data/src/cod/174700.data.s",   0x005536B8),
    (REPO / "asm/data/src/cod/453700.rodata.s", 0x006308A8),
    (REPO / "asm/data/src/cod/530900.lit4.s",   0x006318D0),
]


def trim(path: Path, cutoff: int) -> int:
    if not path.exists():
        return 0
    lines = path.read_text().splitlines()
    blocks: list[list[str]] = []
    header: list[str] = []
    cur: list[str] | None = None
    in_header = True
    for line in lines:
        if line.startswith(".section "):
            in_header = False
            if cur is not None:
                blocks.append(cur)
            cur = [line]
        elif in_header:
            header.append(line)
        else:
            if cur is None:
                cur = []
            cur.append(line)
    if cur is not None:
        blocks.append(cur)

    kept: list[list[str]] = []
    dropped = 0
    for blk in blocks:
        m = re.search(r'\.section\s+"\.[a-z0-9_]+\.0x([0-9A-Fa-f]+)"', blk[0])
        if m:
            vma = int(m.group(1), 16)
            if vma >= cutoff:
                dropped += 1
                continue
        kept.append(blk)

    # Truncate the LAST kept block in-place: drop any per-offset directives
    # whose VMA >= cutoff (i.e. the trailing pad bytes inside the same
    # block whose .section header is before the cutoff).
    if kept:
        last = kept[-1]
        new_last: list[str] = []
        for line in last:
            mm = re.match(
                r'\s*/\*\s+[0-9A-Fa-f]+\s+([0-9A-Fa-f]+)\s+[0-9A-Fa-f]+\s+\*/\s+'
                r'\.(?:word|float|byte|short|double)\b', line)
            if mm:
                line_vma = int(mm.group(1), 16)
                if line_vma >= cutoff:
                    continue
            new_last.append(line)
        kept[-1] = new_last

    new_text = "\n".join(header + sum(kept, [])) + "\n"
    if new_text != path.read_text():
        path.write_text(new_text)
        return 1 + dropped
    return 0


def main() -> int:
    touched = 0
    for path, cutoff in TRIMS:
        n = trim(path, cutoff)
        if n:
            print(f"trim_splat_data_pads: {path.relative_to(REPO)} (cut sections past 0x{cutoff:08X})")
            touched += 1
    if not touched:
        print("trim_splat_data_pads: no changes")
    return 0


if __name__ == "__main__":
    sys.exit(main())
