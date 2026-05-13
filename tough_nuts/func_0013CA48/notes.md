
---

## Attempt at 2026-05-13

**Reason parked:** sw via a0 vs via t0 (alias) reg routing differs; counter ok via pin

Seed: `tough_nuts/func_0013CA48/03CA48.c`

Disassembly excerpt:

```
glabel func_0013CA48
    /* 3CA48 0013CA48 12008010 */  beqz       $a0, .L0013CA94
    /* 3CA4C 0013CA4C 00000000 */   nop
    /* 3CA50 0013CA50 1000A010 */  beqz       $a1, .L0013CA94
    /* 3CA54 0013CA54 2D408000 */   daddu     $t0, $a0, $zero
    /* 3CA58 0013CA58 2D380000 */  daddu      $a3, $zero, $zero
    /* 3CA5C 0013CA5C 040005AD */  sw         $a1, 0x4($t0)
    /* 3CA60 0013CA60 A09888AF */  sw         $t0, %gp_rel(D_00632190)($gp)
    /* 3CA64 0013CA64 0A00C018 */  blez       $a2, .L0013CA90
    /* 3CA68 0013CA68 000006AD */   sw        $a2, 0x0($t0)
    /* 3CA6C 0013CA6C 00000000 */  nop
.align 2
  .L0013CA70:
    /* 3CA70 0013CA70 0400028D */  lw         $v0, 0x4($t0)
    /* 3CA74 0013CA74 80180700 */  sll        $v1, $a3, 2
    /* 3CA78 0013CA78 0100E724 */  addiu      $a3, $a3, 0x1
    /* 3CA7C 0013CA7C 21186200 */  addu       $v1, $v1, $v0
    /* 3CA80 0013CA80 2A20E600 */  slt        $a0, $a3, $a2
    /* 3CA84 0013CA84 000060AC */  sw         $zero, 0x0($v1)
    /* 3CA88 0013CA88 F9FF8014 */  bnez       $a0, .L0013CA70
    /* 3CA8C 0013CA8C 00000000 */   nop
.align 2
  .L0013CA90:
    /* 3CA90 0013CA90 080000AD */  sw         $zero, 0x8($t0)
.align 2
  .L0013CA94:
    /* 3CA94 0013CA94 0800E003 */  jr         $ra
    /* 3CA98 0013CA98 00000000 */   nop
endlabel func_0013CA48
```
