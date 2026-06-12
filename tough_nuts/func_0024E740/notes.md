# func_0024E740 — parked

VRAM: 0x0024E740 (file_off 0x14E740)
Asm source: asm/aug6/nonmatchings/common/src/PObj/func_0024E740.s

## Attempt at 2026-06-12

**Reason parked:** recovered from cancelled bulk campaign (matched, unverified-in-TU); re-verify before integrating

**TU:** `common/src/PObj.c`

**Seed:** `tough_nuts/func_0024E740/func_0024E740.c`

Disassembly:

```
.align 3
nonmatching func_0024E740, 0x84

glabel func_0024E740
    /* 14E740 0024E740 E0FFBD27 */  addiu      $29, $29, -0x20
    /* 14E744 0024E744 0000B0FF */  sd         $16, 0x0($29)
    /* 14E748 0024E748 5500103C */  lui        $16, %hi(D_0054C89C)
    /* 14E74C 0024E74C 1000BFFF */  sd         $31, 0x10($29)
    /* 14E750 0024E750 9CC8028E */  lw         $2, %lo(D_0054C89C)($16)
    /* 14E754 0024E754 06004010 */  beqz       $2, .L0024E770
    /* 14E758 0024E758 2D288000 */   daddu     $5, $4, $0
    /* 14E75C 0024E75C 6300043C */  lui        $4, %hi(D_00628EA8)
    /* 14E760 0024E760 483A090C */  jal        func_0024E920
    /* 14E764 0024E764 A88E8424 */   addiu     $4, $4, %lo(D_00628EA8)
    /* 14E768 0024E768 12000010 */  b          .L0024E7B4
    /* 14E76C 0024E76C 9CC800AE */   sw        $0, %lo(D_0054C89C)($16)
.align 2
  .L0024E770:
    /* 14E770 0024E770 5500023C */  lui        $2, %hi(D_0054C92C)
    /* 14E774 0024E774 03000424 */  addiu      $4, $0, 0x3
    /* 14E778 0024E778 2CC9438C */  lw         $3, %lo(D_0054C92C)($2)
    /* 14E77C 0024E77C 07006414 */  bne        $3, $4, .L0024E79C
    /* 14E780 0024E780 5500023C */   lui       $2, %hi(D_0054C790)
    /* 14E784 0024E784 5500023C */  lui        $2, %hi(D_0054C784)
    /* 14E788 0024E788 FFFFA524 */  addiu      $5, $5, -0x1
    /* 14E78C 0024E78C 6C4F090C */  jal        func_00253DB0
    /* 14E790 0024E790 84C7448C */   lw        $4, %lo(D_0054C784)($2)
    /* 14E794 0024E794 07000010 */  b          .L0024E7B4
    /* 14E798 0024E798 9CC800AE */   sw        $0, %lo(D_0054C89C)($16)
.align 2
  .L0024E79C:
    /* 14E79C 0024E79C 5500033C */  lui        $3, %hi(D_0054C79C)
    /* 14E7A0 0024E7A0 FFFFA624 */  addiu      $6, $5, -0x1
    /* 14E7A4 0024E7A4 90C7448C */  lw         $4, %lo(D_0054C790)($2)
    /* 14E7A8 0024E7A8 B24F090C */  jal        func_00253EC8
    /* 14E7AC 0024E7AC 9CC7658C */   lw        $5, %lo(D_0054C79C)($3)
    /* 14E7B0 0024E7B0 9CC800AE */  sw         $0, %lo(D_0054C89C)($16)
.align 2
  .L0024E7B4:
    /* 14E7B4 0024E7B4 1000BFDF */  ld         $31, 0x10($29)
    /* 14E7B8 0024E7B8 0000B0DF */  ld         $16, 0x0($29)
    /* 14E7BC 0024E7BC 0800E003 */  jr         $31
    /* 14E7C0 0024E7C0 2000BD27 */   addiu     $29, $29, 0x20
endlabel func_0024E740
    /* 14E7C4 0024E7C4 00000000 */  nop
```
