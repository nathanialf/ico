#!/usr/bin/env python3
"""
tu_candidates.py — TU-first matching/coalesce candidate picker.

Replaces `gen_candidates.py`. Produces two views over the same data:

* `docs/tu_candidates.md` — TUs sorted close-to-done first. Each section
  lists the TU's remaining unmatched functions, bucketed by shape
  (4-insn leaf, 1-jal wrapper, etc.). Drives the new MATCH.md workflow.
* `docs/tu_coalesce.md` — TUs sorted by remaining `cod_shim` count
  desc. Drives the active coalesce sprint and PROMOTE.md picker.

Shape buckets are ported from `gen_candidates.py` (same definitions),
but funcs are scoped to their owning TU. Within each TU the bucket
ordering is preserved so the `feedback_fast_pass_subshape` win
(sub-clusters of 3-5 same-shape funcs match in batches) still works.

The script is intentionally cheap and idempotent. Failure prints a
warning and exits 0 — `make setup` must not fail because the
candidate report could not be regenerated.
"""

from __future__ import annotations

import argparse
import datetime as _dt
import glob
import json
import re
import sys
import time
from collections import defaultdict
from pathlib import Path

_HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(_HERE))
from find_leaves import Func, load_funcs  # noqa: E402
from tu_status import compute_tu_status  # noqa: E402

REPO = _HERE.parent
# Prefer the snapshot when present (active coalesce sprint periodically
# nukes asm/cod/*.s via `rm + make setup`; the analyzer pipeline reads
# the snapshot for stability — same convention as identify_tus.py and
# find_callgraph.py).
SNAPSHOT_GLOB = "decomp/asm_snapshot/cod/*.s"
LIVE_GLOB = "asm/cod/*.s"
DEFAULT_GLOB = (SNAPSHOT_GLOB
                if list((REPO / "decomp" / "asm_snapshot" / "cod").glob("*.s"))
                else LIVE_GLOB)
OUT_CANDIDATES = REPO / "docs" / "tu_candidates.md"
OUT_COALESCE = REPO / "docs" / "tu_coalesce.md"
OUT_JSON = REPO / "docs" / "tu_candidates.json"
TOUGH_NUTS_DIR = REPO / "tough_nuts"
TU_MAP_JSON = REPO / "decomp" / "tu_map.json"


# ----------------------------------- shape buckets (ported from gen_candidates)

def _no_vu(fn: Func) -> bool:
    return not fn.has_vu()


def _has_vu(fn: Func) -> bool:
    return fn.has_vu()


def _has_spill_reload(fn: Func) -> bool:
    for i in range(len(fn.insns) - 1):
        a = fn.insns[i]
        b = fn.insns[i + 1]
        if (a.startswith("sw") and "0($sp)" in a and "$a0" in a
                and b.startswith("lw") and "0($sp)" in b and "$a0" in b):
            return True
    return False


def _has_gp_rel(fn: Func) -> bool:
    return any("%gp_rel(" in ins for ins in fn.insns)


def _has_branch(fn: Func) -> bool:
    return any(re.match(r"^(beq|bne|beqz|bnez|bgez|bltz|bgtz|blez)", ins)
               for ins in fn.insns)


