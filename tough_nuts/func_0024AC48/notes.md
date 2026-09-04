# scePadInfoComb — parked

VRAM: 0x0024AC48 (file_off 0x14AC48)
Asm source: asm/aug6/nonmatchings/common/src/PObj/scePadInfoComb.s

## Attempt at 2026-06-21

**Reason parked:** override=permute

**TU:** `common/src/PObj.c`

**Seed:** `tough_nuts/scePadInfoComb/scePadInfoComb.c`

Disassembly:

```
.align 3
nonmatching scePadInfoComb, 0x11C

glabel scePadInfoComb
    /* 14AC48 0024AC48 2D408000 */  daddu      $8, $4, $0
    /* 14AC4C 0024AC4C 70000324 */  addiu      $3, $0, 0x70
    /* 14AC50 0024AC50 1C000424 */  addiu      $4, $0, 0x1C
    /* 14AC54 0024AC54 18180371 */  mult1      $3, $8, $3
    /* 14AC58 0024AC58 1820A400 */  mult       $4, $5, $4
    /* 14AC5C 0024AC5C D0FFBD27 */  addiu      $29, $29, -0x30
    /* 14AC60 0024AC60 7100023C */  lui        $2, %hi(D_007112D0)
    /* 14AC64 0024AC64 1000B1FF */  sd         $17, 0x10($29)
    /* 14AC68 0024AC68 0000B0FF */  sd         $16, 0x0($29)
    /* 14AC6C 0024AC6C D0124224 */  addiu      $2, $2, %lo(D_007112D0)
    /* 14AC70 0024AC70 2000BFFF */  sd         $31, 0x20($29)
    /* 14AC74 0024AC74 2D88C000 */  daddu      $17, $6, $0
    /* 14AC78 0024AC78 21208300 */  addu       $4, $4, $3
    /* 14AC7C 0024AC7C 21104400 */  addu       $2, $2, $4
    /* 14AC80 0024AC80 1000438C */  lw         $3, 0x10($2)
    /* 14AC84 0024AC84 31006010 */  beqz       $3, .L0024AD4C
    /* 14AC88 0024AC88 2D80E000 */   daddu     $16, $7, $0
    /* 14AC8C 0024AC8C 162A090C */  jal        scePadGetDmaStr
    /* 14AC90 0024AC90 2D200001 */   daddu     $4, $8, $0
    /* 14AC94 0024AC94 2D204000 */  daddu      $4, $2, $0
    /* 14AC98 0024AC98 72008390 */  lbu        $3, 0x72($4)
    /* 14AC9C 0024AC9C 01000224 */  addiu      $2, $0, 0x1
    /* 14ACA0 0024ACA0 2B006214 */  bne        $3, $2, .L0024AD50
    /* 14ACA4 0024ACA4 2D100000 */   daddu     $2, $0, $0
    /* 14ACA8 0024ACA8 64008290 */  lbu        $2, 0x64($4)
    /* 14ACAC 0024ACAC 0200422C */  sltiu      $2, $2, 0x2
    /* 14ACB0 0024ACB0 27004014 */  bnez       $2, .L0024AD50
    /* 14ACB4 0024ACB4 2D100000 */   daddu     $2, $0, $0
    /* 14ACB8 0024ACB8 FFFF0524 */  addiu      $5, $0, -0x1
    /* 14ACBC 0024ACBC 03002516 */  bne        $17, $5, .L0024ACCC
    /* 14ACC0 0024ACC0 6B008290 */   lbu       $2, 0x6B($4)
    /* 14ACC4 0024ACC4 23000010 */  b          .L0024AD54
    /* 14ACC8 0024ACC8 2000BFDF */   ld        $31, 0x20($29)
.align 2
  .L0024ACCC:
    /* 14ACCC 0024ACCC 2A102202 */  slt        $2, $17, $2
    /* 14ACD0 0024ACD0 1F004050 */  beql       $2, $0, .L0024AD50
    /* 14ACD4 0024ACD4 2D100000 */   daddu     $2, $0, $0
    /* 14ACD8 0024ACD8 11000052 */  beql       $16, $0, .L0024AD20
    /* 14ACDC 0024ACDC 80181100 */   sll       $3, $17, 2
    /* 14ACE0 0024ACE0 0500001E */  bgtz       $16, .L0024ACF8
    /* 14ACE4 0024ACE4 00000000 */   nop
    /* 14ACE8 0024ACE8 09000512 */  beq        $16, $5, .L0024AD10
    /* 14ACEC 0024ACEC 2D100000 */   daddu     $2, $0, $0
    /* 14ACF0 0024ACF0 18000010 */  b          .L0024AD54
    /* 14ACF4 0024ACF4 2000BFDF */   ld        $31, 0x20($29)
.align 2
  .L0024ACF8:
    /* 14ACF8 0024ACF8 0C000312 */  beq        $16, $3, .L0024AD2C
    /* 14ACFC 0024ACFC 02000224 */   addiu     $2, $0, 0x2
    /* 14AD00 0024AD00 0E000212 */  beq        $16, $2, .L0024AD3C
    /* 14AD04 0024AD04 2D100000 */   daddu     $2, $0, $0
    /* 14AD08 0024AD08 12000010 */  b          .L0024AD54
    /* 14AD0C 0024AD0C 2000BFDF */   ld        $31, 0x20($29)
.align 2
  .L0024AD10:
    /* 14AD10 0024AD10 80181100 */  sll        $3, $17, 2
    /* 14AD14 0024AD14 21188300 */  addu       $3, $4, $3
    /* 14AD18 0024AD18 0D000010 */  b          .L0024AD50
    /* 14AD1C 0024AD1C 40006290 */   lbu       $2, 0x40($3)
.align 2
  .L0024AD20:
    /* 14AD20 0024AD20 21188300 */  addu       $3, $4, $3
    /* 14AD24 0024AD24 0A000010 */  b          .L0024AD50
    /* 14AD28 0024AD28 41006290 */   lbu       $2, 0x41($3)
.align 2
  .L0024AD2C:
    /* 14AD2C 0024AD2C 80181100 */  sll        $3, $17, 2
    /* 14AD30 0024AD30 21188300 */  addu       $3, $4, $3
    /* 14AD34 0024AD34 06000010 */  b          .L0024AD50
    /* 14AD38 0024AD38 42006290 */   lbu       $2, 0x42($3)
.align 2
  .L0024AD3C:
    /* 14AD3C 0024AD3C 80181100 */  sll        $3, $17, 2
    /* 14AD40 0024AD40 21188300 */  addu       $3, $4, $3
    /* 14AD44 0024AD44 02000010 */  b          .L0024AD50
    /* 14AD48 0024AD48 43006290 */   lbu       $2, 0x43($3)
.align 2
  .L0024AD4C:
    /* 14AD4C 0024AD4C 2D100000 */  daddu      $2, $0, $0
.align 2
  .L0024AD50:
    /* 14AD50 0024AD50 2000BFDF */  ld         $31, 0x20($29)
.align 2
  .L0024AD54:
    /* 14AD54 0024AD54 1000B1DF */  ld         $17, 0x10($29)
    /* 14AD58 0024AD58 0000B0DF */  ld         $16, 0x0($29)
    /* 14AD5C 0024AD5C 0800E003 */  jr         $31
    /* 14AD60 0024AD60 3000BD27 */   addiu     $29, $29, 0x30
endlabel scePadInfoComb
    /* 14AD64 0024AD64 00000000 */  nop
```
