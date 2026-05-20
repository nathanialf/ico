
---

## Attempt at 2026-05-12

**Reason parked:** gcc emits pointer arithmetic loop instead of array indexing

Seed: `tough_nuts/func_00240B88/140B88.c`

Disassembly excerpt:

```
glabel func_00240B88
    /* 140B88 00240B88 A8B2868F */  lw         $a2, %gp_rel(D_00633B98)($gp)
    /* 140B8C 00240B8C 2D408000 */  daddu      $t0, $a0, $zero
    /* 140B90 00240B90 0D00C018 */  blez       $a2, .L00240BC8
    /* 140B94 00240B94 2D280000 */   daddu     $a1, $zero, $zero
    /* 140B98 00240B98 7100073C */  lui        $a3, %hi(D_00712CC0)
    /* 140B9C 00240B9C C02CE224 */  addiu      $v0, $a3, %lo(D_00712CC0)
.align 2
  .L00240BA0:
    /* 140BA0 00240BA0 80180500 */  sll        $v1, $a1, 2
    /* 140BA4 00240BA4 21186200 */  addu       $v1, $v1, $v0
    /* 140BA8 00240BA8 0000648C */  lw         $a0, 0x0($v1)
    /* 140BAC 00240BAC 03000455 */  bnel       $t0, $a0, .L00240BBC
    /* 140BB0 00240BB0 0100A524 */   addiu     $a1, $a1, 0x1
    /* 140BB4 00240BB4 0800E003 */  jr         $ra
    /* 140BB8 00240BB8 2D10A000 */   daddu     $v0, $a1, $zero
.align 2
  .L00240BBC:
    /* 140BBC 00240BBC 2A10A600 */  slt        $v0, $a1, $a2
    /* 140BC0 00240BC0 F7FF4014 */  bnez       $v0, .L00240BA0
    /* 140BC4 00240BC4 C02CE224 */   addiu     $v0, $a3, %lo(D_00712CC0)
.align 2
  .L00240BC8:
    /* 140BC8 00240BC8 0800E003 */  jr         $ra
    /* 140BCC 00240BCC FFFF0224 */   addiu     $v0, $zero, -0x1
endlabel func_00240B88
```
