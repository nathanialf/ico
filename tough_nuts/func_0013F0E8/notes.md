# func_0013F0E8 — parked

VRAM: 0x0013F0E8 (file offset 0x03F0E8)
Asm source: asm/cod/03EE60.s

## Attempt at 2026-05-07 — re-park (no .c seed preserved)

**Reason parked:** andi delay-slot scheduling vs ee-gcc 2.9 (sibling family with 13E190)

**Note:** previous near-miss .c attempt was reverted+deleted before this
session's policy update; the original seed is not recoverable. Permuter
must start from scratch on this one. Reason recorded above is from
operator memory of the failure mode.

Disassembly excerpt:

```
glabel func_0013F0E8
    /* 3F0E8 0013F0E8 C0FFBD27 */  addiu      $sp, $sp, -0x40
    /* 3F0EC 0013F0EC 0000B0FF */  sd         $s0, 0x0($sp)
    /* 3F0F0 0013F0F0 2D808000 */  daddu      $s0, $a0, $zero
    /* 3F0F4 0013F0F4 2000B2FF */  sd         $s2, 0x20($sp)
    /* 3F0F8 0013F0F8 1000B1FF */  sd         $s1, 0x10($sp)
    /* 3F0FC 0013F0FC 2D90C000 */  daddu      $s2, $a2, $zero
    /* 3F100 0013F100 3000BFFF */  sd         $ra, 0x30($sp)
    /* 3F104 0013F104 6CFB040C */  jal        func_0013EDB0
    /* 3F108 0013F108 FF00B130 */   andi      $s1, $a1, 0xFF
    /* 3F10C 0013F10C 2D200002 */  daddu      $a0, $s0, $zero
    /* 3F110 0013F110 2D282002 */  daddu      $a1, $s1, $zero
    /* 3F114 0013F114 2D304002 */  daddu      $a2, $s2, $zero
    /* 3F118 0013F118 3000BFDF */  ld         $ra, 0x30($sp)
    /* 3F11C 0013F11C 2000B2DF */  ld         $s2, 0x20($sp)
    /* 3F120 0013F120 1000B1DF */  ld         $s1, 0x10($sp)
    /* 3F124 0013F124 0000B0DF */  ld         $s0, 0x0($sp)
    /* 3F128 0013F128 F4FB0408 */  j          func_0013EFD0
    /* 3F12C 0013F12C 4000BD27 */   addiu     $sp, $sp, 0x40
endlabel func_0013F0E8
```
