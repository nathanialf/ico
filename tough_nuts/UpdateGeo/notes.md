# UpdateGeo — parked

VRAM: 0x0014CBA0 (file_off 0x04CBA0)
Asm source: asm/aug6/nonmatchings/fumi/src/boyact/UpdateGeo.s

## Attempt at 2026-06-29

**Reason parked:** plateau: 30 distinct hand hypotheses, no real_count progress (best=39). PARK the seed, then fire ONE bounded permuter shot on it (REFERENCE Step 4); harvest by true real_count and adopt any improvement (resolution b only if nothing beats best).

**TU:** `fumi/src/boyact.c`

**Seed:** `tough_nuts/UpdateGeo/UpdateGeo.c`

Disassembly:

```
.align 3
nonmatching UpdateGeo, 0x15C

glabel UpdateGeo
    /* 4CBA0 0014CBA0 70FFBD27 */  addiu      $29, $29, -0x90
    /* 4CBA4 0014CBA4 7000B4FF */  sd         $20, 0x70($29)
    /* 4CBA8 0014CBA8 6000B3FF */  sd         $19, 0x60($29)
    /* 4CBAC 0014CBAC 2DA08000 */  daddu      $20, $4, $0
    /* 4CBB0 0014CBB0 8000BFFF */  sd         $31, 0x80($29)
    /* 4CBB4 0014CBB4 2D984000 */  daddu      $19, $2, $0
    /* 4CBB8 0014CBB8 5000B2FF */  sd         $18, 0x50($29)
    /* 4CBBC 0014CBBC 4000B1FF */  sd         $17, 0x40($29)
    /* 4CBC0 0014CBC0 3000B0FF */  sd         $16, 0x30($29)
    /* 4CBC4 0014CBC4 0F008392 */  lbu        $3, 0xF($20)
    /* 4CBC8 0014CBC8 0F006010 */  beqz       $3, .L0014CC08
    /* 4CBCC 0014CBCC 0000A2AF */   sw        $2, 0x0($29)
    /* 4CBD0 0014CBD0 2274050C */  jal        subCommonIdle
    /* 4CBD4 0014CBD4 0000648E */   lw        $4, 0x0($19)
    /* 4CBD8 0014CBD8 000040C4 */  lwc1       $f0, 0x0($2)
    /* 4CBDC 0014CBDC 1000A0E7 */  swc1       $f0, 0x10($29)
    /* 4CBE0 0014CBE0 2274050C */  jal        subCommonIdle
    /* 4CBE4 0014CBE4 0000648E */   lw        $4, 0x0($19)
    /* 4CBE8 0014CBE8 040040C4 */  lwc1       $f0, 0x4($2)
    /* 4CBEC 0014CBEC 1400A0E7 */  swc1       $f0, 0x14($29)
    /* 4CBF0 0014CBF0 2274050C */  jal        subCommonIdle
    /* 4CBF4 0014CBF4 0000648E */   lw        $4, 0x0($19)
    /* 4CBF8 0014CBF8 080040C4 */  lwc1       $f0, 0x8($2)
    /* 4CBFC 0014CBFC 1000B227 */  addiu      $18, $29, 0x10
    /* 4CC00 0014CC00 0D000010 */  b          .L0014CC38
    /* 4CC04 0014CC04 1800A0E7 */   swc1      $f0, 0x18($29)
.align 2
  .L0014CC08:
    /* 4CC08 0014CC08 8EF9040C */  jal        isysGObjSearchFromObjLayoutID
    /* 4CC0C 0014CC0C 2E000424 */   addiu     $4, $0, 0x2E
    /* 4CC10 0014CC10 1000B227 */  addiu      $18, $29, 0x10
    /* 4CC14 0014CC14 3E74050C */  jal        ContinueCorrectPosition
    /* 4CC18 0014CC18 2D204000 */   daddu     $4, $2, $0
    /* 4CC1C 0014CC1C 0000648E */  lw         $4, 0x0($19)
    /* 4CC20 0014CC20 3E74050C */  jal        ContinueCorrectPosition
    /* 4CC24 0014CC24 2D804000 */   daddu     $16, $2, $0
    /* 4CC28 0014CC28 2D280002 */  daddu      $5, $16, $0
    /* 4CC2C 0014CC2C 2D304000 */  daddu      $6, $2, $0
    /* 4CC30 0014CC30 F447060C */  jal        _OrientXZGV
    /* 4CC34 0014CC34 2D204002 */   daddu     $4, $18, $0
.align 2
  .L0014CC38:
    /* 4CC38 0014CC38 10008CC6 */  lwc1       $f12, 0x10($20)
    /* 4CC3C 0014CC3C 2D204002 */  daddu      $4, $18, $0
    /* 4CC40 0014CC40 2D284002 */  daddu      $5, $18, $0
    /* 4CC44 0014CC44 0E00090C */  jal        sceVu0ScaleVector
    /* 4CC48 0014CC48 20009126 */   addiu     $17, $20, 0x20
    /* 4CC4C 0014CC4C 2D284002 */  daddu      $5, $18, $0
    /* 4CC50 0014CC50 30008426 */  addiu      $4, $20, 0x30
    /* 4CC54 0014CC54 0228050C */  jal        ActGame_GetOrientQ
    /* 4CC58 0014CC58 2D300000 */   daddu     $6, $0, $0
    /* 4CC5C 0014CC5C 0000648E */  lw         $4, 0x0($19)
    /* 4CC60 0014CC60 2274050C */  jal        subCommonIdle
    /* 4CC64 0014CC64 2000B027 */   addiu     $16, $29, 0x20
    /* 4CC68 0014CC68 08008CC6 */  lwc1       $f12, 0x8($20)
    /* 4CC6C 0014CC6C 2D200002 */  daddu      $4, $16, $0
    /* 4CC70 0014CC70 0E00090C */  jal        sceVu0ScaleVector
    /* 4CC74 0014CC74 2D284000 */   daddu     $5, $2, $0
    /* 4CC78 0014CC78 3E74050C */  jal        ContinueCorrectPosition
    /* 4CC7C 0014CC7C 0000648E */   lw        $4, 0x0($19)
    /* 4CC80 0014CC80 2D202002 */  daddu      $4, $17, $0
    /* 4CC84 0014CC84 2D300002 */  daddu      $6, $16, $0
    /* 4CC88 0014CC88 FCFF080C */  jal        sceVu0AddVector
    /* 4CC8C 0014CC8C 2D284000 */   daddu     $5, $2, $0
    /* 4CC90 0014CC90 2274050C */  jal        subCommonIdle
    /* 4CC94 0014CC94 0000648E */   lw        $4, 0x0($19)
    /* 4CC98 0014CC98 04008CC6 */  lwc1       $f12, 0x4($20)
    /* 4CC9C 0014CC9C 2D200002 */  daddu      $4, $16, $0
    /* 4CCA0 0014CCA0 0E00090C */  jal        sceVu0ScaleVector
    /* 4CCA4 0014CCA4 2D284000 */   daddu     $5, $2, $0
    /* 4CCA8 0014CCA8 34828CC7 */  lwc1       $f12, %gp_rel(D_00628E24)($28)
    /* 4CCAC 0014CCAC 6E47060C */  jal        func_00191DB8
    /* 4CCB0 0014CCB0 2D200002 */   daddu     $4, $16, $0
    /* 4CCB4 0014CCB4 2D202002 */  daddu      $4, $17, $0
    /* 4CCB8 0014CCB8 2D300002 */  daddu      $6, $16, $0
    /* 4CCBC 0014CCBC FCFF080C */  jal        sceVu0AddVector
    /* 4CCC0 0014CCC0 2D288000 */   daddu     $5, $4, $0
    /* 4CCC4 0014CCC4 0D008292 */  lbu        $2, 0xD($20)
    /* 4CCC8 0014CCC8 240080C6 */  lwc1       $f0, 0x24($20)
    /* 4CCCC 0014CCCC 00088244 */  mtc1       $2, $f1
    /* 4CCD0 0014CCD0 60088046 */  cvt.s.w    $f1, $f1
    /* 4CCD4 0014CCD4 8000BFDF */  ld         $31, 0x80($29)
    /* 4CCD8 0014CCD8 6000B3DF */  ld         $19, 0x60($29)
    /* 4CCDC 0014CCDC 5000B2DF */  ld         $18, 0x50($29)
    /* 4CCE0 0014CCE0 00000146 */  add.s      $f0, $f0, $f1
    /* 4CCE4 0014CCE4 4000B1DF */  ld         $17, 0x40($29)
    /* 4CCE8 0014CCE8 3000B0DF */  ld         $16, 0x30($29)
    /* 4CCEC 0014CCEC 240080E6 */  swc1       $f0, 0x24($20)
    /* 4CCF0 0014CCF0 7000B4DF */  ld         $20, 0x70($29)
    /* 4CCF4 0014CCF4 0800E003 */  jr         $31
    /* 4CCF8 0014CCF8 9000BD27 */   addiu     $29, $29, 0x90
endlabel UpdateGeo
    /* 4CCFC 0014CCFC 00000000 */  nop
```
