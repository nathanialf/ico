import re,sys,math
base='/tmp/claude-1005/-primary-dev-ico/4f803788-72d7-4575-a256-423f93f9bced/scratchpad/dump/motionFileManager.c'
txt=open(base+'.lreg').read().splitlines()
s=next(i for i,l in enumerate(txt) if l.startswith(';; Function ResetStatic2'))
e_=next((i for i,l in enumerate(txt) if i>s and l.startswith(';; Function ')),len(txt))
seg=txt[s:e_]
recs=[];cur=None;bb=None
for l in seg:
    m=re.match(r'\((insn|jump_insn|call_insn|note|code_label|barrier)\b',l)
    if m:
        if cur: recs.append(cur)
        mb=re.search(r'\[bb (\d+)\]',l)
        if mb: bb=int(mb.group(1))
        cur={'bb':bb,'txt':[l]}
    elif cur is not None: cur['txt'].append(l)
if cur: recs.append(cur)
for r in recs: r['s']=' '.join(x.strip() for x in r['txt'])
regbb={};regdef={}
for r in recs:
    for m in re.finditer(r'\(reg[:/A-Za-z0-9]* (\d+)\)',r['s']):
        n=int(m.group(1))
        if n<84: continue
        regbb.setdefault(n,set()).add(r['bb'])
    m=re.search(r'\(set \(reg[:/A-Za-z0-9]* (\d+)\)\s*\(plus:SI \(reg:SI 1 at\)\s*\(const_int (\d+)\)',r['s'])
    if m: regdef[int(m.group(1))]='fr0x%X'%int(m.group(2))
    m=re.search(r'\(set \(reg[:/A-Za-z0-9]* (\d+)\)\s*\(reg:S[FI] (\d+) \$?f?(\w+)\)',r['s'])
    if m and int(m.group(1)) not in regdef: regdef[int(m.group(1))]='ret_'+m.group(3)
    m=re.search(r'\(set \(reg[:/A-Za-z0-9]* (\d+)\)\s*\(mem[:/A-Za-z0-9]*',r['s'])
    if m and int(m.group(1)) not in regdef: regdef[int(m.group(1))]='load'
# greg
g=open(base+'.greg').read().splitlines()
s2=next(i for i,l in enumerate(g) if l.startswith(';; Function ResetStatic2'))
e2=next((i for i,l in enumerate(g) if i>s2 and l.startswith(';; Function ')),len(g))
sg=g[s2:e2]
for l in sg:
    m=re.match(r';; \d+ regs to allocate: (.*)',l)
    if m: order=[int(x) for x in m.group(1).split()]
conf={};ri={}
for l in sg:
    m=re.match(r';; (\d+) conflicts: (.*)',l)
    if m: conf[int(m.group(1))]=[int(x) for x in m.group(2).split()]
    m=re.match(r'Register (\d+), refs = (\d+), live_length = (\d+)',l)
    if m: ri[int(m.group(1))]=(int(m.group(2)),int(m.group(3)))
PREF=[16,17,18,19,20,21,22,23,30]
assign={}
for a in order:
    forb=set()
    for c in conf.get(a,[]):
        if c<84: forb.add(c)
        elif assign.get(c) is not None: forb.add(assign[c])
    assign[a]=next((x for x in PREF if x not in forb),None)
econf=set(conf.get(86,[]))
lo,hi=int(sys.argv[1]),int(sys.argv[2])
print("pos allocno reg  refs  len   pri   ec  def        bbs")
rows=[]
for i,a in enumerate(order):
    bbs=sorted(x for x in regbb.get(a,set()) if x is not None)
    if not any(lo<=x<=hi for x in bbs): continue
    rr,ll=ri.get(a,(0,1)); pri=int(math.log2(rr))*rr*10000//max(ll,1) if rr>0 else 0
    r=assign[a]
    rows.append((i,a,'s%d'%(r-16 if r<30 else 8) if r else '--',rr,ll,pri,'E' if a in econf else '.',regdef.get(a,'?'),bbs))
for row in sorted(rows):
    print("%3d %7d %-4s %4d %5d %6d  %s  %-10s"%tuple(row[:8])+" "+str(row[8])[:90])
