"""ROUND-14: census of every FRAME-ADDRESS pseudo `(set (reg N) (plus (reg 1 at) K))`.
Reports per pseudo: frame offset K, #sets, REG_EQUIV present, refs/live_length/priority
(from -dg 'Pass 1 registers'), rank, and WON hard reg / SPILLED.
A SPILLED pseudo WITH REG_EQUIV  -> rematerialised (addiu at each ref, no store).
A SPILLED pseudo WITHOUT REG_EQUIV -> MEMORY resident (sw at each set, lw at each use).
usage: python3 r14_frame.py [--fn NAME]"""
import re,math,os,sys,collections
SP=os.path.dirname(os.path.abspath(__file__))+'/'
D=SP+'d11/'
FN=sys.argv[sys.argv.index('--fn')+1] if '--fn' in sys.argv else 'ResetStatic2MotionManager'

lreg=open(D+'motionFileManager.c.lreg').read()
blk=[b for b in lreg.split(';; Function ') if b.startswith(FN)][0]

# collapse whitespace so multi-line RTL is matchable
flat=re.sub(r'\s+',' ',blk)
sets=collections.defaultdict(list)   # pseudo -> [(insn, K, has_equiv)]
for m in re.finditer(r'\(insn (\d+) \d+ \d+ \(set \(reg[:/a-zA-Z]* ?\w*:?SI (\d+)\) '
                     r'\(plus:SI \(reg:SI 1 at\) \(const_int (-?\d+)\)\)\)(.{0,220})',flat):
    insn,reg,K,tail=int(m.group(1)),int(m.group(2)),int(m.group(3)),m.group(4)
    if reg<64: continue
    sets[reg].append((insn,K,'REG_EQUIV' in tail))

greg=open(D+'motionFileManager.c.greg').read()
gblk=[b for b in greg.split(';; Function ') if b.startswith(FN)][0]
order=[];disp={};mode=0
for l in gblk.splitlines():
    if l.startswith('Pass 1 registers'): mode=1; continue
    if mode==1 and l.startswith('Register '):
        mm=re.match(r'Register (\d+), refs = (\d+), live_length = (\d+)',l)
        if mm: order.append((int(mm.group(1)),int(mm.group(2)),int(mm.group(3))))
    elif mode==1 and not l.strip(): mode=0
    if l.startswith(';; Register dispositions'): mode=2; continue
    if mode==2:
        if not l.strip(): mode=0; continue
        for a,b in re.findall(r'(\d+) in (\d+)',l): disp[int(a)]=int(b)
idx={r:i for i,(r,_,_) in enumerate(order)}
def pri(r,ll): return int(math.floor(math.log2(r))*r*10000/ll) if ll and r>1 else 0
HN={16:'s0',17:'s1',18:'s2',19:'s3',20:'s4',21:'s5',22:'s6',23:'s7',30:'s8',
    2:'v0',3:'v1',4:'a0',5:'a1',6:'a2',7:'a3'}
NAMES={0x60:'v60',0x70:'v70',0x10:'buf10',0x20:'q20',0x30:'q30',0x40:'q40',0x50:'v50',
       0x80:'g80',0x90:'q90',0xA0:'qA0',0xB0:'gB0',0xC0:'vC0',0xD0:'qD0',0xE0:'gE0',
       0xF0:'qF0',0x100:'g100',0x110:'v110',0x120:'v120',0x130:'v130',0x150:'v150',
       0x160:'v160',0x170:'v170',0x180:'g180',0x190:'q190',0x1A0:'mem'}
rows=[]
for reg,ss in sets.items():
    Ks=sorted({k for _,k,_ in ss})
    eq=any(e for _,_,e in ss)
    if reg in idx:
        r,rf,ll=order[idx[reg]]
        d=disp.get(reg)
        st=('hard '+HN.get(d,str(d))) if d is not None else ('*SPILL/REMAT*' if eq else '*MEMORY*')
        rows.append((idx[reg],reg,Ks,len(ss),eq,rf,ll,pri(rf,ll),st))
    else:
        rows.append((10**6,reg,Ks,len(ss),eq,0,0,0,'not-an-allocno(folded)'))
print(f'{"rank":>6} {"pseudo":>7} {"offs(name)":<22} {"sets":>4} {"EQUIV":>5} {"refs":>4} {"ll":>5} {"pri":>6}  disposition')
for rank,reg,Ks,ns,eq,rf,ll,p,st in sorted(rows):
    nm=','.join(f'{k:#x}({NAMES.get(k,"?")})' for k in Ks)
    rr='' if rank>=10**6 else rank
    print(f'{str(rr):>6} {reg:>7} {nm:<22} {ns:>4} {str(eq):>5} {rf:>4} {ll:>5} {p:>6}  {st}')
print(f'\nallocnos={len(order)} assigned={len(disp)} spilled={len(order)-len(disp)}')
