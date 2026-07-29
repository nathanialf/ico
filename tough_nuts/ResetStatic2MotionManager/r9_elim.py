import re,sys
def find_scope(lines, dl):
    depth=0; i=dl; start=0
    while i>=0:
        brk=False
        for ch in reversed(lines[i]):
            if ch=='}': depth+=1
            elif ch=='{':
                if depth==0: start=i; brk=True; break
                depth-=1
        if brk: break
        i-=1
    d=0; j=start
    while j<len(lines):
        for ch in lines[j]:
            if ch=='{': d+=1
            elif ch=='}':
                d-=1
                if d==0: return start,j
        j+=1
    return start,len(lines)-1

PURE=re.compile(r'^&?[A-Za-z_][\w]*(?:(?:->|\.)[\w]+)*(?:\[\d+\])?$')
def elim(text,name,declline):
    lines=text.split('\n')
    lo,hi=find_scope(lines,declline)
    declre=re.compile(r'^[ \t]*(?:float|void|char|int|short|unsigned int) \*%s(?: = (.+))?;[ \t]*$'%name)
    asg=re.compile(r'^[ \t]*%s = (.+);[ \t]*$'%name)
    tok=re.compile(r'(?<![\w>.])%s\b'%name)
    md=declre.match(lines[declline])
    if not md: return None,'decl mismatch: '+lines[declline]
    out=lines[:lo]; cur=None
    if md.group(1) is not None:
        if not PURE.match(md.group(1)): return None,'impure init: '+md.group(1)
        cur=md.group(1)
    for k in range(lo,hi+1):
        l=lines[k]
        if k==declline: continue
        m=asg.match(l)
        if m and tok.search(m.group(1))is None:
            e=m.group(1)
            if not PURE.match(e): return None,'impure assign: '+e
            cur=e; continue
        if tok.search(l):
            if re.search(r'\b(?:float|void|int|short|char)\b[\w\*, ]*\*?\b%s\b'%name,l): return None,'redecl: '+l
            if cur is None: return None,'use before assign: '+l
            l=tok.sub(lambda _:cur,l)
        out.append(l)
    out+=lines[hi+1:]
    return '\n'.join(out),'ok'
