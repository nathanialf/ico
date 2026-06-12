# func_0024AA38 — parked

VRAM: 0x0024AA38 (file_off 0x14AA38)
Asm source: asm/aug6/nonmatchings/common/src/PObj/func_0024AA38.s

## Attempt at 2026-06-12

**Reason parked:** recovered from cancelled bulk campaign (matched, unverified-in-TU); re-verify before integrating

**TU:** `common/src/PObj.c`

**Seed:** `tough_nuts/func_0024AA38/func_0024AA38.c`

Disassembly:

```
.align 3
nonmatching func_0024AA38, 0x64

glabel func_0024AA38
    /* 14AA38 0024AA38 2D388000 */  daddu      $7, $4, $0
    /* 14AA3C 0024AA3C 70000324 */  addiu      $3, $0, 0x70
    /* 14AA40 0024AA40 1C000424 */  addiu      $4, $0, 0x1C
    /* 14AA44 0024AA44 1818E370 */  mult1      $3, $7, $3
    /* 14AA48 0024AA48 1820A400 */  mult       $4, $5, $4
    /* 14AA4C 0024AA4C E0FFBD27 */  addiu      $29, $29, -0x20
    /* 14AA50 0024AA50 7100023C */  lui        $2, %hi(D_007112D0)
    /* 14AA54 0024AA54 0000B0FF */  sd         $16, 0x0($29)
    /* 14AA58 0024AA58 1000BFFF */  sd         $31, 0x10($29)
    /* 14AA5C 0024AA5C D0124224 */  addiu      $2, $2, %lo(D_007112D0)
    /* 14AA60 0024AA60 21208300 */  addu       $4, $4, $3
    /* 14AA64 0024AA64 21104400 */  addu       $2, $2, $4
    /* 14AA68 0024AA68 1000438C */  lw         $3, 0x10($2)
    /* 14AA6C 0024AA6C 03006014 */  bnez       $3, .L0024AA7C
    /* 14AA70 0024AA70 2D80C000 */   daddu     $16, $6, $0
    /* 14AA74 0024AA74 05000010 */  b          .L0024AA8C
    /* 14AA78 0024AA78 2D100000 */   daddu     $2, $0, $0
.align 2
  .L0024AA7C:
    /* 14AA7C 0024AA7C 162A090C */  jal        func_0024A858
    /* 14AA80 0024AA80 2D20E000 */   daddu     $4, $7, $0
    /* 14AA84 0024AA84 710050A0 */  sb         $16, 0x71($2)
    /* 14AA88 0024AA88 01000224 */  addiu      $2, $0, 0x1
.align 2
  .L0024AA8C:
    /* 14AA8C 0024AA8C 1000BFDF */  ld         $31, 0x10($29)
    /* 14AA90 0024AA90 0000B0DF */  ld         $16, 0x0($29)
    /* 14AA94 0024AA94 0800E003 */  jr         $31
    /* 14AA98 0024AA98 2000BD27 */   addiu     $29, $29, 0x20
endlabel func_0024AA38
    /* 14AA9C 0024AA9C 00000000 */  nop
```
