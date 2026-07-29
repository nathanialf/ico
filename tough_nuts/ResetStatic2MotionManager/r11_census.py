"""ROUND-11 CENSUS ORACLE: read global.c's allocno priority order + dispositions
straight out of the -dg dump.  Tells you DIRECTLY whether a given pseudo won or
lost a hard register, its refs/live_length/priority and its rank.
usage: python3 r11_census.py [reg ...]     (default: 401 408)"""
import re,math,os,subprocess,sys
SP=os.path.dirname(os.path.abspath(__file__))+'/'
ROOT='/primary/dev/ico/.claude/worktrees/motionmgr'
D=SP+'d11/'
def build(src=ROOT+'/sugipon/src/motionFileManager.c'):
    os.makedirs(D,exist_ok=True)
    subprocess.run(['cp',src,D+'motionFileManager.c'],check=True)
    EE='/primary/dev/ico/tools/cc/ee-gcc2.9-991111/ee-gcc'
    LIB='/primary/dev/ico/tools/cc/ee-gcc2.9-991111/gcc-lib/ee/2.9-ee-991111-01/'
    subprocess.run([EE,'-B',LIB,'-S','-G','8','-O2','-mips3','-EL','-fno-builtin',
                    '-nostdinc','-fdata-sections','-I',ROOT+'/include','-dg','-dl',
                    '-o','motionFileManager.s','motionFileManager.c'],cwd=D,check=True)
def parse(fn='ResetStatic2MotionManager'):
    blk=[b for b in open(D+'motionFileManager.c.greg').read().split(';; Function ')
         if b.startswith(fn)][0]
    order=[];disp={};mode=0
    for l in blk.splitlines():
        if l.startswith('Pass 1 registers'): mode=1; continue
        if mode==1 and l.startswith('Register '):
            m=re.match(r'Register (\d+), refs = (\d+), live_length = (\d+)',l)
            order.append((int(m.group(1)),int(m.group(2)),int(m.group(3))))
        elif mode==1 and not l.strip(): mode=0
        if l.startswith(';; Register dispositions'): mode=2; continue
        if mode==2:
            if not l.strip(): mode=0; continue
            for a,b in re.findall(r'(\d+) in (\d+)',l): disp[int(a)]=int(b)
    return order,disp
def pri(r,ll): return int(math.floor(math.log2(r))*r*10000/ll) if ll and r>1 else 0
if __name__=='__main__':
    build(); order,disp=parse()
    idx={r:i for i,(r,_,_) in enumerate(order)}
    tgt=[int(x) for x in sys.argv[1:]] or [401,408]
    print(f'allocnos={len(order)} assigned={len(disp)} spilled={len(order)-len(disp)}')
    for t in tgt:
        if t not in idx: print(f'reg{t}: GONE'); continue
        r,rf,ll=order[idx[t]]
        print(f'reg{t}: rank {idx[t]}/{len(order)} refs={rf} ll={ll} pri={pri(rf,ll)} '
              f'-> {"hard "+str(disp[t]) if t in disp else "*** SPILLED/REMAT ***"}')
