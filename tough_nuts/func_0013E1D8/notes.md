# func_0013E1D8 — parked

VRAM: 0x0013E1D8 (file offset 0x03E1D8)
Asm source: asm/cod/03DD9C.s

## Attempt at 2026-05-07 — re-park (no .c seed preserved)

**Reason parked:** andi delay-slot scheduling vs ee-gcc 2.9 (sibling family with 13E190)

**Note:** previous near-miss .c attempt was reverted+deleted before this
session's policy update; the original seed is not recoverable. Permuter
must start from scratch on this one. Reason recorded above is from
operator memory of the failure mode.

Disassembly excerpt:

```
glabel func_0013E1D8
    /* 3E1D8 0013E1D8 C0FFBD27 */  addiu      $sp, $sp, -0x40
    /* 3E1DC 0013E1DC 0000B0FF */  sd         $s0, 0x0($sp)
    /* 3E1E0 0013E1E0 2D808000 */  daddu      $s0, $a0, $zero
    /* 3E1E4 0013E1E4 2000B2FF */  sd         $s2, 0x20($sp)
    /* 3E1E8 0013E1E8 1000B1FF */  sd         $s1, 0x10($sp)
    /* 3E1EC 0013E1EC 2D90C000 */  daddu      $s2, $a2, $zero
    /* 3E1F0 0013E1F0 3000BFFF */  sd         $ra, 0x30($sp)
    /* 3E1F4 0013E1F4 7EF7040C */  jal        func_0013DDF8
    /* 3E1F8 0013E1F8 FF00B130 */   andi      $s1, $a1, 0xFF
    /* 3E1FC 0013E1FC 2D200002 */  daddu      $a0, $s0, $zero
    /* 3E200 0013E200 2D282002 */  daddu      $a1, $s1, $zero
    /* 3E204 0013E204 2D304002 */  daddu      $a2, $s2, $zero
    /* 3E208 0013E208 3000BFDF */  ld         $ra, 0x30($sp)
    /* 3E20C 0013E20C 2000B2DF */  ld         $s2, 0x20($sp)
    /* 3E210 0013E210 1000B1DF */  ld         $s1, 0x10($sp)
    /* 3E214 0013E214 0000B0DF */  ld         $s0, 0x0($sp)
    /* 3E218 0013E218 30F80408 */  j          func_0013E0C0
    /* 3E21C 0013E21C 4000BD27 */   addiu     $sp, $sp, 0x40
endlabel func_0013E1D8
```
