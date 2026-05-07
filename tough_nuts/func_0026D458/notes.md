# func_0026D458 — parked

VRAM: 0x0026D458 (file offset 0x16D458)
Asm source: asm/cod/16CF2C.s

## Attempt at 2026-05-07 — re-park (no .c seed preserved)

**Reason parked:** daddu schedule (sibling of 26B148)

**Note:** previous near-miss .c attempt was reverted+deleted before this
session's policy update; the original seed is not recoverable. Permuter
must start from scratch on this one. Reason recorded above is from
operator memory of the failure mode.

Disassembly excerpt:

```
glabel func_0026D458
    /* 16D458 0026D458 2D108000 */  daddu      $v0, $a0, $zero
    /* 16D45C 0026D45C 5500033C */  lui        $v1, %hi(D_00553244)
    /* 16D460 0026D460 F0FFBD27 */  addiu      $sp, $sp, -0x10
    /* 16D464 0026D464 2D30A000 */  daddu      $a2, $a1, $zero
    /* 16D468 0026D468 4432648C */  lw         $a0, %lo(D_00553244)($v1)
    /* 16D46C 0026D46C 0000BFFF */  sd         $ra, 0x0($sp)
    /* 16D470 0026D470 7EB4090C */  jal        func_0026D1F8
    /* 16D474 0026D474 2D284000 */   daddu     $a1, $v0, $zero
    /* 16D478 0026D478 0000BFDF */  ld         $ra, 0x0($sp)
    /* 16D47C 0026D47C 0800E003 */  jr         $ra
    /* 16D480 0026D480 1000BD27 */   addiu     $sp, $sp, 0x10
endlabel func_0026D458
```
