#!/usr/bin/env python3
"""
build_placement_plan.py — propose where each currently-unassigned
function should land when the active coalesce sprint absorbs it.

Read-only. Writes `decomp/placement_plan.{md,json}`. Zero yaml writes,
zero file moves, zero git ops. The active coalesce worker (or a future
PROMOTE.md session) reads the plan to decide where to fold a cod shim.

Per-function evidence merge (untagged funcs and `src/cod/<hex>.c`
shims):

| Evidence              | Signal                                              | Weight |
| --------------------- | --------------------------------------------------- | ------ |
| caller-consensus      | >70% of callers in same TU                          | +3     |
| anchor bracketing     | both nearest tagged text-neighbors agree on TU      | +3     |
| vtable membership     | listed in a tagged TU's dispatch table              | +3     |
| boundary co-membership | inside a synthetic-nop slice overlapping a tagged TU | +2     |
| unnamed-slice sibling | same boundary slice as a tagged func                | +1     |
| callee-consensus      | functions it calls cluster in one TU                | +1     |

Confidence: high>=5, medium 3-4, low 1-2, none 0.

Action (per row):
* PROMOTE_TYPED — function is matched (yaml type==c with backing src).
  Coalesce step: move body to `src/<TU>.c` as typed C.
* INCLUDE_ASM — function is unmatched (yaml type==asm). Coalesce step:
  add `INCLUDE_ASM("asm/nonmatchings/cod/<TU>", func_X);` to `src/<TU>.c`.

For fully-unnamed boundary slices (no anchor evidence anywhere in
the slice), propose a placeholder TU name from dominant callgraph
cluster, top shared data symbol, or `unknown_<lo>_<hi>` last resort.
"""

from __future__ import annotations

import argparse
import json
import re
import sys
from bisect import bisect_left, bisect_right
from collections import Counter, defaultdict
from pathlib import Path

try:
    import yaml
except ImportError:
    sys.exit("build_placement_plan: missing PyYAML.")

REPO_ROOT = Path(__file__).resolve().parent.parent
TU_MAP_JSON = REPO_ROOT / "decomp" / "tu_map.json"
CALLGRAPH_JSON = REPO_ROOT / "decomp" / "callgraph.json"
BOUNDARIES_JSON = REPO_ROOT / "decomp" / "boundaries.json"
VTABLES_JSON = REPO_ROOT / "decomp" / "vtables.json"
SOURCE_TREE_DIR = REPO_ROOT / "decomp" / "source_tree"
YAML_PATH = REPO_ROOT / "config" / "ico.us.yaml"

OUT_MD = REPO_ROOT / "decomp" / "placement_plan.md"
OUT_JSON = REPO_ROOT / "decomp" / "placement_plan.json"

VRAM_BASE = 0x00100000
CALLER_CONSENSUS_THRESHOLD = 0.70
CONF_HIGH = 5
CONF_MED = 3
CONF_LOW = 1


# --------------------------------------------------------------------- loaders

def load_tu_map() -> list[dict]:
    return json.loads(TU_MAP_JSON.read_text())


def load_callgraph() -> list[dict]:
    return json.loads(CALLGRAPH_JSON.read_text())


def load_boundaries() -> list[dict]:
    return json.loads(BOUNDARIES_JSON.read_text())


def load_vtables() -> list[dict]:
    if not VTABLES_JSON.exists():
        return []
    return json.loads(VTABLES_JSON.read_text())


def load_yaml_subsegs() -> list[tuple[int, str, str]]:
    """Return (vma, stype, name) for every text subsegment in
    config/ico.us.yaml, sorted by vma. `vma` is absolute (offset +
    VRAM_BASE)."""
    doc = yaml.safe_load(YAML_PATH.read_text())
    out: list[tuple[int, str, str]] = []
    for seg in doc.get("segments", []):
        if isinstance(seg, list):
            continue
        for sub in seg.get("subsegments", []):
            if isinstance(sub, list) and len(sub) >= 2:
                off = sub[0]
                stype = sub[1]
                name = sub[2] if len(sub) >= 3 else ""
            elif isinstance(sub, dict):
                off = sub.get("vram", 0)
                stype = sub.get("type", "")
                name = sub.get("name", "")
            else:
                continue
            if stype in {"asm", "c", "hasm"}:
                out.append((off + VRAM_BASE, stype, name))
    out.sort()
    return out


