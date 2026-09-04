# _dispRefImage — parked

VRAM: 0x00253DB0 (file_off 0x153DB0)
Asm source: asm/aug6/nonmatchings/common/src/PObj/_dispRefImage.s

## Attempt at 2026-06-12

**Reason parked:** recovered from cancelled bulk campaign (matched, unverified-in-TU); re-verify before integrating

**TU:** `common/src/PObj.c`

**Seed:** `tough_nuts/_dispRefImage/_dispRefImage.c`

Disassembly:

```
.align 3
nonmatching _dispRefImage, 0x118

glabel _dispRefImage
    /* 153DB0 00253DB0 C0FFBD27 */  addiu      $29, $29, -0x40
    /* 153DB4 00253DB4 0000B0FF */  sd         $16, 0x0($29)
    /* 153DB8 00253DB8 5500103C */  lui        $16, %hi(D_0054C764)
    /* 153DBC 00253DBC 2000B2FF */  sd         $18, 0x20($29)
    /* 153DC0 00253DC0 64C7068E */  lw         $6, %lo(D_0054C764)($16)
    /* 153DC4 00253DC4 2D908000 */  daddu      $18, $4, $0
    /* 153DC8 00253DC8 3000BFFF */  sd         $31, 0x30($29)
    /* 153DCC 00253DCC 1000B1FF */  sd         $17, 0x10($29)
    /* 153DD0 00253DD0 2000C724 */  addiu      $7, $6, 0x20
    /* 153DD4 00253DD4 4000D18C */  lw         $17, 0x40($6)
    /* 153DD8 00253DD8 1000C524 */  addiu      $5, $6, 0x10
    /* 153DDC 00253DDC 064F090C */  jal        _getPtsDtsFlags
    /* 153DE0 00253DE0 1800C624 */   addiu     $6, $6, 0x18
    /* 153DE4 00253DE4 64C7068E */  lw         $6, %lo(D_0054C764)($16)
    /* 153DE8 00253DE8 5500053C */  lui        $5, %hi(D_0054D0F8)
    /* 153DEC 00253DEC F8D0A524 */  addiu      $5, $5, %lo(D_0054D0F8)
    /* 153DF0 00253DF0 2D204002 */  daddu      $4, $18, $0
    /* 153DF4 00253DF4 2000C2DC */  ld         $2, 0x20($6)
    /* 153DF8 00253DF8 1000C38C */  lw         $3, 0x10($6)
    /* 153DFC 00253DFC F8160200 */  dsll       $2, $2, 27
    /* 153E00 00253E00 3F100200 */  dsra32     $2, $2, 0
    /* 153E04 00253E04 800023AE */  sw         $3, 0x80($17)
    /* 153E08 00253E08 0F004230 */  andi       $2, $2, 0xF
    /* 153E0C 00253E0C 80100200 */  sll        $2, $2, 2
    /* 153E10 00253E10 5C00438E */  lw         $3, 0x5C($18)
    /* 153E14 00253E14 21104500 */  addu       $2, $2, $5
    /* 153E18 00253E18 0000459C */  lwu        $5, 0x0($2)
    /* 153E1C 00253E1C CC0023AE */  sw         $3, 0xCC($17)
    /* 153E20 00253E20 880025FE */  sd         $5, 0x88($17)
    /* 153E24 00253E24 6000428E */  lw         $2, 0x60($18)
    /* 153E28 00253E28 D00022AE */  sw         $2, 0xD0($17)
    /* 153E2C 00253E2C 4400438E */  lw         $3, 0x44($18)
    /* 153E30 00253E30 B40023AE */  sw         $3, 0xB4($17)
    /* 153E34 00253E34 4800428E */  lw         $2, 0x48($18)
    /* 153E38 00253E38 B80022AE */  sw         $2, 0xB8($17)
    /* 153E3C 00253E3C 4C00438E */  lw         $3, 0x4C($18)
    /* 153E40 00253E40 BC0023AE */  sw         $3, 0xBC($17)
    /* 153E44 00253E44 5000428E */  lw         $2, 0x50($18)
    /* 153E48 00253E48 C00022AE */  sw         $2, 0xC0($17)
    /* 153E4C 00253E4C 5400438E */  lw         $3, 0x54($18)
    /* 153E50 00253E50 C40023AE */  sw         $3, 0xC4($17)
    /* 153E54 00253E54 5800428E */  lw         $2, 0x58($18)
    /* 153E58 00253E58 544E090C */  jal        _isOutSizeOK
    /* 153E5C 00253E5C C80022AE */   sw        $2, 0xC8($17)
    /* 153E60 00253E60 13004010 */  beqz       $2, .L00253EB0
    /* 153E64 00253E64 01000224 */   addiu     $2, $0, 0x1
    /* 153E68 00253E68 2800438E */  lw         $3, 0x28($18)
    /* 153E6C 00253E6C 11006214 */  bne        $3, $2, .L00253EB4
    /* 153E70 00253E70 3000BFDF */   ld        $31, 0x30($29)
    /* 153E74 00253E74 B000228E */  lw         $2, 0xB0($17)
    /* 153E78 00253E78 05004010 */  beqz       $2, .L00253E90
    /* 153E7C 00253E7C 00000000 */   nop
    /* 153E80 00253E80 5451090C */  jal        _csc_storeRefImage
    /* 153E84 00253E84 2D204002 */   daddu     $4, $18, $0
    /* 153E88 00253E88 04000010 */  b          .L00253E9C
    /* 153E8C 00253E8C 3000BFDF */   ld        $31, 0x30($29)
.align 2
  .L00253E90:
    /* 153E90 00253E90 7C4E090C */  jal        _cpr8
    /* 153E94 00253E94 2D204002 */   daddu     $4, $18, $0
    /* 153E98 00253E98 3000BFDF */  ld         $31, 0x30($29)
.align 2
  .L00253E9C:
    /* 153E9C 00253E9C 2000B2DF */  ld         $18, 0x20($29)
    /* 153EA0 00253EA0 1000B1DF */  ld         $17, 0x10($29)
    /* 153EA4 00253EA4 0000B0DF */  ld         $16, 0x0($29)
    /* 153EA8 00253EA8 F84E0908 */  j          _markOutput
    /* 153EAC 00253EAC 4000BD27 */   addiu     $29, $29, 0x40
.align 2
  .L00253EB0:
    /* 153EB0 00253EB0 3000BFDF */  ld         $31, 0x30($29)
.align 2
  .L00253EB4:
    /* 153EB4 00253EB4 2000B2DF */  ld         $18, 0x20($29)
    /* 153EB8 00253EB8 1000B1DF */  ld         $17, 0x10($29)
    /* 153EBC 00253EBC 0000B0DF */  ld         $16, 0x0($29)
    /* 153EC0 00253EC0 0800E003 */  jr         $31
    /* 153EC4 00253EC4 4000BD27 */   addiu     $29, $29, 0x40
endlabel _dispRefImage
```
