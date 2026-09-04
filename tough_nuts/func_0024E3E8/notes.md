# _decodeOrSkipFrame — parked

VRAM: 0x0024E3E8 (file_off 0x14E3E8)
Asm source: asm/aug6/nonmatchings/common/src/PObj/_decodeOrSkipFrame.s

## Attempt at 2026-06-22

**Reason parked:** override=permute

**TU:** `common/src/PObj.c`

**Seed:** `tough_nuts/_decodeOrSkipFrame/_decodeOrSkipFrame.c`

Disassembly:

```
.align 3
nonmatching _decodeOrSkipFrame, 0x124

glabel _decodeOrSkipFrame
    /* 14E3E8 0024E3E8 A0FFBD27 */  addiu      $29, $29, -0x60
    /* 14E3EC 0024E3EC FFFF0224 */  addiu      $2, $0, -0x1
    /* 14E3F0 0024E3F0 4000B4FF */  sd         $20, 0x40($29)
    /* 14E3F4 0024E3F4 1000B1FF */  sd         $17, 0x10($29)
    /* 14E3F8 0024E3F8 2DA00000 */  daddu      $20, $0, $0
    /* 14E3FC 0024E3FC 5000BFFF */  sd         $31, 0x50($29)
    /* 14E400 0024E400 2D888000 */  daddu      $17, $4, $0
    /* 14E404 0024E404 3000B3FF */  sd         $19, 0x30($29)
    /* 14E408 0024E408 2000B2FF */  sd         $18, 0x20($29)
    /* 14E40C 0024E40C 0000B0FF */  sd         $16, 0x0($29)
    /* 14E410 0024E410 0400C210 */  beq        $6, $2, .L0024E424
    /* 14E414 0024E414 4000308E */   lw        $16, 0x40($17)
    /* 14E418 0024E418 2A10A600 */  slt        $2, $5, $6
    /* 14E41C 0024E41C 13004010 */  beqz       $2, .L0024E46C
    /* 14E420 0024E420 2D200000 */   daddu     $4, $0, $0
.align 2
  .L0024E424:
    /* 14E424 0024E424 0800028E */  lw         $2, 0x8($16)
    /* 14E428 0024E428 03004014 */  bnez       $2, .L0024E438
    /* 14E42C 0024E42C 01000224 */   addiu     $2, $0, 0x1
    /* 14E430 0024E430 080020AE */  sw         $0, 0x8($17)
    /* 14E434 0024E434 080002AE */  sw         $2, 0x8($16)
.align 2
  .L0024E438:
    /* 14E438 0024E438 5C4D090C */  jal        _updateRefImage
    /* 14E43C 0024E43C 2D200000 */   daddu     $4, $0, $0
    /* 14E440 0024E440 07004010 */  beqz       $2, .L0024E460
    /* 14E444 0024E444 2D180000 */   daddu     $3, $0, $0
    /* 14E448 0024E448 5500133C */  lui        $19, %hi(D_0054C884)
    /* 14E44C 0024E44C 0400058E */  lw         $5, 0x4($16)
    /* 14E450 0024E450 F64C090C */  jal        _decPicture
    /* 14E454 0024E454 84C8648E */   lw        $4, %lo(D_0054C884)($19)
    /* 14E458 0024E458 02000010 */  b          .L0024E464
    /* 14E45C 0024E45C 2B180200 */   sltu      $3, $0, $2
.align 2
  .L0024E460:
    /* 14E460 0024E460 5500133C */  lui        $19, %hi(D_0054C884)
.align 2
  .L0024E464:
    /* 14E464 0024E464 07000010 */  b          .L0024E484
    /* 14E468 0024E468 2D906000 */   daddu     $18, $3, $0
.align 2
  .L0024E46C:
    /* 14E46C 0024E46C 5C4D090C */  jal        _updateRefImage
    /* 14E470 0024E470 01001424 */   addiu     $20, $0, 0x1
    /* 14E474 0024E474 5500133C */  lui        $19, %hi(D_0054C884)
    /* 14E478 0024E478 2D904000 */  daddu      $18, $2, $0
    /* 14E47C 0024E47C 3638090C */  jal        _dispatchMpegCbNodata
    /* 14E480 0024E480 2D202002 */   daddu     $4, $17, $0
.align 2
  .L0024E484:
    /* 14E484 0024E484 84C8648E */  lw         $4, %lo(D_0054C884)($19)
    /* 14E488 0024E488 2E4D090C */  jal        _outputFrame
    /* 14E48C 0024E48C 0400058E */   lw        $5, 0x4($16)
    /* 14E490 0024E490 5500023C */  lui        $2, %hi(D_0054C92C)
    /* 14E494 0024E494 03000424 */  addiu      $4, $0, 0x3
    /* 14E498 0024E498 2CC9438C */  lw         $3, %lo(D_0054C92C)($2)
    /* 14E49C 0024E49C 07006410 */  beq        $3, $4, .L0024E4BC
    /* 14E4A0 0024E4A0 5500033C */   lui       $3, %hi(D_0054C89C)
    /* 14E4A4 0024E4A4 06008016 */  bnez       $20, .L0024E4C0
    /* 14E4A8 0024E4A8 84C8648E */   lw        $4, %lo(D_0054C884)($19)
    /* 14E4AC 0024E4AC 5500033C */  lui        $3, %hi(D_0054C89C)
    /* 14E4B0 0024E4B0 9CC8628C */  lw         $2, %lo(D_0054C89C)($3)
    /* 14E4B4 0024E4B4 0100422C */  sltiu      $2, $2, 0x1
    /* 14E4B8 0024E4B8 9CC862AC */  sw         $2, %lo(D_0054C89C)($3)
.align 2
  .L0024E4BC:
    /* 14E4BC 0024E4BC 84C8648E */  lw         $4, %lo(D_0054C884)($19)
.align 2
  .L0024E4C0:
    /* 14E4C0 0024E4C0 AC00028E */  lw         $2, 0xAC($16)
    /* 14E4C4 0024E4C4 9CC8638C */  lw         $3, %lo(D_0054C89C)($3)
    /* 14E4C8 0024E4C8 23108200 */  subu       $2, $4, $2
    /* 14E4CC 0024E4CC 06006014 */  bnez       $3, .L0024E4E8
    /* 14E4D0 0024E4D0 080022AE */   sw        $2, 0x8($17)
    /* 14E4D4 0024E4D4 0400028E */  lw         $2, 0x4($16)
    /* 14E4D8 0024E4D8 01008324 */  addiu      $3, $4, 0x1
    /* 14E4DC 0024E4DC 84C863AE */  sw         $3, %lo(D_0054C884)($19)
    /* 14E4E0 0024E4E0 01004224 */  addiu      $2, $2, 0x1
    /* 14E4E4 0024E4E4 040002AE */  sw         $2, 0x4($16)
.align 2
  .L0024E4E8:
    /* 14E4E8 0024E4E8 2D104002 */  daddu      $2, $18, $0
    /* 14E4EC 0024E4EC 5000BFDF */  ld         $31, 0x50($29)
    /* 14E4F0 0024E4F0 4000B4DF */  ld         $20, 0x40($29)
    /* 14E4F4 0024E4F4 3000B3DF */  ld         $19, 0x30($29)
    /* 14E4F8 0024E4F8 2000B2DF */  ld         $18, 0x20($29)
    /* 14E4FC 0024E4FC 1000B1DF */  ld         $17, 0x10($29)
    /* 14E500 0024E500 0000B0DF */  ld         $16, 0x0($29)
    /* 14E504 0024E504 0800E003 */  jr         $31
    /* 14E508 0024E508 6000BD27 */   addiu     $29, $29, 0x60
endlabel _decodeOrSkipFrame
    /* 14E50C 0024E50C 00000000 */  nop
```
