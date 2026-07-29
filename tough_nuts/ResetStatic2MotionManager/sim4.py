import re,sys,math
base='/tmp/claude-1005/-primary-dev-ico/4f803788-72d7-4575-a256-423f93f9bced/scratchpad/dump/motionFileManager.c'
# classes from lreg
cls={}
L=open(base+'.lreg').read().splitlines()
s=next(i for i,l in enumerate(L) if l.startswith(';; Function ResetStatic2'))
e_=next((i for i,l in enumerate(L) if i>s and l.startswith(';; Function ')),len(L))
for l in L[s:e_]:
    m=re.match(r'Register (\d+) used .*?; (\w+_REGS)',l)
    if m and 'in block' not in l: cls[int(m.group(1))]=m.group(2)
g=open(base+'.greg').read().splitlines()
s2=next(i for i,l in enumerate(g) if l.startswith(';; Function ResetStatic2'))
e2=next((i for i,l in enumerate(g) if i>s2 and l.startswith(';; Function ')),len(g))
sg=g[s2:e2]
for l in sg:
    m=re.match(r';; \d+ regs to allocate: (.*)',l)
    if m: order=[int(x) for x in m.group(1).split()]
conf={};ri={}
for l in sg:
    m=re.match(r';; (\d+) conflicts: (.*)',l)
    if m: conf[int(m.group(1))]=[int(x) for x in m.group(2).split()]
    m=re.match(r'Register (\d+), refs = (\d+), live_length = (\d+)',l)
    if m: ri[int(m.group(1))]=(int(m.group(2)),int(m.group(3)))
GP=[16,17,18,19,20,21,22,23,30]
FP=[52,53,54,55,56,57,58,59,60,61,62,63]   # $f20-$f31
def pref(a): return FP if cls.get(a)=='FP_REGS' else GP
def run(o,trace=None):
    a={}; info={}
    for x in o:
        f={}
        for c in conf.get(x,[]):
            if c<84: f.setdefault(c,('HARD',c))
            elif a.get(c) is not None: f.setdefault(a[c],('a',c))
        r=next((z for z in pref(x) if z not in f),None)
        a[x]=r; info[x]=f
    return a,info
def nm(r): return 'SPILL' if r is None else ('s%d'%(r-16) if 16<=r<=23 else ('s8' if r==30 else 'f%d'%(r-32)))
if len(sys.argv)>1 and sys.argv[1]=='demote':
    for pos in range(60,110):
        o=[x for x in order if x!=86]; o.insert(pos,86)
        a,info=run(o)
        f=info[86]
        det=" ".join(("s%d=%s"%(c-16 if c<30 else 8, f[c][1] if c in f else '')) if c in f else "s%d=FREE"%(c-16 if c<30 else 8) for c in [19,20,21,22,23,30])
        print(f"e pos {pos:3d} -> {nm(a[86]):5s} b={nm(a[87])} nd={nm(a[88])}  {det}")
else:
    a,info=run(order)
    for t,n2 in ((86,'e'),(87,'b'),(88,'nd')):
        f=info[t]
        print(f"\n{n2}({t}) pos={order.index(t)} -> {nm(a[t])}")
        for c in [19,20,21,22,23,30]:
            if c in f:
                w=f[c][1]; rr,ll=ri.get(w,(0,0))
                print(f"   {nm(c)} BLOCKED by {f[c][0]} {w} refs={rr} len={ll} cls={cls.get(w)}")
            else: print(f"   {nm(c)} FREE")
