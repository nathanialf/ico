#!/usr/bin/env python3
"""
identify_tus.py — map functions to original ICO translation units (TUs).

Reads the anchor table from `decomp/source_tree/` (each placeholder
records the rodata vma of its `__FILE__` literal), scans every function
in `decomp/asm_snapshot/` for `%hi(D_<vma>)` references to those
anchors, and emits a sorted address-ordered list of `(func, vram,
tu_tags)`. Bracketing, vtable, and callgraph propagation passes extend
the tag set conservatively.

Reads from `decomp/asm_snapshot/`, never live `asm/`. Refresh the
snapshot via `tools/snapshot_asm.py` when matching is in a quiet
window — analyzer reads stay isolated from the active matching loop.

Inputs:
  - `decomp/source_tree/`        (anchor placeholders)
  - `decomp/asm_snapshot/`       (asm files; from `snapshot_asm.py`)
  - `decomp/vtables.json`        (optional; from `find_vtables.py`)
  - `decomp/callgraph.json`      (optional; from `find_callgraph.py`)
  - `decomp/boundaries.json`     (optional; from `find_boundaries.py`)

Output:
  - `decomp/tu_map.md`

Idempotent.

Run: `.venv/bin/python tools/identify_tus.py`
"""

from __future__ import annotations

import json
import re
import sys
from collections import defaultdict
from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parent.parent
TREE_ROOT = REPO_ROOT / "decomp" / "source_tree"
# Read from the asm snapshot, not live `asm/` — the active matching
# loop periodically clears `asm/cod/*.s`. Run `tools/snapshot_asm.py`
# once when matching is in a quiet window.
ASM_COD_DIR = REPO_ROOT / "decomp" / "asm_snapshot" / "cod"
ASM_MATCHINGS_DIR = REPO_ROOT / "decomp" / "asm_snapshot" / "matchings" / "cod"
TU_MAP_OUT = REPO_ROOT / "decomp" / "tu_map.md"
TU_MAP_JSON = REPO_ROOT / "decomp" / "tu_map.json"
VTABLES_JSON = REPO_ROOT / "decomp" / "vtables.json"
CALLGRAPH_JSON = REPO_ROOT / "decomp" / "callgraph.json"
BOUNDARIES_JSON = REPO_ROOT / "decomp" / "boundaries.json"

PLACEHOLDER_RE = re.compile(
    r"/\*\s*placeholder:\s*(\S+)\s+—\s+__FILE__ anchor at "
    r"\.rodata\s+0x([0-9a-fA-F]+)"
)
HI_RE = re.compile(r"%hi\(D_([0-9A-Fa-f]{8})\)")
GLABEL_RE = re.compile(r"^glabel\s+(func_[0-9A-Fa-f]+)\s*$")
ENDLABEL_RE = re.compile(r"^endlabel\s+(func_[0-9A-Fa-f]+)\s*$")
INSN_VRAM_RE = re.compile(r"^\s*/\*\s*[0-9A-Fa-f]+\s+([0-9A-Fa-f]+)\s")


def load_anchors() -> dict[int, str]:
    """Parse placeholder one-liners under `decomp/source_tree/` and return
    {anchor_vma: original_path}."""
    anchors: dict[int, str] = {}
    if not TREE_ROOT.exists():
        sys.exit(f"identify_tus: {TREE_ROOT} missing — run "
                 "tools/build_source_tree.py first.")
    for p in TREE_ROOT.rglob("*"):
        if not p.is_file() or p.name == "README.md":
            continue
        text = p.read_text(errors="ignore")
        m = PLACEHOLDER_RE.search(text)
        if not m:
            continue
        path, vma_hex = m.group(1), m.group(2)
        vma = int(vma_hex, 16)
        anchors[vma] = path
    return anchors


