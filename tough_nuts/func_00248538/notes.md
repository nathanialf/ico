# func_00248538 — PARKED (near-miss rc3), not yet permuter-run

VRAM 0x00248538, common/src/PObj.c. DI/swap-global/EI critical section.

## Recovered shape (rc3, the seed)
`int f(int a0){ if(func_002490C0(1)!=0) return 0; DI(); old=D_00710F80[0];
D_00710F80[0]=a0; EI(); return old; }` where DI=func_00101A40 (called with NO
arg — asm has nop in the jal delay; the file-scope proto is `(int*)` so it must
be called through `((void(*)(void))func_00101A40)()`), EI=func_00101A88(void).

## Levers already applied (got rc6 -> rc3)
- far-global D_00710F80 must be `extern int D_00710F80[]` + `[0]` indexing →
  forces %hi/%lo (scalar `extern int` → wrong gp-rel). FIXED.
- EARLY-RETURN form (`if(cond) return 0; ...; return old;`) → avoids ret/old
  coalescing that the `int ret=0; if(){...ret=old;}` form caused (rc6→rc3). FIXED.

## Residual rc3 = pure %hi register tiebreak (1 root, 3 byte-diffs)
ROM puts %hi(D_00710F80) in **v1** ($3); gcc puts it in **v0** ($2) (reuses the
dead func_002490C0-return / early-return-0 reg). lui+lw(read old)+sw(write a0)
all use this one reg. ~13 hand forms tried (ptr, ptr-to-array deref[rc10],
array/scalar __asm__ alias, guard-in-var, uint, body-in-if[rc4], goto[rc4],
write-first) — all rc3 or worse. Same class as parked func_002416F0 (v0/v1 tie).

## RESUME
Find a hand shape that pushes the %hi to v1 (occupy v0 / shift pseudo order)
WITHOUT extra instructions. If genuinely stuck, this is permuter-class (the
regalloc flip) — but per maintainer pref, hand-shape first.
