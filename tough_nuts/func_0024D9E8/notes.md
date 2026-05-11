
---

## Attempt at 2026-05-08

**Reason parked:** DEFEAT_TCO needed but prologue scheduling differs (target: sp-setup early, then args; gcc: args first, sp-setup mid)

Seed: `tough_nuts/func_0024D9E8/14D9E8.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_0024D9E8; check asm/matchings/cod/14D9E8/)
```

---

## Attempt at 2026-05-11

**Reason parked:** near-miss: schedule of lui+addiu+sw for D_00552370 store differs — expected interleaves them before sd ra, built emits them after t0/sd ra group

Seed: `tough_nuts/func_0024D9E8/14D9E8.c.new`

Disassembly excerpt:

```
glabel func_0024D9E8
    /* 14D9E8 0024D9E8 F0FFBD27 */  addiu      $sp, $sp, -0x10
    /* 14D9EC 0024D9EC 5500033C */  lui        $v1, %hi(D_00552370)
    /* 14D9F0 0024D9F0 01000224 */  addiu      $v0, $zero, 0x1
    /* 14D9F4 0024D9F4 2D40A000 */  daddu      $t0, $a1, $zero
    /* 14D9F8 0024D9F8 0000BFFF */  sd         $ra, 0x0($sp)
    /* 14D9FC 0024D9FC 2D280000 */  daddu      $a1, $zero, $zero
    /* 14DA00 0024DA00 702362AC */  sw         $v0, %lo(D_00552370)($v1)
    /* 14DA04 0024DA04 2D300000 */  daddu      $a2, $zero, $zero
    /* 14DA08 0024DA08 4C37090C */  jal        func_0024DD30
    /* 14DA0C 0024DA0C 01000724 */   addiu     $a3, $zero, 0x1
    /* 14DA10 0024DA10 0000BFDF */  ld         $ra, 0x0($sp)
    /* 14DA14 0024DA14 0800E003 */  jr         $ra
    /* 14DA18 0024DA18 1000BD27 */   addiu     $sp, $sp, 0x10
endlabel func_0024D9E8
```
