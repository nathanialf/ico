# stage_SetFrameStep — parked

VRAM: 0x00129DB0 (file_off 0x029DB0)
Asm source: asm/aug6/nonmatchings/seki/src/StageAnimation/stage_SetFrameStep.s

## Attempt at 2026-07-06

**Reason parked:** plateau: 30 distinct hand hypotheses, no real_count progress (best=42). PARK the seed, then fire ONE bounded permuter shot on it (REFERENCE Step 4); harvest by true real_count and adopt any improvement (resolution b only if nothing beats best).

**TU:** `seki/src/StageAnimation.c`

**Seed:** `tough_nuts/stage_SetFrameStep/stage_SetFrameStep.c`

Disassembly:

```
.align 3
nonmatching stage_SetFrameStep, 0x108

glabel stage_SetFrameStep
    /* 29DB0 00129DB0 6700023C */  lui        $2, %hi(D_0066DBD8)
    /* 29DB4 00129DB4 2DC88000 */  daddu      $25, $4, $0
    /* 29DB8 00129DB8 64B3838F */  lw         $3, %gp_rel(D_0062BF54)($28)
    /* 29DBC 00129DBC D8DB4C24 */  addiu      $12, $2, %lo(D_0066DBD8)
    /* 29DC0 00129DC0 3B006018 */  blez       $3, .L00129EB0
    /* 29DC4 00129DC4 2D200000 */   daddu     $4, $0, $0
    /* 29DC8 00129DC8 2DC06000 */  daddu      $24, $3, $0
    /* 29DCC 00129DCC 50000F24 */  addiu      $15, $0, 0x50
.align 2
  .L00129DD0:
    /* 29DD0 00129DD0 8002828D */  lw         $2, 0x280($12)
    /* 29DD4 00129DD4 5800438C */  lw         $3, 0x58($2)
    /* 29DD8 00129DD8 30002317 */  bne        $25, $3, .L00129E9C
    /* 29DDC 00129DDC 01008D24 */   addiu     $13, $4, 0x1
    /* 29DE0 00129DE0 8C02888D */  lw         $8, 0x28C($12)
    /* 29DE4 00129DE4 83170800 */  sra        $2, $8, 30
    /* 29DE8 00129DE8 2D004014 */  bnez       $2, .L00129EA0
    /* 29DEC 00129DEC 90028B25 */   addiu     $11, $12, 0x290
    /* 29DF0 00129DF0 80150800 */  sll        $2, $8, 22
    /* 29DF4 00129DF4 2A004018 */  blez       $2, .L00129EA0
    /* 29DF8 00129DF8 2D280000 */   daddu     $5, $0, $0
    /* 29DFC 00129DFC 01008D24 */  addiu      $13, $4, 0x1
    /* 29E00 00129E00 80008E25 */  addiu      $14, $12, 0x80
    /* 29E04 00129E04 90028B25 */  addiu      $11, $12, 0x290
    /* 29E08 00129E08 80380500 */  sll        $7, $5, 2
    /* 29E0C 00129E0C 00000000 */  nop
.align 2
  .L00129E10:
    /* 29E10 00129E10 2D50C001 */  daddu      $10, $14, $0
    /* 29E14 00129E14 21204701 */  addu       $4, $10, $7
    /* 29E18 00129E18 0000828C */  lw         $2, 0x0($4)
    /* 29E1C 00129E1C 5C01438C */  lw         $3, 0x15C($2)
    /* 29E20 00129E20 0800648C */  lw         $4, 0x8($3)
    /* 29E24 00129E24 14008018 */  blez       $4, .L00129E78
    /* 29E28 00129E28 2D300000 */   daddu     $6, $0, $0
    /* 29E2C 00129E2C 0100A924 */  addiu      $9, $5, 0x1
    /* 29E30 00129E30 21104701 */  addu       $2, $10, $7
    /* 29E34 00129E34 00000000 */  nop
.align 2
  .L00129E38:
    /* 29E38 00129E38 1820CF00 */  mult       $4, $6, $15
    /* 29E3C 00129E3C 0000458C */  lw         $5, 0x0($2)
    /* 29E40 00129E40 0100C624 */  addiu      $6, $6, 0x1
    /* 29E44 00129E44 5C01A28C */  lw         $2, 0x15C($5)
    /* 29E48 00129E48 3008438C */  lw         $3, 0x830($2)
    /* 29E4C 00129E4C 21208300 */  addu       $4, $4, $3
    /* 29E50 00129E50 20008CE4 */  swc1       $f12, 0x20($4)
    /* 29E54 00129E54 28008CE4 */  swc1       $f12, 0x28($4)
    /* 29E58 00129E58 24008CE4 */  swc1       $f12, 0x24($4)
    /* 29E5C 00129E5C 5C01A38C */  lw         $3, 0x15C($5)
    /* 29E60 00129E60 0800628C */  lw         $2, 0x8($3)
    /* 29E64 00129E64 2A10C200 */  slt        $2, $6, $2
    /* 29E68 00129E68 F3FF4014 */  bnez       $2, .L00129E38
    /* 29E6C 00129E6C 21104701 */   addu      $2, $10, $7
    /* 29E70 00129E70 02000010 */  b          .L00129E7C
    /* 29E74 00129E74 8C02888D */   lw        $8, 0x28C($12)
.align 2
  .L00129E78:
    /* 29E78 00129E78 0100A924 */  addiu      $9, $5, 0x1
.align 2
  .L00129E7C:
    /* 29E7C 00129E7C 80150800 */  sll        $2, $8, 22
    /* 29E80 00129E80 2D282001 */  daddu      $5, $9, $0
    /* 29E84 00129E84 83150200 */  sra        $2, $2, 22
    /* 29E88 00129E88 2A10A200 */  slt        $2, $5, $2
    /* 29E8C 00129E8C E0FF4014 */  bnez       $2, .L00129E10
    /* 29E90 00129E90 80380500 */   sll       $7, $5, 2
    /* 29E94 00129E94 03000010 */  b          .L00129EA4
    /* 29E98 00129E98 2D20A001 */   daddu     $4, $13, $0
.align 2
  .L00129E9C:
    /* 29E9C 00129E9C 90028B25 */  addiu      $11, $12, 0x290
.align 2
  .L00129EA0:
    /* 29EA0 00129EA0 2D20A001 */  daddu      $4, $13, $0
.align 2
  .L00129EA4:
    /* 29EA4 00129EA4 2A109800 */  slt        $2, $4, $24
    /* 29EA8 00129EA8 C9FF4014 */  bnez       $2, .L00129DD0
    /* 29EAC 00129EAC 2D606001 */   daddu     $12, $11, $0
.align 2
  .L00129EB0:
    /* 29EB0 00129EB0 0800E003 */  jr         $31
    /* 29EB4 00129EB4 00000000 */   nop
endlabel stage_SetFrameStep
```
