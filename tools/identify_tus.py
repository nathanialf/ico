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
ASM_MATCHINGS_DIR = REPO_ROOT / "decomp" / "asm_snapshot" / "matchings"
ASM_NONMATCHINGS_DIR = REPO_ROOT / "decomp" / "asm_snapshot" / "nonmatchings"
TU_MAP_OUT = REPO_ROOT / "decomp" / "tu_map.md"
TU_MAP_JSON = REPO_ROOT / "decomp" / "tu_map.json"
VTABLES_JSON = REPO_ROOT / "decomp" / "vtables.json"
CALLGRAPH_JSON = REPO_ROOT / "decomp" / "callgraph.json"
BOUNDARIES_JSON = REPO_ROOT / "decomp" / "boundaries.json"
DATA_TU_MAP_JSON = REPO_ROOT / "decomp" / "data_tu_map.json"

PLACEHOLDER_RE = re.compile(
    r"/\*\s*placeholder:\s*(\S+)\s+—\s+__FILE__ anchor at "
    r"\.rodata\s+0x([0-9a-fA-F]+)"
)
HI_RE = re.compile(r"%hi\(D_([0-9A-Fa-f]{8})\)")
# Any %hi / %lo / %gp_rel reference to a D_<vma> data symbol.
# Used by data_propagate (after vote-based assignment in data_tu_map.json)
# to label functions whose data refs all agree on one TU.
DREF_ANY_RE = re.compile(r"%(?:hi|lo|gp_rel)\(D_([0-9A-Fa-f]{8})")
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


def _build_basename_to_tu(anchors: dict[int, str]) -> dict[str, str]:
    """Return {basename_no_ext: full_tu_path} for every TU known to
    source_tree. Used to resolve bare-name matchings/ dirs like
    `matchings/Basic/` → `src/Basic.c`."""
    out: dict[str, str] = {}
    for path in anchors.values():
        # path like "src/way_util.c", "ios/cdvd.c". Strip extension.
        base = Path(path).stem
        if base in out and out[base] != path:
            # Collision (e.g. src/foo.c and ios/foo.c) — drop both so
            # we don't make a wrong guess later.
            out[base] = ""
        else:
            out[base] = path
    return {k: v for k, v in out.items() if v}


# Subdirs that prefix a TU basename in the snapshot's flattened layout.
TU_PREFIX_DIRS = {"src", "ios", "isys", "sound"}


def _tu_from_snapshot_path(rel_parts: tuple[str, ...],
                           basename_to_tu: dict[str, str]) -> str | None:
    """Map a per-function .s file's snapshot-relative parent path to
    a TU path, if the file lives in a per-TU subdir.

    Cases (rel_parts excludes the leading `matchings` / `nonmatchings`
    tree root and the filename itself):
      - ('cod', '<hex>')           → None  (legacy cod-segment .s)
      - ('cod',)                   → None
      - ('<subdir>', '<basename>') → '<subdir>/<basename>.c' if
                                     <subdir> in TU_PREFIX_DIRS
      - ('<basename>',)            → basename_to_tu[<basename>] if known
      - anything else              → None"""
    if not rel_parts:
        return None
    if rel_parts[0] == "cod":
        return None
    if len(rel_parts) == 2 and rel_parts[0] in TU_PREFIX_DIRS:
        return f"{rel_parts[0]}/{rel_parts[1]}.c"
    if len(rel_parts) == 1:
        return basename_to_tu.get(rel_parts[0])
    return None


def _parse_asm_file(sfile: Path, anchors: dict[int, str],
                    results: list[dict], seen_vrams: set[int],
                    source_tag: str,
                    path_tu: str | None = None) -> None:
    """Parse one .s file; append discovered functions to `results`.
    Flushes on `endlabel` or end-of-file. Skips functions whose vram is
    already in `seen_vrams` (dedup across segment + matchings trees).

    `path_tu` is the TU the file's parent directory implies, if any —
    set for per-TU snapshot dirs like `nonmatchings/src/way_tool/` or
    `matchings/Basic/`. None for cod-segment-based files which carry
    no per-file TU signal."""
    cur_func: str | None = None
    cur_vram: int | None = None
    cur_tags: dict[str, int] = defaultdict(int)
    cur_data_refs: set[int] = set()

    def flush() -> None:
        nonlocal cur_func, cur_vram, cur_tags, cur_data_refs
        if cur_func and cur_vram is not None and cur_vram not in seen_vrams:
            seen_vrams.add(cur_vram)
            results.append({
                "name": cur_func,
                "vram": cur_vram,
                "file": sfile.name,
                "source": source_tag,
                "tags": dict(cur_tags),
                "total_refs": sum(cur_tags.values()),
                "data_refs": cur_data_refs,
                "path_tu": path_tu,
            })
        cur_func = None
        cur_vram = None
        cur_tags = defaultdict(int)
        cur_data_refs = set()

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
        for m in DREF_ANY_RE.finditer(line):
            cur_data_refs.add(int(m.group(1), 16))
    flush()


