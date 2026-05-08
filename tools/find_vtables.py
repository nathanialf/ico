#!/usr/bin/env python3
"""
find_vtables.py — locate function-pointer tables in .data / .rodata /
.sdata of `baserom/baseelf.elf`.

A "function-pointer table" here is a run of word-aligned 4-byte values,
each of which is the entry vma of a known function. C tables like

    static int (*acts[])(void *) = { boy_act_idle, boy_act_walk, ... };

emit exactly this shape after compilation. Every entry of the same
table came from the same TU, so a single TU tag on one entry can
propagate to the rest.

This tool is read-only and has zero build impact. It writes a JSON
manifest at `decomp/vtables.json` consumed by `tools/identify_tus.py`.

Run: `.venv/bin/python tools/find_vtables.py [--min-len N]`
"""

from __future__ import annotations

import argparse
import json
import struct
import sys
from pathlib import Path

try:
    from elftools.elf.elffile import ELFFile
except ImportError:
    sys.exit("find_vtables: missing pyelftools.")

REPO_ROOT = Path(__file__).resolve().parent.parent
BASEELF = REPO_ROOT / "baserom" / "baseelf.elf"
OUT_PATH = REPO_ROOT / "decomp" / "vtables.json"

# Sections worth scanning. .data has the most structured tables; .rodata
# tables that splat already migrated into matched functions are gone from
# here (consumed) which is fine. .sdata is small but free to check.
SCAN_SECTIONS = (".data", ".rodata", ".sdata")

# .text vram bounds for sanity-filtering candidates. Outside this range
# is definitely not a function pointer.
TEXT_VMA_LO = 0x00100000
TEXT_VMA_HI = 0x00633C00


def load_function_vrams() -> set[int]:
    """Reuse the asm scanner from identify_tus.py to enumerate every
    function's entry vram. Avoids duplicating the parser."""
    sys.path.insert(0, str(REPO_ROOT / "tools"))
    import identify_tus  # type: ignore[import-not-found]
    anchors: dict[int, str] = {}  # not needed for vram extraction
    funcs = identify_tus.scan_asm(anchors)
    return {f["vram"] for f in funcs if f.get("vram") is not None}


def scan(min_len: int) -> list[dict]:
    if not BASEELF.exists():
        sys.exit(f"find_vtables: {BASEELF} missing")

    funcs = load_function_vrams()
    print(f"find_vtables: {len(funcs)} known function vrams")

    runs: list[dict] = []
    with BASEELF.open("rb") as f:
        elf = ELFFile(f)
        for sec_name in SCAN_SECTIONS:
            sec = elf.get_section_by_name(sec_name)
            if sec is None or sec["sh_size"] == 0:
                continue
            vma = sec["sh_addr"]
            data = sec.data()
            cur: list[tuple[int, int]] = []  # (entry_vma, target_vma)
            for off in range(0, len(data) - 3, 4):
                value = struct.unpack_from("<I", data, off)[0]
                entry_vma = vma + off
                if value in funcs:
                    if cur and entry_vma == cur[-1][0] + 4:
                        cur.append((entry_vma, value))
                    else:
                        if len(cur) >= min_len:
                            runs.append(_finalize(sec_name, cur))
                        cur = [(entry_vma, value)]
                else:
                    if len(cur) >= min_len:
                        runs.append(_finalize(sec_name, cur))
                    cur = []
            if len(cur) >= min_len:
                runs.append(_finalize(sec_name, cur))
    return runs


def _finalize(sec_name: str, run: list[tuple[int, int]]) -> dict:
    return {
        "section": sec_name,
        "vma_start": run[0][0],
        "vma_end": run[-1][0] + 4,
        "count": len(run),
        "entries": [v for _, v in run],
    }


def main() -> int:
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument("--min-len", type=int, default=3,
                   help="minimum consecutive entries to count as a table")
    args = p.parse_args()

    runs = scan(args.min_len)
    runs.sort(key=lambda r: (r["section"], r["vma_start"]))

    OUT_PATH.write_text(json.dumps(runs, indent=2) + "\n")

    print(f"find_vtables: wrote {len(runs)} table(s) to "
          f"{OUT_PATH.relative_to(REPO_ROOT)} "
          f"(min_len={args.min_len})")
    by_section: dict[str, int] = {}
    for r in runs:
        by_section[r["section"]] = by_section.get(r["section"], 0) + 1
    for sec, n in sorted(by_section.items(), key=lambda kv: -kv[1]):
        print(f"  {sec:<10} {n:>5} table(s)")
    if runs:
        sizes = [r["count"] for r in runs]
        print(f"  size: min={min(sizes)} max={max(sizes)} "
              f"median={sorted(sizes)[len(sizes)//2]}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
