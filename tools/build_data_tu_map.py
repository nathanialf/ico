#!/usr/bin/env python3
"""
build_data_tu_map.py — assign every data symbol to an owning TU.

For each data symbol in `.sdata`, `.lit4`, `.rodata`, `.data`, decide
which original translation unit (TU) it belongs to so that
`tools/migrate_data_per_tu.py` can emit one C source per TU containing
its data (parappa2-style layout instead of the per-section monolithic
pool .c files).

Assignment algorithm
--------------------
1. For every function in asm/cod/*.s, parse %hi/%lo/%gp_rel references
   to extract the set of data symbols it touches.
2. Look up each function's TU in `decomp/tu_map.json` (the partial
   text-side TU map, ~16.6% tagged). For each (function, symbol)
   reference where the function has a known TU, vote: increment
   `sym_to_tu_votes[sym][tu]`.
3. For each symbol with at least one vote, assign the TU with the
   highest vote count (ties broken by TU name).
4. For symbols with no votes (touched only by untagged functions, or
   not text-referenced at all — most data has no text refs because
   it's internal tables / vtables / strings), assign by VMA proximity:
   walk the sorted symbol list and propagate the most-recent assigned
   TU forward; symbols before the first assigned VMA get a synthetic
   `_unassigned` TU.

The output is `decomp/data_tu_map.json`:

    {
      "D_00631BC0": {"tu": "src/Basic", "method": "vote", "votes": 2},
      "D_00631BCC": {"tu": "src/Basic", "method": "proximity"},
      ...
    }

Re-run after tu_map.json is regenerated or after new text claims add
references that fill in previously-unknown TU ownership.
"""

from __future__ import annotations

import json
import os
import re
import sys
from collections import Counter, defaultdict
from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parent.parent
TU_MAP_JSON = REPO_ROOT / "decomp" / "tu_map.json"
ASM_COD = REPO_ROOT / "asm" / "cod"
ASM_DATA_FILES = [
    REPO_ROOT / "asm" / "data" / "cod" / "531900.sdata.s",
    REPO_ROOT / "asm" / "data" / "cod" / "530900.lit4.s",
    REPO_ROOT / "asm" / "data" / "cod" / "453700.rodata.s",
    REPO_ROOT / "asm" / "data" / "cod" / "174700.data.s",
]
OUT_JSON = REPO_ROOT / "decomp" / "data_tu_map.json"

# Reference patterns in text. Splat emits either:
#   `lui $X, %hi(D_006XXXXX)` ... `... %lo(D_006XXXXX)(...)`
#   `... %gp_rel(D_006XXXXX)($gp)`
# We also match jtbl_<VMA> (jump tables in .rodata) and func_<VMA>
# (function-pointer table entries — useful for data-side relocations
# we want to attribute to a TU).
REF_RE = re.compile(
    r'%(?:hi|lo|gp_rel)\(((?:D_|jtbl_|func_)[0-9A-Fa-f]{8})\)'
)
GLABEL_RE = re.compile(
    r'^glabel\s+(func_[0-9A-Fa-f]{8})', re.MULTILINE
)

# Symbol-block detector for data files (read to enumerate every D_X
# / jtbl_X that needs an assignment).
DATA_DLABEL_RE = re.compile(
    r'^dlabel\s+((?:D_|jtbl_)[0-9A-Fa-f]{8})', re.MULTILINE
)


def _load_func_tu() -> dict[int, str]:
    """Return {func_vma: tu_name} from decomp/tu_map.json."""
    if not TU_MAP_JSON.exists():
        sys.exit(f"build_data_tu_map: missing {TU_MAP_JSON}; run tools/identify_tus.py first.")
    d = json.loads(TU_MAP_JSON.read_text())
    out: dict[int, str] = {}
    for item in d:
        tu = item.get("tu")
        if tu:
            out[item["vram"]] = tu
    return out