def scan_asm(anchors: dict[int, str]) -> list[dict]:
    """Walk every per-function and segment-level .s file under the
    asm snapshot, returning one dict per distinct function. `source`
    is 'cod' for unmatched-segment files, 'matchings' for matched
    per-function files, 'nonmatchings' for INCLUDE_ASM'd per-function
    files in carved-out per-TU layout. Dedup is by vram.

    Per-TU layout dirs (`matchings/Basic/`, `nonmatchings/src/way_tool/`,
    etc.) feed a `path_tu` hint to the parser — that's the strongest TU
    signal available (it reflects the splat YAML's explicit assignment)."""
    results: list[dict] = []
    seen: set[int] = set()
    if not ASM_COD_DIR.exists():
        sys.exit(f"identify_tus: {ASM_COD_DIR.relative_to(REPO_ROOT)}/ "
                 "missing — run `tools/snapshot_asm.py` first "
                 "(when matching loop is between cycles).")
    basename_to_tu = _build_basename_to_tu(anchors)

    # Per-TU dirs FIRST — they're the authoritative current layout
    # (the splat YAML carved their functions out of cod-segment files
    # and emitted to per-TU subdirs). The cod snapshot may be stale and
    # still hold older copies of those same functions; dedup by vram
    # keeps the per-TU record so the path_tu signal isn't lost.
    for snapshot_dir, source_tag in (
        (ASM_NONMATCHINGS_DIR, "nonmatchings"),
        (ASM_MATCHINGS_DIR, "matchings"),
    ):
        if not snapshot_dir.exists():
            continue
        for sfile in sorted(snapshot_dir.rglob("func_*.s")):
            rel = sfile.relative_to(snapshot_dir).parent.parts
            path_tu = _tu_from_snapshot_path(rel, basename_to_tu)
            _parse_asm_file(sfile, anchors, results, seen,
                            source_tag=source_tag, path_tu=path_tu)

    # Cod-segment files last — they cover functions still on the
    # cod/<offset> layout (not yet promoted to a per-TU subdir).
    for sfile in sorted(ASM_COD_DIR.glob("*.s")):
        _parse_asm_file(sfile, anchors, results, seen, source_tag="cod")
    return results


def best_tag(f: dict) -> str | None:
    if not f["tags"]:
        return None
    return max(f["tags"].items(), key=lambda kv: kv[1])[0]


def bracket_untagged(funcs: list[dict]) -> None:
    """In-place: assign `bracket_tu` to each untagged function whose vram
    sits between two authoritative-tagged functions of the *same* TU.
    "Authoritative" = the function's TU comes from path (splat YAML
    per-TU subdir) or anchor (rodata __FILE__ ref). Other inferred
    sources are NOT treated as authoritative here; they're handled by
    later passes."""
    def authoritative_tu(f: dict) -> str | None:
        return f.get("path_tu") or best_tag(f)

    funcs.sort(key=lambda f: f["vram"] or 0)
    n = len(funcs)
    prev_tag: list[str | None] = [None] * n
    cur: str | None = None
    for i, f in enumerate(funcs):
        t = authoritative_tu(f)
        if t:
            cur = t
        prev_tag[i] = cur
    next_tag: list[str | None] = [None] * n
    cur = None
    for i in range(n - 1, -1, -1):
        t = authoritative_tu(funcs[i])
        if t:
            cur = t
        next_tag[i] = cur
    for i, f in enumerate(funcs):
        f["bracket_tu"] = None
        if authoritative_tu(f):
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
        # For each entry, find its current tag (path/anchor preferred
        # over bracket; ignore prior vtable_tu — single pass).
        tags_seen: dict[str, int] = defaultdict(int)
        members: list[dict] = []
        for vma in table["entries"]:
            f = by_vram.get(vma)
            if not f:
                continue
            members.append(f)
            tag = f.get("path_tu") or best_tag(f) or f.get("bracket_tu")
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
            if (f.get("path_tu") or f["tags"] or f.get("bracket_tu")
                    or f.get("vtable_tu")):
                continue
            f["vtable_tu"] = winner
            n_new += 1
    return n_new


