#!/usr/bin/env python3
"""tools/crutch_prune.py — find inline-asm matching crutches that are REDUNDANT
(the function still matches byte-for-byte without them).

Workstream 3. Many REG()/ANCHOR/KEEP_LIVE/MEM_BARRIER/DEFEAT_TCO/MATERIALIZE
sites are DEFENSIVE — ee-gcc would make the same choice without them. Those bend
the source away from the developer's C for no benefit. This neutralizes each
crutch one at a time, recompiles, and re-measures every matched func in the TU
via match_diff; a crutch whose removal keeps ALL funcs at real_count 0 is
redundant and can be deleted (clean-first, match preserved).

Neutralization:
  * statement macros (KEEP_LIVE/KEEP_LIVE_*/ANCHOR/MEM_BARRIER/DEFEAT_TCO/
    MATERIALIZE) -> the whole `MACRO(...);` is removed.
  * REG("$N") pins -> the ` REG("$N")` token is stripped from the declaration
    (the variable stays, just unpinned).
VU0_*/r5900 intrinsics, NOP(), DEAD_DADDU_V0_SP and LA_SPLIT are NOT touched
(real ops / structural). quick_diff is intra-function, so layout-only effects are
not judged here — every redundant verdict is ninja-confirmed before deletion.

Edits the real src file (quick_diff reads it) and restores in `finally`.

Usage:
  tools/crutch_prune.py [--files src/switch.c,src/act-game.c] [--jobs 8]
  tools/crutch_prune.py            # every src/ios/sound/isys file with a crutch
"""
from __future__ import annotations
import argparse
import json
import re
import sys
from concurrent.futures import ThreadPoolExecutor, as_completed
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "tools"))
import global_flag_sweep as gfs  # noqa: E402
import tu_check  # noqa: E402

STMT_RE = re.compile(
    r'\b(DEFEAT_TCO|KEEP_LIVE_MEM|KEEP_LIVE_FP2|KEEP_LIVE_FP|KEEP_LIVE'
    r'|MATERIALIZE|ANCHOR|MEM_BARRIER)\s*\([^;]*\)\s*;')
REG_RE = re.compile(r'\s*REG\("\$[0-9a-zA-Z]+"\)')


def file_to_tu(path: Path) -> str:
    """src/cod/x.c -> cod/x ; src/Foo.c -> Foo ; ios/y.c -> y."""
    rel = path.relative_to(ROOT)
    parts = rel.parts
    if parts[0] == "src":
        return str(Path(*parts[1:]).with_suffix(""))
    return path.stem


def occurrences(text: str):
    """[(start, end, kind, snippet), ...] for every neutralizable crutch."""
    occ = []
    for m in STMT_RE.finditer(text):
        occ.append((m.start(), m.end(), m.group(1), m.group(0).strip()))
    for m in REG_RE.finditer(text):
        occ.append((m.start(), m.end(), "REG", m.group(0).strip()))
    occ.sort()
    return occ


def prune_file(path: Path):
    tu = file_to_tu(path)
    funcs = tu_check.matched_funcs(tu)
    original = path.read_text(errors="replace")
    occ = occurrences(original)
    if not funcs or not occ:
        return {"file": str(path.relative_to(ROOT)), "tu": tu,
                "matched_funcs": len(funcs), "crutches": len(occ),
                "redundant": [], "load_bearing": [], "skipped": not funcs}
    # baseline: TU must be clean to start (else we can't attribute changes)
    base = gfs.measure_tu(tu, funcs, env=None)
    redundant, load_bearing = [], []
    try:
        for (s, e, kind, snippet) in occ:
            variant = original[:s] + ("" if kind != "REG" else "") + original[e:]
            path.write_text(variant)
            res = gfs.measure_tu(tu, funcs, env=None)
            # redundant iff no func got WORSE than baseline (all still 0 where base 0)
            worse = {f: res[f] for f in funcs
                     if (res.get(f) or 0) != 0 and (base.get(f) or 0) == 0}
            (load_bearing if worse else redundant).append(
                {"kind": kind, "snippet": snippet, "pos": s,
                 **({"breaks": worse} if worse else {})})
    finally:
        path.write_text(original)
    return {"file": str(path.relative_to(ROOT)), "tu": tu,
            "matched_funcs": len(funcs), "crutches": len(occ),
            "baseline_dirty": [f for f in funcs if (base.get(f) or 0) != 0],
            "redundant": redundant, "load_bearing": load_bearing}


