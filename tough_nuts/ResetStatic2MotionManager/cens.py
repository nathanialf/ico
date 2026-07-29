import re,math,sys
D='/primary/dev/ico/.claude/worktrees/motionmgr/tough_nuts/ResetStatic2MotionManager/d11/'
blk=[b for b in open(D+'motionFileManager.c.greg').read().split(';; Function ') if b.startswith('ResetStatic2MotionManager')][0]
order=[];disp={};mode=0
for l in blk.splitlines():
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
off={}
for m in re.finditer(r'\(insn (\d+) \d+ \d+ \(set \(reg[:/a-zA-Z]*\s?\w*:?SI (\d+)\) \(plus:SI \(reg:SI 1 at\) \(const_int (-?\d+)\)\)\)',flat):
    off.setdefault(int(m.group(2)),set()).add(int(m.group(3)))
NAMES={0x60:'v60',0x70:'v70',0xa0:'qA0',0xc0:'vC0',0xd0:'qD0',0xf0:'qF0',0x110:'v110',
 0x120:'v120',0x130:'v130',0x150:'v150',0x160:'v160',0x170:'v170',0x20:'q20',0x30:'q30',0x50:'v50',0x90:'q90',0x40:'q40',0x180:'g180',0x190:'q190',0x1a0:'mem',0x10:'buf10',0x80:'g80',0xb0:'gB0',0xe0:'gE0',0x100:'g100'}
HN={16:'s0',17:'s1',18:'s2',19:'s3',20:'s4',21:'s5',22:'s6',23:'s7',30:'s8'}
def pri(r,ll,sz): return int(math.floor(math.log2(r))*r*10000/ll*sz) if ll and r>1 else 0
want=[int(x,0) for x in sys.argv[1:]] or [0xf0,0x110,0x120,0x130,0x70,0x60]
for i,(r,rf,ll,sz) in enumerate(order):
    ks=off.get(r)
    if not ks: continue
    if not (set(ks)&set(want)): continue
    if rf<3: continue
    nm=','.join(f'{k:#x}({NAMES.get(k,"?")})' for k in sorted(ks))
    d=disp.get(r); st=HN.get(d,str(d)) if d is not None else '*LOST*'
    print(f' rank{i:4d} reg{r:5d} {nm:<16} refs={rf:3d} ll={ll:4d} pri={pri(rf,ll,sz):5d} -> {st}')
