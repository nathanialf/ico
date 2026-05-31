# func_0013E9E0 — parked

VRAM: 0x0013E9E0 (file_off 0x03E9E0)
Asm source: asm/nonmatchings/isys/gobj/func_0013E9E0.s

## Attempt at 2026-05-31

**Reason parked:** crutch-removal: bucket A/B macros (ANCHOR,REG)

**TU:** `isys/gobj.c`

**Seed:** `tough_nuts/func_0013E9E0/func_0013E9E0.c`

Disassembly:

```
/* Symbols accessed via $gp register */
.extern D_00633CA0, 1
.extern D_00633CA4, 1

.align 3
nonmatching func_0013E9E0, 0x104

glabel func_0013E9E0
    /* 3E9E0 0013E9E0 B0FFBD27 */  addiu      $29, $29, -0x50
    /* 3E9E4 0013E9E4 B4B3878F */  lw         $7, (D_00633CA4) /* gp_rel: (D_00633CA4) */
    /* 3E9E8 0013E9E8 2000B2FF */  sd         $18, 0x20($29)
    /* 3E9EC 0013E9EC 3000B3FF */  sd         $19, 0x30($29)
    /* 3E9F0 0013E9F0 2D908000 */  daddu      $18, $4, $0
    /* 3E9F4 0013E9F4 1000B1FF */  sd         $17, 0x10($29)
    /* 3E9F8 0013E9F8 2D98C000 */  daddu      $19, $6, $0
    /* 3E9FC 0013E9FC 4000BFFF */  sd         $31, 0x40($29)
    /* 3EA00 0013EA00 FF00B130 */  andi       $17, $5, 0xFF
    /* 3EA04 0013EA04 0000B0FF */  sd         $16, 0x0($29)
    /* 3EA08 0013EA08 0D00E010 */  beqz       $7, .L0013EA40
    /* 3EA0C 0013EA0C 2D200000 */   daddu     $4, $0, $0
    /* 3EA10 0013EA10 B0B3838F */  lw         $3, (D_00633CA0) /* gp_rel: (D_00633CA0) */
    /* 3EA14 0013EA14 0000628C */  lw         $2, 0x0($3)
    /* 3EA18 0013EA18 09004010 */  beqz       $2, .L0013EA40
    /* 3EA1C 0013EA1C 00000000 */   nop
    /* 3EA20 0013EA20 2D28E000 */  daddu      $5, $7, $0
    /* 3EA24 0013EA24 01008424 */  addiu      $4, $4, 0x1
.align 2
  .L0013EA28:
    /* 3EA28 0013EA28 2B108500 */  sltu       $2, $4, $5
    /* 3EA2C 0013EA2C 04004010 */  beqz       $2, .L0013EA40
    /* 3EA30 0013EA30 74016324 */   addiu     $3, $3, 0x174
    /* 3EA34 0013EA34 0000628C */  lw         $2, 0x0($3)
    /* 3EA38 0013EA38 FBFF4054 */  bnel       $2, $0, .L0013EA28
    /* 3EA3C 0013EA3C 01008424 */   addiu     $4, $4, 0x1
.align 2
  .L0013EA40:
    /* 3EA40 0013EA40 07008714 */  bne        $4, $7, .L0013EA60
    /* 3EA44 0013EA44 74010224 */   addiu     $2, $0, 0x174
    /* 3EA48 0013EA48 5500043C */  lui        $4, %hi(D_00557A30)
    /* 3EA4C 0013EA4C 2D800000 */  daddu      $16, $0, $0
    /* 3EA50 0013EA50 8A9B060C */  jal        func_001A6E28
    /* 3EA54 0013EA54 307A8424 */   addiu     $4, $4, %lo(D_00557A30)
    /* 3EA58 0013EA58 07000010 */  b          .L0013EA78
    /* 3EA5C 0013EA5C 00000000 */   nop
.align 2
  .L0013EA60:
    /* 3EA60 0013EA60 B0B3838F */  lw         $3, (D_00633CA0) /* gp_rel: (D_00633CA0) */
    /* 3EA64 0013EA64 18108200 */  mult       $2, $4, $2
    /* 3EA68 0013EA68 21104300 */  addu       $2, $2, $3
    /* 3EA6C 0013EA6C 640140AC */  sw         $0, 0x164($2)
    /* 3EA70 0013EA70 2D804000 */  daddu      $16, $2, $0
    /* 3EA74 0013EA74 700140AC */  sw         $0, 0x170($2)
.align 2
  .L0013EA78:
    /* 3EA78 0013EA78 06000056 */  bnel       $16, $0, .L0013EA94
    /* 3EA7C 0013EA7C 280012AE */   sw        $18, 0x28($16)
    /* 3EA80 0013EA80 5500043C */  lui        $4, %hi(D_00557A30)
    /* 3EA84 0013EA84 8A9B060C */  jal        func_001A6E28
    /* 3EA88 0013EA88 307A8424 */   addiu     $4, $4, %lo(D_00557A30)
    /* 3EA8C 0013EA8C 0E000010 */  b          .L0013EAC8
    /* 3EA90 0013EA90 2D100000 */   daddu     $2, $0, $0
.align 2
  .L0013EA94:
    /* 3EA94 0013EA94 2D282002 */  daddu      $5, $17, $0
    /* 3EA98 0013EA98 000010AE */  sw         $16, 0x0($16)
    /* 3EA9C 0013EA9C 2D306002 */  daddu      $6, $19, $0
    /* 3EAA0 0013EAA0 30F8040C */  jal        func_0013E0C0
    /* 3EAA4 0013EAA4 2D200002 */   daddu     $4, $16, $0
    /* 3EAA8 0013EAA8 FFFF0324 */  addiu      $3, $0, -0x1
    /* 3EAAC 0013EAAC 5C0100AE */  sw         $0, 0x15C($16)
    /* 3EAB0 0013EAB0 040003AE */  sw         $3, 0x4($16)
    /* 3EAB4 0013EAB4 2D100002 */  daddu      $2, $16, $0
    /* 3EAB8 0013EAB8 080003AE */  sw         $3, 0x8($16)
    /* 3EABC 0013EABC 2C0000AE */  sw         $0, 0x2C($16)
    /* 3EAC0 0013EAC0 300000AE */  sw         $0, 0x30($16)
    /* 3EAC4 0013EAC4 580000AE */  sw         $0, 0x58($16)
.align 2
  .L0013EAC8:
    /* 3EAC8 0013EAC8 4000BFDF */  ld         $31, 0x40($29)
    /* 3EACC 0013EACC 3000B3DF */  ld         $19, 0x30($29)
    /* 3EAD0 0013EAD0 2000B2DF */  ld         $18, 0x20($29)
    /* 3EAD4 0013EAD4 1000B1DF */  ld         $17, 0x10($29)
    /* 3EAD8 0013EAD8 0000B0DF */  ld         $16, 0x0($29)
    /* 3EADC 0013EADC 0800E003 */  jr         $31
    /* 3EAE0 0013EAE0 5000BD27 */   addiu     $29, $29, 0x50
endlabel func_0013E9E0
    /* 3EAE4 0013EAE4 00000000 */  nop
```
