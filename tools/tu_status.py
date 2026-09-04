#!/usr/bin/env python3
"""
tu_status.py — per-TU completion across .text/.data/.rodata/.lit4/.sdata.

For each known translation unit, report:

* **text**: # of functions in the TU's vram range that are matched (have
  a `c` YAML entry with a backing `src/<...>.c` file) vs total functions.
* **data**: for each non-text section, # of symbols owned by the TU that
  are typed in a tracked `src/<TU>.c` (or other non-`_data.c` source)
  vs symbols still in the auto-generated `src/<TU>_data.c` sidecar
  (raw byte arrays / single-element typed defs from baserom).

A TU is "complete" iff every section is at 100% — i.e., every function
is matched and zero data symbols remain in the sidecar.

TU sources
----------
* `decomp/tu_map.json` / `decomp/tu_map.md` — function-to-TU mapping
  (only ~15% of functions are tagged at the moment).
* `decomp/data_tu_map.json` — data-symbol-to-TU mapping (every D_/jtbl_).
* `config/ico.<ver>.yaml` — which subsegments are claimed (`c`) vs `asm`.
* `src/<TU>.c` / `src/<TU>_data.c` — tracked typed defs vs auto sidecar.

Usage:
    .venv/bin/python tools/tu_status.py            # full table
    .venv/bin/python tools/tu_status.py --complete # only fully-done TUs
    .venv/bin/python tools/tu_status.py --top 20   # closest-to-done first
"""

from __future__ import annotations

import argparse
import json
import re
import sys
from collections import Counter, defaultdict
from pathlib import Path

try:
    import yaml
except ImportError:
    sys.exit("tu_status: missing PyYAML. Run `.venv/bin/pip install pyyaml`.")

REPO_ROOT = Path(__file__).resolve().parent.parent
from ico_version import detect_version  # noqa: E402
_VERSION = detect_version(REPO_ROOT)
YAML = REPO_ROOT / "config" / f"ico.{_VERSION}.yaml"
TU_MAP_JSON = REPO_ROOT / "decomp" / "tu_map.json"
TU_MAP_MD = REPO_ROOT / "decomp" / "tu_map.md"
DATA_TU_MAP = REPO_ROOT / "decomp" / "data_tu_map.json"
# Splat YAML subseg names are now repo-root-relative (e.g.
# `src/cod/000110`, `src/Basic`, `ios/cdvd`). Resolve from REPO_ROOT.
SRC_DIR = REPO_ROOT

SECTION_TO_TYPES = {
    ".text":   {"asm", "c", "hasm"},
    ".data":   {"data"},
    ".rodata": {"rodata"},
    ".lit4":   {"lit4"},
    ".sdata":  {"sdata"},
}
MATCHABLE_TYPES = {"c", "hasm"}

# VMA ranges per section, from tools/migrate_data_per_tu.py + the bss/sbss
# asm files. Used to classify a symbol's section by its VMA.
SECTION_VMA_RANGES = [
    (".data",   0x00274700, 0x005536B8),
    (".rodata", 0x00553700, 0x006308A8),
    (".lit4",   0x00630900, 0x006318D0),
    (".sdata",  0x00631900, 0x00633BC6),
    (".sbss",   0x00633C00, 0x00634000),
    (".bss",    0x00634000, 0x0071EB52),
]
DATA_SECTIONS = [s for s, _, _ in SECTION_VMA_RANGES]


def _section_for_vma(vma: int) -> str | None:
    for sec, lo, hi in SECTION_VMA_RANGES:
        if lo <= vma < hi:
            return sec
    return None


# Sidecar lines emitted by tools/migrate_data_per_tu.py — any remaining
# definition with this attribute is a non-decompiled raw symbol.
# (migrate_data_per_tu.py only emits .data/.rodata/.lit4/.sdata; .sbss/.bss
# stay in asm/data/cod/ and are tracked via data_tu_map.json.)
SIDECAR_DEF_RE = re.compile(
    r'__attribute__\(\(section\("\.(data|rodata|lit4|sdata|sbss|bss)\.0x([0-9A-Fa-f]+)"\)\)\)'
)