def _build_anchors_by_tu(funcs: list[dict]) -> dict[str, list[int]]:
    """Per-TU sorted-VMA list of authoritatively-tagged functions —
    path (splat YAML per-TU subdir) or anchor (rodata __FILE__).
    Proximity tests should not be influenced by other inferred tags,
    but path is at least as strong a signal as anchor."""
    anchors_by_tu: dict[str, list[int]] = defaultdict(list)
    for f in funcs:
        tu = f.get("path_tu") or (best_tag(f) if f["tags"] else None)
        if tu:
            anchors_by_tu[tu].append(f["vram"])
    for tu in anchors_by_tu:
        anchors_by_tu[tu].sort()
    return anchors_by_tu


def _closer_anchor_in_other_tu(anchors_by_tu: dict[str, list[int]],
                               vma: int,
                               proposed_tu: str) -> str | None:
    """If any other TU has an anchor closer to `vma` than `proposed_tu`'s
    nearest anchor, return that TU. Else None. Used by both callgraph
    and data propagation as a "don't cross anchor boundaries" guard."""
    import bisect
    vmas_proposed = anchors_by_tu.get(proposed_tu)
    if not vmas_proposed:
        return None  # proposed TU has no anchors → can't proximity-test
    i = bisect.bisect_left(vmas_proposed, vma)
    proposed_d = None
    for j in (i - 1, i):
        if 0 <= j < len(vmas_proposed):
            d = abs(vmas_proposed[j] - vma)
            if proposed_d is None or d < proposed_d:
                proposed_d = d
    if proposed_d is None:
        return None
    for tu, vmas in anchors_by_tu.items():
        if tu == proposed_tu:
            continue
        k = bisect.bisect_left(vmas, vma)
        for j in (k - 1, k):
            if 0 <= j < len(vmas):
                if abs(vmas[j] - vma) < proposed_d:
                    return tu
    return None


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

    anchors_by_tu = _build_anchors_by_tu(funcs)

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
        if (callee.get("path_tu") or callee["tags"]
                or callee.get("bracket_tu")
                or callee.get("vtable_tu")
                or callee.get("callgraph_tu")):
            continue
        # Look at tagged callers (path / anchor / bracket / vtable; not
        # callgraph, to keep this single-pass).
        tu_votes: dict[str, int] = defaultdict(int)
        for c in callers:
            tu = (c.get("path_tu") or best_tag(c)
                  or c.get("bracket_tu") or c.get("vtable_tu"))
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
        closer = _closer_anchor_in_other_tu(anchors_by_tu, vma, tu)
        if closer is not None:
            n_rejected_proximity += 1
            continue
        callee["callgraph_tu"] = tu
        n_new += 1
    if n_rejected_proximity:
        print(f"callgraph_propagate: rejected {n_rejected_proximity} candidate(s) "
              f"by proximity guard", file=sys.stderr)
    return n_new


