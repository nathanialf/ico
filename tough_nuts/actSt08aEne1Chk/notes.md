# actSt08aEne1Chk — parked

VRAM: 0x00220728 (file_off 0x120728)
Asm source: asm/aug6/nonmatchings/script/src/st08a/actSt08aEne1Chk.s

## Attempt at 2026-06-11

**Reason parked:** rc5 door-setup tie (stall=30) — IDENTICAL template to actSt08aEnd (parked rc5, permuter-exhausted x2). Same lui-order/delay coupling. 0xFE/0x134/D_004CCE00/actSt06aDoor.

**TU:** `script/src/st08a.c`

**Seed:** `tough_nuts/actSt08aEne1Chk/actSt08aEne1Chk.c`

Disassembly:

```
.align 3
nonmatching actSt08aEne1Chk, 0x98

glabel actSt08aEne1Chk
    /* 120728 00220728 D0FFBD27 */  addiu      $29, $29, -0x30
    /* 12072C 0022072C 0000A4AF */  sw         $4, 0x0($29)
    /* 120730 00220730 1000B0FF */  sd         $16, 0x10($29)
    /* 120734 00220734 0000A28F */  lw         $2, 0x0($29)
    /* 120738 00220738 0000A48F */  lw         $4, 0x0($29)
    /* 12073C 0022073C 2000BFFF */  sd         $31, 0x20($29)
    /* 120740 00220740 3CFE070C */  jal        actInitialize
    /* 120744 00220744 00000000 */   nop
    /* 120748 00220748 2D804000 */  daddu      $16, $2, $0
    /* 12074C 0022074C 6004080C */  jal        _ACTWait
    /* 120750 00220750 01000424 */   addiu     $4, $0, 0x1
    /* 120754 00220754 6CE3050C */  jal        func_00178DB0
    /* 120758 00220758 FE000424 */   addiu     $4, $0, 0xFE
    /* 12075C 0022075C 11004014 */  bnez       $2, .L002207A4
    /* 120760 00220760 34010424 */   addiu     $4, $0, 0x134
    /* 120764 00220764 2D280000 */  daddu      $5, $0, $0
    /* 120768 00220768 76A5040C */  jal        stage_KillPlayBgAnimation
    /* 12076C 0022076C 2D300000 */   daddu     $6, $0, $0
    /* 120770 00220770 4D00023C */  lui        $2, %hi(D_004CCE00)
    /* 120774 00220774 2200033C */  lui        $3, %hi(actSt06aDoor)
    /* 120778 00220778 00CE4224 */  addiu      $2, $2, %lo(D_004CCE00)
    /* 12077C 0022077C 0000A48F */  lw         $4, 0x0($29)
    /* 120780 00220780 B8EC6324 */  addiu      $3, $3, %lo(actSt06aDoor)
    /* 120784 00220784 89010524 */  addiu      $5, $0, 0x189
    /* 120788 00220788 B40002AE */  sw         $2, 0xB4($16)
    /* 12078C 0022078C F867050C */  jal        BoxBarSoundOn
    /* 120790 00220790 040043AC */   sw        $3, 0x4($2)
    /* 120794 00220794 6004080C */  jal        _ACTWait
    /* 120798 00220798 2D200000 */   daddu     $4, $0, $0
    /* 12079C 0022079C 05000010 */  b          .L002207B4
    /* 1207A0 002207A0 2000BFDF */   ld        $31, 0x20($29)
.align 2
  .L002207A4:
    /* 1207A4 002207A4 2D280000 */  daddu      $5, $0, $0
    /* 1207A8 002207A8 76A5040C */  jal        stage_KillPlayBgAnimation
    /* 1207AC 002207AC FFFF0624 */   addiu     $6, $0, -0x1
    /* 1207B0 002207B0 2000BFDF */  ld         $31, 0x20($29)
.align 2
  .L002207B4:
    /* 1207B4 002207B4 1000B0DF */  ld         $16, 0x10($29)
    /* 1207B8 002207B8 0800E003 */  jr         $31
    /* 1207BC 002207BC 3000BD27 */   addiu     $29, $29, 0x30
endlabel actSt08aEne1Chk
```