BUCKETS: list[tuple[str, str, callable]] = [
    ("leaf-4-0x10", "4-insn / 0x10 leaf (no jal/VU)",
     lambda fn: fn.size == 0x10 and len(fn.insns) == 4 and fn.jal_count() == 0 and _no_vu(fn)),
    ("leaf-5-0x14", "5-insn / 0x14 leaf (no jal/VU)",
     lambda fn: fn.size == 0x14 and len(fn.insns) == 5 and fn.jal_count() == 0 and _no_vu(fn)),
    ("leaf-6-0x18", "6-insn / 0x18 leaf (no jal/VU)",
     lambda fn: fn.size == 0x18 and len(fn.insns) == 6 and fn.jal_count() == 0 and _no_vu(fn)),
    ("leaf-7-0x1C", "7-insn / 0x1C leaf (no jal/VU)",
     lambda fn: fn.size == 0x1C and len(fn.insns) == 7 and fn.jal_count() == 0 and _no_vu(fn)),
    ("wrap-8-0x20", "8-insn / 0x20, 1 jal (passthrough)",
     lambda fn: fn.size == 0x20 and len(fn.insns) == 8 and fn.jal_count() == 1 and _no_vu(fn)),
    ("wrap-9-0x24", "9-insn / 0x24, 1 jal (wrapper + arg setup)",
     lambda fn: fn.size == 0x24 and len(fn.insns) == 9 and fn.jal_count() == 1 and _no_vu(fn)),
    ("wrap-1jal-0x28-0x30", "0x28-0x30, 1 jal (wrapper w/ buffer)",
     lambda fn: 0x28 <= fn.size <= 0x30 and fn.jal_count() == 1 and _no_vu(fn)),
    ("wrap-1jal-0x34-0x40", "0x34-0x40, 1 jal (wrapper w/ stack buffer)",
     lambda fn: 0x34 <= fn.size <= 0x40 and fn.jal_count() == 1 and _no_vu(fn)),
    ("wrap-spill-reload", "Spill+reload (volatile a0)",
     lambda fn: _has_spill_reload(fn) and _no_vu(fn) and fn.jal_count() >= 1),
    ("wrap-2jal-0x18-0x24", "0x18-0x24, 2 jal (compact 2-call)",
     lambda fn: 0x18 <= fn.size <= 0x24 and fn.jal_count() == 2 and _no_vu(fn)),
    ("wrap-2jal-0x28-0x40", "0x28-0x40, 2 jal (2-call mid)",
     lambda fn: 0x28 <= fn.size <= 0x40 and fn.jal_count() == 2 and _no_vu(fn)),
    ("wrap-3jal-mid", "0x28-0x40, 3 jal (3-call mid)",
     lambda fn: 0x28 <= fn.size <= 0x40 and fn.jal_count() == 3 and _no_vu(fn)),
    ("wrap-gp-1jal", "1 jal + %gp_rel (D[0] passthrough)",
     lambda fn: fn.jal_count() == 1 and _has_gp_rel(fn) and _no_vu(fn)),
    ("cond-deref-leaf", "Leaf w/ branch (cond-return / deref+if)",
     lambda fn: fn.jal_count() == 0 and _has_branch(fn) and _no_vu(fn) and 0x14 <= fn.size <= 0x30),
    ("wrap-1jal-0x40-0x60", "0x40-0x60, 1 jal (mid-size wrapper)",
     lambda fn: 0x40 <= fn.size <= 0x60 and fn.jal_count() == 1 and _no_vu(fn)),
    ("wrap-2jal-0x40-0x60", "0x40-0x60, 2 jal (2-call mid)",
     lambda fn: 0x40 <= fn.size <= 0x60 and fn.jal_count() == 2 and _no_vu(fn)),
    ("vu-leaf-4-0x10", "VU leaf, 4-insn / 0x10",
     lambda fn: fn.size == 0x10 and len(fn.insns) == 4 and fn.jal_count() == 0 and _has_vu(fn)),
    ("vu-leaf-56-0x14-0x18", "VU leaf, 5-6 insn / 0x14-0x18",
     lambda fn: fn.size in (0x14, 0x18) and len(fn.insns) in (5, 6)
                and fn.jal_count() == 0 and _has_vu(fn)),
]


LUI_HI_RE = re.compile(r"^lui\s+(\$\w+),\s*%hi\(")
ADDIU_LO_RE = re.compile(r"^addiu\s+(\$\w+),\s*\1,\s*%lo\(")
DADDU_ZERO_RE = re.compile(r"^daddu\s+\$\w+,\s*\$zero,\s*\$zero\b")
FLOAT_PAIR_RE = re.compile(r"^(mtc1|lwc1|swc1|cvt\.|mfc1)\b")


def _hard_pattern_penalty(fn: Func) -> int:
    penalty = 0
    insns = fn.insns
    for i, ins in enumerate(insns):
        m = LUI_HI_RE.match(ins)
        if not m:
            continue
        reg = m.group(1)
        for j in range(i + 1, len(insns)):
            n = ADDIU_LO_RE.match(insns[j])
            if n and n.group(1) == reg:
                if j != i + 1:
                    penalty += 2
                break
    for ins in insns:
        if DADDU_ZERO_RE.match(ins):
            penalty += 1
        if FLOAT_PAIR_RE.match(ins):
            penalty += 1
    return penalty


