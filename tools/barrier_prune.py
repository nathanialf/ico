#!/usr/bin/env python3
"""tools/barrier_prune.py — safely prune redundant memory-clobber barriers
(DEFEAT_TCO / MEM_BARRIER / KEEP_LIVE_MEM) that crutch_prune deliberately skips.

These barriers' real effect is often store ORDERING, which quick_diff cannot see
(it gp-masks store offsets). So instead of match_diff, this verifies via an
OBJECT-level self-diff that IS reloc-aware:

  compile the TU with the barrier  -> reference  objdump -dr of .text
  compile the TU without it        -> candidate  objdump -dr of .text
  identical (instructions AND relocation order/targets) => removal is a no-op at
  link time (same .text bytes + same relocs => same linked output) => redundant.

This is SOUND without linking: two .o's with identical .text bytes and identical
relocations link to identical bytes. Greedy removal compares each cumulative
variant against the ORIGINAL .o, so the final file's object is byte-equal to the
original's. ninja is still run at the end as the whole-tree backstop.

Usage:
  tools/barrier_prune.py --scan [--files a,b]      # report redundant barriers
  tools/barrier_prune.py --apply src/foo.c         # greedily remove, leave edited
  tools/barrier_prune.py --apply-all [--exclude ..][--jobs N]
"""
from __future__ import annotations
import argparse
import json
import re
import subprocess
import sys
import tempfile
from concurrent.futures import ThreadPoolExecutor, as_completed
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "tools"))
import crutch_prune as cp  # file_to_tu, find helpers  # noqa: E402

COMPILE = ROOT / "tools" / "compile_c.sh"
OBJDUMP = "mips-linux-gnu-objdump"

BARRIER_RE = re.compile(r'\b(DEFEAT_TCO|MEM_BARRIER|KEEP_LIVE_MEM)\s*\([^;]*\)\s*;')
# Register-crutch patterns (used with --include-reg); object-self-diff verifies
# them just as soundly as barriers, so this also handles the files crutch_prune
# had to skip (matched func nonzero at baseline / postprocess-dependent).
REG_STMT_RE = re.compile(
    r'\b(KEEP_LIVE_FP2|KEEP_LIVE_FP|KEEP_LIVE|MATERIALIZE|ANCHOR)\s*\([^;]*\)\s*;')
REG_PIN_RE = re.compile(r'\s*REG\("\$[0-9a-zA-Z]+"\)')

INCLUDE_REG = False  # set by main when --include-reg

_ADDR = re.compile(r'^\s*[0-9a-f]+:\s+[0-9a-f]+\s+')      # instruction addr+bytes
_RELOC = re.compile(r'^\s*[0-9a-f]+:\s+(R_[A-Z0-9_]+\s+\S+)')  # reloc line


def objdump_text(o: Path) -> list[str] | None:
    """Reloc-annotated, address-stripped .text stream of the .o. None on failure."""
    # -z: don't collapse runs of >=3 identical instructions (padding nops) to a
    # single '...' line, which would silently drop them from the compared stream
    # (same bug fixed in quick_diff.sh 2026-06-04).
    r = subprocess.run([OBJDUMP, "-drz", "-j", ".text", str(o)],
                       capture_output=True, text=True)
    if r.returncode != 0:
        return None
    out = []
    for line in r.stdout.splitlines():
        m = _RELOC.match(line)
        if m:
            out.append(m.group(1)); continue
        if _ADDR.match(line):
            out.append(_ADDR.sub("", line).rstrip())
    return out


def compile_text(src: Path) -> list[str] | None:
    """Compile src via the real pipeline and return its .text reloc stream."""
    with tempfile.TemporaryDirectory() as td:
        o = Path(td) / "x.o"
        r = subprocess.run([str(COMPILE), str(src), str(o)],
                           capture_output=True, text=True, cwd=str(ROOT))
        if r.returncode != 0 or not o.exists():
            return None
        return objdump_text(o)


def occurrences(text: str):
    occ = [(m.start(), m.end(), m.group(1), m.group(0).strip())
           for m in BARRIER_RE.finditer(text)]
    if INCLUDE_REG:
        occ += [(m.start(), m.end(), m.group(1), m.group(0).strip())
                for m in REG_STMT_RE.finditer(text)]
        occ += [(m.start(), m.end(), "REG", m.group(0).strip())
                for m in REG_PIN_RE.finditer(text)]
        occ.sort()
    return occ


