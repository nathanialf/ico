import re
path='/tmp/claude-1005/-primary-dev-ico/fd7bfd8a-5faa-485e-9c46-6127ff47e64b/scratchpad/dump/motionFileManager.c.greg'
lines=open(path).read().splitlines()
start=next(i for i,l in enumerate(lines) if l.startswith(';; Function ResetStatic2'))
end=next(i for i,l in enumerate(lines) if i>start and l.startswith(';; Function '))
seg=lines[start:end]
for l in seg:
    m=re.match(r';; \d+ regs to allocate: (.*)',l)
    if m: order=[int(x) for x in m.group(1).split()]
conf={}
for l in seg:
    m=re.match(r';; (\d+) conflicts: (.*)',l)
    if m: conf[int(m.group(1))]=[int(x) for x in m.group(2).split()]
reg={}
for l in seg:
    m=re.match(r'Register (\d+), refs = (\d+), live_length = (\d+)',l)
    if m: reg[int(m.group(1))]=(int(m.group(2)),int(m.group(3)))
PREF=[16,17,18,19,20,21,22,23,30]
assign={}
def col(a):
    forb={}
    for c in conf.get(a,[]):
        if c<84: forb[c]=('H',c)
        elif c in assign and assign[c] is not None: forb.setdefault(assign[c],('a',c))
    for r in PREF:
        if r not in forb: return r,forb
    return None,forb
for a in order:
    r,fb=col(a); assign[a]=r
    if a==86:
        print(f"e(86) pos={order.index(a)} -> reg{r} (s{r-16 if r and r<30 else 8})")
        for cand in PREF:
            o=fb.get(cand)
            snm='s'+str(cand-16 if cand<30 else 8)
            if o: print(f"   {snm}({cand}) BLOCKED by {o[1]} refs={reg.get(o[1],'?')}")
            else: print(f"   {snm}({cand}) FREE")
