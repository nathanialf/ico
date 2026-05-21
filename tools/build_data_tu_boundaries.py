#!/usr/bin/env python3
"""
build_data_tu_boundaries.py — derive per-TU contiguous section ranges
from `decomp/data_tu_map.json`.

Output `decomp/data_tu_boundaries.json` shape:

    {
      "src/DmaPacket.c": {
        ".sdata": {
          "promotable": true,
          "ranges": [
            {"lo_vma": "0x00632014", "hi_vma": "0x00632018",
             "lo_off": "0x00532014", "hi_off": "0x00532018",
             "symbols": ["D_00632014"]}
          ]
        }
      }
    }

A TU's section is **promotable** when all its symbols in that section
form one contiguous range with no foreign-TU symbols interleaved. A
promotable section can be lifted out of the SORT_BY_NAME catch-all
into a per-TU subsegment in splat YAML (Phase 3c) and have its typed
defs use plain `.X` section attributes for `%gp_rel` codegen
(Phase 3d).

Non-promotable sections have foreign symbols mixed in; those stay in
the SORT_BY_NAME catch-all until the foreign symbols are reattributed
or the TU is split.
"""

from __future__ import annotations

import json
import re
from collections import defaultdict
from pathlib import Path

REPO = Path(__file__).resolve().parent.parent
DATA_TU_MAP = REPO / "decomp" / "data_tu_map.json"
OUT_PATH = REPO / "decomp" / "data_tu_boundaries.json"

# Tracked typed-def regex: __attribute__((section(".X.0xVMA"))) ... D_X.
# Captures: section name (group 1), VMA (group 2), symbol (group 3).
TYPED_SYM_RE = re.compile(
    r'__attribute__\(\(section\("\.(\w+)\.0x([0-9A-Fa-f]+)"\)\)\)'
    r'\s+(?:[\w\s\*]+?)\s+(D_[0-9A-Fa-f]{8})\b'
)

# Phase 3d-stripped plain-form typed def. Matches at line start (no
# attr prefix), excludes `extern`, requires a type token before D_X,
# and anchors on `=` so in-function writes don't qualify. Captures: D_X.
PLAIN_SYM_RE = re.compile(
    r'(?m)^(?!\s*extern\b)[ \t]*'
    r'(?:[A-Za-z_]\w*\s+)+'
    r'\**\s*'
    r'(D_[0-9A-Fa-f]{8})\b\s*(?:\[[^\]]*\])*\s*='
)


def _scan_tracked_sources() -> tuple[dict[str, str], dict[tuple[str, str], int]]:
    """Walk tracked src/{src,ios,sound,isys}/**/*.{c,h} and return:
      (sym_to_tu, attr_counts)
    where:
      sym_to_tu[D_X] = "src/<TU>.c" for every typed def found (both
      attr-tagged AND plain-form post-Phase 3d strip),
      attr_counts[(tu, ".X")] = number of attr-tagged defs in TU/section.

    Plain-form defs contribute to `sym_to_tu` so the TU still owns
    its symbols after attr-tag strip, but don't increment attr_counts
    (the `stripped` flag downstream needs zero attr-tagged defs).

    `_data.c` sidecars are skipped (auto-generated, not authoritative)."""
    sym_to_tu: dict[str, str] = {}
    attr_counts: dict[tuple[str, str], int] = {}
    for root_name in ("src", "ios", "sound", "isys"):
        root_dir = REPO / root_name
        if not root_dir.is_dir():
            continue
        for ext in ("*.c", "*.h"):
            for path in root_dir.rglob(ext):
                if path.name.endswith("_data.c"):
                    continue
                try:
                    text = path.read_text()
                except Exception:
                    continue
                rel = str(path.relative_to(REPO))
                # Headers attribute to their sibling .c TU.
                if rel.endswith(".h"):
                    rel = rel[:-2] + ".c"
                # Attr-tagged defs: contribute to both sym_to_tu and attr_counts.
                for m in TYPED_SYM_RE.finditer(text):
                    sec_name = "." + m.group(1)
                    sym_to_tu[m.group(3)] = rel
                    attr_counts[(rel, sec_name)] = (
                        attr_counts.get((rel, sec_name), 0) + 1
                    )
                # Plain-form defs (Phase 3d-stripped): contribute to
                # sym_to_tu only. Existing attr-tagged binding (if
                # the symbol is somehow both, e.g. typed first then
                # stripped) wins via the second `if` below.
                for m in PLAIN_SYM_RE.finditer(text):
                    sym = m.group(1)
                    if sym not in sym_to_tu:
                        sym_to_tu[sym] = rel
    return sym_to_tu, attr_counts


def _scan_typed_attributions() -> dict[str, str]:
    """Backward-compatible shim — returns sym_to_tu only."""
    sym_to_tu, _ = _scan_tracked_sources()
    return sym_to_tu


def _tu_to_opath(tu: str) -> str | None:
    """src/DmaPacket.c → build/src/DmaPacket.o. Returns None for synthetic
    TU keys (_unassigned, etc.) that don't correspond to a real source."""
    if not tu.endswith(".c"):
        return None
    if tu.startswith("_") or "/" not in tu:
        return None
    return f"build/{tu[:-2]}.o"

# VMA ranges per section, mirroring tools/migrate_data_per_tu.py +
# the bss/sbss asm files.
SECTION_RANGES = [
    (".data",   0x00274700, 0x005536B8),
    (".rodata", 0x00553700, 0x006308A8),
    (".lit4",   0x00630900, 0x006318D0),
    (".sdata",  0x00631900, 0x00633BC6),
    (".sbss",   0x00633C00, 0x00634000),
    (".bss",    0x00634000, 0x0071EB52),
]
LOAD_BASE = 0x00100000


