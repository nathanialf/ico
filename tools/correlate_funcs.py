#!/usr/bin/env python3
"""Recover dev names + source tree for baseelf.rom functions via ordinal
correlation to the prototype metadata.

baseelf.rom (release boot ELF) has different addresses than MAIN.MAP / TRFILE
(different builds), but the function/file LINK ORDER is identical across builds.
So: anchor baseelf.rom functions to files via the __FILE__ census (rom-native),
then align each file's functions, in address order, to TRFILE's functions for
that file -> recover {name, dev-path}.
"""
from __future__ import annotations
import json, re, struct, bisect
from pathlib import Path
from collections import defaultdict, Counter
ROOT=Path(__file__).resolve().parent.parent; AUG=ROOT/"baserom"/"aug6"
rom=(AUG/"baseelf.rom").read_bytes(); TB,TS=0x100000,0x16b964
def w(o): return struct.unpack_from("<I",rom,o)[0]
JR=0x03e00008
def is_term(x):
    op=(x>>26)&0x3f; return x==JR or op==2 or (op==0 and (x&0x3f)==8)
def br(o):
    x=w(o);op=(x>>26)&0x3f
    if op in(0x04,0x05,0x06,0x07,0x14,0x15,0x16,0x17) or op==1 or (op==0x11 and ((x>>21)&0x1f)==8):
        i=x&0xffff; i-=0x10000 if i>=0x8000 else 0; return TB+o+4+i*4
    return None
# function boundaries (branch-aware)
funcs=[]; start=TB; mbt=TB; o=0
while o<TS:
    va=TB+o; x=w(o); t=br(o)
    if t and t>mbt: mbt=t
    if is_term(x):
        end=va+8
        if mbt<=va+4:
            funcs.append([start,end]); ns=end
            while ns-TB<TS and w(ns-TB)==0: ns+=4
            start=ns; mbt=ns; o=ns-TB; continue
    o+=4
if start<TB+TS: funcs.append([start,TB+TS])
# __FILE__ strings + census -> anchor basenames
strs={}
for m in re.finditer(rb'[ -~]{3,}\.[ch]\x00', rom[0x270a80-TB:0x62aa68-TB]):
    s=m.group()[:-1].decode('latin1')
    if s.endswith(('.c','.h')): strs.setdefault(0x270a80+m.start(),s)
def base(f): return f.rsplit('/',1)[-1]
def census(s,e):
    his={}
    for q in range(s-TB,min(e,TB+TS)-TB,4):
        x=w(q);op=(x>>26)&0x3f
        if op==0x0f: his[(x>>16)&0x1f]=(x&0xffff)<<16
        elif op in(0x09,0x0d,0x23,0x2b):
            rs=(x>>21)&0x1f;lo=x&0xffff; lo-=0x10000 if lo>=0x8000 else 0
            if rs in his and his[rs]+lo in strs: return base(strs[his[rs]+lo])
    return None
anchor=[None]*len(funcs)
for i,(s,e) in enumerate(funcs):
    f=census(s,e)
    if f and f.endswith('.c'): anchor[i]=f
# assign every func a file: forward+backward fill, split gaps at midpoint
fileof=[None]*len(funcs)
last=None
for i in range(len(funcs)):
    if anchor[i]: last=anchor[i]
    fileof[i]=last
# backfill leading + correct gaps where next anchor differs (split at midpoint)
nxt=None
for i in range(len(funcs)-1,-1,-1):
    if anchor[i]: nxt=anchor[i]
    if fileof[i] is None: fileof[i]=nxt
# TRFILE: per-file ordered function names + dev-paths
tr=[]
for l in (AUG/"TRFILE.TXT").read_text(encoding='latin1').splitlines():
    p=l.split(':')
    if len(p)<7: continue
    try: a=int(p[0],16)
    except: continue
    fn=p[4].rstrip('()'); fl=p[5]
    if fl.endswith('.c'): tr.append((a,fn,fl))
tr.sort()
# per basename: ordered distinct func names + a representative dev-path
tr_byfile=defaultdict(list); devpath={}
seen=set()
for a,fn,fl in tr:
    b=base(fl); devpath[b]=fl
    if (b,fn) not in seen:
        seen.add((b,fn)); tr_byfile[b].append(fn)
# per-file ordinal alignment
table={}; named=0
romfile=defaultdict(list)
for i,(s,e) in enumerate(funcs): romfile[fileof[i]].append(i)
for bfile, idxs in romfile.items():
    names=tr_byfile.get(bfile,[]) if bfile else []
    dp=devpath.get(bfile, "src/"+bfile if bfile else None)
    for k,i in enumerate(idxs):
        s,e=funcs[i]
        nm=names[k] if k<len(names) else f"func_{s:08X}"
        if k<len(names): named+=1
        table[f"0x{s:08X}"]={"start":s,"end":e,"name":nm,
            "file":dp,"dir":('/'.join(dp.split('/')[:-1]) if dp else None),
            "anchored":anchor[i] is not None}
out=ROOT/"decomp"/"aug6_func_table.json"; out.write_text(json.dumps(table,indent=0))
print(f"functions: {len(funcs)}  named via correlation: {named}  ({100*named/len(funcs):.0f}%)")
print(f"assigned to a file: {sum(1 for v in table.values() if v['file'])}")
print(f"wrote {out.relative_to(ROOT)}")
dirs=Counter(v['dir'] for v in table.values() if v['dir'])
print("by dev dir:"); [print(f"  {c:5} {d}/") for d,c in dirs.most_common(14)]
# spot-check: clothTest functions
ct=[(v['start'],v['name']) for v in table.values() if v['file'] and 'clothTest' in v['file']]
print("clothTest funcs:", [(hex(a),n) for a,n in sorted(ct)][:6])
