# funcCommonFallDircorrect — parked

VRAM: 0x0015B4F8 (file_off 0x05B4F8)
Asm source: asm/aug6/nonmatchings/fumi/src/commonact/funcCommonFallDircorrect.s

## Attempt at 2026-07-07

**Reason parked:** rc19; body byte-correct (int-return blocks sibcall→jal+frame). Residual=3-arg passthrough regalloc/sched1 tie: gcc materializes D_0055DA10 %hi early + clobbers a1 arg-reg as scratch (move a1,a2 restore) + derefs a0 direct while ROM copies a0->t0/a1->v0 and keeps $4/$5 pristine. 6 distinct source spellings (int/char* param, self/sub/idx temps, (int)base cast form, explicit float temp) ALL FOLD to one rc19 sig — deterministic floor, permuter-class.

**TU:** `fumi/src/commonact.c`

**Seed:** `tough_nuts/funcCommonFallDircorrect/funcCommonFallDircorrect.c`

Disassembly:

```
.align 3
nonmatching funcCommonFallDircorrect, 0x64

glabel funcCommonFallDircorrect
    /* 5B4F8 0015B4F8 F0FFBD27 */  addiu      $29, $29, -0x10
    /* 5B4FC 0015B4FC 2D10A000 */  daddu      $2, $5, $0
    /* 5B500 0015B500 0000BFFF */  sd         $31, 0x0($29)
    /* 5B504 0015B504 2D408000 */  daddu      $8, $4, $0
    /* 5B508 0015B508 90010924 */  addiu      $9, $0, 0x190
    /* 5B50C 0015B50C 000040C4 */  lwc1       $f0, 0x0($2)
    /* 5B510 0015B510 5600063C */  lui        $6, %hi(D_0055DA10)
    /* 5B514 0015B514 6401078D */  lw         $7, 0x164($8)
    /* 5B518 0015B518 10DAC624 */  addiu      $6, $6, %lo(D_0055DA10)
    /* 5B51C 0015B51C 0001E0E4 */  swc1       $f0, 0x100($7)
    /* 5B520 0015B520 040040C4 */  lwc1       $f0, 0x4($2)
    /* 5B524 0015B524 0401E0E4 */  swc1       $f0, 0x104($7)
    /* 5B528 0015B528 080041C4 */  lwc1       $f1, 0x8($2)
    /* 5B52C 0015B52C 0801E1E4 */  swc1       $f1, 0x108($7)
    /* 5B530 0015B530 5C01038D */  lw         $3, 0x15C($8)
    /* 5B534 0015B534 9004628C */  lw         $2, 0x490($3)
    /* 5B538 0015B538 18104900 */  mult       $2, $2, $9
    /* 5B53C 0015B53C 2130C200 */  addu       $6, $6, $2
    /* 5B540 0015B540 3801CCC4 */  lwc1       $f12, 0x138($6)
    /* 5B544 0015B544 20638046 */  cvt.s.w    $f12, $f12
    /* 5B548 0015B548 AC66050C */  jal        actCommonStoneDead
    /* 5B54C 0015B54C 00000000 */   nop
    /* 5B550 0015B550 0000BFDF */  ld         $31, 0x0($29)
    /* 5B554 0015B554 0800E003 */  jr         $31
    /* 5B558 0015B558 1000BD27 */   addiu     $29, $29, 0x10
endlabel funcCommonFallDircorrect
    /* 5B55C 0015B55C 00000000 */  nop
```
