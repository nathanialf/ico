# func_0024DA20 — parked

VRAM: 0x0024DA20 (file offset 0x14DA20)
Asm source: asm/cod/14BBC0.s

## Attempt at 2026-05-07 — re-park (no .c seed preserved)

**Reason parked:** schedule: daddu register-zero ordering vs ee-gcc 2.9 emit (sibling of 24D9B8)

**Note:** previous near-miss .c attempt was reverted+deleted before this
session's policy update; the original seed is not recoverable. Permuter
must start from scratch on this one. Reason recorded above is from
operator memory of the failure mode.

Disassembly excerpt:

```
glabel func_0024DA20
    /* 14DA20 0024DA20 F0FFBD27 */  addiu      $sp, $sp, -0x10
    /* 14DA24 0024DA24 7100083C */  lui        $t0, %hi(D_00717BD8)
    /* 14DA28 0024DA28 0000BFFF */  sd         $ra, 0x0($sp)
    /* 14DA2C 0024DA2C D87B0825 */  addiu      $t0, $t0, %lo(D_00717BD8)
    /* 14DA30 0024DA30 2D280000 */  daddu      $a1, $zero, $zero
    /* 14DA34 0024DA34 2D300000 */  daddu      $a2, $zero, $zero
    /* 14DA38 0024DA38 4C37090C */  jal        func_0024DD30
    /* 14DA3C 0024DA3C 09000724 */   addiu     $a3, $zero, 0x9
    /* 14DA40 0024DA40 0000BFDF */  ld         $ra, 0x0($sp)
    /* 14DA44 0024DA44 0800E003 */  jr         $ra
    /* 14DA48 0024DA48 1000BD27 */   addiu     $sp, $sp, 0x10
endlabel func_0024DA20
```