def apply_file(path: Path):
    """Remove a file's independently-redundant crutches, then verify the COMBINED
    removal still matches (interactions can make a set that's individually safe
    break together). Keeps the edit only if all funcs stay clean; else reverts and
    greedily backs off. Returns the outcome dict. ninja-confirm separately."""
    tu = file_to_tu(path)
    funcs = tu_check.matched_funcs(tu)
    original = path.read_text(errors="replace")
    base = gfs.measure_tu(tu, funcs, env=None)
    dirty = [f for f in funcs if (base.get(f) or 0) != 0]
    if dirty:
        return {"file": str(path.relative_to(ROOT)), "tu": tu,
                "error": "baseline dirty", "dirty": dirty}

    def clean_with(text):
        path.write_text(text)
        res = gfs.measure_tu(tu, funcs, env=None)
        return all((res.get(f) or 0) == 0 for f in funcs), res

    # Greedy: repeatedly remove the first crutch whose removal keeps the TU clean,
    # restarting after each success so positions stay valid and interactions show.
    text = original
    removed, rejected = [], set()
    while True:
        progressed = False
        for (s, e, kind, snip) in occurrences(text):
            tag = (kind, snip, s)
            if tag in rejected:
                continue
            ok, _ = clean_with(text[:s] + text[e:])
            if ok:
                text = text[:s] + text[e:]
                removed.append({"kind": kind, "snippet": snip})
                progressed = True
                break
            rejected.add(tag)
        if not progressed:
            break
    path.write_text(text)  # final greedy-clean version
    ok, final = clean_with(text)
    return {"file": str(path.relative_to(ROOT)), "tu": tu,
            "removed": removed, "removed_count": len(removed),
            "still_present": len(occurrences(text)),
            "quick_diff_clean": ok,
            "note": "ninja-confirm required (rm the .o first)"}


def find_crutch_files():
    pats = ("REG(", "ANCHOR(", "MEM_BARRIER(", "KEEP_LIVE", "DEFEAT_TCO", "MATERIALIZE(")
    out = []
    for root in ("src", "ios", "sound", "isys"):
        d = ROOT / root
        if not d.is_dir():
            continue
        it = d.rglob("*.c") if root == "src" else d.glob("*.c")
        for c in sorted(it):
            t = c.read_text(errors="replace")
            if any(p in t for p in pats):
                out.append(c)
    return out


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--files", default=None,
                    help="comma-separated file paths (default: all crutch files)")
    ap.add_argument("--apply", default=None,
                    help="greedily remove redundant crutches from ONE file, keeping "
                         "the match; leaves the file edited for ninja-confirm")
    ap.add_argument("--jobs", type=int, default=8)
    args = ap.parse_args()

    if args.apply:
        out = apply_file(ROOT / args.apply)
        print(json.dumps(out, indent=2))
        return 0

    if args.files:
        files = [ROOT / f for f in args.files.split(",")]
    else:
        files = find_crutch_files()
    print(f"scanning {len(files)} file(s) for redundant crutches", file=sys.stderr)

    results = []
    # Parallelize across FILES (each edits its own src file; build dirs are
    # per-TU so no collision). Crutches within a file are tested sequentially.
    with ThreadPoolExecutor(max_workers=args.jobs) as ex:
        futs = {ex.submit(prune_file, f): f for f in files}
        done = 0
        for fut in as_completed(futs):
            results.append(fut.result())
            done += 1
            r = results[-1]
            if r.get("redundant") or r.get("load_bearing"):
                print(f"  [{done}/{len(files)}] {r['file']}: "
                      f"redundant={len(r['redundant'])} "
                      f"load_bearing={len(r['load_bearing'])}"
                      + (" DIRTY-BASELINE!" if r.get('baseline_dirty') else ""),
                      file=sys.stderr)
    gfs.CACHE_DIR.mkdir(parents=True, exist_ok=True)
    (gfs.CACHE_DIR / "crutch_prune.json").write_text(json.dumps(results, indent=2))
    tot_red = sum(len(r["redundant"]) for r in results)
    tot_lb = sum(len(r["load_bearing"]) for r in results)
    print(json.dumps({"files": len(results), "redundant_total": tot_red,
                      "load_bearing_total": tot_lb,
                      "by_file": [{"file": r["file"], "redundant": len(r["redundant"]),
                                   "load_bearing": len(r["load_bearing"])}
                                  for r in results if r["redundant"]]}, indent=2))
    return 0


if __name__ == "__main__":
    sys.exit(main())
