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
    l=re.sub(r'\s+',' ',l.strip())
    mn=l.split(' ')[0]
    if mn in ('jal','j'): return mn
    if re.match(r'^(b|beq|bne|beql|bnel|blez|bgez|bltz|bgtz|bc1t|bc1f|bc1tl|bc1fl|beqz|bnez)$',mn):
        l=re.sub(r',?[0-9a-f]+ <[^>]*>','',l)
    return l
A=[n(x) for x in E]; C=[n(x) for x in B]
sm=difflib.SequenceMatcher(a=A,b=C,autojunk=False)
REG=re.compile(r'\b(zero|at|v[01]|a[0-3]|t[0-9]|s[0-8]|k[01]|gp|sp|fp|ra|f[0-9]+)\b')
def skel(l): return REG.sub('R',l)
cats=collections.Counter(); det=collections.defaultdict(list)
for tag,i1,i2,j1,j2 in sm.get_opcodes():
    if tag=='equal': continue
    sz=max(i2-i1,j2-j1)
    r=A[i1:i2]; o=C[j1:j2]
    if tag=='replace' and len(r)==len(o) and all(skel(x)==skel(y) for x,y in zip(r,o)):
        cat='LETTER'
    elif tag=='replace' and len(r)==len(o) and all(x.split('\t')[0]==y.split('\t')[0] for x,y in zip(r,o)):
        cat='OPERAND'   # same mnemonic, different shape (imm/offset)
    elif tag=='replace' and len(r)==len(o):
        cat='OPCODE'
    elif tag=='insert': cat='EXTRA'   # we have insns ROM lacks
    elif tag=='delete': cat='MISSING'
    else: cat='MIXED'
    cats[cat]+=sz
    det[cat].append((i1,sz,r,o))
print('CATEGORY totals (aligned diff insns):')
for k,v in cats.most_common(): print(f'  {k:8s} {v:4d}   hunks={len(det[k])}')
print('TOT',sum(cats.values()))
which=sys.argv[1] if len(sys.argv)>1 else None
if which:
    for i1,sz,r,o in det[which]:
        print(f'-- ROM[{i1}] sz{sz}')
        for t in range(max(len(r),len(o))):
            print(f'   {(r[t] if t<len(r) else ""):36s} | {o[t] if t<len(o) else ""}')

print()
print('bucket x category:')
bb=collections.defaultdict(collections.Counter)
for k,lst in det.items():
    for i1,sz,r,o in lst: bb[i1//200*200][k]+=sz
hdr=['LETTER','OPCODE','MIXED','MISSING','EXTRA']
print('  bucket  '+' '.join(f'{h:>8s}' for h in hdr)+'    TOT')
for b in sorted(bb):
    print(f'  {b:6d}  '+' '.join(f'{bb[b][h]:8d}' for h in hdr)+f'  {sum(bb[b].values()):5d}')