_ANCHOR_RE = re.compile(
    r"/\*\s*placeholder:\s*([^\s]+)\s+—\s+__FILE__\s+anchor\s+at\s+\.rodata\s+0x([0-9a-fA-F]+)"
)


def load_source_tree_anchors() -> dict[str, int]:
    """tu_path -> .rodata anchor VMA. Used only to enumerate known TUs."""
    out: dict[str, int] = {}
    if not SOURCE_TREE_DIR.is_dir():
        return out
    for p in SOURCE_TREE_DIR.rglob("*.c"):
        try:
            first = p.read_text().splitlines()[0]
        except (IndexError, OSError):
            continue
        m = _ANCHOR_RE.match(first)
        if m:
            out[m.group(1)] = int(m.group(2), 16)
    return out


# ----------------------------------------------------------- input index build

class Index:
    """Pre-computed lookups joining all the inputs by VMA."""

    def __init__(self) -> None:
        self.funcs = load_tu_map()  # list of {vram, name, tu, ...}
        self.callgraph = load_callgraph()  # list of {caller, callees, total}
        self.boundaries = load_boundaries()  # list of {vma, kind, evidence}
        self.vtables = load_vtables()  # list of {section, vma_start, vma_end, count, entries}
        self.yaml_subs = load_yaml_subsegs()  # sorted (vma, stype, name)
        self.known_tus = set(load_source_tree_anchors().keys())

        # vma -> func dict
        self.func_by_vma: dict[int, dict] = {f["vram"]: f for f in self.funcs}
        # sorted vma list for bisect
        self.func_vmas: list[int] = sorted(self.func_by_vma.keys())
        # vma -> tu (only for tagged funcs)
        self.tu_by_vma: dict[int, str] = {
            f["vram"]: f["tu"] for f in self.funcs if f.get("tu")
        }
        # Add tagged TU names to the known set (some TUs are tagged in
        # tu_map but have no source_tree placeholder — e.g. inferred
        # bracket-fill TUs without an anchor of their own).
        self.known_tus.update(self.tu_by_vma.values())

        # vma -> list of caller vmas (inverse callgraph)
        self.callers_of: dict[int, list[int]] = defaultdict(list)
        for entry in self.callgraph:
            caller = entry["caller"]
            for callee in entry.get("callees", []):
                self.callers_of[callee].append(caller)
        # vma -> list of callee vmas (direct lookup)
        self.callees_of: dict[int, list[int]] = {
            e["caller"]: list(e.get("callees", []))
            for e in self.callgraph
        }

        # Boundary slices: sorted list of synthetic-nop VMAs. A "slice"
        # is the half-open range [b_i, b_{i+1}). For each tagged func
        # in a slice, the slice gets that TU as one of its tags.
        boundary_vmas = sorted({
            b["vma"] for b in self.boundaries
            if b.get("kind") == "synthetic_nop"
        })
        self.slice_starts: list[int] = boundary_vmas
        self.slice_tu_tags: list[Counter] = [Counter() for _ in boundary_vmas]
        for f in self.funcs:
            if not f.get("tu"):
                continue
            i = bisect_right(self.slice_starts, f["vram"]) - 1
            if i >= 0:
                self.slice_tu_tags[i][f["tu"]] += 1

        # Yaml lookup: vma -> (stype, name). Use bisect on sorted list.
        self.yaml_vmas: list[int] = [v for v, _, _ in self.yaml_subs]

        # Vtable entry index: vma (function pointer) -> list of vtable
        # data-VMAs that reference it. Used for vtable-membership
        # evidence; we then look up the TU that owns each vtable.
        self.vtable_refs_to: dict[int, list[int]] = defaultdict(list)
        for vt in self.vtables:
            for entry_vma in vt.get("entries", []):
                self.vtable_refs_to[entry_vma].append(vt["vma_start"])

    # ---- query helpers ----

    def yaml_subseg_for(self, vma: int) -> tuple[str, str]:
        """Return (stype, name) for the YAML subseg covering vma.
        ('', '') if no enclosing subseg exists."""
        i = bisect_right(self.yaml_vmas, vma) - 1
        if i < 0:
            return ("", "")
        _, stype, name = self.yaml_subs[i]
        return (stype, name)

    def is_matched(self, vma: int) -> bool:
        stype, name = self.yaml_subseg_for(vma)
        if stype not in {"c", "hasm"} or not name:
            return False
        return (REPO_ROOT / f"{name}.{'c' if stype == 'c' else 's'}").exists()

    def is_cod_shim(self, vma: int) -> bool:
        _, name = self.yaml_subseg_for(vma)
        return name.startswith(("cod/", "src/cod/"))

    def slice_index_for(self, vma: int) -> int | None:
        """Index into slice_starts (and slice_tu_tags) for the slice
        containing vma, or None if vma is before the first boundary."""
        i = bisect_right(self.slice_starts, vma) - 1
        return i if i >= 0 else None

    def nearest_tagged_before(self, vma: int) -> str | None:
        i = bisect_left(self.func_vmas, vma) - 1
        while i >= 0:
            v = self.func_vmas[i]
            tu = self.tu_by_vma.get(v)
            if tu:
                return tu
            i -= 1
        return None

    def nearest_tagged_after(self, vma: int) -> str | None:
        i = bisect_right(self.func_vmas, vma)
        while i < len(self.func_vmas):
            v = self.func_vmas[i]
            tu = self.tu_by_vma.get(v)
            if tu:
                return tu
            i += 1
        return None


