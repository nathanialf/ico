#!/usr/bin/env python3
"""List the smallest unmatched matching candidates.

aug6: the .text is carved per translation unit along MAIN.MAP boundaries
(baserom/aug6/text_tu_boundaries.txt), not per-function. So the candidate
shortlist is the smallest ico2000.a TUs not yet flipped to `c` in the yaml,
annotated with function count (named + static) and retail_seed availability.

us (retail): per-function nonmatchings is the model — handled by self-monitor's
existing awk; this tool just prints a pointer there.
"""
from __future__ import annotations
import re, sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parent))
from ico_version import detect_version

REPO = Path(__file__).resolve().parent.parent
V = detect_version(REPO)
N = int(sys.argv[1]) if len(sys.argv) > 1 else 12

if V != "aug6":
    print(f"list_candidates: version '{V}' uses per-function nonmatchings "
          "(see self-monitor's smallest-func list).")
    sys.exit(0)

bounds = REPO / "baserom" / "aug6" / "text_tu_boundaries.txt"
yaml = REPO / "config" / "ico.aug6.yaml"
textasm = REPO / "asm" / "aug6" / "src" / "cod" / "000000.s"
if not bounds.exists():
    sys.exit(f"list_candidates: {bounds} missing")

# carved TUs: yaml subsegment lines `[ADDR, c, src/<TU>]`
carved = set()
if yaml.exists():
    for ln in yaml.read_text().splitlines():
        m = re.search(r'\[\s*0x[0-9A-Fa-f]+\s*,\s*c\s*,\s*\S*?/?([A-Za-z0-9_-]+)\s*\]', ln)
        if m:
            carved.add(m.group(1))

# function start addresses from the disassembly (named + func_), for per-TU counts
func_vmas = []
if textasm.exists():
    cur = False
    for ln in textasm.read_text().splitlines():
        if ln.startswith("glabel "):
            cur = True; continue
        if cur:
            m = re.search(r'/\* ([0-9A-Fa-f]{5,8}) ', ln)
            if m:
                v = int(m.group(1), 16)
                func_vmas.append(v if v >= 0x100000 else 0x100000 + v)
                cur = False
func_vmas.sort()
import bisect

rows = []
for ln in bounds.read_text().splitlines():
    p = ln.split()
    if len(p) < 3 or not p[2].startswith("ico2000.a("):
        continue
    st, en = int(p[0], 16), int(p[1], 16)
    tu = p[2][len("ico2000.a("):-3]
    if tu in carved:
        continue
    nfuncs = bisect.bisect_left(func_vmas, en) - bisect.bisect_left(func_vmas, st)
    seed = (REPO / "retail_seed" / "src" / f"{tu}.c").exists()
    rows.append((en - st, nfuncs, st, tu, seed))

rows.sort()
print(f"Smallest unmatched aug6 TUs ({len(rows)} uncarved ico2000.a TUs; {len(carved)} carved):")
print(f"  {'size':>5} {'funcs':>5} {'vma':>9}  TU  (seed?)")
for size, nf, st, tu, seed in rows[:N]:
    print(f"  {size:5d} {nf:5d} 0x{st:08X}  {tu}{'  [retail_seed]' if seed else ''}")
