# func_00104638 (geometryManager) — clean rc3, FP bc1f delay-slot speculation

3-iter FP clamp loop. CLEAN rc3 seed (no REG/MEM_BARRIER); the retired
crutch seed used `REG("$f0")` + `MEM_BARRIER()`.

## Crack so far: registers FIXED, only delay-slot scheduling left

The big lever: load `min = D_00630908` PER-ITERATION **before the `if`** (not
in the else block, not hoisted out of the loop). That commits `v` to `$f0`
first, so the FP allocation matches EXACTLY: v=$f0, min=$f1, max=$f2 (the old
f0/f1 reg-swap is gone). Hoisting min out of the loop (`float min=...` before
the `for`) also gives rc3 but moves the load OUT of the loop (wrong position);
declaring min in the else block gives rc7 (reg-swap returns).

## The rc3 residual (1 root, 3 diff lines): bc1f delay slot

gcc fills the FIRST `bc1f` delay slot with the speculative `min` load; the
original has a NOP there and loads `min` in the else block (L185c):
```
   bc1f L185c            bc1f L185c
    lwc1 $f1,(min)   vs   nop            <-- the diff
   b L1870               b L1870
    swc1 $f2,0(a0)        swc1 $f2,0(a0)
  L185c:                L185c:
   c.lt.s $f1,$f0        lwc1 $f1,(min)  <-- original loads here
```
The retired `MEM_BARRIER()` in the else created the BB boundary that forced
the nop. A `*(volatile float*)&D_00630908` blocks the speculation but
OVER-serializes (rc5). No zero-cost clean-C blocker found.

## ~31 distinct hand hypotheses (30-stall reached, next=park, best=3)

reg-swap fixers: min-before-if (rc3, regs FIXED), hoist-min (rc3, wrong pos),
min-in-else (rc7), inline *a0 (rc7). Delay-slot attempts (all rc3+, none 0):
goto-CFG mirror, explicit shared-label, store-order permutations, branch
inversion (max>v / max<=v), do-while counter, register v/min, ret|=1,
subtraction compares, pointer-to-min. volatile (rc5/9, over-serializes).

## To reach rc0

Needs a zero-cost BB-boundary / non-speculatable load before the `bc1f` (the
MEM_BARRIER's job). Offline `tools/auto_permute.sh` runs the clean seed; per
`next`, no interactive permuter tokens.