def _promise_key(fn: Func) -> tuple:
    return (_hard_pattern_penalty(fn), len(fn.insns), fn.size, fn.name)


def _bucket_for(fn: Func) -> str | None:
    for slug, _title, pred in BUCKETS:
        if pred(fn):
            return slug
    return None


# ----------------------------------- input joining

def _load_parked() -> set[str]:
    parked: set[str] = set()
    if not TOUGH_NUTS_DIR.is_dir():
        return parked
    for entry in TOUGH_NUTS_DIR.iterdir():
        if entry.is_dir() and entry.name.startswith("func_"):
            parked.add(entry.name)
    return parked


def _load_func_score0(parked: set[str]) -> set[str]:
    """Return names of parked funcs with at least one output-0-N
    (N>=1) score=0 hit — flagged so the report can sweep them first."""
    out: set[str] = set()
    runs_dir = REPO / "lib" / "decomp-permuter" / "runs"
    if not runs_dir.is_dir():
        return out
    for name in parked:
        run_dir = runs_dir / name
        if not run_dir.is_dir():
            continue
        for sd in run_dir.glob("output-0-*"):
            if sd.name == "output-0-base":
                continue
            score_file = sd / "score.txt"
            if score_file.exists() and score_file.read_text().strip() == "0":
                out.add(name)
                break
    return out


def _vma_to_funcname(vma: int) -> str:
    return f"func_{vma:08X}"


# ----------------------------------- per-TU candidate assembly

def build_tu_candidates(
    funcs_by_name: dict[str, Func],
    parked: set[str],
    score0: set[str],
) -> list[dict]:
    """Join tu_status rows with shape data for each TU's remaining
    unmatched funcs. Returns list of TU rows with embedded
    bucketed_funcs."""
    tu_rows = compute_tu_status()
    out = []
    for r in tu_rows:
        if r["complete"]:
            continue
        bucketed: dict[str, list[dict]] = defaultdict(list)
        unbucketed: list[dict] = []
        has_score0 = False
        for f in r["unmatched_funcs"]:
            name = _vma_to_funcname(f["vram"])
            if name in score0:
                has_score0 = True
            if name in parked:
                # Parked funcs are picked up by the permuter; the
                # matching loop ignores them. Drop from candidates.
                continue
            fn = funcs_by_name.get(name)
            entry = {
                "vram": f"0x{f['vram']:08X}",
                "file_off": f"0x{f['file_off']:08X}",
                "size": f["size"],
                "subseg_name": f["subseg_name"],
                "shape_bucket": None,
                "insns": None,
                "jals": None,
                "first_mnemonics": None,
                "penalty": None,
            }
            if fn is not None:
                entry["shape_bucket"] = _bucket_for(fn)
                entry["insns"] = len(fn.insns)
                entry["jals"] = fn.jal_count()
                entry["first_mnemonics"] = " ".join(fn.mnemonics[:4])
                entry["penalty"] = _hard_pattern_penalty(fn)
            if entry["shape_bucket"]:
                bucketed[entry["shape_bucket"]].append(entry)
            else:
                unbucketed.append(entry)
        for slug in bucketed:
            bucketed[slug].sort(key=lambda e: (e["penalty"] or 999,
                                                e["insns"] or 999,
                                                e["size"]))
        unbucketed.sort(key=lambda e: e["size"])
        out.append({
            "tu": r["tu"],
            "text_matched": r["text_matched"],
            "text_total": r["text_total"],
            "text_coalesced": r["text_coalesced"],
            "cod_shim": r["cod_shim"],
            "unmatched_insns": r["unmatched_insns"],
            "data_done": r["data_done"],
            "data_total": r["data_total"],
            "has_score0_permuter": has_score0,
            "match_pct": (r["text_matched"] / r["text_total"]
                          if r["text_total"] else 0.0),
            "bucketed_funcs": {k: bucketed[k] for k in bucketed},
            "unbucketed_funcs": unbucketed,
        })
    return out


# ----------------------------------- emitters

def _bucket_title(slug: str) -> str:
    for s, title, _ in BUCKETS:
        if s == slug:
            return title
    return slug


