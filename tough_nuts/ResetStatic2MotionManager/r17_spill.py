import re,math,sys,collections
D='/primary/dev/ico/.claude/worktrees/motionmgr/tough_nuts/ResetStatic2MotionManager/d11/'
g=[b for b in open(D+'motionFileManager.c.greg').read().split(';; Function ') if b.startswith('ResetStatic2MotionManager')][0]
order=[];disp={};mode=0
for l in g.splitlines():
    if l.startswith('Pass 1 registers'): mode=1; continue
    if mode==1 and l.startswith('Register '):
        m=re.match(r'Register (\d+), refs = (\d+), live_length = (\d+), size = (\d+)',l)
        if m: order.append(tuple(int(x) for x in m.groups()))
    elif mode==1 and not l.strip(): mode=0
    if l.startswith(';; Register dispositions'): mode=2; continue
    if mode==2:
        if not l.strip(): mode=0; continue
        for a,b in re.findall(r'(\d+) in (\d+)',l): disp[int(a)]=int(b)
lb=[b for b in open(D+'motionFileManager.c.lreg').read().split(';; Function ') if b.startswith('ResetStatic2MotionManager')][0]
flat=re.sub(r'\s+',' ',lb)
# capture the FIRST set of each pseudo, with a short src description
src={}
for m in re.finditer(r'\(insn (\d+) \d+ \d+ \(set \(reg[:/a-zA-Z]*\s?\w*:?[SDT][IF] (\d+)\) (.{0,90})',flat):
    r=int(m.group(2))
    if r>=64: src.setdefault(r,(int(m.group(1)),m.group(3)))
def pri(r,ll,sz): return int(math.floor(math.log2(r))*r*10000/ll*sz) if ll and r>1 else 0
print('=== SPILLED allocnos (%d):'%(len(order)-len(disp)))
idx={r:i for i,(r,_,_,_) in enumerate(order)}
for i,(r,rf,ll,sz) in enumerate(order):
    if r in disp: continue
    ins,s=src.get(r,(0,'?'))
    print(f' rank{i:4d} reg{r:5d} refs={rf:3d} ll={ll:4d} sz={sz} pri={pri(rf,ll,sz):6d}  insn{ins}: {s[:80]}')
