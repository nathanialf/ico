# func_0024DA50 — parked

VRAM: 0x0024DA50 (file offset 0x14DA50)
Asm source: asm/cod/14BBC0.s

## Attempt at 2026-05-07 — re-park (no .c seed preserved)

**Reason parked:** schedule: daddu register-zero ordering vs ee-gcc 2.9 emit (sibling of 24D9B8)

**Note:** previous near-miss .c attempt was reverted+deleted before this
session's policy update; the original seed is not recoverable. Permuter
must start from scratch on this one. Reason recorded above is from
operator memory of the failure mode.

Disassembly excerpt:

```
glabel func_0024DA50
    /* 14DA50 0024DA50 F0FFBD27 */  addiu      $sp, $sp, -0x10
    /* 14DA54 0024DA54 7100083C */  lui        $t0, %hi(D_00717BD8)
    /* 14DA58 0024DA58 0000BFFF */  sd         $ra, 0x0($sp)
    /* 14DA5C 0024DA5C D87B0825 */  addiu      $t0, $t0, %lo(D_00717BD8)
    /* 14DA60 0024DA60 2D280000 */  daddu      $a1, $zero, $zero
    /* 14DA64 0024DA64 2D300000 */  daddu      $a2, $zero, $zero
    /* 14DA68 0024DA68 4C37090C */  jal        func_0024DD30
    /* 14DA6C 0024DA6C 04000724 */   addiu     $a3, $zero, 0x4
    /* 14DA70 0024DA70 0000BFDF */  ld         $ra, 0x0($sp)
    /* 14DA74 0024DA74 0800E003 */  jr         $ra
    /* 14DA78 0024DA78 1000BD27 */   addiu     $sp, $sp, 0x10
endlabel func_0024DA50
```