def _parse_asm_file(sfile: Path, anchors: dict[int, str],
                    results: list[dict], seen_vrams: set[int],
                    source_tag: str) -> None:
    """Parse one .s file; append discovered functions to `results`.
    Flushes on `endlabel` or end-of-file. Skips functions whose vram is
    already in `seen_vrams` (dedup across segment + matchings trees)."""
    cur_func: str | None = None
    cur_vram: int | None = None
    cur_tags: dict[str, int] = defaultdict(int)

    def flush() -> None:
        nonlocal cur_func, cur_vram, cur_tags
        if cur_func and cur_vram is not None and cur_vram not in seen_vrams:
            seen_vrams.add(cur_vram)
            results.append({
                "name": cur_func,
                "vram": cur_vram,
                "file": sfile.name,
                "source": source_tag,
                "tags": dict(cur_tags),
                "total_refs": sum(cur_tags.values()),
            })
        cur_func = None
        cur_vram = None
        cur_tags = defaultdict(int)

    for line in sfile.read_text(errors="ignore").splitlines():
        mglabel = GLABEL_RE.match(line)
        if mglabel:
            flush()
            cur_func = mglabel.group(1)
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
        for m in HI_RE.finditer(line):
            vma = int(m.group(1), 16)
            if vma in anchors:
                cur_tags[anchors[vma]] += 1
    flush()


def scan_asm(anchors: dict[int, str]) -> list[dict]:
    """Walk every per-function and segment-level .s file under `asm/`,
    returning {name, vram, file, source, tags, total_refs} for each
    distinct function. `source` is 'cod' for unmatched-segment files,
    'matchings' for per-function matched files. Dedup is by vram."""
    results: list[dict] = []
    seen: set[int] = set()
    if not ASM_COD_DIR.exists():
        sys.exit(f"identify_tus: {ASM_COD_DIR.relative_to(REPO_ROOT)}/ "
                 "missing — run `tools/snapshot_asm.py` first "
                 "(when matching loop is between cycles).")
    # Segment files first — they're the bulk and the format with explicit
    # endlabels. Matched functions don't appear here.
    for sfile in sorted(ASM_COD_DIR.glob("*.s")):
        _parse_asm_file(sfile, anchors, results, seen, source_tag="cod")
    # Per-function matched files. One function per file, no endlabel —
    # flush() runs on EOF too. Adds matched functions to the population.
    if ASM_MATCHINGS_DIR.exists():
        for sfile in sorted(ASM_MATCHINGS_DIR.rglob("func_*.s")):
            _parse_asm_file(sfile, anchors, results, seen,
                            source_tag="matchings")
    return results


def best_tag(f: dict) -> str | None:
    if not f["tags"]:
        return None
    return max(f["tags"].items(), key=lambda kv: kv[1])[0]


def bracket_untagged(funcs: list[dict]) -> None:
    """In-place: assign `bracket_tu` to each untagged function whose vram
    sits between two anchor-tagged functions of the *same* TU. Does not
    touch directly-tagged functions; pure inference."""
    funcs.sort(key=lambda f: f["vram"] or 0)
    n = len(funcs)
    # Forward sweep: nearest preceding anchor tag.
    prev_tag: list[str | None] = [None] * n
    cur: str | None = None
    for i, f in enumerate(funcs):
        if f["tags"]:
            cur = best_tag(f)
        prev_tag[i] = cur
    # Backward sweep: nearest following anchor tag.
    next_tag: list[str | None] = [None] * n
    cur = None
    for i in range(n - 1, -1, -1):
        f = funcs[i]
        if f["tags"]:
            cur = best_tag(f)
        next_tag[i] = cur
    # Assign bracket tag where prev == next and the function isn't already
    # directly tagged.
    for i, f in enumerate(funcs):
        f["bracket_tu"] = None
        if f["tags"]:
            continue
        if prev_tag[i] is not None and prev_tag[i] == next_tag[i]:
            f["bracket_tu"] = prev_tag[i]


