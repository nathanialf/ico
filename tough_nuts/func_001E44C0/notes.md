# func_001E44C0 — parked

VRAM: 0x001E44C0 (file_off 0x0E44C0)
Asm source: asm/nonmatchings/src/motionOrientManager/func_001E44C0.s

## Attempt at 2026-05-20

**Reason parked:** reg-shuffle: gcc copies a0->t0 for loop counter; bne emitted instead of bnel; needs permuter perm_general or perm_temp_for_expr

**TU:** `src/motionOrientManager.c`

**Seed:** `tough_nuts/func_001E44C0/func_001E44C0.c`

Disassembly:

```
.align 3
nonmatching func_001E44C0, 0x84

glabel func_001E44C0
    /* E44C0 001E44C0 2A108500 */  slt        $2, $4, $5
    /* E44C4 001E44C4 13004010 */  beqz       $2, .L001E4514
    /* E44C8 001E44C8 FFFF0A24 */   addiu     $10, $0, -0x1
    /* E44CC 001E44CC 29000B3C */  lui        $11, %hi(D_00292540)
    /* E44D0 001E44D0 18000324 */  addiu      $3, $0, 0x18
    /* E44D4 001E44D4 00000000 */  nop
.align 2
  .L001E44D8:
    /* E44D8 001E44D8 40256925 */  addiu      $9, $11, %lo(D_00292540)
    /* E44DC 001E44DC 18408300 */  mult       $8, $4, $3
    /* E44E0 001E44E0 21102801 */  addu       $2, $9, $8
    /* E44E4 001E44E4 0400438C */  lw         $3, 0x4($2)
    /* E44E8 001E44E8 07006754 */  bnel       $3, $7, .L001E4508
    /* E44EC 001E44EC 01008424 */   addiu     $4, $4, 0x1
    /* E44F0 001E44F0 21180901 */  addu       $3, $8, $9
    /* E44F4 001E44F4 0000628C */  lw         $2, 0x0($3)
    /* E44F8 001E44F8 0E004610 */  beq        $2, $6, .L001E4534
    /* E44FC 001E44FC 3D044238 */   xori      $2, $2, 0x43D
    /* E4500 001E4500 0A508200 */  movz       $10, $4, $2
    /* E4504 001E4504 01008424 */  addiu      $4, $4, 0x1
.align 2
  .L001E4508:
    /* E4508 001E4508 2A108500 */  slt        $2, $4, $5
    /* E450C 001E450C F2FF4054 */  bnel       $2, $0, .L001E44D8
    /* E4510 001E4510 18000324 */   addiu     $3, $0, 0x18
.align 2
  .L001E4514:
    /* E4514 001E4514 FFFF0224 */  addiu      $2, $0, -0x1
    /* E4518 001E4518 08004211 */  beq        $10, $2, .L001E453C
    /* E451C 001E451C 18000324 */   addiu     $3, $0, 0x18
    /* E4520 001E4520 2900023C */  lui        $2, %hi(D_00292540)
    /* E4524 001E4524 18184301 */  mult       $3, $10, $3
    /* E4528 001E4528 40254224 */  addiu      $2, $2, %lo(D_00292540)
    /* E452C 001E452C 0800E003 */  jr         $31
    /* E4530 001E4530 21106200 */   addu      $2, $3, $2
.align 2
  .L001E4534:
    /* E4534 001E4534 0800E003 */  jr         $31
    /* E4538 001E4538 2D106000 */   daddu     $2, $3, $0
.align 2
  .L001E453C:
    /* E453C 001E453C 0800E003 */  jr         $31
    /* E4540 001E4540 2D100000 */   daddu     $2, $0, $0
endlabel func_001E44C0
    /* E4544 001E4544 00000000 */  nop
```
