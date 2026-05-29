# func_001CE5F8 — parked at rc1 (assembler artifact, structure perfect)

TU: src/enemy.c. Best real_count: 1.

## Root cause (NOT a code-shape floor)
Structure fully matches: frame 0x30 (s0/s1, no s2 — `p` live range shortened so
self->0x15C is RE-READ after the func_001224E0 call instead of cached in a
callee-saved reg); func_001CF770 declared `int` (discarded return reserves v0 →
the s0->0x10 load lands in v1 not v0); first func_001CF998 arg is a VOLATILE load
(`*(volatile int*)(s0+0x18)`) so it can't hoist into the bc1f delay → bc1f delay
stays a bare nop and the lw lands in the jal delay (matches original exactly).

ONLY residual: bundled ee-as 2.96 (tools/cc/ee-gcc2.96/bin/as) inserts an FCC
hazard nop BETWEEN `c.eq.s $f0,$f1` and `bc1f` (a real `sll zero,zero` at
.o offset 0x27b4). The original ELF has c.eq.s (CE638) IMMEDIATELY followed by
bc1f (CE63C) with NO hazard nop — i.e. R5900 needs no c.cond→bc1 gap and the
real Sony ee-as didn't insert one. Matched pattern-2 cases (e.g. a_p_1.o
c.lt.s;bc1f;neg.s) avoid it only because their bc1f DELAY is filled with a real
insn; a BARE-delay reorder bc1f (our case, and the original) triggers the
bundled gas's spurious nop.

## Fix needed (infra, like fcc_nop but INVERSE)
postprocess_fcc_nop.py ADDS #nop->nop in noreorder blocks. Need the INVERSE: a
gated pass that STRIPS the bundled-as-inserted hazard nop between a c.{eq,lt,le}.s
and a following reorder bc1[ft] whose delay is a bare nop, for funcs whose
original lacks it. Then func_001CE5F8 matches. (Confirm: with such a strip, rc→0.)