def vtable_propagate(funcs: list[dict]) -> int:
    """If `decomp/vtables.json` exists, propagate TU tags across each
    table: for each table, if any entry is anchor- or bracket-tagged,
    apply that tag to entries that have no tag at all. Sets
    `vtable_tu` on newly-tagged functions. Returns the count of new
    tags assigned."""
    if not VTABLES_JSON.exists():
        return 0
    tables = json.loads(VTABLES_JSON.read_text())
    by_vram: dict[int, dict] = {f["vram"]: f for f in funcs if f.get("vram")}
    n_new = 0
    for table in tables:
        # For each entry, find its current tag (anchor preferred over
        # bracket; ignore prior vtable_tu — single pass).
        tags_seen: dict[str, int] = defaultdict(int)
        members: list[dict] = []
        for vma in table["entries"]:
            f = by_vram.get(vma)
            if not f:
                continue
            members.append(f)
            tag = best_tag(f) or f.get("bracket_tu")
            if tag:
                tags_seen[tag] += 1
        if not tags_seen:
            continue  # nothing to propagate from
        # Pick the dominant tag. If split, use majority; tie → skip
        # (signal of cross-TU table, don't auto-decide).
        ranked = sorted(tags_seen.items(), key=lambda kv: -kv[1])
        if len(ranked) >= 2 and ranked[0][1] == ranked[1][1]:
            continue
        winner = ranked[0][0]
        for f in members:
            if f["tags"] or f.get("bracket_tu") or f.get("vtable_tu"):
                continue
            f["vtable_tu"] = winner
            n_new += 1
    return n_new


def callgraph_propagate(funcs: list[dict], min_callers: int = 2) -> int:
    """Tag untagged functions whose tagged callers agree on a single TU.

    Callee → caller direction is strong because private helpers are
    called only from within their own TU. Public utilities (called by
    many TUs) self-filter: callers disagree → rule rejects.

    Sets `callgraph_tu` on newly-tagged functions. Returns count.
    Strict: requires `min_callers` distinct tagged callers all agreeing
    on the same TU; ignores any caller already tagged via callgraph
    (single-pass, no transitive amplification of weak signal).

    Proximity guard: refuse to tag a callee whose VMA sits closer to a
    DIFFERENT TU's nearest anchor than to the proposed TU's. Without
    this, a public-ish helper that gets called from one TU but lives
    in another TU's text region picks up the caller's TU label and
    poisons the migration boundary."""
    if not CALLGRAPH_JSON.exists():
        return 0
    edges = json.loads(CALLGRAPH_JSON.read_text())
    by_vram: dict[int, dict] = {f["vram"]: f for f in funcs
                                if f.get("vram") is not None}

    # Per-TU sorted-VMA list of anchor-tagged functions only. Anchors
    # are the high-confidence ground truth derived from __FILE__ strings;
    # the proximity test should not be influenced by other inferred tags.
    anchors_by_tu: dict[str, list[int]] = defaultdict(list)
    for f in funcs:
        if f["tags"]:
            tu = best_tag(f)
            if tu:
                anchors_by_tu[tu].append(f["vram"])
    for tu in anchors_by_tu:
        anchors_by_tu[tu].sort()

    import bisect

    def nearest_anchor_distance(vma: int, tu: str) -> Optional[int]:
        """Distance from `vma` to nearest anchor of `tu`. None if `tu`
        has no anchors (callgraph is the only signal — skip proximity)."""
        vmas = anchors_by_tu.get(tu)
        if not vmas:
            return None
        i = bisect.bisect_left(vmas, vma)
        best = None
        for j in (i - 1, i):
            if 0 <= j < len(vmas):
                d = abs(vmas[j] - vma)
                if best is None or d < best:
                    best = d
        return best

    def closer_anchor_in_other_tu(vma: int, proposed_tu: str) -> Optional[str]:
        """If any other TU has an anchor closer to `vma` than `proposed_tu`'s
        nearest anchor, return that TU. Else None."""
        proposed_d = nearest_anchor_distance(vma, proposed_tu)
        if proposed_d is None:
            return None  # proposed TU has no anchors → can't proximity-test
        for tu, vmas in anchors_by_tu.items():
            if tu == proposed_tu:
                continue
            i = bisect.bisect_left(vmas, vma)
            for j in (i - 1, i):
                if 0 <= j < len(vmas):
                    d = abs(vmas[j] - vma)
                    if d < proposed_d:
                        return tu
        return None

    # Build reverse map: callee_vram → [caller_func, ...]
    callers_of: dict[int, list[dict]] = defaultdict(list)
    for e in edges:
        caller = by_vram.get(e["caller"])
        if not caller:
            continue
        for cv in e["callees"]:
            callers_of[cv].append(caller)

    n_new = 0
    n_rejected_proximity = 0
    for vma, callers in callers_of.items():
        callee = by_vram.get(vma)
        if not callee:
            continue
        # Skip already-tagged.
        if (callee["tags"] or callee.get("bracket_tu")
                or callee.get("vtable_tu")
                or callee.get("callgraph_tu")):
            continue
        # Look at tagged callers (anchor / bracket / vtable; not
        # callgraph, to keep this single-pass).
        tu_votes: dict[str, int] = defaultdict(int)
        for c in callers:
            tu = (best_tag(c) or c.get("bracket_tu")
                  or c.get("vtable_tu"))
            if tu:
                tu_votes[tu] += 1
        if not tu_votes:
            continue
        # All tagged callers must agree, and there must be at least
        # `min_callers` of them.
        if len(tu_votes) > 1:
            continue
        ((tu, count),) = tu_votes.items()
        if count < min_callers:
            continue
        # Proximity guard: refuse if a different TU's anchor is closer.
        closer = closer_anchor_in_other_tu(vma, tu)
        if closer is not None:
            n_rejected_proximity += 1
            continue
        callee["callgraph_tu"] = tu
        n_new += 1
    if n_rejected_proximity:
        print(f"callgraph_propagate: rejected {n_rejected_proximity} candidate(s) "
              f"by proximity guard", file=sys.stderr)
    return n_new


