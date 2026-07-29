import re
path='/tmp/claude-1005/-primary-dev-ico/fd7bfd8a-5faa-485e-9c46-6127ff47e64b/scratchpad/dump/motionFileManager.c.greg'
lines=open(path).read().splitlines()
start=next(i for i,l in enumerate(lines) if l.startswith(';; Function ResetStatic2'))
end=next(i for i,l in enumerate(lines) if i>start and l.startswith(';; Function '))
seg=lines[start:end]
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
def run(order):
    assign={}
    for a in order:
        forb=set()
        for c in conf.get(a,[]):
            if c<84: forb.add(c)
            elif assign.get(c) is not None: forb.add(assign[c])
        assign[a]=next((x for x in PREF if x not in forb),None)
    return assign
o=[x for x in order if x!=86]; o.insert(64,86)
a=run(o)
econf=set(conf[86])
# who is on s4(20) and s7(23) and do they conflict e?
for r in [20,23,21,22]:
    holders=[x for x in a if a[x]==r]
    print(f"s{r-16 if r<30 else 8}(reg{r}): "+", ".join(f"{h}{'*e' if h in econf else ''}(refs{reg.get(h)})" for h in holders))
print("\ne conflicts among pos55-63:",[x for x in order[55:64] if x in econf])