def _section_for_vma(vma: int) -> str | None:
    for sec, lo, hi in SECTION_RANGES:
        if lo <= vma < hi:
            return sec
    return None


def main() -> int:
    if not DATA_TU_MAP.exists():
        raise SystemExit(
            f"build_data_tu_boundaries: missing {DATA_TU_MAP}; "
            "run tools/build_data_tu_map.py first."
        )
    sym_to_tu_voted = json.loads(DATA_TU_MAP.read_text())
    typed_attribs, attr_counts = _scan_tracked_sources()

    # Build authoritative TU map. Tracked typed defs override votes:
    # a symbol typed in src/DmaPacket.c belongs to DmaPacket TU even
    # if data_tu_map's vote-based heuristic places it elsewhere.
    sym_to_tu: dict[str, str] = {}
    for sym, info in sym_to_tu_voted.items():
        sym_to_tu[sym] = info.get("tu", "_unassigned")
    for sym, tu in typed_attribs.items():
        sym_to_tu[sym] = tu

    # Sort all symbols by VMA so we can detect interleaving.
    syms_sorted: list[tuple[int, str, str]] = []
    for sym, tu in sym_to_tu.items():
        try:
            vma = int(sym.split("_")[-1], 16)
        except ValueError:
            continue
        syms_sorted.append((vma, sym, tu))
    syms_sorted.sort()

    # Group by (TU, section) and walk to extract contiguous runs.
    # A run starts at a TU's first symbol in a section and ends at the
    # next foreign-TU symbol in the same section.
    per_tu_sec_runs: dict[tuple[str, str], list[list[tuple[int, str]]]] = defaultdict(list)
    # Walk per section so we don't accidentally bridge across boundaries.
    for sec_name, sec_lo, sec_hi in SECTION_RANGES:
        cur_tu: str | None = None
        cur_run: list[tuple[int, str]] = []
        for vma, sym, tu in syms_sorted:
            if vma < sec_lo or vma >= sec_hi:
                continue
            if tu != cur_tu:
                if cur_tu is not None and cur_run:
                    per_tu_sec_runs[(cur_tu, sec_name)].append(cur_run)
                cur_tu = tu
                cur_run = []
            cur_run.append((vma, sym))
        if cur_tu is not None and cur_run:
            per_tu_sec_runs[(cur_tu, sec_name)].append(cur_run)

    # Compute hi_vma for each run by finding the next symbol after the
    # last one in the run (regardless of TU). The hi_vma is "exclusive
    # end": the VMA where the run stops. For the very last symbol in a
    # section, hi_vma is the section's hi.
    sym_idx = {sym: i for i, (vma, sym, tu) in enumerate(syms_sorted)}

    def _hi_vma(last_sym: str, section_hi: int) -> int:
        """VMA at which this symbol's coverage ends — next symbol's VMA
        in the same section, or section_hi if last symbol."""
        i = sym_idx[last_sym]
        for j in range(i + 1, len(syms_sorted)):
            v, _, _ = syms_sorted[j]
            if v >= section_hi:
                return section_hi
            return v
        return section_hi

    # Build the output structure.
    by_tu: dict[str, dict[str, dict]] = defaultdict(dict)
    for (tu, sec), runs in per_tu_sec_runs.items():
        sec_hi = next(h for n, _, h in SECTION_RANGES if n == sec)
        out_runs = []
        for run in runs:
            lo_vma = run[0][0]
            hi_vma = _hi_vma(run[-1][1], sec_hi)
            out_runs.append({
                "lo_vma": f"0x{lo_vma:08X}",
                "hi_vma": f"0x{hi_vma:08X}",
                "lo_off": f"0x{lo_vma - LOAD_BASE:08X}",
                "hi_off": f"0x{hi_vma - LOAD_BASE:08X}",
                "symbols": [s for _, s in run],
            })
        # Promotable iff exactly one contiguous run owns the entire
        # range (no foreign-TU symbols in between any of this TU's
        # symbols in this section).
        promotable = len(out_runs) == 1
        # `stripped` is true when this TU's tracked source has zero
        # __attribute__((section(".<sec>.0x..."))) defs in this
        # section. Phase 3d's slot generator uses this to decide
        # whether to emit a per-TU plain `<o>(.<sec>*)` slot (stripped)
        # or one explicit slot per typed `.<sec>.0xVMA` section.
        stripped = attr_counts.get((tu, sec), 0) == 0
        entry: dict = {
            "promotable": promotable,
            "stripped": stripped,
            "ranges": out_runs,
        }
        opath = _tu_to_opath(tu)
        if opath is not None:
            entry["o_path"] = opath
        by_tu[tu][sec] = entry

    # Sort TUs alphabetically; sort sections in the canonical order.
    sec_order = {n: i for i, (n, _, _) in enumerate(SECTION_RANGES)}
    out: dict[str, dict] = {}
    for tu in sorted(by_tu):
        secs = by_tu[tu]
        out[tu] = {sec: secs[sec] for sec in sorted(secs, key=sec_order.get)}

    OUT_PATH.write_text(json.dumps(out, indent=2) + "\n")

    # Summary stats.
    tot_tus = len(out)
    tot_sec_entries = sum(len(s) for s in out.values())
    promotable = sum(1 for s in out.values() for v in s.values() if v["promotable"])
    print(f"build_data_tu_boundaries: {tot_tus} TUs across {tot_sec_entries} TU-sections")
    print(f"  promotable (single contiguous run): {promotable}")
    print(f"  not yet promotable (foreign syms interleaved): "
          f"{tot_sec_entries - promotable}")
    stripped_count = sum(1 for s in out.values() for v in s.values() if v.get("stripped"))
    print(f"  stripped (no attr-tagged defs in tracked source): {stripped_count}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
