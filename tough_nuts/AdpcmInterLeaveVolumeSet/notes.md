# AdpcmInterLeaveVolumeSet — parked

VRAM: 0x001F98B0 (file_off 0x0F98B0)
Asm source: asm/aug6/nonmatchings/fumi/sound/adpcm_init/AdpcmInterLeaveVolumeSet.s

## Attempt at 2026-06-26

**Reason parked:** plateau: 30 distinct hand hypotheses, no real_count progress (best=6). PARK the seed, then fire ONE bounded permuter shot on it (REFERENCE Step 4); harvest by true real_count and adopt any improvement (resolution b only if nothing beats best).

**TU:** `fumi/sound/adpcm_init.c`

**Seed:** `tough_nuts/AdpcmInterLeaveVolumeSet/AdpcmInterLeaveVolumeSet.c`

Disassembly:

```
.align 3
nonmatching AdpcmInterLeaveVolumeSet, 0x140

glabel AdpcmInterLeaveVolumeSet
    /* F98B0 001F98B0 A0FFBD27 */  addiu      $29, $29, -0x60
    /* F98B4 001F98B4 2000B1FF */  sd         $17, 0x20($29)
    /* F98B8 001F98B8 1000B0FF */  sd         $16, 0x10($29)
    /* F98BC 001F98BC 2D888000 */  daddu      $17, $4, $0
    /* F98C0 001F98C0 4000B3FF */  sd         $19, 0x40($29)
    /* F98C4 001F98C4 2D80A000 */  daddu      $16, $5, $0
    /* F98C8 001F98C8 3000B2FF */  sd         $18, 0x30($29)
    /* F98CC 001F98CC 6100043C */  lui        $4, %hi(D_00613888)
    /* F98D0 001F98D0 5000BFFF */  sd         $31, 0x50($29)
    /* F98D4 001F98D4 2D90C000 */  daddu      $18, $6, $0
    /* F98D8 001F98D8 2D98E000 */  daddu      $19, $7, $0
    /* F98DC 001F98DC F290060C */  jal        debug_assertMessage
    /* F98E0 001F98E0 88388424 */   addiu     $4, $4, %lo(D_00613888)
    /* F98E4 001F98E4 FFFF0232 */  andi       $2, $16, 0xFFFF
    /* F98E8 001F98E8 1100033C */  lui        $3, (0x110000 >> 16)
    /* F98EC 001F98EC 25104300 */  or         $2, $2, $3
    /* F98F0 001F98F0 2D20A003 */  daddu      $4, $29, $0
    /* F98F4 001F98F4 E209050C */  jal        soundDataAreaGet
    /* F98F8 001F98F8 0000A2AF */   sw        $2, 0x0($29)
    /* F98FC 001F98FC 03004050 */  beql       $2, $0, .L001F990C
    /* F9900 001F9900 080032AE */   sw        $18, 0x8($17)
    /* F9904 001F9904 33000010 */  b          .L001F99D4
    /* F9908 001F9908 140020AE */   sw        $0, 0x14($17)
.align 2
  .L001F990C:
    /* F990C 001F990C 80B68427 */  addiu      $4, $28, %gp_rel(D_0062C270)
    /* F9910 001F9910 040030AE */  sw         $16, 0x4($17)
    /* F9914 001F9914 2D280000 */  daddu      $5, $0, $0
    /* F9918 001F9918 80811000 */  sll        $16, $16, 6
    /* F991C 001F991C 6100123C */  lui        $18, %hi(D_006151D8)
    /* F9920 001F9920 2D308000 */  daddu      $6, $4, $0
    /* F9924 001F9924 00000000 */  nop
.align 2
  .L001F9928:
    /* F9928 001F9928 0000828C */  lw         $2, 0x0($4)
    /* F992C 001F992C 0B004010 */  beqz       $2, .L001F995C
    /* F9930 001F9930 2D18C000 */   daddu     $3, $6, $0
    /* F9934 001F9934 0100A524 */  addiu      $5, $5, 0x1
    /* F9938 001F9938 04006624 */  addiu      $6, $3, 0x4
    /* F993C 001F993C 0200A228 */  slti       $2, $5, 0x2
    /* F9940 001F9940 F9FF4014 */  bnez       $2, .L001F9928
    /* F9944 001F9944 04008424 */   addiu     $4, $4, 0x4
    /* F9948 001F9948 6100043C */  lui        $4, %hi(D_00613858)
    /* F994C 001F994C F290060C */  jal        debug_assertMessage
    /* F9950 001F9950 58388424 */   addiu     $4, $4, %lo(D_00613858)
    /* F9954 001F9954 08000010 */  b          .L001F9978
    /* F9958 001F9958 2D100000 */   daddu     $2, $0, $0
.align 2
  .L001F995C:
    /* F995C 001F995C 0500023C */  lui        $2, (0x5C000 >> 16)
    /* F9960 001F9960 78B6838F */  lw         $3, %gp_rel(D_0062C268)($28)
    /* F9964 001F9964 00C04234 */  ori        $2, $2, (0x5C000 & 0xFFFF)
    /* F9968 001F9968 01000424 */  addiu      $4, $0, 0x1
    /* F996C 001F996C 1810A200 */  mult       $2, $5, $2
    /* F9970 001F9970 0000C4AC */  sw         $4, 0x0($6)
    /* F9974 001F9974 21106200 */  addu       $2, $3, $2
.align 2
  .L001F9978:
    /* F9978 001F9978 0F004010 */  beqz       $2, .L001F99B8
    /* F997C 001F997C 0C0022AE */   sw        $2, 0xC($17)
    /* F9980 001F9980 D8514426 */  addiu      $4, $18, %lo(D_006151D8)
    /* F9984 001F9984 2000053C */  lui        $5, %hi(CheckWallAttributeEdegWall)
    /* F9988 001F9988 2000073C */  lui        $7, %hi(func_001FA070)
    /* F998C 001F998C 21200402 */  addu       $4, $16, $4
    /* F9990 001F9990 48A0A524 */  addiu      $5, $5, %lo(CheckWallAttributeEdegWall)
    /* F9994 001F9994 70A0E724 */  addiu      $7, $7, %lo(func_001FA070)
    /* F9998 001F9998 2D302002 */  daddu      $6, $17, $0
    /* F999C 001F999C 2D400000 */  daddu      $8, $0, $0
    /* F99A0 001F99A0 2D482002 */  daddu      $9, $17, $0
    /* F99A4 001F99A4 2D500000 */  daddu      $10, $0, $0
    /* F99A8 001F99A8 4CC9040C */  jal        iosCdvdChgFileName
    /* F99AC 001F99AC 2D580000 */   daddu     $11, $0, $0
    /* F99B0 001F99B0 07000010 */  b          .L001F99D0
    /* F99B4 001F99B4 140022AE */   sw        $2, 0x14($17)
.align 2
  .L001F99B8:
    /* F99B8 001F99B8 D8514526 */  addiu      $5, $18, %lo(D_006151D8)
    /* F99BC 001F99BC 6300043C */  lui        $4, %hi(D_0062D9B0)
    /* F99C0 001F99C0 140020AE */  sw         $0, 0x14($17)
    /* F99C4 001F99C4 21280502 */  addu       $5, $16, $5
    /* F99C8 001F99C8 F290060C */  jal        debug_assertMessage
    /* F99CC 001F99CC B0D98424 */   addiu     $4, $4, %lo(D_0062D9B0)
.align 2
  .L001F99D0:
    /* F99D0 001F99D0 100033AE */  sw         $19, 0x10($17)
.align 2
  .L001F99D4:
    /* F99D4 001F99D4 5000BFDF */  ld         $31, 0x50($29)
    /* F99D8 001F99D8 4000B3DF */  ld         $19, 0x40($29)
    /* F99DC 001F99DC 3000B2DF */  ld         $18, 0x30($29)
    /* F99E0 001F99E0 2000B1DF */  ld         $17, 0x20($29)
    /* F99E4 001F99E4 1000B0DF */  ld         $16, 0x10($29)
    /* F99E8 001F99E8 0800E003 */  jr         $31
    /* F99EC 001F99EC 6000BD27 */   addiu     $29, $29, 0x60
endlabel AdpcmInterLeaveVolumeSet
```
