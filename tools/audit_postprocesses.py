#!/usr/bin/env python3
"""tools/postprocess_prune.py — find config-gated postprocesses that are now
no-ops (the TU still matches without them), the same mechanical redundancy check
that retired 8 cflag overrides.

Each config/<name>.txt allowlist gates a postprocess in BOTH compile_c.sh and
quick_diff.sh. Removing a TU's line disables the postprocess in the quick_diff
measurement, so for each entry we drop it, re-measure the TU via match_diff, and
report whether it still matches (redundant) or breaks (load-bearing).

quick_diff is INTRA-FUNCTION, so this is authoritative only for postprocesses
that change a function's own instruction stream (scheduling / operand order /
delay-slot fills). Cross-function / layout postprocesses (shared_sp_restore,
shared_jr_restore, dummy_sp_prologue, demote_p2align, no_trailing_nop) are
NINJA-ONLY and excluded by default — pass --include-layout to test them anyway
(redundant verdicts there MUST be ninja-confirmed before trusting).

Any redundant candidate must still be ninja-confirmed (rm the affected .o first,
see [[cflags_not_ninja_dep]]) before the line is removed for real.

Usage:
  tools/postprocess_prune.py [--configs a,b,c] [--include-layout] [--jobs 8]
"""
from __future__ import annotations
import argparse
import json
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "tools"))
import global_flag_sweep as gfs  # noqa: E402

# Postprocesses whose effect is intra-function (quick_diff can judge redundancy).
INTRA_FUNC = [
    "swap_addu_operands", "lui_const_swap",
    "move_sw_v0_before_lds", "early_body_swap", "v0_zero_in_bne_delay",
    "fill_beq_delay", "fill_blez_delay", "early_epilogue_restore",
    "unfold_ra_delay", "fcc_nop", "fcc_noreorder",
]
# Cross-function / layout — ninja-only; quick_diff verdicts here are unreliable.
LAYOUT = ["shared_sp_restore", "shared_jr_restore", "dummy_sp_prologue",
          "demote_p2align", "no_trailing_nop"]


def entries(cfg: Path):
    """[(key, full_line), ...] for each non-comment entry (key = first token)."""
    out = []
    for line in cfg.read_text().splitlines():
        s = line.strip()
        if not s or s.startswith("#"):
            continue
        out.append((s.split()[0], line))
    return out


def drop_entry(text: str, full_line: str) -> str:
    """Remove exactly one entry line."""
    keep = [ln for ln in text.splitlines() if ln != full_line]
    return "\n".join(keep) + "\n"


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--configs", default=None,
                    help="comma-separated config basenames (default: intra-func set)")
    ap.add_argument("--include-layout", action="store_true")
    ap.add_argument("--jobs", type=int, default=8)
    args = ap.parse_args()

    names = (args.configs.split(",") if args.configs
             else INTRA_FUNC + (LAYOUT if args.include_layout else []))

    corpus = gfs.enumerate_corpus()
    corpus_map = {tu: fns for tu, fns in corpus}
    corpus_tus = set(corpus_map)

    report = {}
    for name in names:
        cfg = ROOT / "config" / f"{name}.txt"
        if not cfg.exists():
            report[name] = {"error": "missing"}
            continue
        original = cfg.read_text()
        layout = name in LAYOUT
        redundant, load_bearing, unresolved = [], [], []
        try:
            for key, full_line in entries(cfg):
                tu = gfs.key_to_tu(key, corpus_tus)
                if tu is None:
                    unresolved.append(key); continue
                cfg.write_text(drop_entry(original, full_line))
                res = gfs.measure_tu(tu, corpus_map[tu], env=None)
                if all(rc == 0 for rc in res.values()):
                    redundant.append({"key": key, "tu": tu})
                else:
                    load_bearing.append({"key": key, "tu": tu,
                                         "breaks": {f: r for f, r in res.items() if r != 0}})
        finally:
            cfg.write_text(original)
        report[name] = {
            "layout_ninja_only": layout,
            "redundant": redundant,
            "load_bearing": load_bearing,
            "unresolved": unresolved,
        }
        tag = " [LAYOUT — ninja-confirm required]" if layout else ""
        print(f"{name}: redundant={len(redundant)} load_bearing={len(load_bearing)} "
              f"unresolved={len(unresolved)}{tag}", file=sys.stderr)

    gfs.CACHE_DIR.mkdir(parents=True, exist_ok=True)
    (gfs.CACHE_DIR / "pp_prune.json").write_text(json.dumps(report, indent=2))
    # Print just the redundant candidates compactly.
    allred = [(n, r["key"], r["tu"]) for n, d in report.items()
              if "redundant" in d for r in d["redundant"]]
    print(json.dumps({"redundant_candidates": [
        {"config": n, "key": k, "tu": t} for n, k, t in allred]}, indent=2))
    return 0


if __name__ == "__main__":
    sys.exit(main())
