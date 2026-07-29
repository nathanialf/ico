import re,sys
path='/tmp/claude-1005/-primary-dev-ico/4f803788-72d7-4575-a256-423f93f9bced/scratchpad/dump/motionFileManager.c.greg'
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
a=run(order)
econf=set(conf.get(86,[]))
def fl(n):
    import math
    return int(math.log2(n)) if n>0 else 0
N=int(sys.argv[1]) if len(sys.argv)>1 else 70
print("pos  allocno reg   refs  len   pri     econf")
for i,x in enumerate(order[:N]):
    r=a[x]; rr,ll=reg.get(x,(0,1))
    pri=fl(rr)*rr*10000//max(ll,1)
    nm={86:' e',87:' b',88:'nd'}.get(x,'')
    print(f"{i:4d} {x:7d} {'s%d'%(r-16 if r and r<30 else 8) if r else '--':4s} {rr:5d} {ll:5d} {pri:7d}  {'E' if x in econf else '.'} {nm}")
