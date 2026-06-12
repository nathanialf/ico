# func_0024B2B0 — parked

VRAM: 0x0024B2B0 (file_off 0x14B2B0)
Asm source: asm/aug6/nonmatchings/common/src/PObj/func_0024B2B0.s

## Attempt at 2026-06-12

**Reason parked:** recovered from cancelled bulk campaign (matched, unverified-in-TU); re-verify before integrating

**TU:** `common/src/PObj.c`

**Seed:** `tough_nuts/func_0024B2B0/func_0024B2B0.c`

Disassembly:

```
.align 3
nonmatching func_0024B2B0, 0x54

glabel func_0024B2B0
    /* 14B2B0 0024B2B0 2D308000 */  daddu      $6, $4, $0
    /* 14B2B4 0024B2B4 70000324 */  addiu      $3, $0, 0x70
    /* 14B2B8 0024B2B8 1C000424 */  addiu      $4, $0, 0x1C
    /* 14B2BC 0024B2BC 1818C370 */  mult1      $3, $6, $3
    /* 14B2C0 0024B2C0 1820A400 */  mult       $4, $5, $4
    /* 14B2C4 0024B2C4 F0FFBD27 */  addiu      $29, $29, -0x10
    /* 14B2C8 0024B2C8 7100023C */  lui        $2, %hi(D_007112D0)
    /* 14B2CC 0024B2CC 0000BFFF */  sd         $31, 0x0($29)
    /* 14B2D0 0024B2D0 D0124224 */  addiu      $2, $2, %lo(D_007112D0)
    /* 14B2D4 0024B2D4 21208300 */  addu       $4, $4, $3
    /* 14B2D8 0024B2D8 21104400 */  addu       $2, $2, $4
    /* 14B2DC 0024B2DC 1000438C */  lw         $3, 0x10($2)
    /* 14B2E0 0024B2E0 03006014 */  bnez       $3, .L0024B2F0
    /* 14B2E4 0024B2E4 2D20C000 */   daddu     $4, $6, $0
    /* 14B2E8 0024B2E8 03000010 */  b          .L0024B2F8
    /* 14B2EC 0024B2EC 2D100000 */   daddu     $2, $0, $0
.align 2
  .L0024B2F0:
    /* 14B2F0 0024B2F0 682C090C */  jal        func_0024B1A0
    /* 14B2F4 0024B2F4 FF0F0624 */   addiu     $6, $0, 0xFFF
.align 2
  .L0024B2F8:
    /* 14B2F8 0024B2F8 0000BFDF */  ld         $31, 0x0($29)
    /* 14B2FC 0024B2FC 0800E003 */  jr         $31
    /* 14B300 0024B300 1000BD27 */   addiu     $29, $29, 0x10
endlabel func_0024B2B0
    /* 14B304 0024B304 00000000 */  nop
```
