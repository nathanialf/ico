
---

## Attempt at 2026-05-13

**Reason parked:** reg alloc t0/t1/v0 vs a1/a2/v1; scheduling differs significantly

Seed: `tough_nuts/func_0015D358/05D358.c`

Disassembly excerpt:

```
glabel func_0015D358
    /* 5D358 0015D358 F0FFBD27 */  addiu      $sp, $sp, -0x10
    /* 5D35C 0015D35C 2D10A000 */  daddu      $v0, $a1, $zero
    /* 5D360 0015D360 0000BFFF */  sd         $ra, 0x0($sp)
    /* 5D364 0015D364 2D408000 */  daddu      $t0, $a0, $zero
    /* 5D368 0015D368 90010924 */  addiu      $t1, $zero, 0x190
    /* 5D36C 0015D36C 000040C4 */  lwc1       $f0, 0x0($v0)
    /* 5D370 0015D370 5600063C */  lui        $a2, %hi(D_00565060)
    /* 5D374 0015D374 6401078D */  lw         $a3, 0x164($t0)
    /* 5D378 0015D378 6050C624 */  addiu      $a2, $a2, %lo(D_00565060)
    /* 5D37C 0015D37C 1001E0E4 */  swc1       $f0, 0x110($a3)
    /* 5D380 0015D380 040040C4 */  lwc1       $f0, 0x4($v0)
    /* 5D384 0015D384 1401E0E4 */  swc1       $f0, 0x114($a3)
    /* 5D388 0015D388 080041C4 */  lwc1       $f1, 0x8($v0)
    /* 5D38C 0015D38C 1801E1E4 */  swc1       $f1, 0x118($a3)
    /* 5D390 0015D390 5C01038D */  lw         $v1, 0x15C($t0)
    /* 5D394 0015D394 A004628C */  lw         $v0, 0x4A0($v1)
    /* 5D398 0015D398 18104900 */  mult       $v0, $v0, $t1
    /* 5D39C 0015D39C 2130C200 */  addu       $a2, $a2, $v0
    /* 5D3A0 0015D3A0 3801CCC4 */  lwc1       $f12, 0x138($a2)
    /* 5D3A4 0015D3A4 20638046 */  cvt.s.w    $f12, $f12
    /* 5D3A8 0015D3A8 E06D050C */  jal        func_0015B780
    /* 5D3AC 0015D3AC 00000000 */   nop
    /* 5D3B0 0015D3B0 0000BFDF */  ld         $ra, 0x0($sp)
    /* 5D3B4 0015D3B4 0800E003 */  jr         $ra
    /* 5D3B8 0015D3B8 1000BD27 */   addiu     $sp, $sp, 0x10
endlabel func_0015D358
```
