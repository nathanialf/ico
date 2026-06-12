# func_00262D00 — parked

VRAM: 0x00262D00 (file_off 0x162D00)
Asm source: asm/aug6/nonmatchings/common/src/PObj/func_00262D00.s

## Attempt at 2026-06-12

**Reason parked:** recovered from cancelled bulk campaign (matched, unverified-in-TU); re-verify before integrating

**TU:** `common/src/PObj.c`

**Seed:** `tough_nuts/func_00262D00/func_00262D00.c`

Disassembly:

```
.align 3
nonmatching func_00262D00, 0x78

glabel func_00262D00
    /* 162D00 00262D00 C0FFBD27 */  addiu      $29, $29, -0x40
    /* 162D04 00262D04 2000B2FF */  sd         $18, 0x20($29)
    /* 162D08 00262D08 1000B1FF */  sd         $17, 0x10($29)
    /* 162D0C 00262D0C 2D90C000 */  daddu      $18, $6, $0
    /* 162D10 00262D10 0000B0FF */  sd         $16, 0x0($29)
    /* 162D14 00262D14 3000BFFF */  sd         $31, 0x30($29)
    /* 162D18 00262D18 2D808000 */  daddu      $16, $4, $0
    /* 162D1C 00262D1C 5400038E */  lw         $3, 0x54($16)
    /* 162D20 00262D20 05006014 */  bnez       $3, .L00262D38
    /* 162D24 00262D24 2D88A000 */   daddu     $17, $5, $0
    /* 162D28 00262D28 5500023C */  lui        $2, %hi(D_0054D504)
    /* 162D2C 00262D2C 04D5438C */  lw         $3, %lo(D_0054D504)($2)
    /* 162D30 00262D30 540003AE */  sw         $3, 0x54($16)
    /* 162D34 00262D34 00000000 */  nop
.align 2
  .L00262D38:
    /* 162D38 00262D38 3800628C */  lw         $2, 0x38($3)
    /* 162D3C 00262D3C 04004054 */  bnel       $2, $0, .L00262D50
    /* 162D40 00262D40 5400048E */   lw        $4, 0x54($16)
    /* 162D44 00262D44 649A090C */  jal        func_00266990
    /* 162D48 00262D48 2D206000 */   daddu     $4, $3, $0
    /* 162D4C 00262D4C 5400048E */  lw         $4, 0x54($16)
.align 2
  .L00262D50:
    /* 162D50 00262D50 2D280002 */  daddu      $5, $16, $0
    /* 162D54 00262D54 2D302002 */  daddu      $6, $17, $0
    /* 162D58 00262D58 5E8B090C */  jal        func_00262D78
    /* 162D5C 00262D5C 2D384002 */   daddu     $7, $18, $0
    /* 162D60 00262D60 3000BFDF */  ld         $31, 0x30($29)
    /* 162D64 00262D64 2000B2DF */  ld         $18, 0x20($29)
    /* 162D68 00262D68 1000B1DF */  ld         $17, 0x10($29)
    /* 162D6C 00262D6C 0000B0DF */  ld         $16, 0x0($29)
    /* 162D70 00262D70 0800E003 */  jr         $31
    /* 162D74 00262D74 4000BD27 */   addiu     $29, $29, 0x40
endlabel func_00262D00
```
