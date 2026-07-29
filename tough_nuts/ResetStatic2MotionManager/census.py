import re,collections,sys
SP='/tmp/claude-1005/-primary-dev-ico/04159692-777d-4d3f-b622-24989f59a5e8/scratchpad/'
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
exp,blt=load(sys.argv[1])
def ops(ls): return collections.Counter(l.split('\t')[0] for l in ls)
def regs(ls):
    c=collections.Counter()
    for l in ls:
        for r in re.findall(r'\b(s[0-8])\b',l): c[r]+=1
    return c
oe,ob=ops(exp),ops(blt); re_,rb=regs(exp),regs(blt)
dop=sum(abs(oe[k]-ob[k]) for k in set(oe)|set(ob))
dreg=sum(abs(re_[k]-rb[k]) for k in set(re_)|set(rb))
print(f'insns ROM={len(exp)} ours={len(blt)}  |opcode dev|={dop}  |sreg dev|={dreg}')
print('  ' + '  '.join(f'{k}:{ob[k]-oe[k]:+d}' for k in ['addiu','daddu','lw','sw'] ))
print('  ' + '  '.join(f'{k}:{rb[k]-re_[k]:+d}' for k in sorted(set(re_)|set(rb))))
