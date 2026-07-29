import re,math
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
def prio(a):
    r,l=reg.get(a,(0,1)); return (math.floor(math.log2(r)) if r>0 else 0)*r/max(l,1)
econf=set(conf.get(86,[]))
watch={2610:'pv',1009:'v70p',2618:'qF0p',2619:'v110p',986:'qn',2309:'?2309',154:'?154',1778:'?1778',2616:'?2616',280:'?280'}
print("e(86) prio=%.3f pos=%d refs/len=%s"%(prio(86),order.index(86),reg.get(86)))
print("e conflicts with %d allocnos"%len([x for x in econf if x>=84]))
for a,nm in watch.items():
    inc = a in econf
    pos = order.index(a) if a in order else '-'
    print(f"  {nm:7}({a}) econf={inc} pos={pos} prio={prio(a):.3f} refs/len={reg.get(a)}")
# what len does each need to exceed e's 0.186?
print("\n-- len needed to exceed e prio 0.186 --")
for a,nm in watch.items():
    r,l=reg.get(a,(0,1)); lg=math.floor(math.log2(r)) if r>0 else 0
    need = lg*r/0.186
    print(f"  {nm:7}({a}) refs={r} curlen={l} need_len<{need:.0f}")
