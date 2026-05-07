# func_0013F0A0 — parked

VRAM: 0x0013F0A0 (file offset 0x03F0A0)
Asm source: asm/cod/03EE60.s

## Attempt at 2026-05-07 — re-park (no .c seed preserved)

**Reason parked:** andi delay-slot scheduling vs ee-gcc 2.9 (sibling family with 13E190)

**Note:** previous near-miss .c attempt was reverted+deleted before this
session's policy update; the original seed is not recoverable. Permuter
must start from scratch on this one. Reason recorded above is from
operator memory of the failure mode.

Disassembly excerpt:

```
glabel func_0013F0A0
    /* 3F0A0 0013F0A0 C0FFBD27 */  addiu      $sp, $sp, -0x40
    /* 3F0A4 0013F0A4 0000B0FF */  sd         $s0, 0x0($sp)
    /* 3F0A8 0013F0A8 2D808000 */  daddu      $s0, $a0, $zero
    /* 3F0AC 0013F0AC 2000B2FF */  sd         $s2, 0x20($sp)
    /* 3F0B0 0013F0B0 1000B1FF */  sd         $s1, 0x10($sp)
    /* 3F0B4 0013F0B4 2D90C000 */  daddu      $s2, $a2, $zero
    /* 3F0B8 0013F0B8 3000BFFF */  sd         $ra, 0x30($sp)
    /* 3F0BC 0013F0BC 6CFB040C */  jal        func_0013EDB0
    /* 3F0C0 0013F0C0 FF00B130 */   andi      $s1, $a1, 0xFF
    /* 3F0C4 0013F0C4 2D200002 */  daddu      $a0, $s0, $zero
    /* 3F0C8 0013F0C8 2D282002 */  daddu      $a1, $s1, $zero
    /* 3F0CC 0013F0CC 2D304002 */  daddu      $a2, $s2, $zero
    /* 3F0D0 0013F0D0 3000BFDF */  ld         $ra, 0x30($sp)
    /* 3F0D4 0013F0D4 2000B2DF */  ld         $s2, 0x20($sp)
    /* 3F0D8 0013F0D8 1000B1DF */  ld         $s1, 0x10($sp)
    /* 3F0DC 0013F0DC 0000B0DF */  ld         $s0, 0x0($sp)
    /* 3F0E0 0013F0E0 98FB0408 */  j          func_0013EE60
    /* 3F0E4 0013F0E4 4000BD27 */   addiu     $sp, $sp, 0x40
endlabel func_0013F0A0
```
