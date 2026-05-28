# func_0014B168 — parallel-control setter (act-parallel-control)

VRAM 0x0014B168. TU: src/act-parallel-control.c (coalesced). Asm:
asm/nonmatchings/src/act-parallel-control/func_0014B168.s

Best real_count: **6** (gcc scheduler tail, see below).

## What it does
`sub = self->_164`. Returns int (0/1):
- a3 == 6: zero sub->_9C, _98, _A0; return 0.
- a3 < sub->_9C: return 0.
- else: sub->_98 = a1; if (a2 != 0) copy 3 floats a2[0..2] -> sub->_B0/_B4/_B8;
  sub->_9C = a3; sub->_A0 = a4; return 1.
5 args (EE ABI: a0..a3 in $4-$7, a4 in $8/t0). Float copy guarded by a2!=0.

## Levers that WORKED (14 -> 6)
1. `register int rv REG("$4") = 0;` declared AFTER `sub = self->_164` —
   the original reuses the dead `self`/a0 reg for the return value
   (rv=0/rv=1 in a0, `daddu v0,a0` at the end). 14->... (rv reg fix).
2. `goto end` shared exit for the two early `return 0` paths. (rv/end).
   Combined 14->8.
3. `*(volatile int *)` on the _9C/_98/_A0 and _9C/_A0 stores — locks the
   store order (gcc was hoisting the _A0 (offset 160) store before _9C
   (156) in both the a3==6 block and the tail). 8->6. Tail now exact.

## RESIDUAL 6 diffs (gcc scheduler — branch-delay + epilogue distribution)
Two coupled scheduler issues:
1. **a3==6 b-delay**: original emits `_9C; _98; b end; _A0 (in b-delay)`.
   The volatile on _A0 (needed for store ORDER) prevents it from filling
   the `goto end` branch-delay slot, so gcc inlines `jr ra; daddu v0,a0`
   (duplicating the epilogue) instead of `b end`. Making _A0 non-volatile
   restores the b-delay candidacy but then gcc reorders it to the middle
   (_9C, _A0, _98) — store-order vs delay-fill are in tension.
2. **epilogue `daddu v0,a0` (rv->v0) distribution**: the original does
   this move ONCE at the shared end (0x5c); gcc distributes it into the
   a3<_9C bne delay slot (and the a3==6 inline). The branches' delays are
   NOP in the original.

## Next: permuter / fresh idea
Pure gcc store-scheduling + delay-slot/epilogue-sharing tail. Try:
`tools/lever.py reorder` on the a3==6 stores (non-volatile variant) to
find a source order gcc emits as _9C,_98,_A0(delay); and a barrier/anchor
at `end:` to stop the `daddu v0,a0` distributing into the branch delays.
Permuter seed is the rc6 all-volatile form. CFLAGS = exact quick_diff
CFLAGS (no per-file flag).
