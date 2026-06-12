# func_0024A8B8 — parked

VRAM: 0x0024A8B8 (file_off 0x14A8B8)
Asm source: asm/aug6/nonmatchings/common/src/PObj/func_0024A8B8.s

## Attempt at 2026-06-12

**Reason parked:** recovered from cancelled bulk campaign (matched, unverified-in-TU); re-verify before integrating

**TU:** `common/src/PObj.c`

**Seed:** `tough_nuts/func_0024A8B8/func_0024A8B8.c`

Disassembly:

```
.align 3
nonmatching func_0024A8B8, 0x50

glabel func_0024A8B8
    /* 14A8B8 0024A8B8 2D308000 */  daddu      $6, $4, $0
    /* 14A8BC 0024A8BC 70000324 */  addiu      $3, $0, 0x70
    /* 14A8C0 0024A8C0 1C000424 */  addiu      $4, $0, 0x1C
    /* 14A8C4 0024A8C4 1818C370 */  mult1      $3, $6, $3
    /* 14A8C8 0024A8C8 1820A400 */  mult       $4, $5, $4
    /* 14A8CC 0024A8CC F0FFBD27 */  addiu      $29, $29, -0x10
    /* 14A8D0 0024A8D0 7100023C */  lui        $2, %hi(D_007112D0)
    /* 14A8D4 0024A8D4 0000BFFF */  sd         $31, 0x0($29)
    /* 14A8D8 0024A8D8 D0124224 */  addiu      $2, $2, %lo(D_007112D0)
    /* 14A8DC 0024A8DC 21208300 */  addu       $4, $4, $3
    /* 14A8E0 0024A8E0 21104400 */  addu       $2, $2, $4
    /* 14A8E4 0024A8E4 1000438C */  lw         $3, 0x10($2)
    /* 14A8E8 0024A8E8 04006010 */  beqz       $3, .L0024A8FC
    /* 14A8EC 0024A8EC 2D100000 */   daddu     $2, $0, $0
    /* 14A8F0 0024A8F0 162A090C */  jal        func_0024A858
    /* 14A8F4 0024A8F4 2D20C000 */   daddu     $4, $6, $0
    /* 14A8F8 0024A8F8 5800428C */  lw         $2, 0x58($2)
.align 2
  .L0024A8FC:
    /* 14A8FC 0024A8FC 0000BFDF */  ld         $31, 0x0($29)
    /* 14A900 0024A900 0800E003 */  jr         $31
    /* 14A904 0024A904 1000BD27 */   addiu     $29, $29, 0x10
endlabel func_0024A8B8
```
