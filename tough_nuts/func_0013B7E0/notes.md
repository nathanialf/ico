# func_0013B7E0 (ios/pad.c) — build a {f1,0,-f0,0} vec, 2 calls

**Status:** 11 diffs, STRUCTURE BYTE-CORRECT. Pure scheduling near-miss —
permuter candidate.

Builds a 16-byte struct {x=a1[0xC], z0=0, y=-a1[0x10], z1=0} on the stack
(swc1 floats + sw zeros), copies it (aligned ld/sd) to the vec at sp+0,
then func_002439B0(buf=sp+0x20, D_00631970+0x80) and
func_002438B8(a0, buf, &vec).

Key fixes already in the seed:
- struct `__attribute__((aligned(8)))` → the copy uses ld/sd (aligned)
  instead of ldl/ldr (without it the 4-aligned struct copies unaligned).
- declaration order (v, t, buf) → v@sp+0, t@sp+0x10, buf@sp+0x20.

Remaining 11 diffs are gcc's instruction scheduler only:
1. t-build order (z0 vs z1 first, sw/swc1 interleave).
2. struct-copy register order: expected ld v0=low/ld v1=high; gcc emits
   v1=low/v0=high.
3. the D_00631970 gp-load + `addiu +0x80` get interleaved INTO the copy's
   load-use gap in the original (lw a1 between ld and sd), but gcc
   schedules them earlier.
The algorithm/operands are identical — only instruction order + 2 reg
names differ. Hand to permuter (randomizes scheduling).

Tried: member reorder, explicit 2x long long copy (worse, 13), src-as-local.
