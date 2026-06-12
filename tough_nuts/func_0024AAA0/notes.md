# func_0024AAA0 — parked

VRAM: 0x0024AAA0 (file_off 0x14AAA0)
Asm source: asm/aug6/nonmatchings/common/src/PObj/func_0024AAA0.s

## Attempt at 2026-06-12

**Reason parked:** recovered from cancelled bulk campaign (matched, unverified-in-TU); re-verify before integrating

**TU:** `common/src/PObj.c`

**Seed:** `tough_nuts/func_0024AAA0/func_0024AAA0.c`

Disassembly:

```
.align 3
nonmatching func_0024AAA0, 0x50

glabel func_0024AAA0
    /* 14AAA0 0024AAA0 2D308000 */  daddu      $6, $4, $0
    /* 14AAA4 0024AAA4 70000324 */  addiu      $3, $0, 0x70
    /* 14AAA8 0024AAA8 1C000424 */  addiu      $4, $0, 0x1C
    /* 14AAAC 0024AAAC 1818C370 */  mult1      $3, $6, $3
    /* 14AAB0 0024AAB0 1820A400 */  mult       $4, $5, $4
    /* 14AAB4 0024AAB4 F0FFBD27 */  addiu      $29, $29, -0x10
    /* 14AAB8 0024AAB8 7100023C */  lui        $2, %hi(D_007112D0)
    /* 14AABC 0024AABC 0000BFFF */  sd         $31, 0x0($29)
    /* 14AAC0 0024AAC0 D0124224 */  addiu      $2, $2, %lo(D_007112D0)
    /* 14AAC4 0024AAC4 21208300 */  addu       $4, $4, $3
    /* 14AAC8 0024AAC8 21104400 */  addu       $2, $2, $4
    /* 14AACC 0024AACC 1000438C */  lw         $3, 0x10($2)
    /* 14AAD0 0024AAD0 04006010 */  beqz       $3, .L0024AAE4
    /* 14AAD4 0024AAD4 2D100000 */   daddu     $2, $0, $0
    /* 14AAD8 0024AAD8 162A090C */  jal        func_0024A858
    /* 14AADC 0024AADC 2D20C000 */   daddu     $4, $6, $0
    /* 14AAE0 0024AAE0 71004290 */  lbu        $2, 0x71($2)
.align 2
  .L0024AAE4:
    /* 14AAE4 0024AAE4 0000BFDF */  ld         $31, 0x0($29)
    /* 14AAE8 0024AAE8 0800E003 */  jr         $31
    /* 14AAEC 0024AAEC 1000BD27 */   addiu     $29, $29, 0x10
endlabel func_0024AAA0
```
