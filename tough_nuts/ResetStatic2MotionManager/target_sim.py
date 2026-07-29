import re,math,sys
path='/tmp/claude-1005/-primary-dev-ico/fd7bfd8a-5faa-485e-9c46-6127ff47e64b/scratchpad/dump/motionFileManager.c.greg'
lines=open(path).read().splitlines()
start=next(i for i,l in enumerate(lines) if l.startswith(';; Function ResetStatic2'))
end=next(i for i,l in enumerate(lines) if i>start and l.startswith(';; Function '))
seg=lines[start:end]
for l in seg:
    m=re.match(r';; \d+ regs to allocate: (.*)',l)
    if m: order0=[int(x) for x in m.group(1).split()]
conf={};reg={}
for l in seg:
    m=re.match(r';; (\d+) conflicts: (.*)',l)
    if m: conf[int(m.group(1))]=[int(x) for x in m.group(2).split()]
    m=re.match(r'Register (\d+), refs = (\d+), live_length = (\d+)',l)
    if m: reg[int(m.group(1))]=[int(m.group(2)),int(m.group(3))]
# scenario: (regno, new_refs_or_None, halve_len_bool)
import json
mods=json.loads(sys.argv[1])
for r,nr,halve in mods:
    if r in reg:
        if nr: reg[r][0]=nr
        if halve: reg[r][1]=max(1,reg[r][1]//2)
def prio(a):
    r,l=reg.get(a,(0,1)); return (math.floor(math.log2(r)) if r>0 else 0)*r*10000//max(l,1)
order=sorted(order0,key=lambda a:(-prio(a),a))
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
def sn(r): return 's'+str(r-16 if r and r<30 else 8) if r else 'SPILL'
for nm,rr in [('e',86),('b',87),('nd',88),('v70p',1009),('qF0p',2618),('v110p',2619),('qn',986)]:
    print(f"  {nm:6}({rr}) pos={order.index(rr):3} prio={prio(rr):6} -> {sn(a[rr])}")
