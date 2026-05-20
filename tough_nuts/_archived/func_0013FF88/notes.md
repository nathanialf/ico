
---

## Attempt at 2026-05-13

**Reason parked:** addiu+lw via a3 base vs direct a0[idx] access

Seed: `tough_nuts/func_0013FF88/03FF88.c`

Disassembly excerpt:

```
glabel func_0013FF88
    /* 3FF88 0013FF88 2D408000 */  daddu      $t0, $a0, $zero
    /* 3FF8C 0013FF8C 20000224 */  addiu      $v0, $zero, 0x20
    /* 3FF90 0013FF90 54000725 */  addiu      $a3, $t0, 0x54
    /* 3FF94 0013FF94 0400E38C */  lw         $v1, 0x4($a3)
    /* 3FF98 0013FF98 03006214 */  bne        $v1, $v0, .L0013FFA8
    /* 3FF9C 0013FF9C C0180300 */   sll       $v1, $v1, 3
    /* 3FFA0 0013FFA0 0800E003 */  jr         $ra
    /* 3FFA4 0013FFA4 FFFF0224 */   addiu     $v0, $zero, -0x1
.align 2
  .L0013FFA8:
    /* 3FFA8 0013FFA8 2D100000 */  daddu      $v0, $zero, $zero
    /* 3FFAC 0013FFAC 21180301 */  addu       $v1, $t0, $v1
    /* 3FFB0 0013FFB0 5C0065AC */  sw         $a1, 0x5C($v1)
    /* 3FFB4 0013FFB4 0400E48C */  lw         $a0, 0x4($a3)
    /* 3FFB8 0013FFB8 C0180400 */  sll        $v1, $a0, 3
    /* 3FFBC 0013FFBC 01008424 */  addiu      $a0, $a0, 0x1
    /* 3FFC0 0013FFC0 21180301 */  addu       $v1, $t0, $v1
    /* 3FFC4 0013FFC4 0400E4AC */  sw         $a0, 0x4($a3)
    /* 3FFC8 0013FFC8 0800E003 */  jr         $ra
    /* 3FFCC 0013FFCC 600066AC */   sw        $a2, 0x60($v1)
endlabel func_0013FF88
```