def _walk_subsegments(yaml_doc: dict) -> list[tuple[int, str, str]]:
    out: list[tuple[int, str, str]] = []
    for seg in yaml_doc.get("segments", []):
        if isinstance(seg, list):
            continue
        for sub in seg.get("subsegments", []):
            if isinstance(sub, list):
                if len(sub) < 2:
                    continue
                offset = sub[0]
                stype = sub[1]
                name = sub[2] if len(sub) >= 3 else ""
            elif isinstance(sub, dict):
                offset = sub.get("vram", 0)
                stype = sub.get("type", "")
                name = sub.get("name", "")
            else:
                continue
            out.append((offset, stype, name))
    return out


def _src_exists(name: str, stype: str) -> bool:
    if stype == "hasm":
        return (SRC_DIR / f"{name}.s").exists()
    return (SRC_DIR / f"{name}.c").exists()


def _load_yaml_text_subs() -> list[tuple[int, str, str, bool]]:
    """Return (file_off, stype, name, matched) for every text subsegment
    (asm / c / hasm). `matched` is true iff stype in {c,hasm} and the
    backing src file exists.
    """
    doc = yaml.safe_load(YAML.read_text())
    subs = _walk_subsegments(doc)
    out = []
    for off, stype, name in subs:
        if stype not in SECTION_TO_TYPES[".text"]:
            continue
        matched = stype in MATCHABLE_TYPES and bool(name) and _src_exists(name, stype)
        out.append((off, stype, name, matched))
    return out


_NM_DIR_RE = re.compile(r'INCLUDE_ASM\s*\(\s*"[^"]*/nonmatchings/([^"]+)"\s*,\s*func_([0-9A-Fa-f]+)')


def _load_include_asm_vmas() -> set[int]:
    """Scan tracked C files for `INCLUDE_ASM(...nonmatchings/<dir>", func_<VMA>)`
    invocations. Those funcs are NOT C-source matched even though their
    c-subseg owns them — they're the placeholder for unmatched funcs in
    a partially-coalesced TU (Basic.c-style). Tu_status should treat
    them as unmatched."""
    out: set[int] = set()
    for root_name in ("src", "ios", "sound", "isys"):
        root_dir = REPO_ROOT / root_name
        if not root_dir.is_dir():
            continue
        for src_path in root_dir.rglob("*.c"):
            if src_path.name.endswith("_data.c"):
                continue
            try:
                text = src_path.read_text()
            except Exception:
                continue
            for m in _NM_DIR_RE.finditer(text):
                try:
                    out.add(int(m.group(2), 16))
                except ValueError:
                    pass
    return out


def _load_tu_func_map() -> dict[int, str]:
    """vram -> TU for every function that's been tagged in tu_map.json."""
    if not TU_MAP_JSON.exists():
        return {}
    d = json.loads(TU_MAP_JSON.read_text())
    out: dict[int, str] = {}
    for f in d:
        if f.get("tu"):
            out[f["vram"]] = f["tu"]
    return out


# Tag-source precedence in identify_tus.py — strongest first.
TAG_SOURCE_ORDER = (
    "path", "anchor", "bracket", "vtable", "callgraph",
    "data", "revcg", "slice_vote", "bracket_inferred",
)


def _load_tu_tag_sources() -> dict[int, str]:
    """vram -> tag_source (e.g. 'path', 'anchor', 'bracket', ...)
    for every tagged function in tu_map.json. Returns {} when
    tu_map.json is missing."""
    if not TU_MAP_JSON.exists():
        return {}
    d = json.loads(TU_MAP_JSON.read_text())
    out: dict[int, str] = {}
    for f in d:
        if f.get("tu") and f.get("tag_source"):
            out[f["vram"]] = f["tag_source"]
    return out


def _load_all_func_vmas() -> list[int]:
    """Sorted list of every function vma from tu_map.json. Unlike the
    YAML (where unmatched funcs collapse into giant `asm` blobs),
    tu_map.json has one entry per function from `decomp/callgraph.json`,
    so it's the authoritative function set for text counting."""
    if not TU_MAP_JSON.exists():
        return []
    d = json.loads(TU_MAP_JSON.read_text())
    return sorted(f["vram"] for f in d if "vram" in f)


# tu_map.md row format:
# | 0xVMA_LO | 0xVMA_HI | 0xSIZE | `src/foo.c` | A | B | T |
TU_REGION_RE = re.compile(
    r"^\|\s*0x([0-9a-fA-F]+)\s*\|\s*0x([0-9a-fA-F]+)\s*\|\s*0x[0-9a-fA-F]+\s*"
    r"\|\s*`([^`]+)`\s*\|"
)


