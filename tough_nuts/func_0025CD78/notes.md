# func_0025CD78 — isNaN bit-trick (PObj, common/src/PObj.c)

best real_count: 7 (one root cause: a0<->v1 regalloc swap; structure correct)

## ROM
mfc1 $3,$f12 ; daddu $2,$3,$0 ; lui $4,0x7fff ; ori $4 ; lui $3,0x7f80 ;
and $2,$2,$4 ; subu $2,$3,$2 ; (jr delay) srl $2,$2,31
-> v0=accumulator(bits->masked->inf-masked), v1=bits then inf, a0=mask.

## Recovered shape (seed): compound accumulator -> identical data flow, but
mfc1 lands in $4(a0), mask in $3(v1), inf in $4(a0). Pure a0<->v1 mirror.

## Tried (all distinct codegen), none flips int-read mfc1 a0->v1:
union/ptr-pun; abs-var; mask-var/inf-var; both-vars; compound-update; inf-first/
mask-first decl; mask-block; signed `<0`; unsigned compare (gives sltu, wrong);
helper static (mfc1 v0) / static inline (a0); long-union (mfc1 v1 but 64-bit ops);
leading-int arg (a0 freed, no help). Caller (func_0025A768) confirms single float
arg in $f12, a0 unused.

## Next levers: permuter Step-4 shot (v0/v1/a0 swaps are its strength, cf
func_001FB768 rc7->0). Or a 32-bit source form that seeds mfc1 into v1.