def data_propagate(funcs: list[dict]) -> int:
    """Tag untagged functions whose data references all agree on one TU.

    Reads `decomp/data_tu_map.json` (produced by `build_data_tu_map.py`)
    and looks up every `%hi/%lo/%gp_rel(D_<vma>)` reference captured by
    the asm scan. Only unanimous-vote symbols are trusted — a symbol
    whose `votes` dict has exactly one TU. That filter drops shared
    globals (a symbol touched by multiple already-tagged TUs is not a
    private TU asset and tells us nothing about an untagged caller).

    The proposed TU is accepted only if:
      - the function references at least one unanimous-vote symbol;
      - every unanimous-vote symbol the function references agrees on
        the same TU;
      - the proximity guard accepts it (no other TU has an anchor
        closer to the function's vma).

    Sets `data_tu` on newly-tagged functions. Returns count.
    Runs after callgraph_propagate so the order of preference is
    anchor > bracket > vtable > callgraph > data — data is a weaker
    signal than caller agreement (a function can touch a global it
    doesn't own; it cannot be called by N agreeing strangers)."""
    if not DATA_TU_MAP_JSON.exists():
        return 0
    raw = json.loads(DATA_TU_MAP_JSON.read_text())
    unanimous: dict[int, str] = {}
    for key, rec in raw.items():
        if rec.get("method") != "vote":
            continue
        votes = rec.get("votes") or {}
        if len(votes) != 1:
            continue
        tu = rec.get("tu")
        if not tu or tu == "_unassigned":
            continue
        # Keys are "D_XXXXXXXX"; vma is the hex suffix.
        try:
            vma = int(key[2:], 16)
        except ValueError:
            continue
        unanimous[vma] = tu

    if not unanimous:
        return 0

    anchors_by_tu = _build_anchors_by_tu(funcs)

    n_new = 0
    n_split = 0
    n_rejected_proximity = 0
    for f in funcs:
        if (f.get("path_tu") or f["tags"] or f.get("bracket_tu")
                or f.get("vtable_tu") or f.get("callgraph_tu")
                or f.get("data_tu")):
            continue
        refs = f.get("data_refs") or ()
        votes: dict[str, int] = defaultdict(int)
        for r in refs:
            tu = unanimous.get(r)
            if tu:
                votes[tu] += 1
        if not votes:
            continue
        if len(votes) > 1:
            n_split += 1
            continue
        ((tu, _),) = votes.items()
        closer = _closer_anchor_in_other_tu(anchors_by_tu, f["vram"], tu)
        if closer is not None:
            n_rejected_proximity += 1
            continue
        f["data_tu"] = tu
        n_new += 1
    if n_split:
        print(f"data_propagate: skipped {n_split} candidate(s) with "
              f"disagreeing data refs", file=sys.stderr)
    if n_rejected_proximity:
        print(f"data_propagate: rejected {n_rejected_proximity} candidate(s) "
              f"by proximity guard", file=sys.stderr)
    return n_new


def _resolved_tu(f: dict) -> str | None:
    """Single source of truth for tag precedence: path (splat YAML's
    explicit per-TU subdir, strongest) > anchor (rodata __FILE__) >
    bracket > vtable > callgraph > data > revcg > slice_vote >
    bracket_inferred (weakest). Order largely doesn't matter for a
    single function (each function gets at most one tag set), but
    governs the source label shown in reports."""
    return (f.get("path_tu") or best_tag(f) or f.get("bracket_tu")
            or f.get("vtable_tu") or f.get("callgraph_tu")
            or f.get("data_tu") or f.get("revcg_tu")
            or f.get("slice_vote_tu")
            or f.get("bracket_inferred_tu"))


def reverse_callgraph_propagate(funcs: list[dict],
                                min_callees: int = 2) -> int:
    """Tag a caller whose tagged callees all agree on one TU.

    Forward callgraph (caller → callee) catches private helpers
    summoned only from within their owning TU. The reverse direction
    catches the complement: small library wrappers whose body is
    "call into one other module and return" — they sit alone in
    their own TU but every callee belongs to one TU.

    Strict: requires `min_callees` distinct tagged callees all agreeing
    on one TU (path / anchor / bracket / vtable / data — not callgraph
    or bracket_inferred, to keep this single-pass over inferred state).
    Applies the proximity guard so we don't tag a caller that lives
    far from the target TU's anchored region.

    Sets `revcg_tu`. Returns count."""
    if not CALLGRAPH_JSON.exists():
        return 0
    edges = json.loads(CALLGRAPH_JSON.read_text())
    by_vram: dict[int, dict] = {f["vram"]: f for f in funcs
                                if f.get("vram") is not None}
    anchors_by_tu = _build_anchors_by_tu(funcs)

    def callee_tu(f: dict) -> str | None:
        # Authoritative + medium-confidence sources only.
        return (f.get("path_tu") or best_tag(f)
                or f.get("bracket_tu") or f.get("vtable_tu")
                or f.get("data_tu"))

    n_new = 0
    n_split = 0
    n_rejected_proximity = 0
    for e in edges:
        caller = by_vram.get(e["caller"])
        if not caller:
            continue
        if _resolved_tu(caller):
            continue
        votes: dict[str, int] = defaultdict(int)
        for cv in e["callees"]:
            callee = by_vram.get(cv)
            if not callee:
                continue
            tu = callee_tu(callee)
            if tu:
                votes[tu] += 1
        if not votes:
            continue
        if len(votes) > 1:
            n_split += 1
            continue
        ((tu, count),) = votes.items()
        if count < min_callees:
            continue
        closer = _closer_anchor_in_other_tu(anchors_by_tu,
                                            caller["vram"], tu)
        if closer is not None:
            n_rejected_proximity += 1
            continue
        caller["revcg_tu"] = tu
        n_new += 1
    if n_split:
        print(f"reverse_callgraph_propagate: skipped {n_split} caller(s) "
              f"with disagreeing callees", file=sys.stderr)
    if n_rejected_proximity:
        print(f"reverse_callgraph_propagate: rejected "
              f"{n_rejected_proximity} candidate(s) by proximity guard",
              file=sys.stderr)
    return n_new


