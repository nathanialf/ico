#!/usr/bin/env python3
"""tools/global_flag_sweep.py — measure the net effect of a GLOBAL cflag change.

Workstream 1 of the "retire postprocessing / slash per-file cflags" plan. The
hypothesis: some per-file `config/extra_cflags.txt` overrides exist only because
our GLOBAL CFLAGS default is wrong. If the original ICO build used a given flag
globally, baking it in collapses the per-file overrides — but some currently
matching functions may then need the OPPOSITE flag per-file. The structural win
is whichever global yields FEWER total overrides, with the SHA-1 still reachable.

This harness MEASURES that, read-only (no permanent tree change):
  * Baseline: real_count for every matched func across the live corpus
    (src/ + sound/ + ios/ + isys/), via tools/match_diff.py --count.
  * Candidate: same, but with the candidate flag injected into the GLOBAL
    CFLAGS (env var that tools/quick_diff.sh honors) AND the matching per-file
    override lines temporarily removed from config/extra_cflags.txt.
  * Delta report: newly_break / newly_match / redundant_overrides /
    flipped_overrides / net override delta.

config/extra_cflags.txt is edited in place ONLY for the duration of a candidate
pass and restored in a `finally` (mirrors tools/type_entity.py's keep/revert).
Nothing else in the tree is touched; adoption (baking the global into
compile_c.sh + quick_diff.sh and editing the config for real) is a SEPARATE,
ninja-gated step the operator does by hand from this report.

Usage:
  tools/global_flag_sweep.py self-test
      Drop every `-fno-schedule-insns` line (no global added) and confirm the 15
      known TUs re-break — proves the measurement actually sees the flag.

  tools/global_flag_sweep.py sweep --candidate "-fno-schedule-insns2" \
        --remove-pattern "-fno-schedule-insns2?\b" --axis sched2 [--jobs 8] [--limit N]
      Measure baseline (cached) vs candidate; print the delta report as JSON+text.

  tools/global_flag_sweep.py baseline [--jobs 8]
      (Re)compute and cache the baseline only.
"""
from __future__ import annotations
import argparse
import json
import os
import re
import subprocess
import sys
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "tools"))
import tu_check  # matched_funcs / resolve_tu_path  # noqa: E402

MATCH_DIFF = ROOT / "tools" / "match_diff.py"
EXTRA_CFLAGS = ROOT / "config" / "extra_cflags.txt"
CACHE_DIR = ROOT / "build" / "flag_sweep"

# The exact default CFLAGS tools/quick_diff.sh uses (line 145). We replicate it
# so a candidate pass is "default + candidate flag" and the baseline (no env) is
# byte-identical to it. The -B<libdir> prefix quick_diff adds for ee-gcc is
# applied by quick_diff itself regardless of $CFLAGS, so we omit it here.
DEFAULT_CFLAGS = "-S -G 8 -O2 -mips3 -EL -fno-builtin -nostdinc -fdata-sections -Iinclude"

def _iter_tu_names():
    """Yield TU names as tu_check/quick_diff expect them. src/ is RECURSIVE:
    src/cod/<hex>.c -> "cod/<hex>", src/Foo.c -> "Foo". sound/ios/isys by stem.
    (parked tough_nuts/ excluded — not in the linked ELF)."""
    srcd = ROOT / "src"
    if srcd.is_dir():
        for c in sorted(srcd.rglob("*.c")):
            yield str(c.relative_to(srcd).with_suffix(""))
    for root in ("sound", "ios", "isys"):
        d = ROOT / root
        if d.is_dir():
            for c in sorted(d.glob("*.c")):
                yield c.stem


def tu_basename(tu: str) -> str:
    """The extra_cflags lookup key (uppercased) is the .c BASENAME, so cod/163F48
    -> 163F48. Map back via the basename, not the full TU path."""
    return tu.split("/")[-1]


def enumerate_corpus() -> list[tuple[str, list[str]]]:
    """[(tu, [matched funcs]), ...] for every live TU with matched C, sorted."""
    tus: dict[str, list[str]] = {}
    for tu in _iter_tu_names():
        if tu in tus:
            continue
        funcs = tu_check.matched_funcs(tu)
        if funcs:
            tus[tu] = funcs
    return sorted(tus.items())


