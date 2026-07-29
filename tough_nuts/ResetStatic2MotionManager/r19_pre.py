"""ROUND-19 PROBE: read gcse's OWN dump (-dG) and report, for every frame-address
expression (plus (reg 1 at) K) in ResetStatic2MotionManager, whether gcse-PRE
built a reaching-reg web for it: how many occurrences it DELETED and on which
edges it INSERTED.

This is the direct read of `pre_delete`/`pre_edge_insert`, replacing inference
from the .s.

usage: python3 r19_pre.py [candidate.c]      (default: the live TU)
"""
import os, re, subprocess, sys

ROOT = '/primary/dev/ico/.claude/worktrees/motionmgr'
SP   = os.path.dirname(os.path.abspath(__file__)) + '/'
D    = SP + 'g19/'
EE   = '/primary/dev/ico/tools/cc/ee-gcc2.9-991111/ee-gcc'
LIB  = '/primary/dev/ico/tools/cc/ee-gcc2.9-991111/gcc-lib/ee/2.9-ee-991111-01/'
FN   = 'ResetStatic2MotionManager'

def build(src):
    os.makedirs(D, exist_ok=True)
    subprocess.run(['cp', src, D + 'motionFileManager.c'], check=True)
    r = subprocess.run([EE, '-B', LIB, '-S', '-G', '8', '-O2', '-mips3', '-EL',
                        '-fno-builtin', '-nostdinc', '-fdata-sections',
                        '-I', ROOT + '/include', '-dG',
                        '-o', 'm.s', 'motionFileManager.c'],
                       cwd=D, capture_output=True, text=True)
    if r.returncode:
        print(r.stderr[-2000:]); sys.exit(1)

def section(lines):
    """the gcse dump text belonging to FN"""
    starts = [i for i, l in enumerate(lines) if l.startswith(';; Function ')]
    for i, s in enumerate(starts):
        if lines[s].split(';; Function ')[1].strip() == FN:
            e = starts[i + 1] if i + 1 < len(starts) else len(lines)
            return lines[s:e]
    raise SystemExit('function not found in dump')

def main():
    src = sys.argv[1] if len(sys.argv) > 1 else ROOT + '/sugipon/src/motionFileManager.c'
    build(src)
    L = open(D + 'motionFileManager.c.gcse', errors='replace').read().splitlines()
    S = section(L)

    # --- expression hash table: Index N  /  (plus:SI (reg:SI 1 at) (const_int K))
    # the PRE table is the LAST "Expression hash table" in the section
    tstart = max(i for i, l in enumerate(S) if l.startswith('Expression hash table'))
    idx2k, k2idx = {}, {}
    i = tstart
    while i < len(S):
        m = re.match(r'Index (\d+) \(hash', S[i])
        if m:
            body = '\n'.join(S[i + 1:i + 3])
            mm = re.search(r'\(plus:SI \(reg:SI 1 at\)\s*\n\s*\(const_int (-?\d+)', body)
            if mm:
                idx2k[int(m.group(1))] = int(mm.group(1))
                k2idx.setdefault(int(mm.group(1)), int(m.group(1)))
        if S[i].startswith('PRE: redundant') or S[i].startswith('PRE GCSE of'):
            break
        i += 1

    dels, ins, reach = {}, {}, {}
    for l in S:
        m = re.match(r'PRE: redundant insn (\d+) \(expression (\d+)\) in bb (\d+), reaching reg is (\d+)', l)
        if m:
            e = int(m.group(2))
            dels.setdefault(e, []).append((int(m.group(1)), int(m.group(3))))
            reach[e] = int(m.group(4))
        m = re.match(r'PRE/HOIST: edge \((\d+),(\d+)\),  copying expression (\d+)', l)
        if m:
            ins.setdefault(int(m.group(3)), []).append((int(m.group(1)), int(m.group(2))))
    stat = [l for l in S if l.startswith('PRE GCSE of') or l.startswith('GCSE of')]

    names = {0x50:'v50',0x60:'v60',0x70:'v70',0x80:'g80',0x90:'q90',0xA0:'qA0',
             0xB0:'gB0',0xC0:'vC0',0xD0:'qD0',0xE0:'gE0',0xF0:'qF0',0x100:'g100',
             0x110:'v110',0x120:'v120',0x130:'v130',0x150:'v150',0x160:'v160',
             0x170:'v170',0x180:'g180',0x190:'q190',0x10:'buf10',0x20:'q20',
             0x30:'q30',0x40:'q40',0x1A0:'mem'}
    print('  K   name   expr  reach  ndel  del(bb)                inserts')
    for k in sorted(idx2k.values()):
        e = k2idx[k]
        d = dels.get(e, []); s = ins.get(e, [])
        print(f'{k:5d} {names.get(k,"?"):6s} {e:5d} {reach.get(e,0):6d} {len(d):5d}  '
              f'{sorted(set(b for _,b in d))!s:22s} {sorted(set(s))}')
    print()
    # non-frame webs too (b-relative etc) -- report total PRE activity
    for l in stat: print(l)

main()
