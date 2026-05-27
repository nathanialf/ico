# func_001F34C8 (src/weapon.c) — NEAR-MATCH, real_count 9 (was 73)

VRAM 0x001F34C8, 0x228 (138 insns). FP + two 64-byte struct copies + a loop.
asm/nonmatchings/src/weapon/func_001F34C8.s

## Status: structure FULLY correct. 73 -> 9 over a long hand+permuter effort.
PLATEAUED at 9 (match_loop stall 21, verdict=park). Residual is pure
regalloc/scheduling ORDER. Seed = func_001F34C8.c (apply recipe in its header).

## LEVER CHAIN (what got 73 -> 9), all confirmed in TU context
1. **typed `WBody *arg1` PARAM (not int)** + **DROP the REG pins on src/n**
   -> the 64-byte `req.body = *src` copy BATCHES (alias analysis); 73 -> 34.
   (cousin: feedback_struct_copy_batch_typed_param / COOKBOOK §6.10)
2. **pin flag->$8(t0), five(`?5`)->$6(a2), ii(i copy)->$15(t7)** -> 34 -> 24.
3. **`long long new_var; buf[new_var=0x50/4]=1;`** (permuter-found) -> fixes the
   self->$a0 coalescing (self stays in $a0); 24 -> 16.
4. **`volatile unsigned int D_00632010`** (permuter-found; apply to ALL its
   decls in the TU — func_001F43D0 stays 0) -> 16 -> 15.
5. **`int new_var2=1; buf[0x50]=new_var2;` + `-new_var2` as the 6th arg of the
   loop's func_001B7FE8** (permuter-found, score-820) — ties `1` live across the
   loop; 15 -> 13.
6. **VOLATILE flag store: `*(volatile int*)&((int*)&req.body)[0x30/4]=flag;`**
   (HAND-found from a decl-order/store batch) — pins the flag store, collapses
   the 0x10/0x18 copy-temp swap + loop-align nop; 13 -> 9.

## THE RESIDUAL (9) — two pure-ORDER clusters, both resisted ~25 hand tries
AND the permuter (plateaued 820 == this 13-stage; never reached 0):
  a. **0/8 copy-temp swap**: offsets 0 & 8 get $13/$14 swapped (orig 0->t5,8->t6;
     build 0->t6,8->t5). 4 diffs. Pure local-alloc quantity ordering — can't
     volatile a single struct-copy element without serializing.
  b. **jal store-cluster**: original = self-store EARLY (interleaved in copy),
     flag-store LATE, D_0061A850 `%lo addiu` early, jal-delay = `sw s0`(buf[0x50]);
     build swaps self<->flag store positions and puts `addiu a2` in the delay.
     ~5 diffs. Every reorder/volatile/eager/barrier tried regressed or no-changed.

RULED OUT this round (all 15->/9-> no-change or worse): eager D_0061A850 (KEEP_LIVE
45 / light fp no-change), int|long long new_var, 2nd/3rd dead slot, member-wise
copy, body-as-array, MEM_BARRIER (49), ANCHOR(self), cache self[0x15C], volatile
on self/buf[0x50]/buf[0x54]/src/copy-source, MATERIALIZE(flag), buf-store reorder,
self/i-after-copy, __builtin_memcpy(typed src).

## PERMUTER FROM 9-SEED (20 min, ~58k iters): NO improvement. base score=900,
plateaued at 820, never score-0. CRUCIAL: the 820 "best" candidate's only change
is REMOVING the volatile from the flag store (lever 6) — i.e. it is the
real_count-13 variant. So the permuter's diff metric DISAGREES with match_diff's
reloc-normalized real_count here: it scores the 13-variant (820) better than the
9-variant (900) and "optimizes" toward the worse one. **The permuter cannot beat
the hand-found 9 on this function** — do not trust its score; verify any
candidate with match_diff before adopting. 9 is the joint floor (hand + permuter).

Residual (a)/(b) are pure local-alloc/sched ORDER. If ever revisited, the only
untried angle is influencing sched1's load-order for the 0/8 copy elems (cluster
a) or the gas delay-slot fill (cluster b) — likely a postprocess, not C.
Cousins: COOKBOOK §6.10; feedback_struct_copy_batch_typed_param.