def tu_regions(funcs: list[dict]) -> list[dict]:
    """Walk the vram-sorted function list; for each TU compute its
    [vram_start, vram_end], anchor count, bracketed count, and any
    interleaving from other TUs (a sign of inlining or boundary issues)."""
    by_tu: dict[str, list[dict]] = defaultdict(list)
    for f in funcs:
        tu = (best_tag(f) or f.get("bracket_tu")
              or f.get("vtable_tu") or f.get("callgraph_tu"))
        if tu:
            by_tu[tu].append(f)
    regions: list[dict] = []
    for tu, fs in by_tu.items():
        fs.sort(key=lambda f: f["vram"])
        anchors = [f for f in fs if f["tags"]]
        bracketed = [f for f in fs if not f["tags"]]
        regions.append({
            "tu": tu,
            "vram_start": fs[0]["vram"],
            "vram_end": fs[-1]["vram"],
            "anchor_funcs": len(anchors),
            "bracket_funcs": len(bracketed),
            "total": len(fs),
        })
    regions.sort(key=lambda r: r["vram_start"])
    return regions


def render_tu_map(funcs: list[dict], anchors: dict[int, str]) -> str:
    funcs.sort(key=lambda f: f["vram"] or 0)
    bracket_untagged(funcs)
    n_vtable = vtable_propagate(funcs)
    n_call = callgraph_propagate(funcs)

    direct = sum(1 for f in funcs if f["tags"])
    bracketed = sum(1 for f in funcs if f.get("bracket_tu"))
    vtabled = sum(1 for f in funcs if f.get("vtable_tu"))
    callgraphed = sum(1 for f in funcs if f.get("callgraph_tu"))
    untagged = len(funcs) - direct - bracketed - vtabled - callgraphed

    regions = tu_regions(funcs)
    boundaries = (json.loads(BOUNDARIES_JSON.read_text())
                  if BOUNDARIES_JSON.exists() else [])
    high_conf_boundaries = [b for b in boundaries
                            if b["kind"] == "synthetic_nop"]

    # Concordance: count boundary candidates that fall just after a
    # region's vram_end (within +0x40). High count = our detection
    # agrees with splat-style boundary markers.
    concordant = 0
    boundary_vmas_sorted = sorted(b["vma"] for b in high_conf_boundaries)
    for r in regions:
        for b_vma in boundary_vmas_sorted:
            if r["vram_end"] <= b_vma <= r["vram_end"] + 0x40:
                concordant += 1
                break

    lines = [
        "# TU map — function → original translation unit",
        "",
        "Generated by `tools/identify_tus.py`. Re-run after asm changes",
        "or after regenerating `decomp/source_tree/`.",
        "",
        "Each row is one function from `asm/cod/*.s`. The **TU** column",
        "shows which original-tree file the function belongs to, inferred",
        "from `%hi(D_<vma>)` references to anchor addresses recorded in",
        "the skeleton tree. **Direct** tags come from a function loading",
        "an anchor; **bracketed** tags come from a function sitting in",
        "vram between two same-TU anchors (inferred via link-input order).",
        "",
        f"**Coverage:** {direct} direct + {bracketed} bracketed + "
        f"{vtabled} vtable + {callgraphed} callgraph = "
        f"{direct + bracketed + vtabled + callgraphed} / "
        f"{len(funcs)} total "
        f"({100.0 * (direct + bracketed + vtabled + callgraphed) / max(1, len(funcs)):.1f}%) — "
        f"{untagged} untagged",
        "",
        "## TU regions (vram-sorted)",
        "",
        "Each row is a contiguous span of `.text` attributable to one TU.",
        "Adjacent TUs reveal file-boundary candidates. Overlap (same vram",
        "range claimed by two TUs) is a sign of inlining or assert macros",
        "in headers.",
        "",
        f"**Boundary concordance:** {concordant} / {len(regions)} regions",
        "have a high-confidence `synthetic_nop` boundary marker within",
        "0x40 bytes of their `vram_end`. High concordance = our",
        "anchor-based detection agrees with splat-style boundary",
        "heuristics.",
        "",
        "| vram_start | vram_end | size | TU | anchors | bracketed | total |",
        "| ---: | ---: | ---: | --- | ---: | ---: | ---: |",
    ]
    for r in regions:
        size = r["vram_end"] - r["vram_start"]
        lines.append(
            f"| 0x{r['vram_start']:08x} | 0x{r['vram_end']:08x} | "
            f"0x{size:x} | `{r['tu']}` | {r['anchor_funcs']} | "
            f"{r['bracket_funcs']} | {r['total']} |"
        )

    # Boundary candidates inside currently-untagged gaps reveal TUs we
    # haven't identified yet — each cluster of synthetic_nop markers
    # delineates a probable TU we're missing.
    if high_conf_boundaries:
        tagged_vrams = sorted({r["vram_start"] for r in regions} |
                              {r["vram_end"] for r in regions})
        lines.extend([
            "",
            "## Boundary markers in untagged regions",
            "",
            f"`{len(high_conf_boundaries)}` `synthetic_nop` (high-confidence)",
            "boundary markers were found in `.text`. Markers whose nearest",
            "tagged region is more than 0x40 bytes away are listed below —",
            "each likely delineates a TU we haven't yet identified.",
            "",
            "| boundary vma | nearest tagged TU (distance) |",
            "| ---: | --- |",
        ])
        shown = 0
        for b in high_conf_boundaries:
            v = b["vma"]
            # Find nearest region.
            nearest_dist = None
            nearest_tu = None
            for r in regions:
                for ref in (r["vram_start"], r["vram_end"]):
                    d = abs(v - ref)
                    if nearest_dist is None or d < nearest_dist:
                        nearest_dist = d
                        nearest_tu = r["tu"]
            if nearest_dist is None or nearest_dist <= 0x40:
                continue  # too close to a known TU boundary; concordant
            lines.append(
                f"| 0x{v:08x} | `{nearest_tu}` "
                f"(0x{nearest_dist:x} away) |"
            )
            shown += 1
            if shown >= 50:
                lines.append("| … | (truncated; see "
                             "`decomp/boundaries.json` for full list) |")
                break

    lines.extend(["", "## Functions per TU (anchor + bracketed)", ""])
    lines.append("| TU | Function count |")
    lines.append("| --- | ---: |")
    counts: dict[str, int] = defaultdict(int)
    for f in funcs:
        tu = (best_tag(f) or f.get("bracket_tu")
              or f.get("vtable_tu") or f.get("callgraph_tu"))
        if tu:
            counts[tu] += 1
    for tu, n in sorted(counts.items(), key=lambda kv: -kv[1]):
        lines.append(f"| `{tu}` | {n} |")
    lines.append(f"| `(none)` | {untagged} |")

    lines.extend(["", "## Function listing (sorted by vram)", ""])
    lines.append("| vram | function | file | matched | TU | source | refs |")
    lines.append("| ---: | --- | --- | :---: | --- | --- | ---: |")

    for f in funcs:
        vram = f["vram"]
        vram_str = f"0x{vram:08x}" if vram is not None else "?"
        if f["tags"]:
            tu = best_tag(f)
            refs = f["tags"][tu]
            extras = [k for k in f["tags"] if k != tu]
            tu_cell = f"`{tu}`"
            if extras:
                tu_cell += f" *(+{len(extras)} other)*"
            source = "anchor"
        elif f.get("bracket_tu"):
            tu_cell = f"`{f['bracket_tu']}`"
            source = "bracket"
            refs = 0
        elif f.get("vtable_tu"):
            tu_cell = f"`{f['vtable_tu']}`"
            source = "vtable"
            refs = 0
        elif f.get("callgraph_tu"):
            tu_cell = f"`{f['callgraph_tu']}`"
            source = "callgraph"
            refs = 0
        else:
            tu_cell = "(none)"
            source = "—"
            refs = 0
        matched_cell = "✓" if f.get("source") == "matchings" else ""
        lines.append(
            f"| {vram_str} | `{f['name']}` | `{f['file']}` | "
            f"{matched_cell} | {tu_cell} | {source} | {refs} |"
        )
    return "\n".join(lines) + "\n"


