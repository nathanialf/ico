#!/usr/bin/env python3
"""Flag nested-function candidates: $2 READ before being written, before any call."""
import re, sys, glob, os

STORES = {"sw","sh","sb","sd","swc1","sdc1","swl","swr","sdl","sdr","sq","cache"}
CALLS  = {"jal","jalr","j","b","bal"}
INSN = re.compile(r'^\s*/\*[^*]*\*/\s+(\S+)\s*(.*?)\s*$')

def regs(op):
    return re.findall(r'\$(\w+)', op)

def scan(path):
    lines = []
    for ln in open(path, encoding="utf-8", errors="replace"):
        m = INSN.match(ln)
        if m:
            lines.append((m.group(1), m.group(2)))
    written = set()
    for mn, ops in lines:
        base = mn.split('.')[0]
        parts = [p.strip() for p in ops.split(',')] if ops else []
        srcs, dst = [], None
        if base in STORES or base.startswith('b') or base in CALLS:
            srcs = regs(ops)
        elif parts:
            d = regs(parts[0])
            dst = d[0] if d else None
            srcs = regs(",".join(parts[1:]))
            # base register inside 0(...) of the first operand is a source
            if '(' in parts[0]:
                srcs += regs(parts[0])
                dst = None
        if '2' in srcs and '2' not in written:
            return True
        if dst:
            written.add(dst)
        if base in ('jal','jalr'):
            return False
    return False

hits = []
for f in sorted(glob.glob('asm/nonmatchings/**/*.s', recursive=True)):
    try:
        if scan(f):
            tu = f.split('/')[-2]; fn = os.path.basename(f)[:-2]
            hits.append((tu, fn))
    except Exception:
        pass
for tu, fn in hits:
    print(f"{tu}\t{fn}")
print(f"\n-- {len(hits)} candidates across all unmatched functions --", file=sys.stderr)
