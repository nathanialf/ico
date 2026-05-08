#!/usr/bin/env python3
"""
find_unnamed_tus.py — partition `.text` into TU-shaped slices using
synthetic_nop boundary markers, then surface slices we haven't named.

Reads:
  - `decomp/callgraph.json`  (authoritative function vram set)
  - `decomp/boundaries.json` (synthetic_nop / gap markers)
  - `decomp/tu_map.md`       (optional; supplies TU tags if present)

Each `synthetic_nop` boundary is a lone-nop padding function the linker
inserted between two TUs — strong evidence a TU boundary sits there.
Slicing the function set at every such boundary partitions `.text` into
candidate TU regions. Cross-referencing with TU tags from `tu_map.md`
(if available) marks each slice as named, partly-named, or fully
unnamed.

Output: `decomp/unnamed_tus.md`.

Read-only; consumes only existing artifacts. No snapshot needed; works
even when `asm/cod/` is empty.

Run: `.venv/bin/python tools/find_unnamed_tus.py`
"""

from __future__ import annotations

import json
import re
import sys
from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parent.parent
TU_MAP_JSON = REPO_ROOT / "decomp" / "tu_map.json"
TU_MAP_MD = REPO_ROOT / "decomp" / "tu_map.md"
BOUNDARIES_JSON = REPO_ROOT / "decomp" / "boundaries.json"
CALLGRAPH_JSON = REPO_ROOT / "decomp" / "callgraph.json"
MATCHINGS_DIR = REPO_ROOT / "decomp" / "asm_snapshot" / "matchings" / "cod"
OUT_PATH = REPO_ROOT / "decomp" / "unnamed_tus.md"

# Function listing row format from tu_map.md.
ROW_RE = re.compile(
    r"^\|\s*0x([0-9a-fA-F]+)\s*"
    r"\|\s*`(func_[0-9A-Fa-f]+)`\s*"
    r"\|\s*`([^`]+)`\s*"
    r"\|\s*([✓\s]*?)\s*"
    r"\|\s*(.+?)\s*"
    r"\|\s*(\w+|—)\s*"
    r"\|\s*(\d+)\s*\|\s*$",
    re.MULTILINE,
)


def parse_tu_cell(cell: str) -> str | None:
    cell = cell.strip()
    if cell == "(none)":
        return None
    m = re.search(r"`([^`]+)`", cell)
    return m.group(1) if m else None


def load_function_vrams_with_tags() -> dict[int, str | None]:
    """Authoritative vram set from callgraph.json; tags preferentially
    from tu_map.json (machine-readable sidecar), falling back to
    parsing tu_map.md if the JSON isn't present yet. Functions absent
    from both but present in callgraph.json get tag=None."""
    if not CALLGRAPH_JSON.exists():
        sys.exit(f"find_unnamed_tus: "
                 f"{CALLGRAPH_JSON.relative_to(REPO_ROOT)} missing — "
                 "run `tools/find_callgraph.py` first.")
    edges = json.loads(CALLGRAPH_JSON.read_text())
    by_vram: dict[int, str | None] = {e["caller"]: None for e in edges}

    if TU_MAP_JSON.exists():
        rows = json.loads(TU_MAP_JSON.read_text())
        for row in rows:
            by_vram[row["vram"]] = row.get("tu")
        print(f"find_unnamed_tus: loaded tags for {len(rows)} functions "
              f"from {TU_MAP_JSON.relative_to(REPO_ROOT)}")
    elif TU_MAP_MD.exists():
        text = TU_MAP_MD.read_text()
        n_md = 0
        for m in ROW_RE.finditer(text):
            vram = int(m.group(1), 16)
            tu = parse_tu_cell(m.group(5))
            by_vram[vram] = tu
            n_md += 1
        print(f"find_unnamed_tus: parsed {n_md} tagged-function rows "
              f"from {TU_MAP_MD.relative_to(REPO_ROOT)} "
              "(tu_map.json absent; consider re-running identify_tus)")
    else:
        print("find_unnamed_tus: no tu_map.{json,md} — slices will be "
              "reported without TU tags")

    return by_vram


