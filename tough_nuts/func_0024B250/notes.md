# func_0024B250 (common/src/PObj) — parked rc7 after 30-stall

## State: rc7. PURE regalloc swap (multiply-unit assignment is IDENTICAL: a0*0x70->mult1, a1*0x1C->mult).
ROM: daddu a2,a0 (SAVE orig a0->a2); addiu v1,0x70; addiu a0,0x1C (REUSE a0 reg as the 0x1C const);
     mult1 v1,a2,v1 (orig_a0*0x70); mult a0,a1,a0 (a1*0x1C); ... addu a0,a0,v1 (index in a0);
     ... func_0024B0E8(a2 = orig a0).
Built: keeps a0 (orig), uses a1 as the a1*0x1C accumulator and v0 as the 0x1C const; index in a1.

## Root: func_0024B0E8(a0) keeps a0 live across the 2D index. ROM sacrifices a0 (saves to a2) and
reuses the a0 register for the const+index; gcc(mine) keeps a0 and uses a1/v0. Source-invariant.

## Exhausted (30 distinct hand hypotheses, all rc7 or worse):
2D-array D[a0][a1].f10 (rc7=best, dev idiom, matches sibling func_0024A858 style); explicit
a0*0x70+a1*0x1C (rc10) / col-first (rc9); reassign a0=index + orig (rc9); row ptr D[a0] (rc12);
elem ptr &D[a0][a1] (rc11); result temp (rc7); xor/sub/unsigned/!cond/0x40000-1/262143 compares (rc7-10);
int-deref f10 (rc7-9); index temp (rc8-9); a0 copy local; (*rows)[4] ptr; nested ret.
The a0-save/reuse regalloc is INVARIANT to source shape.

## Verdict: permuter-domain regalloc swap (same class as staffRollMain, which the permuter cracked
via store reorder + shared-const). RESUME: apply seed, reset, permuter or fresh non-source idiom.
