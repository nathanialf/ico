#!/usr/bin/env python3
"""
find_callgraph.py — extract caller → callee edges from `asm/cod/*.s`
and `asm/matchings/cod/**/func_*.s`.

Edges captured:
  - direct calls: `jal func_<addr>` or `jal D_<addr>` if the target is a
    known function entry vma.
  - indirect calls via address load: `lui+addiu` to a known function
    entry, followed (in the same function body) by `jalr`. Conservative:
    we don't try to track register flow precisely; we just record any
    `%hi/%lo` reference to a function vram that occurs in a function
    that also contains a `jalr`. False positives here are tolerable —
    downstream propagation requires multi-callee agreement.

Output: `decomp/callgraph.json` — list of
  {caller: vram, callees: [vram, ...], total: N}

Read-only; zero build impact.

Run: `.venv/bin/python tools/find_callgraph.py`
"""

from __future__ import annotations

import json
import re
import sys
from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parent.parent
OUT_PATH = REPO_ROOT / "decomp" / "callgraph.json"
# Read from snapshot to stay isolated from the live matching loop.
ASM_COD_DIR = REPO_ROOT / "decomp" / "asm_snapshot" / "cod"
# Whole matchings/ and nonmatchings/ trees — the snapshot includes
# per-TU subdirs (`matchings/Basic/`, `nonmatchings/src/way_tool/`, …)
# alongside the legacy `cod/<offset>/` layout. rglob picks up every
# func_*.s regardless of nesting.
ASM_MATCHINGS_DIR = REPO_ROOT / "decomp" / "asm_snapshot" / "matchings"
ASM_NONMATCHINGS_DIR = REPO_ROOT / "decomp" / "asm_snapshot" / "nonmatchings"

JAL_RE = re.compile(r"\bjal\s+(?:func_|D_)([0-9A-Fa-f]+)\b")
HI_FUNC_RE = re.compile(r"%hi\((?:func_|D_)([0-9A-Fa-f]+)\)")
JALR_RE = re.compile(r"\bjalr\b")
GLABEL_RE = re.compile(r"^glabel\s+(func_[0-9A-Fa-f]+)\s*$")
ENDLABEL_RE = re.compile(r"^endlabel\s+(func_[0-9A-Fa-f]+)\s*$")
INSN_VRAM_RE = re.compile(r"^\s*/\*\s*[0-9A-Fa-f]+\s+([0-9A-Fa-f]+)\s")


def load_function_vrams() -> set[int]:
    sys.path.insert(0, str(REPO_ROOT / "tools"))
    import identify_tus  # type: ignore[import-not-found]
    funcs = identify_tus.scan_asm({})
    return {f["vram"] for f in funcs if f.get("vram") is not None}


def parse_calls(sfile: Path, func_vrams: set[int],
                edges: list[dict], seen: set[int]) -> None:
    cur_func: str | None = None
    cur_vram: int | None = None
    direct: set[int] = set()
    addr_loads: set[int] = set()
    has_jalr = False

    def flush() -> None:
        nonlocal cur_func, cur_vram, direct, addr_loads, has_jalr
        if cur_func and cur_vram is not None and cur_vram not in seen:
            seen.add(cur_vram)
            callees = set(direct)
            if has_jalr:
                # Indirect call: any `lui+%hi(func_X)` in the same body
                # is a plausible target. Filtered by func_vrams.
                callees |= addr_loads
            edges.append({
                "caller": cur_vram,
                "callees": sorted(callees),
                "total": len(callees),
            })
        cur_func = None
        cur_vram = None
        direct = set()
        addr_loads = set()
        has_jalr = False

    for line in sfile.read_text(errors="ignore").splitlines():
        m = GLABEL_RE.match(line)
        if m:
            flush()
            cur_func = m.group(1)
            continue
        if ENDLABEL_RE.match(line):
            flush()
            continue
        if cur_func is None:
            continue
        if cur_vram is None:
            mv = INSN_VRAM_RE.match(line)
            if mv:
                cur_vram = int(mv.group(1), 16)

        for m in JAL_RE.finditer(line):
            tgt = int(m.group(1), 16)
            if tgt in func_vrams:
                direct.add(tgt)
        for m in HI_FUNC_RE.finditer(line):
            tgt = int(m.group(1), 16)
            if tgt in func_vrams:
                addr_loads.add(tgt)
        if JALR_RE.search(line):
            has_jalr = True
    flush()


def main() -> int:
    func_vrams = load_function_vrams()
    print(f"find_callgraph: {len(func_vrams)} known function vrams")

    edges: list[dict] = []
    seen: set[int] = set()
    if not ASM_COD_DIR.exists():
        sys.exit(f"find_callgraph: {ASM_COD_DIR.relative_to(REPO_ROOT)}/ "
                 "missing — run `tools/snapshot_asm.py` first.")
    # Per-TU dirs (matchings + nonmatchings) FIRST — they're the
    # authoritative current layout. The cod snapshot may still hold
    # older copies of those same vrams; dedup by vram keeps the more
    # specific record.
    for snapshot_dir in (ASM_NONMATCHINGS_DIR, ASM_MATCHINGS_DIR):
        if snapshot_dir.exists():
            for sfile in sorted(snapshot_dir.rglob("func_*.s")):
                parse_calls(sfile, func_vrams, edges, seen)
    for sfile in sorted(ASM_COD_DIR.glob("*.s")):
        parse_calls(sfile, func_vrams, edges, seen)

    edges.sort(key=lambda e: e["caller"])
    OUT_PATH.write_text(json.dumps(edges, indent=2) + "\n")

    total_edges = sum(e["total"] for e in edges)
    funcs_with_calls = sum(1 for e in edges if e["total"] > 0)
    print(f"find_callgraph: {len(edges)} functions, "
          f"{funcs_with_calls} with ≥1 callee, "
          f"{total_edges} total edges")
    print(f"find_callgraph: wrote {OUT_PATH.relative_to(REPO_ROOT)}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