def _load_tu_regions() -> dict[str, tuple[int, int]]:
    """Read tu_map.md for vram_start..vram_end per TU. Falls back to
    empty if the file is missing."""
    out: dict[str, tuple[int, int]] = {}
    if not TU_MAP_MD.exists():
        return out
    in_region = False
    for line in TU_MAP_MD.read_text().splitlines():
        if line.startswith("## TU regions"):
            in_region = True
            continue
        if in_region and line.startswith("## "):
            break
        if not in_region:
            continue
        m = TU_REGION_RE.match(line)
        if m:
            lo = int(m.group(1), 16)
            hi = int(m.group(2), 16)
            tu = m.group(3)
            # Keep widest range if a TU has multiple region rows.
            if tu in out:
                lo0, hi0 = out[tu]
                lo, hi = min(lo, lo0), max(hi, hi0)
            out[tu] = (lo, hi)
    return out


def _load_data_tu_map() -> dict[str, str]:
    """sym -> TU. Auto-generated by build_data_tu_map.py."""
    if not DATA_TU_MAP.exists():
        return {}
    d = json.loads(DATA_TU_MAP.read_text())
    return {sym: info["tu"] for sym, info in d.items()}


def _scan_sidecar(path: Path) -> dict[str, int]:
    """Count remaining auto-generated definitions per section in a
    sidecar file. Returns {section: count}."""
    counts: dict[str, int] = Counter()
    if not path.exists():
        return counts
    for m in SIDECAR_DEF_RE.finditer(path.read_text()):
        counts["." + m.group(1)] += 1
    return counts


# Same pattern as SIDECAR_DEF_RE but also captures the symbol name.
TYPED_SYM_RE = re.compile(
    r'__attribute__\(\(section\("\.(?P<sect>data|rodata|lit4|sdata|sbss|bss)\.0x([0-9A-Fa-f]+)"\)\)\)'
    r'\s+(?:[\w\s\*]+?)\s+(?P<sym>D_[0-9A-Fa-f]{8})\b'
)


def _scan_typed_defs_per_tu(tu_files: dict[str, Path]) -> tuple[dict[str, dict[str, int]], set[str]]:
    """For each TU's tracked `src/<TU>.c` (and per-TU `src/<TU>.h` if it
    exists), count typed section-attributed defs. These are symbols the
    user has already moved out of the sidecar / asm.

    Returns (counts_per_tu, all_typed_symbols). The symbol set lets
    callers exclude already-typed entries from the `data_tu_map.json`
    todo bucket — that map is generated from full asm before the
    rewriter strips typed defs out, so it lists every symbol including
    typed ones."""
    out: dict[str, dict[str, int]] = {}
    typed_syms: set[str] = set()
    # Walk every source root: src/, plus the original ICO sibling
    # subsystems ios/, sound/, isys/ (relocated to repo root). Scan any
    # non-`_data.c` source for typed defs — typed symbols owned by
    # another TU still need to be excluded from `todo` counts globally
    # (a typed def in src/Basic.c counts for Basic, but also means the
    # symbol is "done" wherever data_tu_map says it lives).
    src_paths: list = []
    for root_name in ("src", "ios", "sound", "isys"):
        root_dir = REPO_ROOT / root_name
        if root_dir.is_dir():
            src_paths += list(root_dir.rglob("*.c"))
    for src_path in src_paths:
        if src_path.name.endswith("_data.c"):
            continue
        for m in TYPED_SYM_RE.finditer(src_path.read_text()):
            typed_syms.add(m.group("sym"))
    h_paths: list = []
    for root_name in ("src", "ios", "sound", "isys"):
        root_dir = REPO_ROOT / root_name
        if root_dir.is_dir():
            h_paths += list(root_dir.rglob("*.h"))
    for src_path in h_paths:
        for m in TYPED_SYM_RE.finditer(src_path.read_text()):
            typed_syms.add(m.group("sym"))
    for tu, src in tu_files.items():
        counts: dict[str, int] = Counter()
        for path in (src, src.with_suffix(".h")):
            if path.exists():
                for m in SIDECAR_DEF_RE.finditer(path.read_text()):
                    counts["." + m.group(1)] += 1
        out[tu] = counts
    return out, typed_syms


def _tu_filename(tu: str) -> Path:
    """`src/Basic.c` (TU id) -> `<repo>/src/Basic.c`,
    `ios/cdvd.c` -> `<repo>/ios/cdvd.c`. TU strings already
    include the `src/` prefix in tu_map.json / data_tu_map.json."""
    return REPO_ROOT / (tu if tu.endswith(".c") else tu + ".c")


