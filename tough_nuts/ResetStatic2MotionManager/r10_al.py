"""Align ROM .s (with real jal target symbols) against our objdump -dr,
using mnemonic + jal-target as the alignment key. Reports hunks."""
import re,sys,difflib,subprocess,os
ROOT='/primary/dev/ico/.claude/worktrees/motionmgr'
SP='/primary/dev/ico/.claude/worktrees/motionmgr/tough_nuts/ResetStatic2MotionManager/_sp/'
ROM=ROOT+'/asm/aug6/matchings/sugipon/src/motionFileManager/ResetStatic2MotionManager.s'

REGS={0:'zero',1:'at',2:'v0',3:'v1',4:'a0',5:'a1',6:'a2',7:'a3',8:'t0',9:'t1',10:'t2',
 11:'t3',12:'t4',13:'t5',14:'t6',15:'t7',16:'s0',17:'s1',18:'s2',19:'s3',20:'s4',
 21:'s5',22:'s6',23:'s7',24:'t8',25:'t9',26:'k0',27:'k1',28:'gp',29:'sp',30:'s8',31:'ra'}

def rom_insns():
    out=[]
    for l in open(ROM):
        m=re.match(r'\s*/\*[^*]*\*/\s+(\S+)\s*(.*)',l)
        if not m: continue
        mn,ops=m.group(1),m.group(2).strip()
        ops=re.sub(r'\$(\d+)',lambda g:REGS[int(g.group(1))],ops)
        ops=re.sub(r'\s+','',ops)
        out.append((mn,ops))
    return out

def our_insns(dis=None):
    if dis is None:
        dis=SP+'r10_ours.dis'
        subprocess.run(['bash','-c',f"mips-linux-gnu-objdump -dr {ROOT}/build/quick_diff/sugipon/src/motionFileManager.o > {dis}"],check=True)
    L=open(dis).read().splitlines()
    start=None;end=None
    for i,l in enumerate(L):
        m=re.match(r'^[0-9a-f]+ <(\w+)>:',l)
        if m:
            if m.group(1)=='ResetStatic2MotionManager': start=i
            elif start is not None and end is None: end=i
    if end is None: end=len(L)
    seg=L[start+1:end]
    out=[]
    pend=None
    for l in seg:
        m=re.match(r'\s*[0-9a-f]+:\s+[0-9a-f ]+\t(\S+)\s*(.*)',l)
        if m:
            mn,ops=m.group(1),m.group(2).strip()
            ops=ops.split(';')[0]
            ops=re.sub(r'\s+','',ops)
            out.append([mn,ops])
            continue
        m=re.search(r'R_MIPS_(\S+)\s+(\S+)',l)
        if m and out:
            out[-1][1]=out[-1][1]+'|'+m.group(2)
    return [tuple(x) for x in out]

def key_rom(mn,ops):
    if mn in ('jal','j'): return mn+' '+ops
    if mn in ('b','beq','bne','beql','bnel','blez','bgez','bltz','bgtz','bc1t','bc1f','bc1tl','bc1fl','beqz','bnez'):
        ops=re.sub(r'\.L\w+','L',ops)
    ops=re.sub(r'%gp_rel\((\w+)\)','G',ops)
    ops=re.sub(r'%hi\((\w+)\)','H',ops); ops=re.sub(r'%lo\((\w+)\)','L',ops)
    return mn+' '+ops

def key_our(mn,ops):
    if mn in ('jal','j'):
        t=ops.split('|')[-1]
        t=t.split('+')[0]
        return mn+' '+t
    if mn.startswith('b'):
        ops=re.sub(r'^[0-9a-f]+','L',ops.split('|')[0])
        ops=re.sub(r'[0-9a-f]+<[^>]*>','L',ops)
    ops=re.sub(r'0\(gp\)\|(\w+)','G',ops)
    ops=re.sub(r'\|.*','',ops)
    ops=re.sub(r'0x0','H',ops)
    return mn+' '+ops

if __name__=='__main__':
    R=rom_insns(); O=our_insns()
    print('rom',len(R),'ours',len(O))
    A=[key_rom(*x) for x in R]; B=[key_our(*x) for x in O]
    sm=difflib.SequenceMatcher(a=A,b=B,autojunk=False)
    tot=0
    for tag,i1,i2,j1,j2 in sm.get_opcodes():
        if tag=='equal': continue
        tot+=max(i2-i1,j2-j1)
    print('aligned diff insns',tot)
    # find jal mismatches
    for tag,i1,i2,j1,j2 in sm.get_opcodes():
        if tag=='equal': continue
        rj=[A[k] for k in range(i1,i2) if A[k].startswith('jal')]
        oj=[B[k] for k in range(j1,j2) if B[k].startswith('jal')]
        if rj!=oj:
            print(f'--{tag}-- R{i1}:{i2} B{j1}:{j2}')
            for k in range(max(0,i1-3),i1): print(f'   ctx {k:5d} {A[k]}')
            for k in range(i1,i2): print(f' R  {k:5d} {A[k]}')
            for k in range(j1,j2): print(f' B  {k:5d} {B[k]}')
