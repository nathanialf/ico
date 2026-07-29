import re,math,collections
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
sets=collections.defaultdict(list)
for m in re.finditer(r'\(insn (\d+) \d+ \d+ \(set \(reg[:/a-zA-Z]*\s?\w*:?SI (\d+)\) \(plus:SI \(reg/v:SI 87\) \(const_int (-?\d+)\)\)\)(.{0,200})',flat):
    sets[int(m.group(2))].append((int(m.group(1)),int(m.group(3)),'REG_EQUIV' in m.group(4)))
# also copies of those
cop=collections.defaultdict(list)
for m in re.finditer(r'\(insn (\d+) \d+ \d+ \(set \(reg[:/a-zA-Z]*\s?\w*:?SI (\d+)\) \(reg[:/a-zA-Z]*\s?\w*:?SI (\d+)\)\)',flat):
    cop[int(m.group(3))].append(int(m.group(2)))
HN={16:'s0',17:'s1',18:'s2',19:'s3',20:'s4',21:'s5',22:'s6',23:'s7',30:'s8',2:'v0',3:'v1',4:'a0',5:'a1',6:'a2',7:'a3'}
NM={16:'q1',32:'q2',48:'q3',0:'rate',4:'f_4',8:'f_8',14:'f_E'}
idx={r:i for i,(r,_,_,_) in enumerate(order)}
def pri(r,ll,sz): return int(math.floor(math.log2(r))*r*10000/ll*sz) if ll and r>1 else 0
print('b-relative pointer pseudos  (b = reg/v 87):')
tgt=set(sets)|{c for r in sets for c in cop.get(r,[])}
for r in sorted(tgt):
    ks=sorted({k for _,k,_ in sets.get(r,[])})
    nm=','.join(f'{k:#x}({NM.get(k,"?")})' for k in ks) or f'copy-of{[s for s in sets if r in cop.get(s,[])]}'
    if r in idx:
        _,rf,ll,sz=order[idx[r]]
        d=disp.get(r); st=HN.get(d,str(d)) if d is not None else '*LOST*'
        print(f'  rank{idx[r]:4d} reg{r:5d} {nm:<24} sets={len(sets.get(r,[]))} refs={rf:3d} ll={ll:5d} pri={pri(rf,ll,sz):6d} -> {st}')
    else:
        print(f'  rank  -- reg{r:5d} {nm:<24} sets={len(sets.get(r,[]))} (local/folded)')
