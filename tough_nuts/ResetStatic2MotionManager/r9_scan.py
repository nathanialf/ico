import re,os,sys,subprocess
SP='/primary/dev/ico/.claude/worktrees/motionmgr/tough_nuts/ResetStatic2MotionManager/_sp/'
sys.path.insert(0,SP)
from r9_elim import elim
from r9_m import measure,fmt
ROOT='/primary/dev/ico/.claude/worktrees/motionmgr'
TU=ROOT+'/sugipon/src/motionFileManager.c'
base=open(SP+sys.argv[1]).read()
open(TU,'w').write(base); b=measure(); print('BASE',fmt(b),flush=True)
lines=base.split('\n')
cands=[(i,m.group(1)) for i,l in enumerate(lines) for m in [re.match(r'^[ \t]*(?:float|void|char|int|short) \*(\w+)(?: = .+)?;[ \t]*$',l)] if m]
res=[]
for i,n in cands:
    t,msg=elim(base,n,i)
    if t is None or t==base: continue
    open(TU,'w').write(t); r=measure()
    if r is None: print(f'L{i+1} {n} FAIL'); continue
    res.append((r['score'],r['sites'],r['rc'],i+1,n))
    print(f"L{i+1:5d} {n:6s} {fmt(r)}",flush=True)
open(TU,'w').write(base)
print('--- sorted by score ---')
for x in sorted(res)[:15]: print(x)
