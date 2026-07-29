"""INVISIBLE-ARGUMENT SCAN.
For every jal in ROM and in our build, determine which argument registers
($4-$7 int, $f12-$f19 float) are DEFINED in the basic block preceding the call.
A register that ROM never defines locally but we do (or vice versa) is a
candidate arity / self-move difference.
"""
import re,sys,subprocess,os,collections
ROOT='/primary/dev/ico/.claude/worktrees/motionmgr'
SP=os.path.dirname(os.path.abspath(__file__))+'/'
ROM=ROOT+'/asm/aug6/matchings/sugipon/src/motionFileManager/ResetStatic2MotionManager.s'
NAME2N={'zero':0,'at':1,'v0':2,'v1':3,'a0':4,'a1':5,'a2':6,'a3':7,'t0':8,'t1':9,
 't2':10,'t3':11,'t4':12,'t5':13,'t6':14,'t7':15,'s0':16,'s1':17,'s2':18,'s3':19,
 's4':20,'s5':21,'s6':22,'s7':23,'t8':24,'t9':25,'k0':26,'k1':27,'gp':28,'sp':29,
 's8':30,'fp':30,'ra':31}
def norm(ops):
    ops=re.sub(r'\b('+'|'.join(NAME2N)+r')\b',lambda m:'$%d'%NAME2N[m.group(1)],ops)
    return ops
ARG_I=['$4','$5','$6','$7']
ARG_F=['$f12','$f13','$f14','$f15','$f16','$f17','$f18','$f19']
ARGS=ARG_I+ARG_F

def rom_stream():
    out=[]
    for l in open(ROM):
        m=re.match(r'\s*/\*[^*]*\*/\s+(\S+)\s*(.*)',l)
        if m: out.append((m.group(1),m.group(2).strip()))
        elif re.match(r'\s*\.L?\w+:',l) or re.match(r'^\w+:',l): out.append(('LABEL',l.strip()))
    return out

def our_stream():
    dis=SP+'r12_ours.dis'
    subprocess.run(['bash','-c',
      f"mips-linux-gnu-objdump -dr {ROOT}/build/quick_diff/sugipon/src/motionFileManager.o > {dis}"],check=True)
    L=open(dis).read().splitlines()
    st=None;en=None
    for i,l in enumerate(L):
        m=re.match(r'^[0-9a-f]+ <(\w+)>:',l)
        if m:
            if m.group(1)=='ResetStatic2MotionManager': st=i
            elif st is not None and en is None: en=i
    if en is None: en=len(L)
    out=[];targets=set()
    for l in L[st+1:en]:
        m=re.match(r'\s*([0-9a-f]+):\s+[0-9a-f ]+\t(\S+)\s*(.*)',l)
        if m:
            out.append([m.group(2),norm(m.group(3).split(';')[0].strip()),int(m.group(1),16)])
            continue
        m=re.search(r'R_MIPS_(\S+)\s+(\S+)',l)
        if m and out: out[-1][1]+='|'+m.group(2)
    # mark branch targets as labels
    for mn,ops,a in out:
        for t in re.findall(r'\b([0-9a-f]+) <',ops): targets.add(int(t,16))
    res=[]
    for mn,ops,a in out:
        if a in targets: res.append(('LABEL','L%x'%a))
        res.append((mn,ops))
    return res

DEF_RE=re.compile(r'^(\$[a-z0-9]+)\s*,')
NODEF={'sw','sh','sb','sd','swc1','sdc1','beq','bne','beql','bnel','blez','bgez',
       'bltz','bgtz','j','jal','jr','b','nop','break','mult','multu','div','divu',
       'c.eq.s','c.lt.s','c.le.s','c.olt.s','c.ole.s','bc1t','bc1f','bc1tl','bc1fl','sq','sqc2'}

def scan(stream,name):
    res=[]
    for i,(mn,ops) in enumerate(stream):
        if mn!='jal': continue
        tgt=ops.split('|')[-1].split('+')[0].split('<')[-1].rstrip('>')
        defined=set()
        j=i-1
        # include the delay slot (insn after jal)
        window=[stream[i+1]] if i+1<len(stream) else []
        while j>=0:
            m2,o2=stream[j]
            if m2=='LABEL': break
            if m2 in ('jal','j','jr'): break
            window.append((m2,o2))
            j-=1
        for m2,o2 in window:
            if m2 in NODEF: continue
            d=DEF_RE.match(o2)
            if d and d.group(1) in ARGS: defined.add(d.group(1))
            # mtc1 rt,fs : dest is 2nd operand
            if m2 in ('mtc1','dmtc1','ctc1'):
                p=[x.strip() for x in o2.split(',')]
                if len(p)>1 and p[1] in ARGS: defined.add(p[1])
        res.append((tgt,frozenset(defined),i))
    return res

R=scan(rom_stream(),'rom')
O=scan(our_stream(),'ours')
print('rom jals=%d ours jals=%d'%(len(R),len(O)))
seqR=[t for t,_,_ in R]; seqO=[t for t,_,_ in O]
import difflib
sm=difflib.SequenceMatcher(a=seqR,b=seqO,autojunk=False)
mism=collections.Counter()
for tag,i1,i2,j1,j2 in sm.get_opcodes():
    if tag!='equal':
        print('  !! %s rom[%d:%d]=%s ours[%d:%d]=%s'%(tag,i1,i2,seqR[i1:i2][:6],j1,j2,seqO[j1:j2][:6]))
        continue
    for k in range(i2-i1):
        t=seqR[i1+k]; a=R[i1+k][1]; b=O[j1+k][1]
        if a!=b:
            mism[(t,tuple(sorted(a)),tuple(sorted(b)))]+=1
print('\n--- per-call arg-def differences (ROM vs OURS) ---')
for (t,a,b),n in mism.most_common():
    print('%-28s x%-3d ROM=%-34s OURS=%s'%(t,n,list(a),list(b)))
print('\n--- per-callee UNION of ROM arg defs ---')
u=collections.defaultdict(set); c=collections.Counter()
for t,d,_ in R: u[t]|=set(d); c[t]+=1
for t in sorted(u):
    print('%-28s n=%-3d %s'%(t,c[t],sorted(u[t],key=lambda x:(x[1]=='f',x))))