def load_matched_vrams() -> set[int]:
    """vrams of every function that has a per-function .s in the asm
    snapshot's matchings/ tree — i.e. functions claimed `c` in the
    YAML and being driven by the matching pipeline."""
    out: set[int] = set()
    if not MATCHINGS_DIR.exists():
        return out
    for p in MATCHINGS_DIR.rglob("func_*.s"):
        m = re.match(r"func_([0-9A-Fa-f]+)\.s", p.name)
        if m:
            out.add(int(m.group(1), 16))
    return out


def find_slices(by_vram: dict[int, str | None],
                boundaries: list[dict],
                matched_vrams: set[int]) -> list[dict]:
    """Slice `.text` at every `synthetic_nop` boundary. We do NOT use
    `gap` boundaries here: in this binary every gap is exactly 4 bytes
    (routine inter-function alignment), so they don't distinguish TU
    boundaries from same-TU function boundaries. synthetic_nop is the
    only reliable boundary signal we can extract from asm; regions
    with no synthetic_nop padding inside (e.g. when consecutive TUs
    happen to align cleanly without padding) appear as one large slice
    that other signals — callgraph clustering, jumptables — would have
    to subdivide later."""
    funcs = sorted(by_vram.items(), key=lambda kv: kv[0])
    sn_boundaries = sorted(b["vma"] for b in boundaries
                           if b["kind"] == "synthetic_nop")
    if not sn_boundaries:
        return []

    bounds = ([funcs[0][0]] + sn_boundaries
              + [funcs[-1][0] + 0x10000])

    slices: list[dict] = []
    for i in range(len(bounds) - 1):
        lo, hi = bounds[i], bounds[i + 1]
        if lo >= hi:
            continue
        members = [(v, t) for v, t in funcs if lo <= v < hi]
        if not members:
            continue
        tagged = [(v, t) for v, t in members if t]
        untagged = [(v, t) for v, t in members if not t]
        tu_set = {t for _, t in tagged}
        matched_in_slice = sum(1 for v, _ in members if v in matched_vrams)
        slices.append({
            "vram_start": lo,
            "vram_end": hi,
            "size": hi - lo,
            "members": members,
            "tagged_count": len(tagged),
            "untagged_count": len(untagged),
            "matched_count": matched_in_slice,
            "tu_set": tu_set,
        })
    return slices


