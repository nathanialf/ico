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
PREF=[16,17,18,19,20,21,22,23,30]
def run(order):
    assign={}
    for a in order:
        forb=set()
        for c in conf.get(a,[]):
            if c<84: forb.add(c)
            elif assign.get(c) is not None: forb.add(assign[c])
        r=next((x for x in PREF if x not in forb),None)
        assign[a]=r
    return assign
# baseline
base=run(order)
print("baseline e->",base[86])
# demote e to various later positions
for newpos in [61,62,63,64,65,66,67,68,70,72,75]:
    o=[x for x in order if x!=86]
    o.insert(newpos,86)
    a=run(o)
    print(f"e moved to pos{newpos}: e->{a[86]} (s{a[86]-16 if a[86] and a[86]<30 else 8})")