def process_file(path: Path, apply: bool):
    original = path.read_text(errors="replace")
    occ = occurrences(original)
    if not occ:
        return {"file": str(path.relative_to(ROOT)), "barriers": 0,
                "redundant": [], "load_bearing": []}
    ref = compile_text(path)
    if ref is None:
        return {"file": str(path.relative_to(ROOT)), "error": "ref compile failed"}
    text = original
    redundant, load_bearing, rejected = [], [], set()
    try:
        while True:
            progressed = False
            for (s, e, kind, snip) in occurrences(text):
                tag = (kind, snip, s)
                if tag in rejected:
                    continue
                cand = text[:s] + text[e:]
                path.write_text(cand)
                ct = compile_text(path)
                if ct is not None and ct == ref:
                    redundant.append({"kind": kind, "snippet": snip})
                    text = cand
                    progressed = True
                    break
                rejected.add(tag)
                if ct is not None and ct != ref:
                    pass  # load-bearing; recorded once below
            if not progressed:
                break
        # tally load-bearing (those rejected)
        for (kind, snip, _s) in rejected:
            load_bearing.append({"kind": kind, "snippet": snip})
        if apply:
            path.write_text(text)   # keep greedy-clean version
        else:
            path.write_text(original)
    except BaseException:
        path.write_text(original)
        raise
    return {"file": str(path.relative_to(ROOT)), "tu": cp.file_to_tu(path),
            "barriers": len(occ), "removed": len(redundant),
            "redundant": redundant, "load_bearing_count": len(set(
                (lb["kind"], lb["snippet"]) for lb in load_bearing))}


def barrier_files():
    pats = ("DEFEAT_TCO", "MEM_BARRIER", "KEEP_LIVE_MEM")
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
    ap.add_argument("--scan", action="store_true")
    ap.add_argument("--apply", default=None)
    ap.add_argument("--apply-all", action="store_true")
    ap.add_argument("--files", default=None)
    ap.add_argument("--exclude", default="")
    ap.add_argument("--include-reg", action="store_true",
                    help="also prune register crutches (REG/KEEP_LIVE/ANCHOR/"
                         "MATERIALIZE) via the same object-self-diff")
    ap.add_argument("--jobs", type=int, default=8)
    args = ap.parse_args()

    global INCLUDE_REG
    INCLUDE_REG = args.include_reg

    if args.apply:
        print(json.dumps(process_file(ROOT / args.apply, apply=True), indent=2))
        return 0

    if args.files:
        files = [ROOT / f for f in args.files.split(",")]
    else:
        files = barrier_files()
    if args.exclude:
        excl = {(ROOT / e).resolve() for e in args.exclude.split(",") if e}
        files = [f for f in files if f.resolve() not in excl]

    apply = args.apply_all
    print(f"{'apply' if apply else 'scan'} over {len(files)} barrier file(s)",
          file=sys.stderr)
    results = []
    with ThreadPoolExecutor(max_workers=args.jobs) as ex:
        futs = {ex.submit(process_file, f, apply): f for f in files}
        done = 0
        for fut in as_completed(futs):
            r = fut.result(); results.append(r); done += 1
            if r.get("removed") or r.get("error"):
                print(f"  [{done}/{len(files)}] {r['file']}: removed={r.get('removed',0)}"
                      f" load_bearing={r.get('load_bearing_count',0)}"
                      f"{' ERR:'+r['error'] if r.get('error') else ''}", file=sys.stderr)
    cp.gfs.CACHE_DIR.mkdir(parents=True, exist_ok=True)
    (cp.gfs.CACHE_DIR / "barrier_prune.json").write_text(json.dumps(results, indent=2))
    tot = sum(r.get("removed", 0) for r in results)
    print(json.dumps({"files": len(results), "total_removed": tot,
                      "edited": [r["file"] for r in results if r.get("removed")]},
                     indent=2))
    return 0


if __name__ == "__main__":
    sys.exit(main())
