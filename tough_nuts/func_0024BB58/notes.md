# func_0024BB58 — parked

VRAM: 0x0024BB58 (file offset 0x14BB58)
Asm source: asm/cod/14B8D4.s

## Attempt at 2026-05-07 — re-park (no .c seed preserved)

**Reason parked:** lui v0/v1 swap

**Note:** previous near-miss .c attempt was reverted+deleted before this
session's policy update; the original seed is not recoverable. Permuter
must start from scratch on this one. Reason recorded above is from
operator memory of the failure mode.

Disassembly excerpt:

```
glabel func_0024BB58
    /* 14BB58 0024BB58 F0FFBD27 */  addiu      $sp, $sp, -0x10
    /* 14BB5C 0024BB5C 0000BFFF */  sd         $ra, 0x0($sp)
    /* 14BB60 0024BB60 B602040C */  jal        func_00100AD8
    /* 14BB64 0024BB64 05000424 */   addiu     $a0, $zero, 0x5
    /* 14BB68 0024BB68 7100033C */  lui        $v1, %hi(D_00717754)
    /* 14BB6C 0024BB6C 05000424 */  addiu      $a0, $zero, 0x5
    /* 14BB70 0024BB70 9400040C */  jal        func_00100250
    /* 14BB74 0024BB74 5477658C */   lw        $a1, %lo(D_00717754)($v1)
    /* 14BB78 0024BB78 5500033C */  lui        $v1, %hi(D_005508F8)
    /* 14BB7C 0024BB7C 0000BFDF */  ld         $ra, 0x0($sp)
    /* 14BB80 0024BB80 F80860AC */  sw         $zero, %lo(D_005508F8)($v1)
    /* 14BB84 0024BB84 0800E003 */  jr         $ra
    /* 14BB88 0024BB88 1000BD27 */   addiu     $sp, $sp, 0x10
endlabel func_0024BB58
```