def _render_tu_section(tu: dict, limit: int) -> list[str]:
    lines = []
    lines.append(f"### {tu['tu']}")
    flag = " 🎯 score-0 permuter hit pending" if tu["has_score0_permuter"] else ""
    lines.append(f"_text {tu['text_matched']}/{tu['text_total']} "
                 f"({tu['match_pct']*100:.0f}%) · "
                 f"coal {tu['text_coalesced']}/{tu['text_total']} · "
                 f"cod {tu['cod_shim']} · "
                 f"uninsn {tu['unmatched_insns']} · "
                 f"data {tu['data_done']}/{tu['data_total']}_{flag}")
    lines.append("")
    if not tu["bucketed_funcs"] and not tu["unbucketed_funcs"]:
        lines.append("_(nothing pickable in defined buckets)_")
        lines.append("")
        return lines
    shown = 0
    for slug in tu["bucketed_funcs"]:
        items = tu["bucketed_funcs"][slug]
        if not items:
            continue
        lines.append(f"**{_bucket_title(slug)}** ({len(items)})")
        lines.append("")
        lines.append("| vram | size | insns | jal | first mnemonics |")
        lines.append("| --- | ---: | ---: | ---: | --- |")
        for e in items[:limit]:
            lines.append(f"| `{e['vram']}` | 0x{e['size']:X} | "
                         f"{e['insns']} | {e['jals']} | "
                         f"`{e['first_mnemonics'] or ''}` |")
            shown += 1
            if shown >= limit:
                break
        if len(items) > limit:
            lines.append(f"| … | | | | _{len(items)-limit} more_ |")
        lines.append("")
        if shown >= limit:
            break
    if tu["unbucketed_funcs"] and shown < limit:
        rem = limit - shown
        lines.append(f"**uncategorized** ({len(tu['unbucketed_funcs'])})")
        lines.append("")
        lines.append("| vram | size | subseg |")
        lines.append("| --- | ---: | --- |")
        for e in tu["unbucketed_funcs"][:rem]:
            lines.append(f"| `{e['vram']}` | 0x{e['size']:X} | "
                         f"{e['subseg_name']} |")
        if len(tu["unbucketed_funcs"]) > rem:
            lines.append(f"| … | | _{len(tu['unbucketed_funcs'])-rem} more_ |")
        lines.append("")
    return lines


def emit_candidates_md(tus: list[dict], top: int, per_tu_limit: int) -> str:
    """Close-to-done sort. Drives MATCH.md TU picker."""
    now = _dt.datetime.now(_dt.timezone.utc).strftime("%Y-%m-%d %H:%M:%S UTC")
    lines = []
    lines.append("# TU candidates — close-to-done first")
    lines.append("")
    lines.append("Auto-generated TU-first matching shortlist. Drives "
                 "`decomp/MATCH.md`'s TU picker. For the cod-shim "
                 "reduction view (active coalesce sprint), see "
                 "[`docs/tu_coalesce.md`](tu_coalesce.md).")
    lines.append("")
    lines.append(f"- Generated: {now}")
    lines.append("- Source: `tools/tu_candidates.py`")
    lines.append("- Regenerate: runs at end of `tools/build.sh setup`")
    lines.append("- Per-TU sort: close-to-done by text-matched ratio, "
                 "ties broken by remaining unmatched count.")
    lines.append("- Per-bucket sort: hard-pattern penalty, insn count, size.")
    lines.append(f"- Showing top {top} TUs, up to {per_tu_limit} funcs each.")
    lines.append("")
    ranked = sorted(tus, key=lambda t: (
        # Prefer TUs that have *some* matches already (compounding context).
        -t["match_pct"],
        # Then smaller remaining work.
        t["text_total"] - t["text_matched"],
        # Then larger TUs (higher impact when finished).
        -t["text_total"],
        t["tu"],
    ))
    lines.append("## Top picks")
    lines.append("")
    for tu in ranked[:top]:
        lines.extend(_render_tu_section(tu, per_tu_limit))
    return "\n".join(lines) + "\n"


