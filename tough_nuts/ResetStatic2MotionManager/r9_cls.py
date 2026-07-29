import re,sys,difflib,collections
SP='/primary/dev/ico/.claude/worktrees/motionmgr/tough_nuts/ResetStatic2MotionManager/_sp/'
def load(path):
    L=open(path).read().splitlines()
    idx=[i for i,l in enumerate(L) if l.startswith('=== ')]
    def grab(a,b):
        out=[]
        for l in L[a:b]:
            m=re.match(r'\s*\d+\t(.*)',l)
            if m: out.append(m.group(1))
        return out
    return grab(idx[0],idx[1]), grab(idx[1],idx[2])
E,B=load(sys.argv[1])
def n(l):
    l=re.sub(r'\s+',' ',l.strip())
    # normalize branch targets: keep only +0xNNN part
    l=re.sub(r'\b[0-9a-f]+ <[^>]*\+(0x[0-9a-f]+)>', r'T\1', l)
    l=re.sub(r'\b[0-9a-f]+ <[^>]*>', 'T0', l)
    l=re.sub(r'jal 0','jal',l)
    return l
A=[n(x) for x in E]; C=[n(x) for x in B]
sm=difflib.SequenceMatcher(a=A,b=C,autojunk=False)
cnt=collections.Counter(); ex=collections.defaultdict(list); tot=0
for tag,i1,i2,j1,j2 in sm.get_opcodes():
    if tag=='equal': continue
    ro=tuple(x.split(' ')[0] for x in A[i1:i2]); bo=tuple(x.split(' ')[0] for x in C[j1:j2])
    tot+=max(i2-i1,j2-j1)
    if ro==bo:
        for a,b in zip(A[i1:i2],C[j1:j2]):
            key=('OPD',a.split(' ')[0]); cnt[key]+=1
            ex[key].append((i1,a,b))
    else:
        key=('SEQ',ro,bo); cnt[key]+=1
        ex[key].append((i1,A[i1:i2],C[j1:j2]))
print('total diff insns',tot)
for k,v in cnt.most_common(int(sys.argv[2]) if len(sys.argv)>2 else 25):
    print(v,k)
    for e in ex[k][:int(sys.argv[3]) if len(sys.argv)>3 else 3]: print('     ',e)
