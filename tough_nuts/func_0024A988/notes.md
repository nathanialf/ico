# func_0024A988 — parked

VRAM: 0x0024A988 (file_off 0x14A988)
Asm source: asm/aug6/nonmatchings/common/src/PObj/func_0024A988.s

## Attempt at 2026-06-12

**Reason parked:** recovered from cancelled bulk campaign (near-miss); re-verify before integrating

**TU:** `common/src/PObj.c`

**Seed:** `tough_nuts/func_0024A988/func_0024A988.c`

Disassembly:

```
.align 3
nonmatching func_0024A988, 0x78

glabel func_0024A988
    /* 14A988 0024A988 2D308000 */  daddu      $6, $4, $0
    /* 14A98C 0024A98C 70000324 */  addiu      $3, $0, 0x70
    /* 14A990 0024A990 1C000424 */  addiu      $4, $0, 0x1C
    /* 14A994 0024A994 1818C370 */  mult1      $3, $6, $3
    /* 14A998 0024A998 1820A400 */  mult       $4, $5, $4
    /* 14A99C 0024A99C F0FFBD27 */  addiu      $29, $29, -0x10
    /* 14A9A0 0024A9A0 7100023C */  lui        $2, %hi(D_007112D0)
    /* 14A9A4 0024A9A4 0000BFFF */  sd         $31, 0x0($29)
    /* 14A9A8 0024A9A8 D0124224 */  addiu      $2, $2, %lo(D_007112D0)
    /* 14A9AC 0024A9AC 21208300 */  addu       $4, $4, $3
    /* 14A9B0 0024A9B0 21104400 */  addu       $2, $2, $4
    /* 14A9B4 0024A9B4 1000438C */  lw         $3, 0x10($2)
    /* 14A9B8 0024A9B8 0E006010 */  beqz       $3, .L0024A9F4
    /* 14A9BC 0024A9BC 63000224 */   addiu     $2, $0, 0x63
    /* 14A9C0 0024A9C0 162A090C */  jal        func_0024A858
    /* 14A9C4 0024A9C4 2D20C000 */   daddu     $4, $6, $0
    /* 14A9C8 0024A9C8 2D204000 */  daddu      $4, $2, $0
    /* 14A9CC 0024A9CC 06000324 */  addiu      $3, $0, 0x6
    /* 14A9D0 0024A9D0 70008290 */  lbu        $2, 0x70($4)
    /* 14A9D4 0024A9D4 08004314 */  bne        $2, $3, .L0024A9F8
    /* 14A9D8 0024A9D8 0000BFDF */   ld        $31, 0x0($29)
    /* 14A9DC 0024A9DC 71008390 */  lbu        $3, 0x71($4)
    /* 14A9E0 0024A9E0 02000224 */  addiu      $2, $0, 0x2
    /* 14A9E4 0024A9E4 04006254 */  bnel       $3, $2, .L0024A9F8
    /* 14A9E8 0024A9E8 70008290 */   lbu       $2, 0x70($4)
    /* 14A9EC 0024A9EC 02000010 */  b          .L0024A9F8
    /* 14A9F0 0024A9F0 05000224 */   addiu     $2, $0, 0x5
.align 2
  .L0024A9F4:
    /* 14A9F4 0024A9F4 0000BFDF */  ld         $31, 0x0($29)
.align 2
  .L0024A9F8:
    /* 14A9F8 0024A9F8 0800E003 */  jr         $31
    /* 14A9FC 0024A9FC 1000BD27 */   addiu     $29, $29, 0x10
endlabel func_0024A988
```
