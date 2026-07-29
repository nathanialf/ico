import re
path='/tmp/claude-1005/-primary-dev-ico/fd7bfd8a-5faa-485e-9c46-6127ff47e64b/scratchpad/dump/motionFileManager.c.greg'
lines=open(path).read().splitlines()
start=next(i for i,l in enumerate(lines) if l.startswith(';; Function ResetStatic2'))
end=next(i for i,l in enumerate(lines) if i>start and l.startswith(';; Function '))
seg=lines[start:end]
order=None
for l in seg:
    m=re.match(r';; \d+ regs to allocate: (.*)',l)
    if m: order=[int(x) for x in m.group(1).split()]
conf={}
for l in seg:
    m=re.match(r';; (\d+) conflicts: (.*)',l)
    if m: conf[int(m.group(1))]=[int(x) for x in m.group(2).split()]
# refs/live_length table (global, printed before order) - parse from whole file region
reginfo={}
for l in seg:
    m=re.match(r'Register (\d+), refs = (\d+), live_length = (\d+)',l)
    if m: reginfo[int(m.group(1))]=(int(m.group(2)),int(m.group(3)))
PREF=[16,17,18,19,20,21,22,23,30]
assign={}
def col(a):
    forb={}
    for c in conf.get(a,[]):
        if c<84: forb[c]=('HARD',c)
        elif c in assign and assign[c] is not None: forb.setdefault(assign[c],('allocno',c))
    for r in PREF:
        if r not in forb: return r,forb
    return None,forb
for a in order:
    r,forb=col(a)
    assign[a]=r
    if a in (86,87,88):
        nm={86:'e',87:'b',88:'nd'}[a]
        print(f"\n{nm}({a}) pos={order.index(a)} -> s{r-16 if r and r<30 else 8}({r})")
        for cand in [19,20,21,22,23,30]:
            o=forb.get(cand)
            if o: 
                who=o[1]; ri=reginfo.get(who,('?','?'))
                print(f"   s{cand-16 if cand<30 else 8}({cand}) BLOCKED by {o[0]} {who}  refs={ri[0]} len={ri[1]}")
            else:
                print(f"   s{cand-16 if cand<30 else 8}({cand}) FREE")
