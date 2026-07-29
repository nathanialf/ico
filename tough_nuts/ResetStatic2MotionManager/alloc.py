import re,sys,math,subprocess,os
SP='/tmp/claude-1005/-primary-dev-ico/04159692-777d-4d3f-b622-24989f59a5e8/scratchpad/'
ROOT='/primary/dev/ico/.claude/worktrees/motionmgr'
src=sys.argv[1]
d=SP+'dumpv'
os.makedirs(d,exist_ok=True)
subprocess.run(['cp',src,d+'/motionFileManager.c'],check=True)
EEGCC='/primary/dev/ico/tools/cc/ee-gcc2.9-991111/ee-gcc'
LIB='/primary/dev/ico/tools/cc/ee-gcc2.9-991111/gcc-lib/ee/2.9-ee-991111-01/'
for f in ('motionFileManager.c.greg','motionFileManager.c.lreg'):
    try: os.remove(d+'/'+f)
    except OSError: pass
r=subprocess.run([EEGCC,'-B',LIB,'-S','-G','8','-O2','-mips3','-EL','-fno-builtin','-nostdinc',
  '-fdata-sections','-I'+ROOT+'/include','-dg','-dl','-o','motionFileManager.s','motionFileManager.c'],
  cwd=d,capture_output=True,text=True)
if not os.path.exists(d+'/motionFileManager.c.greg'):
    print('COMPILE FAIL'); print(r.stderr[-800:]); sys.exit(1)
base=d+'/motionFileManager.c'
cls={}
L=open(base+'.lreg').read().splitlines()
s=next(i for i,l in enumerate(L) if l.startswith(';; Function ResetStatic2'))
e_=next((i for i,l in enumerate(L) if i>s and l.startswith(';; Function ')),len(L))
for l in L[s:e_]:
    m=re.match(r'Register (\d+) used .*?; (\w+_REGS)',l)
    if m and 'in block' not in l: cls[int(m.group(1))]=m.group(2)
g=open(base+'.greg').read().splitlines()
s2=next(i for i,l in enumerate(g) if l.startswith(';; Function ResetStatic2'))
e2=next((i for i,l in enumerate(g) if i>s2 and l.startswith(';; Function ')),len(g))
sg=g[s2:e2]
order=None
for l in sg:
    m=re.match(r';; \d+ regs to allocate: (.*)',l)
    if m: order=[int(x) for x in m.group(1).split()]
conf={};ri={}
for l in sg:
    m=re.match(r';; (\d+) conflicts: (.*)',l)
    if m: conf[int(m.group(1))]=[int(x) for x in m.group(2).split()]
    m=re.match(r'Register (\d+), refs = (\d+), live_length = (\d+)',l)
    if m: ri[int(m.group(1))]=(int(m.group(2)),int(m.group(3)))
GP=[16,17,18,19,20,21,22,23,30]; FP=list(range(52,64))
def pref(a): return FP if cls.get(a)=='FP_REGS' else GP
def run(o):
    a={}
    for x in o:
        f=set()
        for c in conf.get(x,[]):
            if c<84: f.add(c)
            elif a.get(c) is not None: f.add(a[c])
        a[x]=next((z for z in pref(x) if z not in f),None)
    return a
def nm(r): return 'SPILL' if r is None else ('s%d'%(r-16) if 16<=r<=23 else ('s8' if r==30 else 'r%d'%r))
a=run(order)
i=next(i for i,l in enumerate(sg) if 'dispositions' in l)
disp={}
for l in sg[i+1:]:
    if not l.strip(): break
    for x,y in re.findall(r'(\d+) in (\d+)',l): disp[int(x)]=int(y)
out=[]
for t,nme in ((86,'e'),(87,'b'),(88,'nd'),(92,'eqp')):
    n,ll=ri.get(t,(0,0)); p=(math.floor(math.log2(n)) if n else 0)*n*10000//max(ll,1)
    out.append(f'{nme}({t}) refs={n} len={ll} pri={p} pos={order.index(t) if t in order else "-"} sim={nm(a.get(t))} real={nm(disp.get(t))}')
print(' | '.join(out))