# ------------------------------------------------------- evidence computation

def evidence_caller_consensus(idx: Index, vma: int) -> dict | None:
    callers = idx.callers_of.get(vma, [])
    if not callers:
        return None
    tu_counts: Counter = Counter()
    untagged = 0
    for c in callers:
        tu = idx.tu_by_vma.get(c)
        if tu:
            tu_counts[tu] += 1
        else:
            untagged += 1
    if not tu_counts:
        return None
    top_tu, top_n = tu_counts.most_common(1)[0]
    total = len(callers)
    if top_n / total < CALLER_CONSENSUS_THRESHOLD:
        return None
    return {
        "kind": "caller_consensus",
        "tu": top_tu,
        "weight": 3,
        "detail": f"{top_n}/{total} callers in {top_tu}"
                  + (f" ({untagged} untagged)" if untagged else ""),
    }


def evidence_callee_consensus(idx: Index, vma: int) -> dict | None:
    callees = idx.callees_of.get(vma, [])
    if not callees:
        return None
    tu_counts: Counter = Counter()
    for c in callees:
        tu = idx.tu_by_vma.get(c)
        if tu:
            tu_counts[tu] += 1
    if not tu_counts:
        return None
    top_tu, top_n = tu_counts.most_common(1)[0]
    if top_n / len(callees) < CALLER_CONSENSUS_THRESHOLD:
        return None
    return {
        "kind": "callee_consensus",
        "tu": top_tu,
        "weight": 1,
        "detail": f"{top_n}/{len(callees)} callees in {top_tu}",
    }


def evidence_bracketing(idx: Index, vma: int) -> dict | None:
    before = idx.nearest_tagged_before(vma)
    after = idx.nearest_tagged_after(vma)
    if before and after and before == after:
        return {
            "kind": "bracketing",
            "tu": before,
            "weight": 3,
            "detail": f"both neighbors tagged {before}",
        }
    if before and not after:
        return {
            "kind": "bracketing",
            "tu": before,
            "weight": 2,
            "detail": f"trailing neighbor tagged {before}",
        }
    if after and not before:
        return {
            "kind": "bracketing",
            "tu": after,
            "weight": 2,
            "detail": f"leading neighbor tagged {after}",
        }
    return None


