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

## PERMUTER PASS 1 (240s, -j4, from rc7 seed): best = rc4 (output-20), NO clean rc0.
The rc4 came via UB (uninitialized `new_var` used as the col index → phantom register
pressure that makes gcc SAVE a0 like ROM). The rc4 diff is now TINY — only the register
for the saved a0: ROM `daddu a2,a0` + `mult1 v1,a2` + `daddu a0,a2` (saved a0 in a2);
built puts it in a1 and shifts the col (a1) to v0. So the save-a0 STRUCTURE is correct;
only an a1<->a2 register-rename remains.
CLEAN reproductions of the save (orig=a0 before/after the if) are ELIDED by gcc → rc7;
the UB phantom var is what forces the save, so rc4 is not a valid seed.
RESUME LEVER: find a clean way to (a) force gcc to materialize the a0-copy (not elide it)
AND (b) keep the col in a1 so the saved a0 lands in a2 — e.g. a valid extra live int that
mimics the phantom new_var's pressure, or pin-free reg steering. Then permute from there.
