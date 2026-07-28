#!/usr/bin/env bash
# convpass wave-2 helper (worker 3)
#   convpass_rd.sh <tu-stem> <func>
# Re-diffs quick_diff's own two canonical streams (parsed out of its
# "=== expected:" / "=== built:" listings, not its diff -y gutter) and applies
# the four coalesced-TU tolerances, so the printed count is the REAL count:
#   1. same-function relative branch (identical +0xNN, different absolute)
#   2. call unresolved on BOTH sides (jal/j 0 <x> vs jal/j 0 <y>)
#   3. %lo / %hi / jal the built object left unresolved (0) where the splat
#      baseline printed the literal (splat does not always annotate the reloc)
#   4. one trailing sll zero,zero,0x0 (the .p2align pad past endlabel)
set -uo pipefail
ROOT="$(cd "$(dirname "$0")/.." && pwd)"
cd "$ROOT"
STEM="$1"; FUNC="$2"
# GUARD: an INCLUDE_ASM'd function assembles the baseline itself, so quick_diff
# reports a meaningless rc0.  Refuse to report a match for one.
for c in "$STEM.c" "$(dirname "$STEM")/$(basename "$STEM").c"; do
  if [ -f "$c" ] && grep -qE "INCLUDE_ASM\([^)]*[ ,]$FUNC\)" "$c"; then
    echo "NOT-IMPLEMENTED (still INCLUDE_ASM) $FUNC"; exit 3
  fi
done
./tools/quick_diff.sh "$STEM" "$FUNC" 2>/dev/null | python3 -c '
import sys,re,difflib
exp=[];bui=[];cur=None
for ln in sys.stdin:
    ln=ln.rstrip("\n")
    if ln.startswith("=== expected:"): cur=exp; continue
    if ln.startswith("=== built:"):    cur=bui; continue
    if ln.startswith("=== "):          cur=None; continue
    if cur is None: continue
    m=re.match(r"^\s*\d+\t(.*)$",ln)
    if m: cur.append(m.group(1))

def relbr(l,r):
    lm=re.search(r"<[^>]*(\+0x[0-9a-f]+)>$",l); rm=re.search(r"<[^>]*(\+0x[0-9a-f]+)>$",r)
    if not(lm and rm and lm.group(1)==rm.group(1)): return False
    return re.sub(r"[0-9a-f]+ <.*","",l)==re.sub(r"[0-9a-f]+ <.*","",r)
def unresolved_call(l,r):
    lo=l.split(); ro=r.split()
    if not lo or not ro or lo[0]!=ro[0] or lo[0] not in ("jal","j"): return False
    return bool(re.match(r"^\S+\s+0 <",l))
def hi_unres(l,r):
    lm=re.match(r"^lui\s+(\S+),0x([0-9a-f]+)$",l); rm=re.match(r"^lui\s+(\S+),0x([0-9a-f]+)$",r)
    if not(lm and rm and lm.group(1)==rm.group(1)): return False
    return rm.group(2)=="0" or lm.group(2)=="0"
def lo_intu(l,r):
    lz=re.match(r"^(\S+)\s+(\S+),(\S+),(-?\d+)$",l); rz=re.match(r"^(\S+)\s+(\S+),(\S+),(-?\d+)$",r)
    if not(lz and rz): return False
    return lz.group(1)==rz.group(1) and lz.groups()[1:3]==rz.groups()[1:3] and lz.group(4)=="0"

real=[]
sm=difflib.SequenceMatcher(None,exp,bui,autojunk=False)
for tag,i1,i2,j1,j2 in sm.get_opcodes():
    if tag=="equal": continue
    L=exp[i1:i2]; R=bui[j1:j2]
    n=max(len(L),len(R))
    for k in range(n):
        l=L[k] if k<len(L) else ""
        r=R[k] if k<len(R) else ""
        if l and r and (relbr(l,r) or unresolved_call(l,r) or lo_intu(l,r) or hi_unres(l,r)): continue
        if l=="sll\tzero,zero,0x0" and not r: continue
        if r=="sll\tzero,zero,0x0" and not l: continue
        real.append((l,r))
for l,r in real: print("  %-52s | %s"%(l.expandtabs(1),r.expandtabs(1)))
print("real_count=%d  (expected %d insns, built %d)"%(len(real),len(exp),len(bui)))
'
