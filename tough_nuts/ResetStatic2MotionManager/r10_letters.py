import re,difflib,sys,subprocess,os
SP=os.path.dirname(os.path.abspath(__file__))+'/'
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
    l=re.sub(r'\b[0-9a-f]+ <[^>]*\+(0x[0-9a-f]+)>', r'T\1', l)
    l=re.sub(r'\b[0-9a-f]+ <[^>]*>', 'T0', l)
    return l
A=[n(x) for x in E]; C=[n(x) for x in B]
sm=difflib.SequenceMatcher(a=A,b=C,autojunk=False)
out=[]
for tag,i1,i2,j1,j2 in sm.get_opcodes():
    if tag!='replace' or (i2-i1)!=(j2-j1): continue
    for k,(a,b) in enumerate(zip(A[i1:i2],C[j1:j2])):
        if a.split(' ')[0]!=b.split(' ')[0]: continue
        sa=re.sub(r'\bs[0-8]\b','#',a); sb=re.sub(r'\bs[0-8]\b','#',b)
        if sa==sb and a!=b: out.append((i1+k,a,b))
if len(sys.argv)>1:
    lo,hi=int(sys.argv[1]),int(sys.argv[2])
    for i,a,b in out:
        if lo<=i<=hi: print(i,'|',a,'|',b)
print('LETTERSITES',len(out))
