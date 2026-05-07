# func_0013E190 — parked

VRAM: 0x0013E190 (file offset 0x03E190)
Asm source: asm/cod/03DD9C.s

## Attempt at 2026-05-07 — re-park (no .c seed preserved)

**Reason parked:** andi delay-slot scheduling vs ee-gcc 2.9 (sibling family with 13F0A0/F0E8)

**Note:** previous near-miss .c attempt was reverted+deleted before this
session's policy update; the original seed is not recoverable. Permuter
must start from scratch on this one. Reason recorded above is from
operator memory of the failure mode.

Disassembly excerpt:

```
glabel func_0013E190
    /* 3E190 0013E190 C0FFBD27 */  addiu      $sp, $sp, -0x40
    /* 3E194 0013E194 0000B0FF */  sd         $s0, 0x0($sp)
    /* 3E198 0013E198 2D808000 */  daddu      $s0, $a0, $zero
    /* 3E19C 0013E19C 2000B2FF */  sd         $s2, 0x20($sp)
    /* 3E1A0 0013E1A0 1000B1FF */  sd         $s1, 0x10($sp)
    /* 3E1A4 0013E1A4 2D90C000 */  daddu      $s2, $a2, $zero
    /* 3E1A8 0013E1A8 3000BFFF */  sd         $ra, 0x30($sp)
    /* 3E1AC 0013E1AC 7EF7040C */  jal        func_0013DDF8
    /* 3E1B0 0013E1B0 FF00B130 */   andi      $s1, $a1, 0xFF
    /* 3E1B4 0013E1B4 2D200002 */  daddu      $a0, $s0, $zero
    /* 3E1B8 0013E1B8 2D282002 */  daddu      $a1, $s1, $zero
    /* 3E1BC 0013E1BC 2D304002 */  daddu      $a2, $s2, $zero
    /* 3E1C0 0013E1C0 3000BFDF */  ld         $ra, 0x30($sp)
    /* 3E1C4 0013E1C4 2000B2DF */  ld         $s2, 0x20($sp)
    /* 3E1C8 0013E1C8 1000B1DF */  ld         $s1, 0x10($sp)
    /* 3E1CC 0013E1CC 0000B0DF */  ld         $s0, 0x0($sp)
    /* 3E1D0 0013E1D0 FCF70408 */  j          func_0013DFF0
    /* 3E1D4 0013E1D4 4000BD27 */   addiu     $sp, $sp, 0x40
endlabel func_0013E190
```
