# func_00107B28 (motionManager2 — best-bone-match, FP) — near-match @69, NOT matched

VRAM 0x00107B28, 0x2B0 (172 insns). FLOATING-POINT heavy.
asm/nonmatchings/src/motionManager2/func_00107B28.s

## Status: CFG + logic fully CORRECT; ~8 genuine iters, 85 -> 69 diffs

`int func_00107B28(int a0,int a1,int a2,int *a3,int a4,int a5)` — loops 4
candidate keyframe PAIRS from D_00275FD0[]={0,1,3,2,0} (pairs (p[0],p[1]),
p walks +1 int/iter), builds a transform (func_00243AE8/978/930 into
sp+0x80), optional flip if a4 (func_00244448 with -1.0f), computes an FP
distance (func_00168A28 with the transform xyz + a negated func_00243950
result; then func_00168BD0 -> f0), abs it (bc1tl+neg), tracks the min
(fbest=$f21 init FLT_MAX, best=$23 init -1). After loop: assert if best==-1
(func_001AD748/func_00263FF0, line 0x54E); emit to a0/a1 if nonzero.
vbase=$19 = a2 ? a2 : <sp+0 buffer>. thresh=$f22=D_0063097C(-0.1).

Draft (69 diffs, full correct structure) in func_00107B28.c — paste into
src/motionManager2.c replacing the INCLUDE_ASM. FIXES ALREADY FOUND:
- `D_00631B5C` (FLT_MAX bits) loaded gp_rel by default but original uses
  %hi/%lo -> alias `extern unsigned int D_00631B5C_hi[] __asm__("D_00631B5C")`
  + `*(float*)D_00631B5C_hi`. Same for D_00631B50 / D_00631B58 (assert args).
- `fbest = *(float*)D_..._hi` (bit reinterpret, NOT (float)int convert).
- func_00263FF0 3rd arg is `&D_00631B58` (addr of the int), proto `const void*`.

## REMAINING (the ~55 residual, all regalloc/scheduling — permuter territory)
1. s5<->s6 swap: sp+0x40 buffer wants $s6 (orig) but gets $s5; sp+0x70 the
   reverse. Cascades through every buffer ref.
2. v0<->v1 swap: a3[0] wants $v0 (orig), a3[1] $v1; built reversed. Source
   reorder via temps did NOT flip it.
3. fbest ($f21) load placement: orig loads it BEFORE the first func_00168AE0
   call; built after.
4. FP-LICM: orig keeps thresh(D_0063097C) in $f22 + re-materializes 0.0
   (mtc1 $0,$f1) inline for the `d<0` abs; built hoists 0.0 into $f22 and
   reloads thresh each iter. (A `float thresh=...` var REGRESSED to 88 —
   do NOT do that.)

NEXT: structure is correct, so this is a permuter case (cf. func_00198218)
— but seed it AFTER collapsing the s5/s6 + v0/v1 systematic swaps by hand
(try REG() pins: pin the sp+0x40 buffer ptr to $22/$s6, pin a3[0] to $v0),
which should drop it under ~15 first. FP + stack-layout = a dedicated
session. Cousins: [[far_global_direct_index_hoists_hi]] (the alias trick),
[[pin_computed_var_to_dead_arg_reg]], [[base_copy_pin_and_countup_flag]].
