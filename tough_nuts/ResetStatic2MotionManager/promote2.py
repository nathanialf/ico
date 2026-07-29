import re,sys,math
exec(open('/tmp/claude-1005/-primary-dev-ico/4f803788-72d7-4575-a256-423f93f9bced/scratchpad/sim4.py').read().split("if len(sys.argv)")[0])
ep=order.index(86)
econf=set(conf.get(86,[]))
base,_=run(order)
print("baseline e=",nm(base[86]))
res=[]
for x in order[ep+1:]:
    if x not in econf or cls.get(x)!='GR_REGS': continue
    o=[y for y in order if y!=x]; o.insert(ep,x)
    a,_=run(o)
    if a[86]==30 and a[87]==21 and a[88]==22:
        rr,ll=ri.get(x,(0,0))
        res.append((x,rr,ll,nm(a[x])))
print("SINGLE promotions giving full trio:")
for x,rr,ll,r in res: print(f"   allocno {x}: refs={rr} len={ll} -> {r}   (needs pri>{int(math.log2(25))*25*10000//535})  cur pri={int(math.log2(rr))*rr*10000//ll}")
