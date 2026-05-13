
---

## Attempt at 2026-05-13

**Reason parked:** near-miss: mult/mult1 pipeline swap + v0/v1 reg alloc; gcc pipeline choice not driveable from C

Seed: `tough_nuts/func_0024E528/14E528.c`

Disassembly excerpt:

```
glabel func_0024E528
    /* 14E528 0024E528 2D308000 */  daddu      $a2, $a0, $zero
    /* 14E52C 0024E52C 70000324 */  addiu      $v1, $zero, 0x70
    /* 14E530 0024E530 1C000424 */  addiu      $a0, $zero, 0x1C
    /* 14E534 0024E534 1818C370 */  mult1      $v1, $a2, $v1
    /* 14E538 0024E538 1820A400 */  mult       $a0, $a1, $a0
    /* 14E53C 0024E53C F0FFBD27 */  addiu      $sp, $sp, -0x10
    /* 14E540 0024E540 7100023C */  lui        $v0, %hi(D_00717C50)
    /* 14E544 0024E544 0000BFFF */  sd         $ra, 0x0($sp)
    /* 14E548 0024E548 507C4224 */  addiu      $v0, $v0, %lo(D_00717C50)
    /* 14E54C 0024E54C 21208300 */  addu       $a0, $a0, $v1
    /* 14E550 0024E550 21104400 */  addu       $v0, $v0, $a0
    /* 14E554 0024E554 1000438C */  lw         $v1, 0x10($v0)
    /* 14E558 0024E558 04006010 */  beqz       $v1, .L0024E56C
    /* 14E55C 0024E55C 2D100000 */   daddu     $v0, $zero, $zero
    /* 14E560 0024E560 3239090C */  jal        func_0024E4C8
    /* 14E564 0024E564 2D20C000 */   daddu     $a0, $a2, $zero
    /* 14E568 0024E568 5800428C */  lw         $v0, 0x58($v0)
.align 2
  .L0024E56C:
    /* 14E56C 0024E56C 0000BFDF */  ld         $ra, 0x0($sp)
    /* 14E570 0024E570 0800E003 */  jr         $ra
    /* 14E574 0024E574 1000BD27 */   addiu     $sp, $sp, 0x10
endlabel func_0024E528
```