def evidence_vtable_membership(idx: Index, vma: int) -> dict | None:
    """If this function appears in a vtable, and that vtable's
    data-VMA falls inside a TU's known data span (we don't compute
    data spans yet, so approximate via tu_by_vma of nearby functions
    that reference the vtable). v1 heuristic: just record raw vtable
    membership; the TU it implies isn't computed."""
    vtables = idx.vtable_refs_to.get(vma, [])
    if not vtables:
        return None
    return {
        "kind": "vtable_membership",
        "tu": None,  # v1: TU inference deferred
        "weight": 0,  # no scoring weight until TU inference lands
        "detail": f"in {len(vtables)} dispatch table(s) "
                  + ",".join(f"0x{v:08X}" for v in vtables[:3]),
    }


def evidence_boundary_membership(idx: Index, vma: int) -> dict | None:
    i = idx.slice_index_for(vma)
    if i is None:
        return None
    tags = idx.slice_tu_tags[i]
    if not tags:
        return None
    top_tu, top_n = tags.most_common(1)[0]
    return {
        "kind": "boundary_membership",
        "tu": top_tu,
        "weight": 2 if top_n >= 2 else 1,
        "detail": f"in boundary slice tagged {top_tu} "
                  f"({top_n} siblings)",
    }


# ----------------------------------------------------------------- scoring

def score_evidence(evidence: list[dict]) -> tuple[str | None, str, int, list[dict]]:
    """Sum weights per candidate TU. Return:
    (recommended_tu, confidence_label, score, alternatives)."""
    score_by_tu: Counter = Counter()
    for e in evidence:
        if e.get("tu") and e.get("weight"):
            score_by_tu[e["tu"]] += e["weight"]
    if not score_by_tu:
        return (None, "none", 0, [])
    ranked = score_by_tu.most_common()
    top_tu, top_score = ranked[0]
    if top_score >= CONF_HIGH:
        conf = "high"
    elif top_score >= CONF_MED:
        conf = "medium"
    elif top_score >= CONF_LOW:
        conf = "low"
    else:
        conf = "none"
    alternatives = [
        {"tu": tu, "score": sc,
         "confidence": ("high" if sc >= CONF_HIGH
                        else "medium" if sc >= CONF_MED
                        else "low" if sc >= CONF_LOW else "none")}
        for tu, sc in ranked[1:6]
    ]
    return (top_tu, conf, top_score, alternatives)


def action_for(idx: Index, vma: int) -> str:
    return "PROMOTE_TYPED" if idx.is_matched(vma) else "INCLUDE_ASM"


# ----------------------------------------------- per-function row construction

def build_function_rows(idx: Index) -> list[dict]:
    rows = []
    for f in idx.funcs:
        vma = f["vram"]
        # Eligible: untagged in tu_map, OR currently in a cod/ shim
        # (matched or not — both need to move into a TU file).
        cod_shim = idx.is_cod_shim(vma)
        tagged = bool(f.get("tu"))
        if tagged and not cod_shim:
            continue  # already placed AND not in a cod shim
        evidence = [
            e for e in (
                evidence_caller_consensus(idx, vma),
                evidence_callee_consensus(idx, vma),
                evidence_bracketing(idx, vma),
                evidence_vtable_membership(idx, vma),
                evidence_boundary_membership(idx, vma),
            )
            if e is not None
        ]
        # If the function is tagged but is in a cod shim, use the
        # existing tag as a confident recommendation (weight from
        # identify_tus already vetted it).
        if tagged:
            evidence.insert(0, {
                "kind": "existing_tag",
                "tu": f["tu"],
                "weight": 5,
                "detail": f"already tagged {f['tu']} in tu_map "
                          f"(source={f.get('tag_source','?')})",
            })
        rec_tu, conf, score, alts = score_evidence(evidence)
        stype, subseg_name = idx.yaml_subseg_for(vma)
        rows.append({
            "vram": f"0x{vma:08X}",
            "vram_int": vma,
            "current_file": subseg_name or "(no yaml)",
            "current_type": stype,
            "is_matched": idx.is_matched(vma),
            "is_cod_shim": cod_shim,
            "recommended_tu": rec_tu,
            "confidence": conf,
            "score": score,
            "action": action_for(idx, vma) if rec_tu else "NO_ACTION",
            "evidence": evidence,
            "alternatives": alts,
        })
    return rows


