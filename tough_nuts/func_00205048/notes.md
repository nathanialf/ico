
---

## Attempt at 2026-05-12

**Reason parked:** same as func_0017B0D8: missing nop between c.lt.s and bc1*

Seed: `tough_nuts/func_00205048/105048.c`

Disassembly excerpt:

```
glabel func_00205048
    /* 105048 00205048 040081C4 */  lwc1       $f1, 0x4($a0)
    /* 10504C 0020504C 0400A0C4 */  lwc1       $f0, 0x4($a1)
    /* 105050 00205050 34080046 */  c.lt.s     $f1, $f0
    /* 105054 00205054 00000000 */  nop
    /* 105058 00205058 06000145 */  bc1t       .L00205074
    /* 10505C 0020505C FFFF0224 */   addiu     $v0, $zero, -0x1
    /* 105060 00205060 34000146 */  c.lt.s     $f0, $f1
    /* 105064 00205064 00000000 */  nop
    /* 105068 00205068 02000045 */  bc1f       .L00205074
    /* 10506C 0020506C 2D100000 */   daddu     $v0, $zero, $zero
    /* 105070 00205070 01000224 */  addiu      $v0, $zero, 0x1
.align 2
  .L00205074:
    /* 105074 00205074 0800E003 */  jr         $ra
    /* 105078 00205078 00000000 */   nop
endlabel func_00205048
```