def slice_vote(funcs: list[dict]) -> int:
    """Slice-level data-ref voting for fully-unnamed slices.

    Each `synthetic_nop`-bounded slice that currently has zero tagged
    members aggregates the data references of all its functions and
    looks them up in `data_tu_map.json`. Both unanimous-vote and
    unanimous-proximity-assigned symbols count. Each referenced
    symbol contributes one vote to its assigned TU.

    Tag the slice's members with the winning TU iff:
      - the leader scores ≥3 distinct contributing symbols, and
      - it scores ≥2× the runner-up (or runner-up is zero).

    Differs from `bracket_inferred` in two ways:
      - `bracket_inferred` only fires when a slice already has at
        least one tagged member; this attacks slices with none;
      - it can use proximity-assigned data symbols, not just
        unanimous-vote ones, since the slice-level aggregate is more
        resistant to noise than per-function inference.

    Sets `slice_vote_tu`. Returns count of newly-tagged functions."""
    if not DATA_TU_MAP_JSON.exists() or not BOUNDARIES_JSON.exists():
        return 0
    raw = json.loads(DATA_TU_MAP_JSON.read_text())
    sym_to_tu: dict[int, str] = {}
    for key, rec in raw.items():
        tu = rec.get("tu")
        if not tu or tu == "_unassigned":
            continue
        method = rec.get("method")
        if method == "vote":
            votes = rec.get("votes") or {}
            if len(votes) != 1:
                continue  # shared global — skip
        elif method != "proximity":
            continue
        try:
            vma = int(key[2:], 16)
        except ValueError:
            continue
        sym_to_tu[vma] = tu

    if not sym_to_tu:
        return 0

    boundaries = json.loads(BOUNDARIES_JSON.read_text())
    sn = sorted(b["vma"] for b in boundaries
                if b["kind"] == "synthetic_nop")
    funcs.sort(key=lambda f: f["vram"] or 0)
    if not funcs or not sn:
        return 0

    import bisect
    func_vrams = [f["vram"] or 0 for f in funcs]
    bounds = [func_vrams[0]] + sn + [func_vrams[-1] + 0x10000]

    n_new = 0
    n_unanimous_low = 0
    n_split_rejected = 0
    for i in range(len(bounds) - 1):
        lo, hi = bounds[i], bounds[i + 1]
        if lo >= hi:
            continue
        lo_i = bisect.bisect_left(func_vrams, lo)
        hi_i = bisect.bisect_left(func_vrams, hi)
        members = funcs[lo_i:hi_i]
        if not members:
            continue
        # Only fire on fully-unnamed slices.
        if any(_resolved_tu(f) for f in members):
            continue
        votes: dict[str, int] = defaultdict(int)
        for f in members:
            for r in (f.get("data_refs") or ()):
                tu = sym_to_tu.get(r)
                if tu:
                    votes[tu] += 1
        if not votes:
            continue
        ranked = sorted(votes.items(), key=lambda kv: -kv[1])
        winner, w_score = ranked[0]
        runner_up = ranked[1][1] if len(ranked) >= 2 else 0
        if w_score < 3:
            n_unanimous_low += 1
            continue
        if runner_up > 0 and w_score < 2 * runner_up:
            n_split_rejected += 1
            continue
        for f in members:
            f["slice_vote_tu"] = winner
            n_new += 1
    if n_unanimous_low:
        print(f"slice_vote: {n_unanimous_low} slice(s) had a candidate "
              f"with <3 voting symbols", file=sys.stderr)
    if n_split_rejected:
        print(f"slice_vote: {n_split_rejected} slice(s) rejected for "
              f"split votes (winner < 2x runner-up)", file=sys.stderr)
    return n_new