def measure_tu(tu: str, funcs: list[str], env: dict | None) -> dict[str, int | None]:
    """real_count per func for ONE tu, sequentially (funcs in a TU share the
    build/quick_diff/<tu>.* scratch files, so they must not run concurrently)."""
    out: dict[str, int | None] = {}
    for fn in funcs:
        r = subprocess.run(
            [sys.executable, str(MATCH_DIFF), "--count", tu, fn],
            capture_output=True, text=True, cwd=str(ROOT), env=env)
        try:
            out[fn] = int(r.stdout.strip())
        except ValueError:
            out[fn] = None  # compile-fail / error
    return out


def measure_all(corpus, env: dict | None, jobs: int) -> dict[str, dict]:
    """{tu: {func: rc}} across the corpus; TUs run in parallel, funcs serial."""
    results: dict[str, dict] = {}
    with ThreadPoolExecutor(max_workers=jobs) as ex:
        futs = {ex.submit(measure_tu, tu, funcs, env): tu for tu, funcs in corpus}
        done = 0
        for fut in futs:
            pass  # submitted; iterate as_completed below
        from concurrent.futures import as_completed
        for fut in as_completed(futs):
            tu = futs[fut]
            results[tu] = fut.result()
            done += 1
            if done % 25 == 0 or done == len(futs):
                print(f"  measured {done}/{len(futs)} TUs", file=sys.stderr)
    return results


def cand_env(candidate: str | None) -> dict:
    env = dict(os.environ)
    env["CFLAGS"] = DEFAULT_CFLAGS + (f" {candidate}" if candidate else "")
    return env


def flatten(results: dict[str, dict]) -> dict[tuple[str, str], int | None]:
    return {(tu, fn): rc for tu, fns in results.items() for fn, rc in fns.items()}


# ----------------------------------------------------------------------------
# config/extra_cflags.txt temporary surgery (restored in finally)
# ----------------------------------------------------------------------------
def parse_overrides() -> list[tuple[str, str]]:
    """[(key, flags)] for each non-comment override line, in file order."""
    out = []
    for line in EXTRA_CFLAGS.read_text().splitlines():
        s = line.strip()
        if not s or s.startswith("#"):
            continue
        parts = s.split(None, 1)
        if len(parts) == 2:
            out.append((parts[0], parts[1]))
    return out


def drop_lines(pattern: str) -> tuple[str, list[tuple[str, str]]]:
    """Return (new_text, dropped[(key,flags)]) with every override line whose
    FLAGS match `pattern` removed. Comments/blank lines preserved."""
    rx = re.compile(pattern)
    kept, dropped = [], []
    for line in EXTRA_CFLAGS.read_text().splitlines():
        s = line.strip()
        if s and not s.startswith("#"):
            parts = s.split(None, 1)
            if len(parts) == 2 and rx.search(parts[1]):
                dropped.append((parts[0], parts[1]))
                continue
        kept.append(line)
    return "\n".join(kept) + "\n", dropped


# ----------------------------------------------------------------------------
def load_or_make_baseline(corpus, jobs: int, force: bool) -> dict[str, dict]:
    CACHE_DIR.mkdir(parents=True, exist_ok=True)
    cache = CACHE_DIR / "baseline.json"
    if cache.exists() and not force:
        return json.loads(cache.read_text())
    print("Measuring baseline (current tree, default CFLAGS)...", file=sys.stderr)
    base = measure_all(corpus, env=None, jobs=jobs)
    cache.write_text(json.dumps(base, indent=2))
    return base


def key_to_tu(key: str, corpus_tus: set[str]) -> str | None:
    """Map an extra_cflags KEY (uppercased TU basename, or hex file-off) to a
    live TU name if we can. Hex/file-off keys (src/cod/<HEX>) don't map to a
    src/<tu>.c name and are reported as-is."""
    lo = key.lower()
    for tu in corpus_tus:
        if tu_basename(tu).lower() == lo:
            return tu
    return None


