import re,collections
SP='/primary/dev/ico/.claude/worktrees/motionmgr/tough_nuts/ResetStatic2MotionManager/_sp/'
L=open(SP+'m_qd.txt').read().splitlines()
idx=[i for i,l in enumerate(L) if l.startswith('=== ')]
def grab(a,b):
    out=[]
    for l in L[a:b]:
        m=re.match(r'\s*\d+\t(.*)',l)
        if m: out.append(m.group(1))
    return out
E=grab(idx[0],idx[1]); B=grab(idx[1],idx[2])
NAMES={0x60:'v60',0x70:'v70',0x10:'buf10',0x20:'q20',0x30:'q30',0x40:'q40',0x50:'v50',
 0x80:'g80',0x90:'q90',0xA0:'qA0',0xB0:'gB0',0xC0:'vC0',0xD0:'qD0',0xE0:'gE0',
 0xF0:'qF0',0x100:'g100',0x110:'v110',0x120:'v120',0x130:'v130',0x150:'v150',
 0x160:'v160',0x170:'v170',0x180:'g180',0x190:'q190',0x1A0:'mem'}
def cnt(ls):
    c=collections.Counter()
    for l in ls:
        m=re.match(r'addiu\t(\w+),sp,(\d+)',l)
        if m: c[int(m.group(2))]+=1
    return c
ce,cb=cnt(E),cnt(B)
tot=0
for k in sorted(set(ce)|set(cb)):
    d=cb[k]-ce[k]
    if d: print(f'{k:#6x} {NAMES.get(k,"?"):<8} ROM {ce[k]:>3} ours {cb[k]:>3}  {d:>+3}'); tot+=abs(d)
print('sum |delta|',tot)