def bracket_inferred(funcs: list[dict]) -> int:
    """Slice-level bracketing using any inferred tag.

    Partition `.text` at every `synthetic_nop` boundary (same geometry
    `find_unnamed_tus.py` uses). For each slice, if every tagged
    function in the slice agrees on one TU, propagate that TU to the
    slice's untagged members. Uses the full inferred tag set
    (anchor / bracket / vtable / callgraph / data) — so the gains from
    `data_propagate` feed this pass.

    `bracket_untagged` already does an anchor-only walk-the-list
    version. This pass differs in two ways:
      - it respects `synthetic_nop` slice boundaries (won't bracket
        across them);
      - it accepts inferred tags as evidence, not just anchors.

    Sets `bracket_inferred_tu` on newly-tagged functions. Returns
    count."""
    if not BOUNDARIES_JSON.exists():
        return 0
    boundaries = json.loads(BOUNDARIES_JSON.read_text())
    sn = sorted(b["vma"] for b in boundaries
                if b["kind"] == "synthetic_nop")
    funcs.sort(key=lambda f: f["vram"] or 0)
    if not funcs or not sn:
        return 0

    import bisect
    func_vrams = [f["vram"] or 0 for f in funcs]
    bounds = [func_vrams[0]] + sn + [func_vrams[-1] + 0x10000]

    n_new = 0
    n_split_slices = 0
    for i in range(len(bounds) - 1):
        lo, hi = bounds[i], bounds[i + 1]
        if lo >= hi:
            continue
        lo_i = bisect.bisect_left(func_vrams, lo)
        hi_i = bisect.bisect_left(func_vrams, hi)
        members = funcs[lo_i:hi_i]
        if not members:
            continue
        tus = {tu for tu in (_resolved_tu(f) for f in members) if tu}
        if not tus:
            continue
        if len(tus) > 1:
            n_split_slices += 1
            continue
        tu = next(iter(tus))
        for f in members:
            if _resolved_tu(f) is None:
                f["bracket_inferred_tu"] = tu
                n_new += 1
    if n_split_slices:
        print(f"bracket_inferred: skipped {n_split_slices} multi-TU slice(s)",
              file=sys.stderr)
    return n_new


