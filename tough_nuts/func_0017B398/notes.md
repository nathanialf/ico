
---

## Attempt at 2026-05-09

**Reason parked:** plateau on s0/s1 swap + lwc1 offset folding.

Seed: `tough_nuts/func_0017B398/07B398.c` — natural-C form is functionally
correct but two diffs persist after exhausting source-level tweaks:

1. **s0/s1 register swap.** Target allocates `s1 = self` and `s0 = y`; gcc
   emits `s1 = y` and `s0 = self`. Both args used twice (call + tail call),
   so usage-frequency tiebreak can't decide. `register T x REG("$17")`
   pin causes gcc to add a third callee-save (s2) instead of swapping.
2. **lwc1 offset folded into addiu.** Target keeps `lwc1 f12, 0x138(v1)`
   with `addiu v1, v1, %lo(D_00565060)`; gcc folds 0x138 into the addiu
   (`addiu v1, v1, %lo+0x138`) and emits `lwc1 f12, 0(v1)`. Same total
   bytes, different scheduling.

Disassembly excerpt (asm/cod/07B398.s):

```
glabel func_0017B398
    addiu      $sp, $sp, -0x30
    sd         $s1, 0x10($sp)
    sd         $s0, 0x0($sp)
    daddu      $s1, $a0, $zero      # s1 = self
    daddu      $s0, $a1, $zero      # s0 = y
    sd         $ra, 0x20($sp)
    jal        func_00243978
     daddu     $a0, $s0, $zero       # delay: a0 = s0 = y
    lw         $a1, 0x15C($s1)       # a1 = self->15C
    addiu      $a2, $zero, 0x190
    lui        $v1, %hi(D_00565060)
    daddu      $a0, $s1, $zero
    lw         $v0, 0x4A0($a1)
    addiu      $v1, $v1, %lo(D_00565060)   # base, no +0x138
    daddu      $a1, $s0, $zero
    ld         $ra, 0x20($sp)
    mult       $v0, $v0, $a2
    ld         $s1, 0x10($sp)
    ld         $s0, 0x0($sp)
    addu       $v1, $v1, $v0
    lwc1       $f12, 0x138($v1)
    cvt.s.w    $f12, $f12
    j          func_0015B780
     addiu     $sp, $sp, 0x30
endlabel func_0017B398
```

Permuter targets: shuffle the order of arg-saving / first-use of self vs y,
or try a typed `D_00565060[idx][0x138/4]` 2D array form to keep 0x138 out of
the addiu.