def _tu_sidecar(tu: str) -> Path:
    p = _tu_filename(tu)
    return p.with_name(p.stem + "_data.c")


def compute_tu_status() -> list[dict]:
    # Inputs
    text_subs = _load_yaml_text_subs()
    func_tu = _load_tu_func_map()
    func_tag_source = _load_tu_tag_sources()
    tu_regions = _load_tu_regions()
    data_tu = _load_data_tu_map()
    all_vmas = _load_all_func_vmas()
    include_asm_vmas = _load_include_asm_vmas()

    # All TUs known to the system.
    all_tus: set[str] = set()
    all_tus.update(func_tu.values())
    all_tus.update(tu_regions.keys())
    all_tus.update(data_tu.values())

    # Bucket data symbols by TU.
    sym_by_tu: dict[str, list[str]] = defaultdict(list)
    for sym, tu in data_tu.items():
        sym_by_tu[tu].append(sym)

    # Build sorted intervals from YAML text subsegs. Each interval
    # records (vma, matched, name, stype) so we can answer two
    # questions per function:
    #   matched   — is the containing subseg `c`/`hasm` with a backing src?
    #   coalesced — is the containing subseg's `name` equal to the TU
    #               stem (e.g. `src/DmaPacket` for TU `src/DmaPacket.c`)?
    # A subseg covers [vma_i, vma_{i+1}); the lookup handles both
    # per-function `cod/<offset>` claims and coalesced `c, <TU>` claims
    # that span multiple functions.
    VRAM_BASE = 0x00100000
    intervals = sorted([
        (off + VRAM_BASE, matched, name, stype)
        for (off, stype, name, matched) in text_subs
    ])
    _vmas_sorted = [iv[0] for iv in intervals]

    def _interval_for(vma: int):
        import bisect
        i = bisect.bisect_right(_vmas_sorted, vma) - 1
        if i < 0:
            return None
        return intervals[i]

    def _is_matched(vma: int) -> bool:
        if vma in include_asm_vmas:
            return False
        iv = _interval_for(vma)
        return bool(iv and iv[1])

    def _tu_stem(tu: str) -> str:
        return tu[:-2] if tu.endswith(".c") else tu

    def _is_coalesced(vma: int, tu: str) -> bool:
        """True iff the YAML subseg covering `vma` is a matched `c`
        claim whose name equals the TU's stem path (i.e. the function
        is compiled out of the TU's own `.c`, not a per-function
        `src/cod/<hex>.c`)."""
        iv = _interval_for(vma)
        if iv is None:
            return False
        _, matched, name, stype = iv
        return matched and stype == "c" and name == _tu_stem(tu)

    # Text counts: for each TU with a region, every callgraph vma in
    # [lo, hi] counts; matched if it has a `c` YAML claim with a backing
    # src file. TUs without regions but with per-function tags get just
    # their tagged vmas.
    text_total: dict[str, int] = Counter()
    text_matched: dict[str, int] = Counter()
    text_coalesced: dict[str, int] = Counter()
    # Approximate per-TU sum of instructions in still-unmatched funcs:
    # size(func) = (next_vma - this_vma); insns = size/4. Tells us
    # whether a TU's unmatched funcs are 4-insn wrappers or 200-insn
    # state machines — more honest than function counts for target
    # selection.
    unmatched_insns: dict[str, int] = Counter()
    _sorted_vmas = sorted(all_vmas)
    _vma_pos = {v: i for i, v in enumerate(_sorted_vmas)}
    def _insns_at(vma: int) -> int:
        i = _vma_pos.get(vma)
        if i is None or i + 1 >= len(_sorted_vmas):
            return 0
        return max(0, (_sorted_vmas[i + 1] - vma) // 4)

    tagged_addrs_by_tu: dict[str, set[int]] = defaultdict(set)
    for vma, tu in func_tu.items():
        tagged_addrs_by_tu[tu].add(vma)

    for tu, (lo, hi) in tu_regions.items():
        for vma in all_vmas:
            if vma < lo or vma > hi:
                continue
            text_total[tu] += 1
            if _is_matched(vma):
                text_matched[tu] += 1
            else:
                unmatched_insns[tu] += _insns_at(vma)
            if _is_coalesced(vma, tu):
                text_coalesced[tu] += 1

    for tu, addrs in tagged_addrs_by_tu.items():
        if tu in tu_regions:
            continue
        for vma in addrs:
            text_total[tu] += 1
            if _is_matched(vma):
                text_matched[tu] += 1
            else:
                unmatched_insns[tu] += _insns_at(vma)
            if _is_coalesced(vma, tu):
                text_coalesced[tu] += 1

    # Data: typed defs in tracked <TU>.c (done) vs symbols still in
    # asm/data/cod (todo, tracked via data_tu_map.json — which now
    # includes .sbss and .bss). The sidecar `_data.c` is just the
    # generated mirror of "what's still in asm for this TU" for the
    # four initialized sections — we use data_tu_map directly so the
    # accounting works uniformly for .sbss/.bss too.
    tu_files = {tu: _tu_filename(tu) for tu in all_tus}
    typed, typed_syms = _scan_typed_defs_per_tu(tu_files)

    # Bucket remaining (untyped) symbols by (TU, section). Skip any
    # symbol that's already typed anywhere in tracked src/ — those are
    # done; data_tu_map still lists them because it's built from full
    # asm before the rewriter strips typed defs.
    todo_by_tu_sec: dict[str, dict[str, int]] = defaultdict(lambda: Counter())
    for sym, tu in data_tu.items():
        if sym in typed_syms:
            continue
        # VMA suffix is the last 8 hex chars of the symbol name.
        try:
            vma = int(sym.split("_")[-1], 16)
        except ValueError:
            continue
        sec = _section_for_vma(vma)
        if sec is None:
            continue
        todo_by_tu_sec[tu][sec] += 1

    # Per-TU tag-source counts (which identify_tus.py pass tagged each
    # function — path / anchor / bracket / data / slice_vote / ...).
    tag_sources_by_tu: dict[str, Counter] = defaultdict(Counter)
    for vma, tu in func_tu.items():
        src = func_tag_source.get(vma)
        if src:
            tag_sources_by_tu[tu][src] += 1

    rows: list[dict] = []
    for tu in sorted(all_tus):
        tt = text_total.get(tu, 0)
        tm = text_matched.get(tu, 0)
        tc = text_coalesced.get(tu, 0)
        tp = typed.get(tu, {})
        td = todo_by_tu_sec.get(tu, {})
        sec_data = {}
        for sec in DATA_SECTIONS:
            done = tp.get(sec, 0)
            todo = td.get(sec, 0)
            sec_data[sec] = (done, done + todo)
        data_done = sum(d for d, _ in sec_data.values())
        data_total = sum(t for _, t in sec_data.values())
        complete = (
            tt > 0
            and tm == tt
            and (data_total == 0 or data_done == data_total)
        )
        # "Fully coalesced" = every attributed function is compiled
        # out of the TU's own .c (not via a per-function
        # src/cod/<hex>.c). Strictly tighter than `complete`, since
        # `complete` accepts matched-anywhere.
        fully_coalesced = tt > 0 and tc == tt
        rows.append({
            "tu": tu,
            "text_matched": tm,
            "text_total": tt,
            "text_coalesced": tc,
            "unmatched_insns": unmatched_insns.get(tu, 0),
            "data_done": data_done,
            "data_total": data_total,
            "sections": sec_data,
            "complete": complete,
            "fully_coalesced": fully_coalesced,
            "tag_sources": dict(tag_sources_by_tu.get(tu, {})),
        })
    return rows


def _pct(n: int, d: int) -> str:
    if d == 0:
        return "  —  "
    return f"{100.0 * n / d:5.1f}%"


def _fmt_section(done: int, total: int) -> str:
    if total == 0:
        return "    —"
    return f"{done:3d}/{total:<3d}"


def main(argv: list[str]) -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--complete", action="store_true",
                    help="show only TUs that are fully complete")
    ap.add_argument("--top", type=int, default=0,
                    help="show only the N closest-to-complete TUs")
    ap.add_argument("--min-funcs", type=int, default=0,
                    help="hide TUs with fewer than N tagged functions")
    ap.add_argument("--hide-coalesced", action="store_true",
                    help="hide TUs where every attributed function is "
                         "already compiled out of the TU's own .c "
                         "(strictly tighter than --complete; useful "
                         "for spotting what's left to coalesce)")
    ap.add_argument("--json", action="store_true",
                    help="emit JSON instead of a table")
    ap.add_argument("--tag-sources", action="store_true",
                    help="show per-TU tag-source breakdown from "
                         "identify_tus.py (path / anchor / bracket / "
                         "vtable / callgraph / data / revcg / "
                         "slice_vote / bracket_inferred) instead of "
                         "the text/data completion table")
    args = ap.parse_args(argv)

    rows = compute_tu_status()

    if args.complete:
        rows = [r for r in rows if r["complete"]]
    if args.hide_coalesced:
        rows = [r for r in rows if not r["fully_coalesced"]]
    if args.min_funcs:
        rows = [r for r in rows if r["text_total"] >= args.min_funcs]

    if args.top:
        # Distance from complete: # remaining unmatched-text + remaining-data.
        def remaining(r):
            return (r["text_total"] - r["text_matched"]) + (r["data_total"] - r["data_done"])
        rows.sort(key=lambda r: (
            0 if r["complete"] else 1,
            remaining(r),
            -r["text_total"],
            r["tu"],
        ))
        rows = rows[:args.top]

    if args.json:
        print(json.dumps(rows, indent=2))
        return 0

    if args.tag_sources:
        # Per-TU tag-source breakdown view. Surfaces how each function's
        # TU assignment was inferred (path/anchor/bracket/...) so a
        # reader can tell which TUs rest on authoritative signals vs.
        # weaker inference (bracket_inferred at the bottom of the chain).
        cols = TAG_SOURCE_ORDER
        # Abbreviate long source names for the header.
        short = {"bracket": "brkt", "vtable": "vt", "callgraph": "cg",
                 "slice_vote": "slc_v", "bracket_inferred": "brkt_i",
                 "anchor": "anch", "path": "path", "data": "data",
                 "revcg": "revcg"}
        hdr = (f"{'TU':<40} {'total':>6}  "
               + "".join(f" {short[c]:>7}" for c in cols))
        # Filter to TUs that have at least one tagged function.
        srows = [r for r in rows if r.get("tag_sources")]
        srows.sort(key=lambda r: (-sum(r["tag_sources"].values()),
                                  r["tu"]))
        print(hdr)
        print("-" * len(hdr))
        global_total = Counter()
        for r in srows:
            ts = r["tag_sources"]
            total = sum(ts.values())
            cells = [f" {ts.get(c, 0) or '':>7}" for c in cols]
            print(f"{r['tu']:<40} {total:>6}  " + "".join(cells))
            for k, v in ts.items():
                global_total[k] += v
        print("-" * len(hdr))
        gtot = sum(global_total.values())
        print(f"{'TOTAL':<40} {gtot:>6}  "
              + "".join(f" {global_total.get(c, 0):>7}" for c in cols))
        print()
        print(f"{len(srows)} TUs with at least one tagged function. "
              f"Source precedence (strongest first): "
              + " > ".join(cols))
        return 0

    # Table. `text` = functions matched anywhere; `coal` = functions
    # specifically compiled out of the TU's own .c (subset of text);
    # `uninsn` = approximate sum of instructions in still-unmatched
    # funcs (size derived from next-vma deltas).
    cols = ["text", "coal", "uninsn", "data", ".data", ".rodata", ".lit4",
            ".sdata", ".sbss", ".bss"]
    hdr = f"{'TU':<46}" + "".join(f" {c:>9}" for c in cols) + "  done?"
    print(hdr)
    print("-" * len(hdr))
    for r in rows:
        s = r["sections"]
        ui = r["unmatched_insns"]
        ui_s = f"{ui:>9}" if ui else "        —"
        print(f"{r['tu']:<46} "
              f"{_fmt_section(r['text_matched'], r['text_total']):>9} "
              f"{_fmt_section(r['text_coalesced'], r['text_total']):>9} "
              f"{ui_s} "
              f"{_fmt_section(r['data_done'], r['data_total']):>9} "
              f"{_fmt_section(*s['.data']):>9} "
              f"{_fmt_section(*s['.rodata']):>9} "
              f"{_fmt_section(*s['.lit4']):>9} "
              f"{_fmt_section(*s['.sdata']):>9} "
              f"{_fmt_section(*s['.sbss']):>9} "
              f"{_fmt_section(*s['.bss']):>9}  "
              f"{'✔' if r['complete'] else ''}")

    if not args.complete:
        n_done = sum(1 for r in rows if r["complete"])
        n_coal = sum(1 for r in rows if r["fully_coalesced"])
        print(f"\n{n_done} / {len(rows)} TUs complete, "
              f"{n_coal} fully coalesced")
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
