#!/usr/bin/env python3
import re, sys, os, glob
cands=[l.strip().split('\t') for l in open(sys.argv[1]) if '\t' in l]
names={c[1].strip():c[0] for c in cands}
pat=re.compile(r'\bjal\s+('+'|'.join(re.escape(n) for n in names)+r')\s*$')
chainpat=re.compile(r'(daddu|addu|move|daddiu|addiu)\s+\$2,\s*\$(29|sp)')
found={}
for f in glob.glob('asm/**/*.s',recursive=True):
    try: lines=open(f,encoding='utf-8',errors='replace').read().splitlines()
    except Exception: continue
    for i,ln in enumerate(lines):
        m=pat.search(ln)
        if m:
            nm=m.group(1)
            win=lines[max(0,i-3):i+2]
            chain=any(chainpat.search(w) for w in win)
            found.setdefault(nm,[]).append((os.path.basename(f)[:-2],chain))
for n,tu in sorted(names.items()):
    sites=found.get(n)
    if not sites: print(f"{tu:22s} {n:30s} no-caller")
    else:
        for c,ch in sites: print(f"{tu:22s} {n:30s} {'** CHAIN-SET **' if ch else 'no-chain'} caller={c}")
