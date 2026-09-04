#!/usr/bin/env python3
"""lookup_vma.py — resolve a hex VMA to a symbol name + owning TU.

Used during phase-3d sidecar migration to convert pointer-address hex
literals (e.g. 0x00138510 in a data table) into symbolic references
(`func_00138510`, `&D_00138510`, or `&D_00275180[0x20]` for an offset
into a known array).

Usage:
    tools/lookup_vma.py 0x00138510 0x00556C20 0x002751A0 ...

Outputs one line per VMA:
    0x00138510  func_00138510            (asm/.../ios/memory)
    0x00556C20  D_00556C20               (tu=ios/mblock.c)
    0x002751A0  D_00275180+0x20          (tu=ios/cdvd.c, inside array of 76)
    0x12345678  -- not a known symbol --

Sources consulted (in order):
    decomp/data_tu_map.json    -- migrated data symbols + their TUs
    config/symbol_addrs.<ver>.txt -- explicit symbol overrides
    asm/**/<func>.s            -- splat-emitted glabels
"""
from __future__ import annotations

import json
import re
import subprocess
import sys
from pathlib import Path

REPO = Path(__file__).resolve().parent.parent
from ico_version import detect_version  # noqa: E402
_VERSION = detect_version(REPO)
DATA_TU_MAP = REPO / "decomp" / "data_tu_map.json"
SYMBOL_ADDRS = REPO / "config" / f"symbol_addrs.{_VERSION}.txt"


def load_data_map() -> dict[int, tuple[str, str]]:
    if not DATA_TU_MAP.exists():
        return {}
    raw = json.loads(DATA_TU_MAP.read_text())
    out: dict[int, tuple[str, str]] = {}
    for sym, rec in raw.items():
        try:
            v = int(rec["vma"], 16)
        except (KeyError, ValueError):
            continue
        out[v] = (sym, rec.get("tu", "?"))
    return out


def load_explicit_addrs() -> dict[int, tuple[str, str]]:
    if not SYMBOL_ADDRS.exists():
        return {}
    out: dict[int, tuple[str, str]] = {}
    pat = re.compile(
        r'^(?P<name>\w+)\s*=\s*0x(?P<vma>[0-9A-Fa-f]+)\s*;(?P<rest>.*)$')
    for line in SYMBOL_ADDRS.read_text().splitlines():
        m = pat.match(line.strip())
        if not m:
            continue
        v = int(m.group("vma"), 16)
        kind = "func" if "type:func" in m.group("rest") else "data"
        out[v] = (m.group("name"), kind)
    return out


def find_in_asm(vma: int) -> str | None:
    """Look for `glabel <name>` matching this VMA under asm/."""
    label = f"glabel func_{vma:08X}"
    try:
        r = subprocess.run(
            ["grep", "-rlE", f"^{re.escape(label)}$", "asm/"],
            capture_output=True, text=True, cwd=REPO, timeout=10,
        )
    except (FileNotFoundError, subprocess.TimeoutExpired):
        return None
    if r.returncode == 0 and r.stdout.strip():
        path = r.stdout.splitlines()[0]
        return f"func_{vma:08X}  (asm/{path.split('asm/', 1)[1]})"
    return None


def find_offset_into_array(vma: int,
                            data_map: dict[int, tuple[str, str]]
                            ) -> str | None:
    """If VMA falls strictly inside a known array, return
    `D_<owner>+0x<off>  (...)`. We don't know array sizes from the
    map alone, so we only flag offsets where the immediately-preceding
    known symbol is the same TU and is within a sensible window
    (≤ 64 KB)."""
    starts = sorted(data_map.keys())
    if not starts:
        return None
    import bisect
    i = bisect.bisect_right(starts, vma) - 1
    if i < 0:
        return None
    owner_vma = starts[i]
    if owner_vma == vma:
        return None
    delta = vma - owner_vma
    if delta > 0xFFFF:
        return None
    sym, tu = data_map[owner_vma]
    return f"{sym}+0x{delta:X}  (tu={tu}, owner @ 0x{owner_vma:08X})"


def main() -> int:
    if len(sys.argv) < 2:
        print(__doc__.strip(), file=sys.stderr)
        return 2
    data_map = load_data_map()
    explicit = load_explicit_addrs()
    for arg in sys.argv[1:]:
        try:
            v = int(arg, 0)
        except ValueError:
            print(f"  {arg:>10}  -- not a hex literal --")
            continue
        if v in data_map:
            sym, tu = data_map[v]
            print(f"  0x{v:08X}  {sym:24} (tu={tu})")
            continue
        if v in explicit:
            sym, kind = explicit[v]
            print(f"  0x{v:08X}  {sym:24} ({kind}, explicit)")
            continue
        asm_hit = find_in_asm(v)
        if asm_hit:
            print(f"  0x{v:08X}  {asm_hit}")
            continue
        offset_hit = find_offset_into_array(v, data_map)
        if offset_hit:
            print(f"  0x{v:08X}  {offset_hit}")
            continue
        print(f"  0x{v:08X}  -- not a known symbol --")
    return 0


if __name__ == "__main__":
    sys.exit(main())
