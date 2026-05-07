# func_0026B148 — parked

VRAM: 0x0026B148 (file offset 0x16B148)
Asm source: asm/cod/16B144.s

## Attempt at 2026-05-07 — re-park (no .c seed preserved)

**Reason parked:** daddu schedule (sibling of 26D458/E5C8)

**Note:** previous near-miss .c attempt was reverted+deleted before this
session's policy update; the original seed is not recoverable. Permuter
must start from scratch on this one. Reason recorded above is from
operator memory of the failure mode.

Disassembly excerpt:

```
glabel func_0026B148
    /* 16B148 0026B148 2D108000 */  daddu      $v0, $a0, $zero
    /* 16B14C 0026B14C 5500033C */  lui        $v1, %hi(D_00553244)
    /* 16B150 0026B150 F0FFBD27 */  addiu      $sp, $sp, -0x10
    /* 16B154 0026B154 2D30A000 */  daddu      $a2, $a1, $zero
    /* 16B158 0026B158 4432648C */  lw         $a0, %lo(D_00553244)($v1)
    /* 16B15C 0026B15C 0000BFFF */  sd         $ra, 0x0($sp)
    /* 16B160 0026B160 2CAC090C */  jal        func_0026B0B0
    /* 16B164 0026B164 2D284000 */   daddu     $a1, $v0, $zero
    /* 16B168 0026B168 0000BFDF */  ld         $ra, 0x0($sp)
    /* 16B16C 0026B16C 0800E003 */  jr         $ra
    /* 16B170 0026B170 1000BD27 */   addiu     $sp, $sp, 0x10
endlabel func_0026B148
```
