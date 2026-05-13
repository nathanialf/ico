
---

## Attempt at 2026-05-08

**Reason parked:** ee-gcc 2.9 hoists lui above addiu sp in prologue; original places addiu sp first

Seed: `tough_nuts/func_0024DA80/14DA80.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_0024DA80; check asm/matchings/cod/14DA80/)
```

---

## Attempt at 2026-05-11

**Reason parked:** near-miss schedule: sw zero/sd ra/addiu t0 ordering differs from expected

Seed: `tough_nuts/func_0024DA80/14DA80.c.new`

Disassembly excerpt:

```
glabel func_0024DA80
    /* 14DA80 0024DA80 F0FFBD27 */  addiu      $sp, $sp, -0x10
    /* 14DA84 0024DA84 5500023C */  lui        $v0, %hi(D_00552370)
    /* 14DA88 0024DA88 7100083C */  lui        $t0, %hi(D_00717BD8)
    /* 14DA8C 0024DA8C 0000BFFF */  sd         $ra, 0x0($sp)
    /* 14DA90 0024DA90 702340AC */  sw         $zero, %lo(D_00552370)($v0)
    /* 14DA94 0024DA94 D87B0825 */  addiu      $t0, $t0, %lo(D_00717BD8)
    /* 14DA98 0024DA98 2D200000 */  daddu      $a0, $zero, $zero
    /* 14DA9C 0024DA9C 2D280000 */  daddu      $a1, $zero, $zero
    /* 14DAA0 0024DAA0 2D300000 */  daddu      $a2, $zero, $zero
    /* 14DAA4 0024DAA4 4C37090C */  jal        func_0024DD30
    /* 14DAA8 0024DAA8 03000724 */   addiu     $a3, $zero, 0x3
    /* 14DAAC 0024DAAC 0000BFDF */  ld         $ra, 0x0($sp)
    /* 14DAB0 0024DAB0 0800E003 */  jr         $ra
    /* 14DAB4 0024DAB4 1000BD27 */   addiu     $sp, $sp, 0x10
endlabel func_0024DA80
```

---

## Attempt at 2026-05-13

**Reason parked:** near-miss retry: addiu t0 lo-half hoisted past daddu args

Seed: `tough_nuts/func_0024DA80/14DA80.c.new`

Disassembly excerpt:

```
glabel func_0024DA80
    /* 14DA80 0024DA80 F0FFBD27 */  addiu      $sp, $sp, -0x10
    /* 14DA84 0024DA84 5500023C */  lui        $v0, %hi(D_00552370)
    /* 14DA88 0024DA88 7100083C */  lui        $t0, %hi(D_00717BD8)
    /* 14DA8C 0024DA8C 0000BFFF */  sd         $ra, 0x0($sp)
    /* 14DA90 0024DA90 702340AC */  sw         $zero, %lo(D_00552370)($v0)
    /* 14DA94 0024DA94 D87B0825 */  addiu      $t0, $t0, %lo(D_00717BD8)
    /* 14DA98 0024DA98 2D200000 */  daddu      $a0, $zero, $zero
    /* 14DA9C 0024DA9C 2D280000 */  daddu      $a1, $zero, $zero
    /* 14DAA0 0024DAA0 2D300000 */  daddu      $a2, $zero, $zero
    /* 14DAA4 0024DAA4 4C37090C */  jal        func_0024DD30
    /* 14DAA8 0024DAA8 03000724 */   addiu     $a3, $zero, 0x3
    /* 14DAAC 0024DAAC 0000BFDF */  ld         $ra, 0x0($sp)
    /* 14DAB0 0024DAB0 0800E003 */  jr         $ra
    /* 14DAB4 0024DAB4 1000BD27 */   addiu     $sp, $sp, 0x10
endlabel func_0024DA80
```
