
---

## Attempt at 2026-05-12

**Reason parked:** store-order reordering: built emits sw 12 before sw 8, sw zero 4 in delay slot

Seed: `tough_nuts/func_002456F8/1456F8.c`

Disassembly excerpt:

```
glabel func_002456F8
    /* 1456F8 002456F8 7100023C */  lui        $v0, %hi(D_00713000)
    /* 1456FC 002456FC 00304324 */  addiu      $v1, $v0, %lo(D_00713000)
    /* 145700 00245700 003044AC */  sw         $a0, %lo(D_00713000)($v0)
    /* 145704 00245704 10006424 */  addiu      $a0, $v1, 0x10
    /* 145708 00245708 2D106000 */  daddu      $v0, $v1, $zero
    /* 14570C 0024570C 080064AC */  sw         $a0, 0x8($v1)
    /* 145710 00245710 040060AC */  sw         $zero, 0x4($v1)
    /* 145714 00245714 0800E003 */  jr         $ra
    /* 145718 00245718 0C0064AC */   sw        $a0, 0xC($v1)
endlabel func_002456F8
```