def main() -> int:
    anchors = load_anchors()
    print(f"identify_tus: loaded {len(anchors)} anchors from "
          f"{TREE_ROOT.relative_to(REPO_ROOT)}/")

    funcs = scan_asm(anchors)
    print(f"identify_tus: scanned {len(funcs)} functions from "
          f"{ASM_COD_DIR.relative_to(REPO_ROOT)}/")

    body = render_tu_map(funcs, anchors)
    TU_MAP_OUT.write_text(body)

    # Sidecar JSON — durable, machine-readable, survives partial runs
    # better than the markdown table. Downstream tools should prefer
    # this over re-parsing the .md.
    tu_map_data = []
    for f in funcs:
        tu = (best_tag(f) or f.get("bracket_tu")
              or f.get("vtable_tu") or f.get("callgraph_tu"))
        if best_tag(f):
            source = "anchor"
        elif f.get("bracket_tu"):
            source = "bracket"
        elif f.get("vtable_tu"):
            source = "vtable"
        elif f.get("callgraph_tu"):
            source = "callgraph"
        else:
            source = None
        tu_map_data.append({
            "vram": f["vram"],
            "name": f["name"],
            "file": f["file"],
            "source_file": f.get("source"),
            "tu": tu,
            "tag_source": source,
            "tags": f["tags"],
        })
    TU_MAP_JSON.write_text(json.dumps(tu_map_data, indent=2) + "\n")

    direct = sum(1 for f in funcs if f["tags"])
    bracketed = sum(1 for f in funcs if f.get("bracket_tu"))
    vtabled = sum(1 for f in funcs if f.get("vtable_tu"))
    callgraphed = sum(1 for f in funcs if f.get("callgraph_tu"))
    total = direct + bracketed + vtabled + callgraphed
    print(f"identify_tus: {direct} direct + {bracketed} bracketed + "
          f"{vtabled} vtable + {callgraphed} callgraph = {total} / "
          f"{len(funcs)} ({100.0 * total / max(1, len(funcs)):.1f}%)")

    tu_counts: dict[str, int] = defaultdict(int)
    for f in funcs:
        tu = (best_tag(f) or f.get("bracket_tu")
              or f.get("vtable_tu") or f.get("callgraph_tu"))
        if tu:
            tu_counts[tu] += 1
    print("identify_tus: top TUs by function count (all sources):")
    for tu, n in sorted(tu_counts.items(), key=lambda kv: -kv[1])[:15]:
        print(f"  {n:>4}  {tu}")
    print(f"identify_tus: wrote {TU_MAP_OUT.relative_to(REPO_ROOT)}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
