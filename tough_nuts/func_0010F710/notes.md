# func_0010F710 — packet-mgr init (D_004C7710), carved cod subsegment src/cod/00F710

Best real_count: **2** (default scheduler). Carved from the
`[0x00F5D4, asm]` blob (stale orphan: orphan .s was under
asm/nonmatchings/src/cod/00F710 + sibling note at yaml line for 0x0118E8).

## What it does
`D_004C7710` is a double-buffered packet/DMA manager (`int[]`; `[4]`/0x10 =
free pointer, see siblings src/cod/0FBBE0.c, src/cod/011918.c). The function
reads the free pointer `p = D_004C7710[4]` and writes a sequence of fields,
advancing the free pointer 3x (p+8, p+0x18, p+0x20). The intermediate
free-pointer writes survive DSE only because of the interleaved stores
THROUGH `p` (`p[2]=0x11000000` tag, `*(ll*)(p+6)=0xE`), which gcc can't prove
don't alias `D_004C7710` (p is loaded from memory).

## Root cause of the residual 2 diffs (SCHEDULER coupling)
The original (clean C, default scheduler) emits:
- `base[4]=p+0x18` store FIRST of the three field stores,
- BUT computes the `p+0x18` addiu LAST (reusing `a0` from the dead `p+8`),
- `p+0xC`→a3, `p+0x10`→a2 (computed before p+0x18, descending fresh regs).

Every hand form trades store-ORDER against the temp-REGISTER assignment:
- **2-diff** (seed, volatile base[6]/[7]+sd+final base[4], base[4]=p+0x18
  non-vol): temp regs RIGHT (a0/a3/a2), but base[4]=p+0x18 store sinks
  BELOW base[6]/[7] (non-vol sinks past volatiles).
- **5-diff** (also pin `e=p+0x18`→$4): store order RIGHT, but p+0x10/p+0x20
  regs swap a1<->a2 (pinning forced early compute → different fresh-reg order).
- Pinning p+0x10/$6 + p+0x20/$5 → 9 (collides with tag const reg $8).
- all-volatile incl base[4]=p+0x18 → 6 (rotates a0/a2/a3).
- MEM_BARRIER after p+0x18 → 19 (forces reload).
- `-fno-schedule-insns` → 12 (constants no longer hoisted; original IS
  scheduled). Removed from extra_cflags.

## Next levers (for resume / permuter)
This is a pure instruction-SCHEDULING reorder (store position vs fresh-reg
order are coupled in ee-gcc's list scheduler). The permuter is the right
tool (cf. [[permuter_cracks_reorg_tail]]). Seed is the 2-diff form. The
permuter needs to find the statement ordering that places base[4]=p+0x18
first while leaving its addiu late (a0 reuse) — a statement reorder it can
explore. CFLAGS for permute_run = exact quick_diff CFLAGS (no per-file flag).

## UPDATE 2026-05-28: in-loop permuter PLATEAUED at base score 30 (=2 diffs) after 5281 iters, no score-0. Left for offline auto_permute.sh (longer runs) or a fresh struct-based structural rewrite. Carve kept so the permuter has its target.

## UPDATE 2026-05-28 re-grind (user: don't park before 30 iters, tracked by match_loop)
NOT a plateau — new progress. The **c$7/t$6/e$4 pins (drop f) on the
all-volatile form** make the STORE ORDER fully correct (base[4]=p+0x18,
base[6], base[7], sd, base[4]=p+0x20 all match) -> rc4. Remaining 4 = the
addiu EMIT order: gcc computes p+0x18 (e) before p+0x10 (t) because e is
stored first (base[4]=e), but the original computes ascending
(p+0xC,p+0x10,p+0x18,p+0x20) interleaved with the base[3]/base[5]/tag
stores. So store-order and addiu-emit-order are decoupled in the original;
the volatile-store forms couple them via first-use.
Ruled out this round: reorder lever on non-vol stores (best 9, DSEs);
full 4-pin incl f=$5 (rc9, f displaces tag const to a1); ANCHOR(c/t/e)
(rc12, disrupts tag); interleaved c/t/e assignment between early stores
(rc4, gcc still sinks the base[5] store before the t addiu); dependency
e=t+8 would change the addiu base p->t (won't match).
NEXT (toward 30): force the p+0x10 addiu before the p+0x18 addiu while
keeping e stored first — e.g. a non-volatile use/ANCHOR of t before e that
doesn't touch the tag reg; or revisit whether base[6]/[7] stores can be
non-volatile with only the sd+final-base[4] as the §8.17 pair. Best seed
remains the rc2 form (regs right, one store mis-positioned).
