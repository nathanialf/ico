#!/usr/bin/env python3
"""Find the `p ? *p : DFLT` signature: gp-rel ADDRESS materialised into a reg,
then that reg tested with bnez/beqz.  (`la` of a small object == addiu rN,$28,%gp_rel)"""
import re, glob, os, sys
ADDR = re.compile(r'addiu\s+\$(\d+),\s*\$28,\s*%gp_rel\((\w+)\)')
TEST = re.compile(r'\b(bnez|beqz|bne|beq)\s+\$(\d+),')
INSN = re.compile(r'^\s*/\*[^*]*\*/\s+(.*?)\s*$')
hits = {}
for f in sorted(glob.glob('asm/nonmatchings/**/*.s', recursive=True)):
    try: lines = [m.group(1) for m in (INSN.match(l) for l in open(f, encoding='utf-8', errors='replace')) if m]
    except Exception: continue
    pend = {}   # reg -> (sym, idx)
    for i, ln in enumerate(lines):
        a = ADDR.search(ln)
        if a:
            pend[a.group(1)] = (a.group(2), i)
            continue
        t = TEST.search(ln)
        if t:
            r = t.group(2)
            if r in pend:
                sym, j = pend[r]
                # test must be a zero-test: bnez/beqz, or bne/beq against $0
                if t.group(1) in ('bnez','beqz') or ',$0,' in ln.replace(' ','') or ', $0,' in ln:
                    tu = f.split('/')[-2]; fn = os.path.basename(f)[:-2]
                    hits.setdefault((tu, fn), set()).add(sym)
        # a redefinition of the reg clears it
        m = re.match(r'\s*\S+\s+\$(\d+)\s*,', ln)
        if m and m.group(1) in pend and not a:
            if not TEST.search(ln): pend.pop(m.group(1), None)
for (tu, fn), syms in sorted(hits.items()):
    print(f"{tu}\t{fn}\t{','.join(sorted(syms))}")
print(f"\n-- {len(hits)} unmatched functions carry the address-test signature --", file=sys.stderr)
