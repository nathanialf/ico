# func_0024A908 — parked

VRAM: 0x0024A908 (file_off 0x14A908)
Asm source: asm/aug6/nonmatchings/common/src/PObj/func_0024A908.s

## Attempt at 2026-06-12

**Reason parked:** recovered from cancelled bulk campaign (matched, unverified-in-TU); re-verify before integrating

**TU:** `common/src/PObj.c`

**Seed:** `tough_nuts/func_0024A908/func_0024A908.c`

Disassembly:

```
.align 3
nonmatching func_0024A908, 0x7C

glabel func_0024A908
    /* 14A908 0024A908 2D388000 */  daddu      $7, $4, $0
    /* 14A90C 0024A90C 70000324 */  addiu      $3, $0, 0x70
    /* 14A910 0024A910 1C000424 */  addiu      $4, $0, 0x1C
    /* 14A914 0024A914 1818E370 */  mult1      $3, $7, $3
    /* 14A918 0024A918 1820A400 */  mult       $4, $5, $4
    /* 14A91C 0024A91C D0FFBD27 */  addiu      $29, $29, -0x30
    /* 14A920 0024A920 7100023C */  lui        $2, %hi(D_007112D0)
    /* 14A924 0024A924 1000B1FF */  sd         $17, 0x10($29)
    /* 14A928 0024A928 2000BFFF */  sd         $31, 0x20($29)
    /* 14A92C 0024A92C D0124224 */  addiu      $2, $2, %lo(D_007112D0)
    /* 14A930 0024A930 0000B0FF */  sd         $16, 0x0($29)
    /* 14A934 0024A934 21208300 */  addu       $4, $4, $3
    /* 14A938 0024A938 21104400 */  addu       $2, $2, $4
    /* 14A93C 0024A93C 1000438C */  lw         $3, 0x10($2)
    /* 14A940 0024A940 03006014 */  bnez       $3, .L0024A950
    /* 14A944 0024A944 2D88C000 */   daddu     $17, $6, $0
    /* 14A948 0024A948 09000010 */  b          .L0024A970
    /* 14A94C 0024A94C 2D100000 */   daddu     $2, $0, $0
.align 2
  .L0024A950:
    /* 14A950 0024A950 162A090C */  jal        func_0024A858
    /* 14A954 0024A954 2D20E000 */   daddu     $4, $7, $0
    /* 14A958 0024A958 2D804000 */  daddu      $16, $2, $0
    /* 14A95C 0024A95C 2D202002 */  daddu      $4, $17, $0
    /* 14A960 0024A960 6000068E */  lw         $6, 0x60($16)
    /* 14A964 0024A964 2E81090C */  jal        func_002604B8
    /* 14A968 0024A968 2D280002 */   daddu     $5, $16, $0
    /* 14A96C 0024A96C 6000028E */  lw         $2, 0x60($16)
.align 2
  .L0024A970:
    /* 14A970 0024A970 2000BFDF */  ld         $31, 0x20($29)
    /* 14A974 0024A974 1000B1DF */  ld         $17, 0x10($29)
    /* 14A978 0024A978 0000B0DF */  ld         $16, 0x0($29)
    /* 14A97C 0024A97C 0800E003 */  jr         $31
    /* 14A980 0024A980 3000BD27 */   addiu     $29, $29, 0x30
endlabel func_0024A908
    /* 14A984 0024A984 00000000 */  nop
```