def tu_regions(funcs: list[dict]) -> list[dict]:
    """Walk the vram-sorted function list; for each TU compute its
    [vram_start, vram_end], anchor count, bracketed count, and any
    interleaving from other TUs (a sign of inlining or boundary issues)."""
    by_tu: dict[str, list[dict]] = defaultdict(list)
    for f in funcs:
        tu = _resolved_tu(f)
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
    n_data = data_propagate(funcs)
    n_revcg = reverse_callgraph_propagate(funcs)
    # slice_vote runs BEFORE bracket_inferred. Both work at slice
    # granularity, but slice_vote attacks fully-unnamed slices using
    # data-symbol evidence, then bracket_inferred fills in any slice
    # that has at least one tag (including the just-added slice_vote
    # and revcg ones).
    n_slice = slice_vote(funcs)
    n_brinf = bracket_inferred(funcs)

    # path_tu beats f["tags"] in _resolved_tu — count it first so
    # path-tagged funcs aren't double-counted as "direct" too.
    pathed = sum(1 for f in funcs if f.get("path_tu"))
    direct = sum(1 for f in funcs
                 if f["tags"] and not f.get("path_tu"))
    bracketed = sum(1 for f in funcs if f.get("bracket_tu"))
    vtabled = sum(1 for f in funcs if f.get("vtable_tu"))
    callgraphed = sum(1 for f in funcs if f.get("callgraph_tu"))
    datad = sum(1 for f in funcs if f.get("data_tu"))
    revcgd = sum(1 for f in funcs if f.get("revcg_tu"))
    sliced = sum(1 for f in funcs if f.get("slice_vote_tu"))
    brinfd = sum(1 for f in funcs if f.get("bracket_inferred_tu"))
    untagged = (len(funcs) - pathed - direct - bracketed - vtabled
                - callgraphed - datad - revcgd - sliced - brinfd)

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
        f"**Coverage:** {pathed} path + {direct} direct + "
        f"{bracketed} bracketed + {vtabled} vtable + "
        f"{callgraphed} callgraph + {datad} data + "
        f"{revcgd} revcg + {sliced} slice_vote + "
        f"{brinfd} bracket_inferred = "
        f"{pathed + direct + bracketed + vtabled + callgraphed + datad + revcgd + sliced + brinfd} / "
        f"{len(funcs)} total "
        f"({100.0 * (pathed + direct + bracketed + vtabled + callgraphed + datad + revcgd + sliced + brinfd) / max(1, len(funcs)):.1f}%) — "
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
        tu = _resolved_tu(f)
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
        if f.get("path_tu"):
            tu_cell = f"`{f['path_tu']}`"
            source = "path"
            refs = 0
        elif f["tags"]:
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
        elif f.get("data_tu"):
            tu_cell = f"`{f['data_tu']}`"
            source = "data"
            refs = 0
        elif f.get("revcg_tu"):
            tu_cell = f"`{f['revcg_tu']}`"
            source = "revcg"
            refs = 0
        elif f.get("slice_vote_tu"):
            tu_cell = f"`{f['slice_vote_tu']}`"
            source = "slice_vote"
            refs = 0
        elif f.get("bracket_inferred_tu"):
            tu_cell = f"`{f['bracket_inferred_tu']}`"
            source = "bracket_inferred"
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
        tu = _resolved_tu(f)
        if f.get("path_tu"):
            source = "path"
        elif best_tag(f):
            source = "anchor"
        elif f.get("bracket_tu"):
            source = "bracket"
        elif f.get("vtable_tu"):
            source = "vtable"
        elif f.get("callgraph_tu"):
            source = "callgraph"
        elif f.get("data_tu"):
            source = "data"
        elif f.get("revcg_tu"):
            source = "revcg"
        elif f.get("slice_vote_tu"):
            source = "slice_vote"
        elif f.get("bracket_inferred_tu"):
            source = "bracket_inferred"
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

    pathed = sum(1 for f in funcs if f.get("path_tu"))
    direct = sum(1 for f in funcs
                 if f["tags"] and not f.get("path_tu"))
    bracketed = sum(1 for f in funcs if f.get("bracket_tu"))
    vtabled = sum(1 for f in funcs if f.get("vtable_tu"))
    callgraphed = sum(1 for f in funcs if f.get("callgraph_tu"))
    datad = sum(1 for f in funcs if f.get("data_tu"))
    revcgd = sum(1 for f in funcs if f.get("revcg_tu"))
    sliced = sum(1 for f in funcs if f.get("slice_vote_tu"))
    brinfd = sum(1 for f in funcs if f.get("bracket_inferred_tu"))
    total = (pathed + direct + bracketed + vtabled
             + callgraphed + datad + revcgd + sliced + brinfd)
    print(f"identify_tus: {pathed} path + {direct} direct + "
          f"{bracketed} bracketed + {vtabled} vtable + "
          f"{callgraphed} callgraph + {datad} data + "
          f"{revcgd} revcg + {sliced} slice_vote + "
          f"{brinfd} bracket_inferred = "
          f"{total} / {len(funcs)} "
          f"({100.0 * total / max(1, len(funcs)):.1f}%)")

    tu_counts: dict[str, int] = defaultdict(int)
    for f in funcs:
        tu = _resolved_tu(f)
        if tu:
            tu_counts[tu] += 1
    print("identify_tus: top TUs by function count (all sources):")
    for tu, n in sorted(tu_counts.items(), key=lambda kv: -kv[1])[:15]:
        print(f"  {n:>4}  {tu}")
    print(f"identify_tus: wrote {TU_MAP_OUT.relative_to(REPO_ROOT)}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
