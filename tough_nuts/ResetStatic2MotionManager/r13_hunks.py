import re,sys,difflib
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
E,B=load(SP+'m_qd.txt')
def n(l):
    l=re.sub(r'\s+',' ',l.strip())
    mn=l.split(' ')[0]
    if mn in ('jal','j'): return mn
    if re.match(r'^(b|beq|bne|beql|bnel|blez|bgez|bltz|bgtz|bc1t|bc1f|bc1tl|bc1fl|beqz|bnez)$',mn):
        l=re.sub(r',?[0-9a-f]+ <[^>]*>','',l)
    return l
A=[n(x) for x in E]; C=[n(x) for x in B]
sm=difflib.SequenceMatcher(a=A,b=C,autojunk=False)
lo=int(sys.argv[1]) if len(sys.argv)>1 else 0
hi=int(sys.argv[2]) if len(sys.argv)>2 else 10**9
tot=0
for tag,i1,i2,j1,j2 in sm.get_opcodes():
    if tag=='equal': continue
    tot+=max(i2-i1,j2-j1)
    if i1<lo or i1>hi: continue
    print(f'== {tag} ROM[{i1}:{i2}] OURS[{j1}:{j2}]')
    for k in range(max(0,i1-2),i1): print(f'    ctx {k:5d}  {A[k]}')
    m=max(i2-i1,j2-j1)
    for t in range(m):
        r=A[i1+t] if i1+t<i2 else ''
        o=C[j1+t] if j1+t<j2 else ''
        print(f'    R{i1+t if i1+t<i2 else 0:5d} {r:34s} | {o}')
print('TOTAL aligned diff insns',tot)