def render(slices: list[dict]) -> str:
    fully_unnamed = [s for s in slices
                     if s["tagged_count"] == 0
                     and s["untagged_count"] >= 1]
    partly = [s for s in slices
              if s["tagged_count"] >= 1
              and s["untagged_count"] >= 1
              and len(s["tu_set"]) >= 1]
    multi_tu = [s for s in slices if len(s["tu_set"]) >= 2]
    clean = [s for s in slices
             if s["tagged_count"] >= 1
             and s["untagged_count"] == 0
             and len(s["tu_set"]) == 1]

    lines = [
        "# Unnamed TU candidates",
        "",
        "Generated by `tools/find_unnamed_tus.py`. Each candidate is a",
        "vram region delimited by `synthetic_nop` boundary markers — lone",
        "padding-nop functions the linker inserted between two TUs. The",
        "presence of those markers is strong evidence a TU boundary sits",
        "there, even when no `__FILE__` anchor lets us name it.",
        "",
        f"**Slices total:** {len(slices)}",
        f"- {len(clean)} cleanly-named (one TU, no untagged members)",
        f"- {len(partly)} partly-named (some untagged members in a "
        "tagged slice; bracket-fill candidates)",
        f"- {len(multi_tu)} multi-TU (boundary cuts inside an inlined "
        "or shared region)",
        f"- {len(fully_unnamed)} fully-unnamed (boundary-delimited "
        "but no TU evidence at all — highest priority for new anchors)",
        "",
        "## Fully-unnamed TU candidates",
        "",
        "Vram regions where boundary markers say a TU lives but no",
        "anchor evidence has surfaced. The **matched** column shows how",
        "many functions in the slice are already claimed `c` in the YAML",
        "(via the active matching pipeline) — high matched% means naming",
        "this slice would *not* displace in-progress matching work.",
        "Sorted by size — large regions have the most leverage if named.",
        "",
        "| vram_start | vram_end | size | funcs | matched | match% | first vram | last vram |",
        "| ---: | ---: | ---: | ---: | ---: | ---: | ---: | ---: |",
    ]

    for s in sorted(fully_unnamed, key=lambda s: -s["size"])[:80]:
        first_v = s["members"][0][0]
        last_v = s["members"][-1][0]
        n = len(s["members"])
        m = s["matched_count"]
        pct = (100 * m / n) if n else 0
        lines.append(
            f"| 0x{s['vram_start']:08x} | 0x{s['vram_end']:08x} | "
            f"0x{s['size']:x} | {n} | {m} | {pct:.0f}% | "
            f"0x{first_v:08x} | 0x{last_v:08x} |"
        )
    if len(fully_unnamed) > 80:
        lines.append(f"| … | _{len(fully_unnamed)-80} more_ | | | | | | |")

    if partly:
        lines.extend([
            "",
            "## Partly-named TU candidates",
            "",
            "Slices with both tagged and untagged members — bracket-fill",
            "or callgraph-propagation should pick these up next.",
            "",
            "| vram_start | vram_end | TU(s) | tagged | untagged |",
            "| ---: | ---: | --- | ---: | ---: |",
        ])
        for s in sorted(partly, key=lambda s: -s["size"])[:40]:
            tus = ", ".join(f"`{t}`" for t in sorted(s["tu_set"]))
            lines.append(
                f"| 0x{s['vram_start']:08x} | 0x{s['vram_end']:08x} | "
                f"{tus} | {s['tagged_count']} | "
                f"{s['untagged_count']} |"
            )

    if multi_tu:
        lines.extend([
            "",
            "## Multi-TU slices (review)",
            "",
            "Boundary cuts inside a region claimed by two or more TUs —",
            "either inlining across TUs (header-defined helpers) or a",
            "spurious boundary marker. Worth manual review.",
            "",
            "| vram_start | vram_end | TUs |",
            "| ---: | ---: | --- |",
        ])
        for s in sorted(multi_tu, key=lambda s: -s["size"])[:30]:
            tus = ", ".join(f"`{t}`" for t in sorted(s["tu_set"]))
            lines.append(
                f"| 0x{s['vram_start']:08x} | 0x{s['vram_end']:08x} | "
                f"{tus} |"
            )

    return "\n".join(lines) + "\n"


def main() -> int:
    if not BOUNDARIES_JSON.exists():
        sys.exit(f"find_unnamed_tus: "
                 f"{BOUNDARIES_JSON.relative_to(REPO_ROOT)} missing — "
                 "run `tools/find_boundaries.py` first.")
    by_vram = load_function_vrams_with_tags()
    boundaries = json.loads(BOUNDARIES_JSON.read_text())
    matched_vrams = load_matched_vrams()

    print(f"find_unnamed_tus: {len(by_vram)} function vrams loaded")
    print(f"find_unnamed_tus: {len(boundaries)} boundary markers loaded")
    print(f"find_unnamed_tus: {len(matched_vrams)} matched function "
          "vrams loaded")

    slices = find_slices(by_vram, boundaries, matched_vrams)

    fully_unnamed = sum(1 for s in slices
                        if s["tagged_count"] == 0
                        and s["untagged_count"] >= 1)
    multi = sum(1 for s in slices if len(s["tu_set"]) >= 2)
    partly = sum(1 for s in slices
                 if s["tagged_count"] >= 1
                 and s["untagged_count"] >= 1)
    print(f"find_unnamed_tus: {len(slices)} slices total")
    print(f"  fully-unnamed: {fully_unnamed}")
    print(f"  partly-named:  {partly}")
    print(f"  multi-TU:      {multi}")

    OUT_PATH.write_text(render(slices))
    print(f"find_unnamed_tus: wrote {OUT_PATH.relative_to(REPO_ROOT)}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
