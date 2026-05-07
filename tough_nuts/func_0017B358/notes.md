# func_0017B358 — parked

VRAM: 0x0017B358 (file offset 0x07B358)
Asm source: asm/cod/07B314.s

## Attempt at 2026-05-07 — re-park (no .c seed preserved)

**Reason parked:** regalloc shuffle

**Note:** previous near-miss .c attempt was reverted+deleted before this
session's policy update; the original seed is not recoverable. Permuter
must start from scratch on this one. Reason recorded above is from
operator memory of the failure mode.

Disassembly excerpt:

```
glabel func_0017B358
    /* 7B358 0017B358 D0FFBD27 */  addiu      $sp, $sp, -0x30
    /* 7B35C 0017B35C 1000B1FF */  sd         $s1, 0x10($sp)
    /* 7B360 0017B360 0000B0FF */  sd         $s0, 0x0($sp)
    /* 7B364 0017B364 2D888000 */  daddu      $s1, $a0, $zero
    /* 7B368 0017B368 2D80A000 */  daddu      $s0, $a1, $zero
    /* 7B36C 0017B36C 2000BFFF */  sd         $ra, 0x20($sp)
    /* 7B370 0017B370 5E0E090C */  jal        func_00243978
    /* 7B374 0017B374 2D200002 */   daddu     $a0, $s0, $zero
    /* 7B378 0017B378 2D202002 */  daddu      $a0, $s1, $zero
    /* 7B37C 0017B37C 2D280002 */  daddu      $a1, $s0, $zero
    /* 7B380 0017B380 2000BFDF */  ld         $ra, 0x20($sp)
    /* 7B384 0017B384 1000B1DF */  ld         $s1, 0x10($sp)
    /* 7B388 0017B388 0000B0DF */  ld         $s0, 0x0($sp)
    /* 7B38C 0017B38C AE1A0408 */  j          func_00106AB8
    /* 7B390 0017B390 3000BD27 */   addiu     $sp, $sp, 0x30
endlabel func_0017B358
```
