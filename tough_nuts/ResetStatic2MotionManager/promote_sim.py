import re,sys
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
        assign[a]=next((x for x in PREF if x not in forb),None)
    return assign
def sname(r): return 's'+str(r-16 if r and r<30 else 8) if r else 'SPILL'
# promote given allocnos to just before e (pos of e), keep relative order
promote=[int(x) for x in sys.argv[1:]]
epos=order.index(86)
o=[x for x in order if x not in promote]
ei=o.index(86)
for i,a in enumerate(promote):
    o.insert(ei+i,a)  # insert promoted right BEFORE e
a=run(o)
print("promote",promote,"-> e =",sname(a[86]))
for r in [19,20,21,22,23,30]:
    holders=[x for x in o if a[x]==r]
    print(f"  {sname(r)}: {holders[:6]}")
