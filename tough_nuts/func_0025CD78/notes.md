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

## Cycle 2 findings (resume)
- CONFIRMED isnanf bit-twiddle (COOKBOOK §7.3: mfc1+lui0x7fff+ori0xffff+and...).
  Canonical ISNANF_BIT_TWIDDLE macro is RETIRED (include/matching.h deleted) -> pure clean-C only.
- KEY LEVER FOUND but conflicting: the OUTER subtraction direction flips mfc1 reg.
    `(u.i & mask) - const`  -> mfc1 $3 (v1), mask a0, copy v0  [ROM front!] but tail = addu+sra (abs-const)
    `const - (u.i & mask)`  -> mfc1 $4 (a0)                    [wrong front] but tail = subu+srl  [ROM tail!]
  ROM needs BOTH: v1-front AND subu+srl tail (inf - abs). No 32-bit form yields both.
- permuter REFUSED at stall 4/30 (gate working). next=iterate. ~35 distinct forms total.
- NEXT: find a source form giving `(u.i&mask)` as left-operand of the outer op while
  computing `inf - abs` (subu) — or fire permuter at a real 30-stall / PERMUTE_FORCE override.
