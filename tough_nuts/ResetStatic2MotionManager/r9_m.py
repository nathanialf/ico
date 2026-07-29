import re,os,sys,json,subprocess,collections
SP='/primary/dev/ico/.claude/worktrees/motionmgr/tough_nuts/ResetStatic2MotionManager/_sp/'
ROOT='/primary/dev/ico/.claude/worktrees/motionmgr'
TU=ROOT+'/sugipon/src/motionFileManager.c'
def _load(path):
    L=open(path).read().splitlines()
    idx=[i for i,l in enumerate(L) if l.startswith('=== ')]
    def grab(a,b):
        out=[]
        for l in L[a:b]:
            m=re.match(r'\s*\d+\t(.*)',l)
            if m: out.append(m.group(1))
        return out
    return grab(idx[0],idx[1]), grab(idx[1],idx[2])
def measure(tag=''):
    env=dict(os.environ); env['VERSION']='aug6'
    o=subprocess.run(['python3','tools/match_diff.py','sugipon/src/motionFileManager','ResetStatic2MotionManager'],
                     capture_output=True,text=True,env=env,cwd=ROOT)
    try: d=json.loads(o.stdout); rc,st=d['real_count'],d['diff_sites']
    except Exception: return None
    subprocess.run(['bash','tools/quick_diff.sh','sugipon/src/motionFileManager','ResetStatic2MotionManager'],
                   env=env,cwd=ROOT,stdout=open(SP+'m_qd.txt','w'),stderr=subprocess.STDOUT)
    exp,blt=_load(SP+'m_qd.txt')
    def ops(ls): return collections.Counter(l.split('\t')[0] for l in ls)
    def regs(ls):
        c=collections.Counter()
        for l in ls:
            for r in re.findall(r'\b(s[0-8])\b',l): c[r]+=1
        return c
    oe,ob=ops(exp),ops(blt); re_,rb=regs(exp),regs(blt)
    dop=sum(abs(oe[k]-ob[k]) for k in set(oe)|set(ob))
    dreg=sum(abs(re_[k]-rb[k]) for k in set(re_)|set(rb))
    return dict(rc=rc,sites=st,dop=dop,dreg=dreg,n=len(blt),nrom=len(exp),
                score=dop+dreg,
                dops={k:ob[k]-oe[k] for k in set(oe)|set(ob) if ob[k]!=oe[k]},
                dregs={k:rb[k]-re_[k] for k in sorted(set(re_)|set(rb)) if rb[k]!=re_[k]})
def fmt(m): return f"rc{m['rc']} s{m['sites']} dop{m['dop']} dreg{m['dreg']} SCORE{m['score']} n{m['n']}"
if __name__=='__main__':
    if len(sys.argv)>1: subprocess.run(['cp',sys.argv[1],TU],check=True)
    m=measure(); print(fmt(m)); print(' ',m['dops']); print(' ',m['dregs'])
