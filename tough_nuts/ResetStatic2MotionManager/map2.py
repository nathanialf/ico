import re,sys
base='/tmp/claude-1005/-primary-dev-ico/4f803788-72d7-4575-a256-423f93f9bced/scratchpad/dump/motionFileManager.c'
txt=open(base+'.lreg').read().splitlines()
start=next(i for i,l in enumerate(txt) if l.startswith(';; Function ResetStatic2'))
end=next((i for i,l in enumerate(txt) if i>start and l.startswith(';; Function ')),len(txt))
seg=txt[start:end]
# split into insn records
recs=[];cur=None;bb=None;bbof={}
for l in seg:
    m=re.match(r'\((insn|jump_insn|call_insn|note|code_label|barrier)\b',l)
    if m:
        if cur: recs.append(cur)
        cur={'bb':bb,'txt':[l],'kind':m.group(1)}
        mb=re.search(r'\[bb (\d+)\]',l)
        if mb: bb=int(mb.group(1)); cur['bb']=bb
    elif cur is not None: cur['txt'].append(l)
if cur: recs.append(cur)
for r in recs: r['s']='\n'.join(r['txt'])
want=[int(x) for x in sys.argv[1:]]
for w in want:
    pat=re.compile(r'\(reg[:/A-Za-z0-9]* %d\)'%w)
    hits=[(i,r) for i,r in enumerate(recs) if pat.search(r['s'])]
    bbs=sorted(set(r['bb'] for i,r in hits if r['bb'] is not None))
    print(f"\n===== reg {w}: {len(hits)} refs, bbs {bbs}")
    # def insn = first with (set (reg w)
    for i,r in hits[:2]:
        if re.search(r'\(set \(reg[:/A-Za-z0-9]* %d\)'%w, r['s']):
            print("DEF bb%s:"%r['bb'], r['s'][:400].replace('\n',' '))
            break
    # nearest call after def
    for i,r in hits:
        pass