def _scan_text_references(func_tu: dict[int, str]) -> dict[str, Counter]:
    """For every (function, symbol) ref where the function has a known
    TU, accumulate `sym_to_tu_votes[sym][tu] += 1`. Symbols only touched
    by untagged functions get no votes here — they'll fall back to
    VMA-proximity assignment in `_propagate_by_proximity`."""
    sym_to_votes: dict[str, Counter] = defaultdict(Counter)
    for path in ASM_COD.glob("*.s"):
        text = path.read_text()
        matches = list(GLABEL_RE.finditer(text))
        for i, m in enumerate(matches):
            func_name = m.group(1)
            vma = int(func_name[5:], 16)
            tu = func_tu.get(vma)
            if not tu:
                continue
            body_start = m.end()
            body_end = (matches[i + 1].start() if i + 1 < len(matches)
                        else len(text))
            for ref in REF_RE.finditer(text[body_start:body_end]):
                sym_to_votes[ref.group(1)][tu] += 1
    return sym_to_votes


def _enumerate_data_symbols() -> list[tuple[str, int]]:
    """Walk every asm/data/cod/*.s data file and collect every dlabel
    name + its VMA, sorted by VMA. We need the full list so we can
    propagate TU assignments through unreferenced symbols by proximity."""
    out: list[tuple[str, int]] = []
    seen: set[str] = set()
    for path in ASM_DATA_FILES:
        if not path.exists():
            continue
        for m in DATA_DLABEL_RE.finditer(path.read_text()):
            sym = m.group(1)
            if sym in seen:
                continue
            seen.add(sym)
            # VMA suffix is the last 8 hex chars of the symbol name.
            vma = int(sym.split("_")[-1], 16)
            out.append((sym, vma))
    out.sort(key=lambda x: x[1])
    return out


def _resolve_by_vote(votes: Counter) -> str:
    """Highest vote count; ties broken alphabetically by TU name."""
    return sorted(votes.items(), key=lambda kv: (-kv[1], kv[0]))[0][0]


def _propagate_by_proximity(
    symbols: list[tuple[str, int]],
    assigned: dict[str, str],
) -> dict[str, str]:
    """For each symbol with no vote-based assignment, copy the most-
    recently-assigned TU as we walk forward in VMA order. Symbols
    before the first assignment get `_unassigned`."""
    out: dict[str, str] = {}
    last_tu = "_unassigned"
    for sym, _vma in symbols:
        if sym in assigned:
            last_tu = assigned[sym]
            out[sym] = last_tu
        else:
            out[sym] = last_tu
    return out


def main() -> int:
    func_tu = _load_func_tu()
    votes = _scan_text_references(func_tu)

    # Phase 1: vote-based assignment.
    vote_assigned: dict[str, str] = {}
    for sym, c in votes.items():
        vote_assigned[sym] = _resolve_by_vote(c)

    # Phase 2: enumerate every data symbol + propagate by proximity.
    symbols = _enumerate_data_symbols()
    final = _propagate_by_proximity(symbols, vote_assigned)

    # Emit JSON with rich metadata.
    out: dict[str, dict] = {}
    for sym, vma in symbols:
        rec = {"vma": f"0x{vma:08X}"}
        if sym in vote_assigned:
            rec["tu"] = vote_assigned[sym]
            rec["method"] = "vote"
            rec["votes"] = dict(votes[sym])
        else:
            rec["tu"] = final[sym]
            rec["method"] = "proximity"
        out[sym] = rec

    OUT_JSON.write_text(json.dumps(out, indent=2, sort_keys=True) + "\n")

    # Summary stats.
    by_tu: Counter = Counter()
    by_method: Counter = Counter()
    for rec in out.values():
        by_tu[rec["tu"]] += 1
        by_method[rec["method"]] += 1
    print(f"build_data_tu_map: {len(out)} symbols assigned across "
          f"{len(by_tu)} TUs.")
    print(f"  method=vote:      {by_method['vote']}")
    print(f"  method=proximity: {by_method['proximity']}")
    print(f"  largest TUs:")
    for tu, n in by_tu.most_common(10):
        print(f"    {n:6d}  {tu}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
