# ReadEndCheckFile — parked

VRAM: 0x0019FAA0 (file_off 0x09FAA0)
Asm source: asm/aug6/nonmatchings/common/src/charFileManager/ReadEndCheckFile.s

## Attempt at 2026-06-20

**Reason parked:** plateau: 30 distinct hand hypotheses, no real_count progress (best=2). PARK the seed, then fire ONE bounded permuter shot on it (REFERENCE Step 4); harvest by true real_count and adopt any improvement (resolution b only if nothing beats best).

**TU:** `common/src/charFileManager.c`

**Seed:** `tough_nuts/ReadEndCheckFile/ReadEndCheckFile.c`

Disassembly:

```
.align 3
nonmatching ReadEndCheckFile, 0x110

glabel ReadEndCheckFile
    /* 9FAA0 0019FAA0 A0FFBD27 */  addiu      $29, $29, -0x60
    /* 9FAA4 0019FAA4 2700033C */  lui        $3, %hi(D_00271240)
    /* 9FAA8 0019FAA8 4000B4FF */  sd         $20, 0x40($29)
    /* 9FAAC 0019FAAC 40126324 */  addiu      $3, $3, %lo(D_00271240)
    /* 9FAB0 0019FAB0 3000B3FF */  sd         $19, 0x30($29)
    /* 9FAB4 0019FAB4 2DA0A000 */  daddu      $20, $5, $0
    /* 9FAB8 0019FAB8 2000B2FF */  sd         $18, 0x20($29)
    /* 9FABC 0019FABC 2D98E000 */  daddu      $19, $7, $0
    /* 9FAC0 0019FAC0 0000B0FF */  sd         $16, 0x0($29)
    /* 9FAC4 0019FAC4 2D90C000 */  daddu      $18, $6, $0
    /* 9FAC8 0019FAC8 5000BFFF */  sd         $31, 0x50($29)
    /* 9FACC 0019FACC 2D808000 */  daddu      $16, $4, $0
    /* 9FAD0 0019FAD0 1000B1FF */  sd         $17, 0x10($29)
    /* 9FAD4 0019FAD4 2000628C */  lw         $2, 0x20($3)
    /* 9FAD8 0019FAD8 01004224 */  addiu      $2, $2, 0x1
    /* 9FADC 0019FADC 17004015 */  bnez       $10, .L0019FB3C
    /* 9FAE0 0019FAE0 200062AC */   sw        $2, 0x20($3)
    /* 9FAE4 0019FAE4 24CF070C */  jal        malloc_GetPartition
    /* 9FAE8 0019FAE8 2D200000 */   daddu     $4, $0, $0
    /* 9FAEC 0019FAEC 03004016 */  bnez       $18, .L0019FAFC
    /* 9FAF0 0019FAF0 6100063C */   lui       $6, %hi(D_0060B4E0)
    /* 9FAF4 0019FAF4 0F000010 */  b          .L0019FB34
    /* 9FAF8 0019FAF8 2D880000 */   daddu     $17, $0, $0
.align 2
  .L0019FAFC:
    /* 9FAFC 0019FAFC 4897848F */  lw         $4, %gp_rel(D_0062A338)($28)
    /* 9FB00 0019FB00 E0B4C624 */  addiu      $6, $6, %lo(D_0060B4E0)
    /* 9FB04 0019FB04 10004526 */  addiu      $5, $18, 0x10
    /* 9FB08 0019FB08 CEE2040C */  jal        iosFree
    /* 9FB0C 0019FB0C 07030724 */   addiu     $7, $0, 0x307
    /* 9FB10 0019FB10 2D884000 */  daddu      $17, $2, $0
    /* 9FB14 0019FB14 2D200002 */  daddu      $4, $16, $0
    /* 9FB18 0019FB18 10003026 */  addiu      $16, $17, 0x10
    /* 9FB1C 0019FB1C 2D304002 */  daddu      $6, $18, $0
    /* 9FB20 0019FB20 EEC7040C */  jal        iosCdvdLoad
    /* 9FB24 0019FB24 2D280002 */   daddu     $5, $16, $0
    /* 9FB28 0019FB28 2D280002 */  daddu      $5, $16, $0
    /* 9FB2C 0019FB2C DCEF040C */  jal        ShockRequestBox_DecodeRequest
    /* 9FB30 0019FB30 2D202002 */   daddu     $4, $17, $0
.align 2
  .L0019FB34:
    /* 9FB34 0019FB34 11000010 */  b          .L0019FB7C
    /* 9FB38 0019FB38 A49891AF */   sw        $17, %gp_rel(D_0062A494)($28)
.align 2
  .L0019FB3C:
    /* 9FB3C 0019FB3C 24CF070C */  jal        malloc_GetPartition
    /* 9FB40 0019FB40 01000424 */   addiu     $4, $0, 0x1
    /* 9FB44 0019FB44 0C004012 */  beqz       $18, .L0019FB78
    /* 9FB48 0019FB48 2D880000 */   daddu     $17, $0, $0
    /* 9FB4C 0019FB4C 28CF070C */  jal        freeseki
    /* 9FB50 0019FB50 10004426 */   addiu     $4, $18, 0x10
    /* 9FB54 0019FB54 2D884000 */  daddu      $17, $2, $0
    /* 9FB58 0019FB58 2D200002 */  daddu      $4, $16, $0
    /* 9FB5C 0019FB5C 10003026 */  addiu      $16, $17, 0x10
    /* 9FB60 0019FB60 2D304002 */  daddu      $6, $18, $0
    /* 9FB64 0019FB64 EEC7040C */  jal        iosCdvdLoad
    /* 9FB68 0019FB68 2D280002 */   daddu     $5, $16, $0
    /* 9FB6C 0019FB6C 2D280002 */  daddu      $5, $16, $0
    /* 9FB70 0019FB70 DCEF040C */  jal        ShockRequestBox_DecodeRequest
    /* 9FB74 0019FB74 2D202002 */   daddu     $4, $17, $0
.align 2
  .L0019FB78:
    /* 9FB78 0019FB78 A89891AF */  sw         $17, %gp_rel(D_0062A498)($28)
.align 2
  .L0019FB7C:
    /* 9FB7C 0019FB7C 2D286002 */  daddu      $5, $19, $0
    /* 9FB80 0019FB80 2D308002 */  daddu      $6, $20, $0
    /* 9FB84 0019FB84 2D384002 */  daddu      $7, $18, $0
    /* 9FB88 0019FB88 6100043C */  lui        $4, %hi(D_0060BA60)
    /* 9FB8C 0019FB8C 5000BFDF */  ld         $31, 0x50($29)
    /* 9FB90 0019FB90 60BA8424 */  addiu      $4, $4, %lo(D_0060BA60)
    /* 9FB94 0019FB94 4000B4DF */  ld         $20, 0x40($29)
    /* 9FB98 0019FB98 3000B3DF */  ld         $19, 0x30($29)
    /* 9FB9C 0019FB9C 2000B2DF */  ld         $18, 0x20($29)
    /* 9FBA0 0019FBA0 1000B1DF */  ld         $17, 0x10($29)
    /* 9FBA4 0019FBA4 0000B0DF */  ld         $16, 0x0($29)
    /* 9FBA8 0019FBA8 F2900608 */  j          debug_StdPrintfDummy
    /* 9FBAC 0019FBAC 6000BD27 */   addiu     $29, $29, 0x60
endlabel ReadEndCheckFile
```
