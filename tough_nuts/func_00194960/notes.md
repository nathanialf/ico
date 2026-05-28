# func_00194960 — angle normalize mod 360 (mail-add-data)

VRAM 0x00194960. TU: src/mail-add-data.c (coalesced). Asm:
asm/nonmatchings/src/mail-add-data/func_00194960.s

Best real_count: **2** (everything matches except ONE instruction position).

## What it does
Normalizes an int angle into (-180, 180]. 0x168 = 360.
- a0 > 0:  v = a0 % 360            (signed remainder, mfhi)
- a0 <= 0: v = a0 + (|a0|/360*360 + 360)   (quotient mflo, mult back, add)
  (== a0 % 360 + 360, but the dev wrote it the abs/quotient way)
- return (v < 181) ? v : v - 360   (slti + addiu + movn clamp)

## Levers that WORKED (14 -> 2)
1. Reuse `a0` as the accumulator (not a separate `v`) -> keeps it in $4,
   gives the `bgez+negu` branch abs instead of a movn abs + copy.
2. Group the negative path as `a0 + (q*360 + 360)` via a temp
   `t = a/360*360 + 360` -> folds the +360 into the (q*360) chain.
3. **`register int c REG("$2") = 360;`** — THE unlock (9 -> 2): forces the
   constant 360 into ONE shared register (v0) across both the `%` and `/`
   paths, the `*360`, and the `+360`. Without it gcc materializes 360
   twice (v0 + v1) and uses an immediate `+360`, cascading the regalloc
   (abs/q reg, mult dest a1). Use literal 360 for the final `a0 - 360`
   (that one IS an addiu immediate). Seed has this.

## RESIDUAL 2 diffs (scheduler floor)
The 2nd div (`|a0| / 360`, else path) has its divzero guard SWAPPED with
the div: original = `negu; div; beql c,0; break`, built = `negu; beql c,0;
break; div`. gcc hoists the guard (depends only on the ready divisor c)
into the slot while the freshly-`negu`'d dividend |a0| settles. The first
div (a0 % 360, dividend a0 ready at entry) emits div-then-guard correctly.

Levers RULED OUT for the residual:
- abs-up-front (compute `|a0|` before the `if`): FIXES the div/guard order
  but hoists the whole abs block above the `blez` (net 6 diffs).
- split quotient `int q = a/c;`, inline abs, `ANCHOR(a)` before div: no change (still 2).
- `int c=360` unpinned: regresses to 14 (360 lands in a1).

## Next: permuter
Pure 1-instruction scheduler reorder = ideal permuter target (permute_run
now finds carved/coalesced asm after the maxdepth fix). CFLAGS = exact
quick_diff CFLAGS (no per-file flag). See [[branch_likely_emission]] /
scheduler-coupling notes. Or a fresh idea to keep |a0| "older" before the
2nd div without hoisting the abs out of the else block.
