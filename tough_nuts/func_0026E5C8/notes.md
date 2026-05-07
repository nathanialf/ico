# func_0026E5C8 — parked

VRAM: 0x0026E5C8 (file offset 0x16E5C8)
Asm source: asm/cod/16D6C8.s

## Attempt at 2026-05-07 — re-park (no .c seed preserved)

**Reason parked:** daddu schedule (sibling of 26B148)

**Note:** previous near-miss .c attempt was reverted+deleted before this
session's policy update; the original seed is not recoverable. Permuter
must start from scratch on this one. Reason recorded above is from
operator memory of the failure mode.

Disassembly excerpt:

```
glabel func_0026E5C8
    /* 16E5C8 0026E5C8 2D108000 */  daddu      $v0, $a0, $zero
    /* 16E5CC 0026E5CC 5500033C */  lui        $v1, %hi(D_00553244)
    /* 16E5D0 0026E5D0 F0FFBD27 */  addiu      $sp, $sp, -0x10
    /* 16E5D4 0026E5D4 2D30A000 */  daddu      $a2, $a1, $zero
    /* 16E5D8 0026E5D8 4432648C */  lw         $a0, %lo(D_00553244)($v1)
    /* 16E5DC 0026E5DC 0000BFFF */  sd         $ra, 0x0($sp)
    /* 16E5E0 0026E5E0 B2B5090C */  jal        func_0026D6C8
    /* 16E5E4 0026E5E4 2D284000 */   daddu     $a1, $v0, $zero
    /* 16E5E8 0026E5E8 0000BFDF */  ld         $ra, 0x0($sp)
    /* 16E5EC 0026E5EC 0800E003 */  jr         $ra
    /* 16E5F0 0026E5F0 1000BD27 */   addiu     $sp, $sp, 0x10
endlabel func_0026E5C8
```
