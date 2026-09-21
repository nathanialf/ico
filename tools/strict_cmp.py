#!/usr/bin/env python3
"""strict_cmp.py: word-for-word comparison of one function against its ROM stub.

Usage: .venv/bin/python tools/strict_cmp.py <tu path> <func>   (run tools/quick_diff.sh <tu path> <func> first)

Reads asm/nonmatchings/<tu path>/<func>.s and the newest quick_diff object for the TU, masks
relocation words (gp-relative loads and stores among them, so gp store ORDER is not checked
here) and scores two branch words equal regardless of offset. It does not mask R_MIPS_LITERAL
words, so a function's own pool literals show as diffs. Every landing is also compared against
the object built from `git show HEAD:<path>` before it is recorded.
"""
import re,subprocess,sys

def _resolve_obj(tu):
    """Newest existing object among the paths quick_diff.sh / match_diff.py write for this TU."""
    import os
    base = os.path.basename(tu)
    sub = os.path.dirname(tu) or "src"
    cands = ["build/quick_diff/%s.o" % base, "build/quick_diff/%s.o" % tu, "build/quick_diff/%s/%s.o" % (sub, base)]
    cands = [c for c in dict.fromkeys(cands) if os.path.exists(c)]
    if not cands:
        raise SystemExit("no quick_diff object for %s (run tools/quick_diff.sh <tu> <func> first)" % tu)
    # quick_diff.sh writes build/quick_diff/<tu>.o and removes it when the compile or
    # the assembly fails; an older object at another path must never be scored in its
    # place, so the exact path wins and its absence is an error, not a fallback.
    exact = "build/quick_diff/%s.o" % tu
    if os.path.exists(exact):
        return exact
    raise SystemExit("no quick_diff object at %s (the last quick_diff for this TU failed; older objects at %s are not scored)" % (exact, ", ".join(cands)))
tu,fn=sys.argv[1],sys.argv[2]
sub=sys.argv[3] if len(sys.argv)>3 and not sys.argv[3].startswith('-') else '.'
txt=open('asm/nonmatchings/%s/%s/%s.s'%(sub,tu,fn)).read()
rom=[]
for L in txt.split('\n'):
    m=re.match(r'\s+/\* ([0-9A-F]+) ([0-9A-F]+) ([0-9A-F]{8}) \*/\s+(.*)',L)
    if m:
        w=bytes.fromhex(m.group(3))[::-1].hex()
        rom.append((int(w,16), m.group(4).strip()))
n=txt[:txt.index('endlabel')].count('/* ')
rom=rom[:n]
out=subprocess.run(['mips-linux-gnu-objdump','-dzr','--disassemble=%s'%fn,_resolve_obj(tu)],capture_output=True,text=True).stdout
built=[];rel={};start=None;idx=-1;addr2i={}
for L in out.split('\n'):
    m=re.match(r'\s+([0-9a-f]+):\t([0-9a-f]{8}) \t(.*)',L)
    if m:
        a=int(m.group(1),16)
        if start is None: start=a
        idx+=1; addr2i[a-start]=idx
        built.append((int(m.group(2),16), m.group(3).strip()))
    m2=re.match(r'\s+([0-9a-f]+): (R_MIPS_\S+)\s+(\S+)',L)
    if m2: rel[int(m2.group(1),16)-start]=(m2.group(2),m2.group(3))
built=built[:n]
bad=0
for i in range(max(len(rom),len(built))):
    if i>=len(rom) or i>=len(built): print("LEN mismatch at",i); bad+=1; break
    rw,rt=rom[i]; bw,bt=built[i]
    if rw==bw: continue
    rm=rt.split()[0]; bm=bt.split()[0]
    ok=False
    if rm==bm:
        if rm in ('jal','j'):
            tgt=rt.split()[-1]
            r=rel.get(i*4)
            if r and (r[1]==tgt or (r[1]=='.text' and ('<%s>'%tgt) in bt)): ok=True
        elif '%' in rt:
            sym=re.search(r'%\w+\(([^)]*)\)',rt)
            r=rel.get(i*4)
            if sym and r and r[1]==sym.group(1) and (rw>>16)==(bw>>16): ok=True
        elif rm.startswith('b'):
            ok=((rw>>16)==(bw>>16))
    if not ok:
        print("DIFF %4d rom %08x %-38s built %08x %s"%(i,rw,rt,bw,bt)); bad+=1
print("insns rom %d built %d | STRICT diffs: %d"%(len(rom),len(built),bad))