def report(axis, candidate, base, cand, dropped, corpus):
    bflat, cflat = flatten(base), flatten(cand)
    corpus_tus = {tu for tu, _ in corpus}

    newly_break, newly_match, became_fail = [], [], []
    for k in cflat:
        b, c = bflat.get(k), cflat[k]
        if b == 0 and c not in (0, None) and c is not None and c != 0:
            newly_break.append((k, c))
        elif b not in (0, None) and c == 0:
            newly_match.append((k, b))
        if c is None and b is not None:
            became_fail.append(k)

    # Per-dropped-override verdict: did dropping the per-file line (now relying on
    # the candidate global) keep that TU's funcs matching?
    broken_tus = {tu for (tu, _fn), _c in newly_break}
    redundant, flipped = [], []
    for key, flags in dropped:
        tu = key_to_tu(key, corpus_tus)
        label = tu or f"{key} (file-off; not a src/<tu>.c)"
        if tu and tu in broken_tus:
            flipped.append((label, flags))
        else:
            redundant.append((label, flags))

    net = len(redundant) - len(flipped)  # lines removable minus opposite-flips needed

    summary = {
        "axis": axis,
        "candidate_global": candidate,
        "dropped_override_lines": len(dropped),
        "newly_break": [{"tu": k[0], "func": k[1], "rc": c} for k, c in newly_break],
        "newly_match": [{"tu": k[0], "func": k[1], "was_rc": b} for k, b in newly_match],
        "became_compile_fail": [{"tu": k[0], "func": k[1]} for k in became_fail],
        "redundant_overrides": [{"key": l, "flags": f} for l, f in redundant],
        "flipped_overrides": [{"key": l, "flags": f} for l, f in flipped],
        "net_override_delta": -net,  # negative = fewer total overrides = win
        "verdict": ("ADOPT-CANDIDATE (fewer overrides, but ninja-gate required)"
                    if net > 0 and not newly_break else
                    "NET-NEUTRAL/LOSS — do not adopt" if net <= 0 else
                    "MIXED — candidate removes overrides but BREAKS funcs that "
                    "need opposite per-file flags; weigh flipped vs redundant"),
    }
    return summary


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = ap.add_subparsers(dest="cmd", required=True)

    p_base = sub.add_parser("baseline", help="(re)compute the cached baseline")
    p_base.add_argument("--jobs", type=int, default=8)

    p_self = sub.add_parser("self-test", help="prove the harness sees a per-file flag")
    p_self.add_argument("--jobs", type=int, default=8)

    p_prune = sub.add_parser("prune", help="find per-file overrides that are redundant "
                             "(TU still matches without them) — quick_diff level")
    p_prune.add_argument("--jobs", type=int, default=8)

    p_sweep = sub.add_parser("sweep", help="measure a candidate global flag")
    p_sweep.add_argument("--candidate", required=True,
                         help="global flag(s) to inject, e.g. '-fno-schedule-insns2'")
    p_sweep.add_argument("--remove-pattern", required=True,
                         help="regex; per-file override lines whose FLAGS match are dropped")
    p_sweep.add_argument("--axis", default="custom")
    p_sweep.add_argument("--jobs", type=int, default=8)
    p_sweep.add_argument("--force-baseline", action="store_true")
    args = ap.parse_args()

    corpus = enumerate_corpus()
    total = sum(len(f) for _, f in corpus)
    print(f"corpus: {len(corpus)} TUs, {total} matched funcs", file=sys.stderr)

    if args.cmd == "baseline":
        load_or_make_baseline(corpus, args.jobs, force=True)
        print("baseline cached at build/flag_sweep/baseline.json")
        return 0

    if args.cmd == "self-test":
        # Drop all -fno-schedule-insns lines, NO global; the 15 known TUs must break.
        original = EXTRA_CFLAGS.read_text()
        new_text, dropped = drop_lines(r"-fno-schedule-insns\b")
        dropped_tus = sorted({k.lower() for k, _ in dropped})
        try:
            EXTRA_CFLAGS.write_text(new_text)
            # Only measure the affected TUs for speed.
            affected = [(tu, fns) for tu, fns in corpus
                        if tu_basename(tu).lower() in dropped_tus]
            res = measure_all(affected, env=None, jobs=args.jobs)
        finally:
            EXTRA_CFLAGS.write_text(original)
        broke = {tu: fns for tu, fns in res.items()
                 if any(rc not in (0, None) for rc in fns.values())}
        print(json.dumps({
            "dropped_lines": [k for k, _ in dropped],
            "affected_tus_measured": [tu for tu, _ in affected],
            "tus_that_broke": sorted(broke),
            "self_test": "PASS — dropping the flag re-breaks the TUs"
                         if broke else
                         "INCONCLUSIVE — nothing broke; measurement may not see the flag",
        }, indent=2))
        return 0 if broke else 1

    if args.cmd == "prune":
        # For each override line, drop ONLY it (no global), re-measure its TU.
        # All funcs still rc0 -> redundant. quick_diff is intra-function, so it
        # is authoritative for codegen flags (schedule/aliasing/strength-reduce)
        # but BLIND to layout flags (-malign-*): those are flagged ninja-only.
        overrides = parse_overrides()
        corpus_map = {tu: fns for tu, fns in corpus}
        corpus_tus = set(corpus_map)
        original = EXTRA_CFLAGS.read_text()
        redundant, load_bearing, layout_only, unresolved = [], [], [], []
        try:
            for key, flags in overrides:
                tu = key_to_tu(key, corpus_tus)
                if tu is None:
                    unresolved.append((key, flags)); continue
                if "-malign" in flags and "-fno-sch" not in flags \
                        and "aliasing" not in flags and "strength" not in flags:
                    layout_only.append((key, flags, tu)); continue
                # drop just this key's line(s)
                new_text, _ = drop_lines(re.escape(flags))
                # drop_lines matches on flags; if several keys share flags it drops
                # all — so instead drop by exact (key,flags) line.
                kept = []
                for line in original.splitlines():
                    s = line.strip()
                    if s and not s.startswith("#"):
                        p = s.split(None, 1)
                        if len(p) == 2 and p[0] == key and p[1] == flags:
                            continue
                    kept.append(line)
                EXTRA_CFLAGS.write_text("\n".join(kept) + "\n")
                res = measure_tu(tu, corpus_map[tu], env=None)
                if all(rc == 0 for rc in res.values()):
                    redundant.append((key, flags, tu))
                else:
                    load_bearing.append((key, flags, tu,
                                         {f: r for f, r in res.items() if r != 0}))
        finally:
            EXTRA_CFLAGS.write_text(original)
        out = {
            "redundant_overrides": [{"key": k, "flags": f, "tu": t}
                                    for k, f, t in redundant],
            "load_bearing": [{"key": k, "flags": f, "tu": t, "breaks": b}
                             for k, f, t, b in load_bearing],
            "layout_only_ninja_required": [{"key": k, "flags": f, "tu": t}
                                           for k, f, t in layout_only],
            "unresolved_keys": [{"key": k, "flags": f} for k, f in unresolved],
        }
        CACHE_DIR.mkdir(parents=True, exist_ok=True)
        (CACHE_DIR / "prune.json").write_text(json.dumps(out, indent=2))
        print(json.dumps(out, indent=2))
        print(f"\nredundant={len(redundant)} load_bearing={len(load_bearing)} "
              f"layout_only={len(layout_only)} unresolved={len(unresolved)}",
              file=sys.stderr)
        return 0

    if args.cmd == "sweep":
        base = load_or_make_baseline(corpus, args.jobs, force=args.force_baseline)
        original = EXTRA_CFLAGS.read_text()
        new_text, dropped = drop_lines(args.remove_pattern)
        print(f"dropping {len(dropped)} override line(s) matching "
              f"{args.remove_pattern!r}; injecting global {args.candidate!r}",
              file=sys.stderr)
        try:
            EXTRA_CFLAGS.write_text(new_text)
            cand = measure_all(corpus, env=cand_env(args.candidate), jobs=args.jobs)
        finally:
            EXTRA_CFLAGS.write_text(original)
        summary = report(args.axis, args.candidate, base, cand, dropped, corpus)
        out = CACHE_DIR / f"sweep-{args.axis}.json"
        out.write_text(json.dumps(summary, indent=2))
        # Human summary
        print(json.dumps(summary, indent=2))
        print(f"\n[{args.axis}] dropped={summary['dropped_override_lines']} "
              f"redundant={len(summary['redundant_overrides'])} "
              f"flipped={len(summary['flipped_overrides'])} "
              f"newly_break={len(summary['newly_break'])} "
              f"net_override_delta={summary['net_override_delta']}", file=sys.stderr)
        print(f"VERDICT: {summary['verdict']}", file=sys.stderr)
        print(f"(full report: {out})", file=sys.stderr)
        return 0

    return 2


if __name__ == "__main__":
    sys.exit(main())
