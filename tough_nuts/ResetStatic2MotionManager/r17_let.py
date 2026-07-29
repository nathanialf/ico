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
E,B=load(SP+'m_qd.txt')
def n(l):
    l=re.sub(r'\s+',' ',l.strip()); mn=l.split(' ')[0]
    if mn in ('jal','j'): return mn
    if re.match(r'^(b|beq|bne|beql|bnel|blez|bgez|bltz|bgtz|bc1t|bc1f|bc1tl|bc1fl|beqz|bnez)$',mn):
        l=re.sub(r',?[0-9a-f]+ <[^>]*>','',l)
    return l
A=[n(x) for x in E]; C=[n(x) for x in B]
sm=difflib.SequenceMatcher(a=A,b=C,autojunk=False)
REG=re.compile(r'\b(zero|at|v[01]|a[0-3]|t[0-9]|s[0-8]|k[01]|gp|sp|fp|ra|f[0-9]+)\b')
sub=collections.Counter(); loc=collections.defaultdict(list)
for tag,i1,i2,j1,j2 in sm.get_opcodes():
    if tag!='replace' or (i2-i1)!=(j2-j1): continue
    for t in range(i2-i1):
        r,o=A[i1+t],C[j1+t]
        if REG.sub('R',r)!=REG.sub('R',o): continue
        rr=REG.findall(r); oo=REG.findall(o)
        if len(rr)!=len(oo): continue
        for x,y in zip(rr,oo):
            if x!=y: sub[(x,y)]+=1; loc[(x,y)].append(i1+t)
print('ROM->ours register substitutions (LETTER sites), count desc:')
for (x,y),c in sub.most_common(30):
    bs=sorted(set(v//200*200 for v in loc[(x,y)]))
    print(f'  {x:>4s} -> {y:<4s} {c:3d}   buckets {bs}')
print('total letter substitutions',sum(sub.values()))

print()
tg=[('a1','a0'),('a0','a1'),('f4','f5'),('f5','f4')]
seen=set()
for tag,i1,i2,j1,j2 in sm.get_opcodes():
    if tag!='replace' or (i2-i1)!=(j2-j1): continue
    for t in range(i2-i1):
        r,o=A[i1+t],C[j1+t]
        if REG.sub('R',r)!=REG.sub('R',o): continue
        rr=REG.findall(r); oo=REG.findall(o)
        if len(rr)!=len(oo): continue
        if any((x,y) in tg for x,y in zip(rr,oo) if x!=y):
            print(f'  ROM{i1+t:5d}  {r:34s} | {o}')
