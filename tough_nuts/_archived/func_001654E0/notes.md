
---

## Attempt at 2026-05-12

**Reason parked:** guard+bit-test: complex branch backflow; bne to L_RET_0 backward instead of separate zero: label

Seed: `tough_nuts/func_001654E0/0654E0.c`

Disassembly excerpt:

```
glabel func_001654E0
    /* 654E0 001654E0 2D288000 */  daddu      $a1, $a0, $zero
    /* 654E4 001654E4 6401A28C */  lw         $v0, 0x164($a1)
    /* 654E8 001654E8 7006438C */  lw         $v1, 0x670($v0)
    /* 654EC 001654EC DC01648C */  lw         $a0, 0x1DC($v1)
    /* 654F0 001654F0 03008054 */  bnel       $a0, $zero, .L00165500
    /* 654F4 001654F4 0800A38C */   lw        $v1, 0x8($a1)
.align 2
  .L001654F8:
    /* 654F8 001654F8 0800E003 */  jr         $ra
    /* 654FC 001654FC 2D100000 */   daddu     $v0, $zero, $zero
.align 2
  .L00165500:
    /* 65500 00165500 4C000424 */  addiu      $a0, $zero, 0x4C
    /* 65504 00165504 2A00023C */  lui        $v0, %hi(D_002A4C48)
    /* 65508 00165508 18186400 */  mult       $v1, $v1, $a0
    /* 6550C 0016550C 484C4224 */  addiu      $v0, $v0, %lo(D_002A4C48)
    /* 65510 00165510 21186200 */  addu       $v1, $v1, $v0
    /* 65514 00165514 4800648C */  lw         $a0, 0x48($v1)
    /* 65518 00165518 82140400 */  srl        $v0, $a0, 18
    /* 6551C 0016551C 01004230 */  andi       $v0, $v0, 0x1
    /* 65520 00165520 F5FF4014 */  bnez       $v0, .L001654F8
    /* 65524 00165524 42150400 */   srl       $v0, $a0, 21
    /* 65528 00165528 01004230 */  andi       $v0, $v0, 0x1
    /* 6552C 0016552C 01004238 */  xori       $v0, $v0, 0x1
    /* 65530 00165530 F1FF4014 */  bnez       $v0, .L001654F8
    /* 65534 00165534 01000224 */   addiu     $v0, $zero, 0x1
    /* 65538 00165538 0800E003 */  jr         $ra
    /* 6553C 0016553C 00000000 */   nop
endlabel func_001654E0
```
