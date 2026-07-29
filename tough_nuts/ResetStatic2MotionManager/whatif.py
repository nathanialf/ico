import re,sys,math
exec(open('/tmp/claude-1005/-primary-dev-ico/4f803788-72d7-4575-a256-423f93f9bced/scratchpad/sim4.py').read().split("if len(sys.argv)")[0])
def pri(a):
    rr,ll=ri.get(a,(0,1))
    return (math.floor(math.log2(rr)) if rr>0 else 0)*rr/max(ll,1)*10000
def sortorder(override={}):
    def key(a):
        if a in override:
            rr,ll=override[a]
        else:
            rr,ll=ri.get(a,(0,1))
        p=(math.floor(math.log2(rr)) if rr>0 else 0)*rr/max(ll,1)*10000
        return (-p,a)
    return sorted(order,key=key)
# sanity: does recomputed sort match greg order?
s=sortorder()
print("sort reproduces greg order:", s==order, " first mismatch:",
      next((i for i,(x,y) in enumerate(zip(s,order)) if x!=y), None))
tgt=int(sys.argv[1]); 
for L in [int(x) for x in sys.argv[2:]]:
    rr,ll=ri[tgt]
    o=sortorder({tgt:(rr,L)})
    a,_=run(o)
    print(f"  {tgt} len {ll}->{L} (pri {int(pri(tgt))}->{int(math.floor(math.log2(rr))*rr/L*10000)}) pos={o.index(tgt)} reg={nm(a[tgt])} | e={nm(a[86])} b={nm(a[87])} nd={nm(a[88])}")