# ----------------------------------------------- placeholder slice proposals

def build_placeholder_slices(idx: Index, rows: list[dict]) -> list[dict]:
    """For fully-unnamed boundary slices (no tagged func, no high/med
    confidence row inside), propose a placeholder name.

    Priority:
      (a) dominant external callgraph cluster (>70% of slice's funcs'
          callers share an external TU) → `<that_tu>_neighbors.c`
      (b) `unknown_<lo>_<hi>.c` last resort
    """
    slices_with_funcs: dict[int, list[dict]] = defaultdict(list)
    for f in idx.funcs:
        i = idx.slice_index_for(f["vram"])
        if i is not None:
            slices_with_funcs[i].append(f)

    rec_by_vma = {r["vram_int"]: r for r in rows}

    out = []
    for i, funcs in sorted(slices_with_funcs.items()):
        tagged = [f for f in funcs if f.get("tu")]
        if tagged:
            continue  # not fully-unnamed
        # Aggregate external caller TUs across all funcs in this slice.
        ext_callers: Counter = Counter()
        for f in funcs:
            for caller in idx.callers_of.get(f["vram"], []):
                tu = idx.tu_by_vma.get(caller)
                if tu:
                    ext_callers[tu] += 1
        lo = idx.slice_starts[i]
        hi = (idx.slice_starts[i + 1] if i + 1 < len(idx.slice_starts)
              else funcs[-1]["vram"] + 4)
        proposal = None
        if ext_callers:
            top_tu, top_n = ext_callers.most_common(1)[0]
            total = sum(ext_callers.values())
            if top_n / total >= CALLER_CONSENSUS_THRESHOLD:
                proposal = {
                    "name": f"{top_tu[:-2] if top_tu.endswith('.c') else top_tu}_neighbors.c",
                    "rationale": f"{top_n}/{total} external callers in {top_tu}",
                }
        if proposal is None:
            proposal = {
                "name": f"unknown_{lo:08X}_{hi:08X}.c",
                "rationale": "no caller cluster; last-resort placeholder",
            }
        out.append({
            "slice_index": i,
            "vma_lo": f"0x{lo:08X}",
            "vma_hi": f"0x{hi:08X}",
            "func_count": len(funcs),
            "placeholder_tu": proposal["name"],
            "rationale": proposal["rationale"],
            "placeholder": True,
            "confidence": "low",
            # Attach the func VMAs so a future coalesce session can
            # cross-reference. Cap to keep JSON readable.
            "funcs": [f"0x{f['vram']:08X}" for f in funcs[:30]],
            "funcs_truncated": len(funcs) > 30,
        })
    return out


# ----------------------------------------------------------------- emitters

def emit_json(rows: list[dict], slices: list[dict]) -> dict:
    return {
        "rows": [
            {k: v for k, v in r.items() if k != "vram_int"}
            for r in rows
        ],
        "placeholder_slices": slices,
    }


