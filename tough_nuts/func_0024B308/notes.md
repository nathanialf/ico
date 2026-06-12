# func_0024B308 — parked

VRAM: 0x0024B308 (file_off 0x14B308)
Asm source: asm/aug6/nonmatchings/common/src/PObj/func_0024B308.s

## Attempt at 2026-06-12

**Reason parked:** recovered from cancelled bulk campaign (matched, unverified-in-TU); re-verify before integrating

**TU:** `common/src/PObj.c`

**Seed:** `tough_nuts/func_0024B308/func_0024B308.c`

Disassembly:

```
.align 3
nonmatching func_0024B308, 0x54

glabel func_0024B308
    /* 14B308 0024B308 2D308000 */  daddu      $6, $4, $0
    /* 14B30C 0024B30C 70000324 */  addiu      $3, $0, 0x70
    /* 14B310 0024B310 1C000424 */  addiu      $4, $0, 0x1C
    /* 14B314 0024B314 1818C370 */  mult1      $3, $6, $3
    /* 14B318 0024B318 1820A400 */  mult       $4, $5, $4
    /* 14B31C 0024B31C F0FFBD27 */  addiu      $29, $29, -0x10
    /* 14B320 0024B320 7100023C */  lui        $2, %hi(D_007112D0)
    /* 14B324 0024B324 0000BFFF */  sd         $31, 0x0($29)
    /* 14B328 0024B328 D0124224 */  addiu      $2, $2, %lo(D_007112D0)
    /* 14B32C 0024B32C 21208300 */  addu       $4, $4, $3
    /* 14B330 0024B330 21104400 */  addu       $2, $2, $4
    /* 14B334 0024B334 1000438C */  lw         $3, 0x10($2)
    /* 14B338 0024B338 03006014 */  bnez       $3, .L0024B348
    /* 14B33C 0024B33C 2D20C000 */   daddu     $4, $6, $0
    /* 14B340 0024B340 03000010 */  b          .L0024B350
    /* 14B344 0024B344 2D100000 */   daddu     $2, $0, $0
.align 2
  .L0024B348:
    /* 14B348 0024B348 682C090C */  jal        func_0024B1A0
    /* 14B34C 0024B34C 2D300000 */   daddu     $6, $0, $0
.align 2
  .L0024B350:
    /* 14B350 0024B350 0000BFDF */  ld         $31, 0x0($29)
    /* 14B354 0024B354 0800E003 */  jr         $31
    /* 14B358 0024B358 1000BD27 */   addiu     $29, $29, 0x10
endlabel func_0024B308
    /* 14B35C 0024B35C 00000000 */  nop
```
