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
conf={};reg={}
for l in seg:
    m=re.match(r';; (\d+) conflicts: (.*)',l)
    if m: conf[int(m.group(1))]=[int(x) for x in m.group(2).split()]
    m=re.match(r'Register (\d+), refs = (\d+), live_length = (\d+)',l)
    if m: reg[int(m.group(1))]=(int(m.group(2)),int(m.group(3)))
PREF=[16,17,18,19,20,21,22,23,30]
assign={}
def col(a):
    forb=set()
    for c in conf.get(a,[]):
        if c<84: forb.add(c)
        elif assign.get(c) is not None: forb.add(assign[c])
    return next((x for x in PREF if x not in forb),None)
for a in order:
    assign[a]=col(a)
import math
def prio(a):
    r,l=reg.get(a,(0,1))
    return (math.floor(math.log2(r)) if r>0 else 0)*r/max(l,1)
watch={86:'e',87:'b',88:'nd',1009:'v70p',2618:'qF0p',2619:'v110p',986:'qn',2610:'?2610'}
for a in sorted(watch,key=lambda x:order.index(x) if x in order else 999):
    if a in order:
        p=order.index(a)
        r=assign[a]
        print(f"{watch[a]:6}({a}) pos={p:3} prio={prio(a):.3f} refs/len={reg.get(a)} -> reg{r} s{r-16 if r and r<30 else 8 if r else '-'}")
    else:
        print(f"{watch[a]:6}({a}) NOT IN ORDER (spilled/coalesced?) refs/len={reg.get(a)}")
