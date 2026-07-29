import re,collections,subprocess,sys
SP='/primary/dev/ico/.claude/worktrees/motionmgr/tough_nuts/ResetStatic2MotionManager/_sp/'
out=subprocess.run(['python3','/primary/dev/ico/.claude/worktrees/motionmgr/tough_nuts/ResetStatic2MotionManager/r13_hunks.py','0','999999'],capture_output=True,text=True).stdout
buck=collections.Counter()
for l in out.splitlines():
    m=re.match(r'== (\w+) ROM\[(\d+):(\d+)\] OURS\[(\d+):(\d+)\]',l)
    if m:
        i1,i2,j1,j2=map(int,m.groups()[1:])
        buck[i1//200*200]+=max(i2-i1,j2-j1)
print(' '.join(f'{k}:{v}' for k,v in sorted(buck.items())),' TOT',sum(buck.values()))