def emit_markdown(rows: list[dict], slices: list[dict],
                  limit_per_tu: int = 50) -> str:
    out: list[str] = []
    out.append("# Placement plan — ICO cod-shim reduction\n")
    out.append("Generated by `tools/build_placement_plan.py`. "
               "**Read-only** — the active coalesce worker consults "
               "this to pick where to fold each `src/cod/<hex>.c` "
               "shim. Re-run after every `make setup` to refresh "
               "against the current yaml state.\n")
    out.append("Two action paths (aligned with `decomp/PROMOTE.md`):\n")
    out.append("- **PROMOTE_TYPED** — matched cod shim. Move the C "
               "body into `src/<TU>.c`.\n")
    out.append("- **INCLUDE_ASM** — unmatched cod shim. Add "
               "`INCLUDE_ASM(\"asm/nonmatchings/cod/<TU>\", func_X);` "
               "to `src/<TU>.c`.\n")

    # Summary
    conf_hist: Counter = Counter(r["confidence"] for r in rows)
    action_hist: Counter = Counter(r["action"] for r in rows)
    out.append("## Summary\n")
    out.append(f"- Total candidate functions: **{len(rows)}**\n")
    out.append("- Confidence: " + ", ".join(
        f"{k}={conf_hist[k]}" for k in ("high", "medium", "low", "none")
    ) + "\n")
    out.append("- Action: " + ", ".join(
        f"{k}={action_hist[k]}" for k in
        ("PROMOTE_TYPED", "INCLUDE_ASM", "NO_ACTION")
    ) + "\n")
    out.append(f"- Placeholder slices (fully unnamed): "
               f"**{len(slices)}** ({sum(s['func_count'] for s in slices)} funcs)\n")

    # Per-TU recommendations
    by_tu: dict[str, list[dict]] = defaultdict(list)
    for r in rows:
        key = r["recommended_tu"] or "(no recommendation)"
        by_tu[key].append(r)
    out.append("## Per-TU recommendations\n")
    out.append("Sorted by candidate count (high-impact TUs first).\n")
    for tu, tu_rows in sorted(by_tu.items(),
                              key=lambda kv: -len(kv[1])):
        out.append(f"### {tu}  ({len(tu_rows)} candidates)\n")
        out.append("| vram | matched | action | confidence | top evidence |\n")
        out.append("| --- | --- | --- | --- | --- |\n")
        # Sort within TU: high confidence first, then by vma
        ranked = sorted(tu_rows, key=lambda r: (
            {"high": 0, "medium": 1, "low": 2, "none": 3}[r["confidence"]],
            r["vram_int"],
        ))
        for r in ranked[:limit_per_tu]:
            top_ev = r["evidence"][0]["detail"] if r["evidence"] else "—"
            yes = "✓" if r["is_matched"] else " "
            out.append(f"| {r['vram']} | {yes} | {r['action']} | "
                       f"{r['confidence']} | {top_ev} |\n")
        if len(tu_rows) > limit_per_tu:
            out.append(f"| … | | | | _{len(tu_rows) - limit_per_tu} more_ |\n")
        out.append("\n")

    # Placeholder slices
    if slices:
        out.append("## Placeholder slices (fully unnamed)\n")
        out.append("Boundary-delimited slices with zero tagged "
                   "functions. Names are tentative — review before "
                   "use in any yaml/source change.\n")
        out.append("| vma range | funcs | proposed name | rationale |\n")
        out.append("| --- | --- | --- | --- |\n")
        for s in sorted(slices, key=lambda s: -s["func_count"]):
            out.append(f"| {s['vma_lo']}–{s['vma_hi']} | "
                       f"{s['func_count']} | `{s['placeholder_tu']}` | "
                       f"{s['rationale']} |\n")

    return "".join(out)


# ----------------------------------------------------------------- main

def main(argv: list[str]) -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--out-md", default=str(OUT_MD),
                    help="markdown output path (default: decomp/placement_plan.md)")
    ap.add_argument("--out-json", default=str(OUT_JSON),
                    help="json output path (default: decomp/placement_plan.json)")
    ap.add_argument("--limit", type=int, default=0,
                    help="if >0, only emit the first N rows (debugging)")
    ap.add_argument("--json-only", action="store_true",
                    help="skip markdown emission")
    ap.add_argument("--stdout", action="store_true",
                    help="print markdown to stdout instead of writing")
    args = ap.parse_args(argv)

    idx = Index()
    rows = build_function_rows(idx)
    if args.limit:
        rows = rows[: args.limit]
    slices = build_placeholder_slices(idx, rows)

    payload = emit_json(rows, slices)
    Path(args.out_json).write_text(json.dumps(payload, indent=2) + "\n")

    md = emit_markdown(rows, slices)
    if args.stdout:
        sys.stdout.write(md)
    elif not args.json_only:
        Path(args.out_md).write_text(md)

    n_high = sum(1 for r in rows if r["confidence"] == "high")
    n_med = sum(1 for r in rows if r["confidence"] == "medium")
    print(f"placement_plan: {len(rows)} candidates "
          f"({n_high} high, {n_med} medium), "
          f"{len(slices)} placeholder slices",
          file=sys.stderr)
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