def emit_coalesce_md(tus: list[dict], top: int, per_tu_limit: int) -> str:
    """cod_shim count desc sort. Drives PROMOTE.md / coalesce sprint."""
    now = _dt.datetime.now(_dt.timezone.utc).strftime("%Y-%m-%d %H:%M:%S UTC")
    lines = []
    lines.append("# TU coalesce queue — cod-shim count desc")
    lines.append("")
    lines.append("Auto-generated cod-shim reduction shortlist. Drives "
                 "the active coalesce sprint and `decomp/PROMOTE.md`. "
                 "For per-function placement recommendations see "
                 "[`decomp/placement_plan.md`](../decomp/placement_plan.md). "
                 "For the matching picker see "
                 "[`docs/tu_candidates.md`](tu_candidates.md).")
    lines.append("")
    lines.append(f"- Generated: {now}")
    lines.append("- Source: `tools/tu_candidates.py`")
    lines.append("- Per-TU sort: cod_shim count desc (most shims first).")
    lines.append("")
    total_shims = sum(t["cod_shim"] for t in tus)
    lines.append(f"**Total cod shims across all TUs: {total_shims}** "
                 "(reduction target).")
    lines.append("")
    ranked = sorted(tus, key=lambda t: (
        -t["cod_shim"],
        -t["text_total"],
        t["tu"],
    ))
    ranked = [t for t in ranked if t["cod_shim"] > 0]
    lines.append(f"## Top {min(top, len(ranked))} TUs by cod-shim count")
    lines.append("")
    for tu in ranked[:top]:
        lines.extend(_render_tu_section(tu, per_tu_limit))
    return "\n".join(lines) + "\n"


def emit_json(tus: list[dict]) -> str:
    return json.dumps(tus, indent=2) + "\n"


# ----------------------------------- main

def main(argv: list[str] | None = None) -> int:
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    ap.add_argument("--path", default=DEFAULT_GLOB,
                    help=f"glob for splat asm (default: {DEFAULT_GLOB})")
    ap.add_argument("--top", type=int, default=40,
                    help="max TUs per output (default: 40)")
    ap.add_argument("--per-tu-limit", type=int, default=30,
                    help="max funcs shown per TU (default: 30)")
    ap.add_argument("--rebuild-cache", action="store_true",
                    help="ignore the find_leaves.py cache")
    ap.add_argument("--candidates-out", default=str(OUT_CANDIDATES))
    ap.add_argument("--coalesce-out", default=str(OUT_COALESCE))
    ap.add_argument("--json-out", default=str(OUT_JSON))
    ap.add_argument("--stdout", action="store_true",
                    help="write candidates md to stdout, skip files")
    args = ap.parse_args(argv)

    paths = sorted(glob.glob(args.path))
    if not paths:
        print(f"tu_candidates: no files matched {args.path}",
              file=sys.stderr)
        return 0

    t0 = time.time()
    funcs = load_funcs(paths, rebuild=args.rebuild_cache)
    funcs_by_name = {f.name: f for f in funcs}
    parked = _load_parked()
    score0 = _load_func_score0(parked)
    tus = build_tu_candidates(funcs_by_name, parked, score0)
    elapsed = time.time() - t0

    cand_md = emit_candidates_md(tus, args.top, args.per_tu_limit)
    coal_md = emit_coalesce_md(tus, args.top, args.per_tu_limit)
    js = emit_json(tus)

    if args.stdout:
        sys.stdout.write(cand_md)
        return 0

    for path, body in ((args.candidates_out, cand_md),
                       (args.coalesce_out, coal_md),
                       (args.json_out, js)):
        p = Path(path)
        p.parent.mkdir(parents=True, exist_ok=True)
        p.write_text(body, encoding="utf-8")
    n_with_score0 = sum(1 for t in tus if t["has_score0_permuter"])
    print(f"tu_candidates: {len(tus)} incomplete TUs, "
          f"{sum(t['cod_shim'] for t in tus)} cod shims, "
          f"{n_with_score0} TUs with score-0 permuter hits "
          f"({elapsed:.2f}s)",
          file=sys.stderr)
    return 0


if __name__ == "__main__":
    try:
        sys.exit(main())
    except Exception as exc:  # noqa: BLE001 — never break `make setup`
        print(f"tu_candidates: WARNING — generation failed: {exc}",
              file=sys.stderr)
        sys.exit(0)
