# func_0013E8D8 — parked

VRAM: 0x0013E8D8 (file_off 0x03E8D8)
Asm source: asm/nonmatchings/isys/gobj/func_0013E8D8.s

## Attempt at 2026-05-31

**Reason parked:** crutch-removal: bucket A/B macros (ANCHOR,REG)

**TU:** `isys/gobj.c`

**Seed:** `tough_nuts/func_0013E8D8/func_0013E8D8.c`

Disassembly:

```
/* Symbols accessed via $gp register */
.extern D_00633CA0, 1
.extern D_00633CA4, 1

.align 3
nonmatching func_0013E8D8, 0x108

glabel func_0013E8D8
    /* 3E8D8 0013E8D8 B0FFBD27 */  addiu      $29, $29, -0x50
    /* 3E8DC 0013E8DC B4B3878F */  lw         $7, (D_00633CA4) /* gp_rel: (D_00633CA4) */
    /* 3E8E0 0013E8E0 2000B2FF */  sd         $18, 0x20($29)
    /* 3E8E4 0013E8E4 3000B3FF */  sd         $19, 0x30($29)
    /* 3E8E8 0013E8E8 2D908000 */  daddu      $18, $4, $0
    /* 3E8EC 0013E8EC 1000B1FF */  sd         $17, 0x10($29)
    /* 3E8F0 0013E8F0 2D98C000 */  daddu      $19, $6, $0
    /* 3E8F4 0013E8F4 4000BFFF */  sd         $31, 0x40($29)
    /* 3E8F8 0013E8F8 FF00B130 */  andi       $17, $5, 0xFF
    /* 3E8FC 0013E8FC 0000B0FF */  sd         $16, 0x0($29)
    /* 3E900 0013E900 0D00E010 */  beqz       $7, .L0013E938
    /* 3E904 0013E904 2D200000 */   daddu     $4, $0, $0
    /* 3E908 0013E908 B0B3838F */  lw         $3, (D_00633CA0) /* gp_rel: (D_00633CA0) */
    /* 3E90C 0013E90C 0000628C */  lw         $2, 0x0($3)
    /* 3E910 0013E910 09004010 */  beqz       $2, .L0013E938
    /* 3E914 0013E914 00000000 */   nop
    /* 3E918 0013E918 2D28E000 */  daddu      $5, $7, $0
    /* 3E91C 0013E91C 01008424 */  addiu      $4, $4, 0x1
.align 2
  .L0013E920:
    /* 3E920 0013E920 2B108500 */  sltu       $2, $4, $5
    /* 3E924 0013E924 04004010 */  beqz       $2, .L0013E938
    /* 3E928 0013E928 74016324 */   addiu     $3, $3, 0x174
    /* 3E92C 0013E92C 0000628C */  lw         $2, 0x0($3)
    /* 3E930 0013E930 FBFF4054 */  bnel       $2, $0, .L0013E920
    /* 3E934 0013E934 01008424 */   addiu     $4, $4, 0x1
.align 2
  .L0013E938:
    /* 3E938 0013E938 07008714 */  bne        $4, $7, .L0013E958
    /* 3E93C 0013E93C 74010224 */   addiu     $2, $0, 0x174
    /* 3E940 0013E940 5500043C */  lui        $4, %hi(D_00557A30)
    /* 3E944 0013E944 2D800000 */  daddu      $16, $0, $0
    /* 3E948 0013E948 8A9B060C */  jal        func_001A6E28
    /* 3E94C 0013E94C 307A8424 */   addiu     $4, $4, %lo(D_00557A30)
    /* 3E950 0013E950 07000010 */  b          .L0013E970
    /* 3E954 0013E954 00000000 */   nop
.align 2
  .L0013E958:
    /* 3E958 0013E958 B0B3838F */  lw         $3, (D_00633CA0) /* gp_rel: (D_00633CA0) */
    /* 3E95C 0013E95C 18108200 */  mult       $2, $4, $2
    /* 3E960 0013E960 21104300 */  addu       $2, $2, $3
    /* 3E964 0013E964 640140AC */  sw         $0, 0x164($2)
    /* 3E968 0013E968 2D804000 */  daddu      $16, $2, $0
    /* 3E96C 0013E96C 700140AC */  sw         $0, 0x170($2)
.align 2
  .L0013E970:
    /* 3E970 0013E970 06000056 */  bnel       $16, $0, .L0013E98C
    /* 3E974 0013E974 280012AE */   sw        $18, 0x28($16)
    /* 3E978 0013E978 5500043C */  lui        $4, %hi(D_00557A30)
    /* 3E97C 0013E97C 8A9B060C */  jal        func_001A6E28
    /* 3E980 0013E980 307A8424 */   addiu     $4, $4, %lo(D_00557A30)
    /* 3E984 0013E984 0F000010 */  b          .L0013E9C4
    /* 3E988 0013E988 2D100000 */   daddu     $2, $0, $0
.align 2
  .L0013E98C:
    /* 3E98C 0013E98C 2D282002 */  daddu      $5, $17, $0
    /* 3E990 0013E990 000010AE */  sw         $16, 0x0($16)
    /* 3E994 0013E994 2D306002 */  daddu      $6, $19, $0
    /* 3E998 0013E998 FCF7040C */  jal        func_0013DFF0
    /* 3E99C 0013E99C 2D200002 */   daddu     $4, $16, $0
    /* 3E9A0 0013E9A0 FFFF0324 */  addiu      $3, $0, -0x1
    /* 3E9A4 0013E9A4 5C0100AE */  sw         $0, 0x15C($16)
    /* 3E9A8 0013E9A8 040003AE */  sw         $3, 0x4($16)
    /* 3E9AC 0013E9AC 2D100002 */  daddu      $2, $16, $0
    /* 3E9B0 0013E9B0 080003AE */  sw         $3, 0x8($16)
    /* 3E9B4 0013E9B4 2C0000AE */  sw         $0, 0x2C($16)
    /* 3E9B8 0013E9B8 300000AE */  sw         $0, 0x30($16)
    /* 3E9BC 0013E9BC 580000AE */  sw         $0, 0x58($16)
    /* 3E9C0 0013E9C0 0C0000AE */  sw         $0, 0xC($16)
.align 2
  .L0013E9C4:
    /* 3E9C4 0013E9C4 4000BFDF */  ld         $31, 0x40($29)
    /* 3E9C8 0013E9C8 3000B3DF */  ld         $19, 0x30($29)
    /* 3E9CC 0013E9CC 2000B2DF */  ld         $18, 0x20($29)
    /* 3E9D0 0013E9D0 1000B1DF */  ld         $17, 0x10($29)
    /* 3E9D4 0013E9D4 0000B0DF */  ld         $16, 0x0($29)
    /* 3E9D8 0013E9D8 0800E003 */  jr         $31
    /* 3E9DC 0013E9DC 5000BD27 */   addiu     $29, $29, 0x50
endlabel func_0013E8D8
```
