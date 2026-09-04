# _lshift — parked

VRAM: 0x00268A68 (file_off 0x168A68)
Asm source: asm/aug6/nonmatchings/common/src/PObj/_lshift.s

## Attempt at 2026-07-04

**Reason parked:** plateau: 30 distinct hand hypotheses, no real_count progress (best=19). PARK the seed, then fire ONE bounded permuter shot on it (REFERENCE Step 4); harvest by true real_count and adopt any improvement (resolution b only if nothing beats best).

**TU:** `common/src/PObj.c`

**Seed:** `tough_nuts/_lshift/_lshift.c`

Disassembly:

```
.align 3
nonmatching _lshift, 0x178

glabel _lshift
    /* 168A68 00268A68 80FFBD27 */  addiu      $29, $29, -0x80
    /* 168A6C 00268A6C 6000B6FF */  sd         $22, 0x60($29)
    /* 168A70 00268A70 4000B4FF */  sd         $20, 0x40($29)
    /* 168A74 00268A74 2DB08000 */  daddu      $22, $4, $0
    /* 168A78 00268A78 1000B1FF */  sd         $17, 0x10($29)
    /* 168A7C 00268A7C 43A10600 */  sra        $20, $6, 5
    /* 168A80 00268A80 0000B0FF */  sd         $16, 0x0($29)
    /* 168A84 00268A84 2D88A000 */  daddu      $17, $5, $0
    /* 168A88 00268A88 7000BFFF */  sd         $31, 0x70($29)
    /* 168A8C 00268A8C 5000B5FF */  sd         $21, 0x50($29)
    /* 168A90 00268A90 3000B3FF */  sd         $19, 0x30($29)
    /* 168A94 00268A94 2000B2FF */  sd         $18, 0x20($29)
    /* 168A98 00268A98 1000238E */  lw         $3, 0x10($17)
    /* 168A9C 00268A9C 0800278E */  lw         $7, 0x8($17)
    /* 168AA0 00268AA0 21188302 */  addu       $3, $20, $3
    /* 168AA4 00268AA4 01007024 */  addiu      $16, $3, 0x1
    /* 168AA8 00268AA8 2A10F000 */  slt        $2, $7, $16
    /* 168AAC 00268AAC 0D004010 */  beqz       $2, .L00268AE4
    /* 168AB0 00268AB0 0400258E */   lw        $5, 0x4($17)
    /* 168AB4 00268AB4 1F00D330 */  andi       $19, $6, 0x1F
    /* 168AB8 00268AB8 14003226 */  addiu      $18, $17, 0x14
    /* 168ABC 00268ABC 00000000 */  nop
.align 2
  .L00268AC0:
    /* 168AC0 00268AC0 40380700 */  sll        $7, $7, 1
    /* 168AC4 00268AC4 0100A524 */  addiu      $5, $5, 0x1
    /* 168AC8 00268AC8 2A10F000 */  slt        $2, $7, $16
    /* 168ACC 00268ACC 00000000 */  nop
    /* 168AD0 00268AD0 00000000 */  nop
    /* 168AD4 00268AD4 FAFF4014 */  bnez       $2, .L00268AC0
    /* 168AD8 00268AD8 00000000 */   nop
    /* 168ADC 00268ADC 03000010 */  b          .L00268AEC
    /* 168AE0 00268AE0 00000000 */   nop
.align 2
  .L00268AE4:
    /* 168AE4 00268AE4 1F00D330 */  andi       $19, $6, 0x1F
    /* 168AE8 00268AE8 14003226 */  addiu      $18, $17, 0x14
.align 2
  .L00268AEC:
    /* 168AEC 00268AEC A0A0090C */  jal        _Balloc
    /* 168AF0 00268AF0 2D20C002 */   daddu     $4, $22, $0
    /* 168AF4 00268AF4 2DA84000 */  daddu      $21, $2, $0
    /* 168AF8 00268AF8 0A00801A */  blez       $20, .L00268B24
    /* 168AFC 00268AFC 1400A626 */   addiu     $6, $21, 0x14
    /* 168B00 00268B00 2D388002 */  daddu      $7, $20, $0
    /* 168B04 00268B04 00000000 */  nop
.align 2
  .L00268B08:
    /* 168B08 00268B08 0000C0AC */  sw         $0, 0x0($6)
    /* 168B0C 00268B0C FFFFE724 */  addiu      $7, $7, -0x1
    /* 168B10 00268B10 0400C624 */  addiu      $6, $6, 0x4
    /* 168B14 00268B14 00000000 */  nop
    /* 168B18 00268B18 00000000 */  nop
    /* 168B1C 00268B1C FAFFE014 */  bnez       $7, .L00268B08
    /* 168B20 00268B20 00000000 */   nop
.align 2
  .L00268B24:
    /* 168B24 00268B24 1000228E */  lw         $2, 0x10($17)
    /* 168B28 00268B28 2D204002 */  daddu      $4, $18, $0
    /* 168B2C 00268B2C 80100200 */  sll        $2, $2, 2
    /* 168B30 00268B30 13006012 */  beqz       $19, .L00268B80
    /* 168B34 00268B34 21388200 */   addu      $7, $4, $2
    /* 168B38 00268B38 20000224 */  addiu      $2, $0, 0x20
    /* 168B3C 00268B3C 2D180000 */  daddu      $3, $0, $0
    /* 168B40 00268B40 23285300 */  subu       $5, $2, $19
    /* 168B44 00268B44 01000826 */  addiu      $8, $16, 0x1
.align 2
  .L00268B48:
    /* 168B48 00268B48 0000828C */  lw         $2, 0x0($4)
    /* 168B4C 00268B4C 04106202 */  sllv       $2, $2, $19
    /* 168B50 00268B50 25104300 */  or         $2, $2, $3
    /* 168B54 00268B54 0000C2AC */  sw         $2, 0x0($6)
    /* 168B58 00268B58 0400C624 */  addiu      $6, $6, 0x4
    /* 168B5C 00268B5C 0000838C */  lw         $3, 0x0($4)
    /* 168B60 00268B60 04008424 */  addiu      $4, $4, 0x4
    /* 168B64 00268B64 2B108700 */  sltu       $2, $4, $7
    /* 168B68 00268B68 F7FF4014 */  bnez       $2, .L00268B48
    /* 168B6C 00268B6C 0618A300 */   srlv      $3, $3, $5
    /* 168B70 00268B70 0B800301 */  movn       $16, $8, $3
    /* 168B74 00268B74 0000C3AC */  sw         $3, 0x0($6)
    /* 168B78 00268B78 0A000010 */  b          .L00268BA4
    /* 168B7C 00268B7C FFFF0526 */   addiu     $5, $16, -0x1
.align 2
  .L00268B80:
    /* 168B80 00268B80 FFFF0526 */  addiu      $5, $16, -0x1
    /* 168B84 00268B84 00000000 */  nop
.align 2
  .L00268B88:
    /* 168B88 00268B88 0000828C */  lw         $2, 0x0($4)
    /* 168B8C 00268B8C 04008424 */  addiu      $4, $4, 0x4
    /* 168B90 00268B90 0000C2AC */  sw         $2, 0x0($6)
    /* 168B94 00268B94 2B188700 */  sltu       $3, $4, $7
    /* 168B98 00268B98 0400C624 */  addiu      $6, $6, 0x4
    /* 168B9C 00268B9C FAFF6014 */  bnez       $3, .L00268B88
    /* 168BA0 00268BA0 00000000 */   nop
.align 2
  .L00268BA4:
    /* 168BA4 00268BA4 1000A5AE */  sw         $5, 0x10($21)
    /* 168BA8 00268BA8 2D20C002 */  daddu      $4, $22, $0
    /* 168BAC 00268BAC CAA0090C */  jal        _Bfree
    /* 168BB0 00268BB0 2D282002 */   daddu     $5, $17, $0
    /* 168BB4 00268BB4 2D10A002 */  daddu      $2, $21, $0
    /* 168BB8 00268BB8 7000BFDF */  ld         $31, 0x70($29)
    /* 168BBC 00268BBC 6000B6DF */  ld         $22, 0x60($29)
    /* 168BC0 00268BC0 5000B5DF */  ld         $21, 0x50($29)
    /* 168BC4 00268BC4 4000B4DF */  ld         $20, 0x40($29)
    /* 168BC8 00268BC8 3000B3DF */  ld         $19, 0x30($29)
    /* 168BCC 00268BCC 2000B2DF */  ld         $18, 0x20($29)
    /* 168BD0 00268BD0 1000B1DF */  ld         $17, 0x10($29)
    /* 168BD4 00268BD4 0000B0DF */  ld         $16, 0x0($29)
    /* 168BD8 00268BD8 0800E003 */  jr         $31
    /* 168BDC 00268BDC 8000BD27 */   addiu     $29, $29, 0x80
endlabel _lshift
```
