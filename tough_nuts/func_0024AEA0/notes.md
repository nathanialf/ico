# func_0024AEA0 — parked

VRAM: 0x0024AEA0 (file_off 0x14AEA0)
Asm source: asm/aug6/nonmatchings/common/src/PObj/func_0024AEA0.s

## Attempt at 2026-06-12

**Reason parked:** recovered from cancelled bulk campaign (matched, unverified-in-TU); re-verify before integrating

**TU:** `common/src/PObj.c`

**Seed:** `tough_nuts/func_0024AEA0/func_0024AEA0.c`

Disassembly:

```
.align 3
nonmatching func_0024AEA0, 0xB4

glabel func_0024AEA0
    /* 14AEA0 0024AEA0 B0FFBD27 */  addiu      $29, $29, -0x50
    /* 14AEA4 0024AEA4 7100033C */  lui        $3, %hi(D_007115C0)
    /* 14AEA8 0024AEA8 1000B0FF */  sd         $16, 0x10($29)
    /* 14AEAC 0024AEAC 06000224 */  addiu      $2, $0, 0x6
    /* 14AEB0 0024AEB0 C0157024 */  addiu      $16, $3, %lo(D_007115C0)
    /* 14AEB4 0024AEB4 3000B2FF */  sd         $18, 0x30($29)
    /* 14AEB8 0024AEB8 2000B1FF */  sd         $17, 0x20($29)
    /* 14AEBC 0024AEBC 2D908000 */  daddu      $18, $4, $0
    /* 14AEC0 0024AEC0 4000BFFF */  sd         $31, 0x40($29)
    /* 14AEC4 0024AEC4 2D88A000 */  daddu      $17, $5, $0
    /* 14AEC8 0024AEC8 0C0006AE */  sw         $6, 0xC($16)
    /* 14AECC 0024AECC 7100043C */  lui        $4, %hi(D_00711280)
    /* 14AED0 0024AED0 100007AE */  sw         $7, 0x10($16)
    /* 14AED4 0024AED4 80128424 */  addiu      $4, $4, %lo(D_00711280)
    /* 14AED8 0024AED8 C01562AC */  sw         $2, %lo(D_007115C0)($3)
    /* 14AEDC 0024AEDC 01000524 */  addiu      $5, $0, 0x1
    /* 14AEE0 0024AEE0 040012AE */  sw         $18, 0x4($16)
    /* 14AEE4 0024AEE4 2D300000 */  daddu      $6, $0, $0
    /* 14AEE8 0024AEE8 080011AE */  sw         $17, 0x8($16)
    /* 14AEEC 0024AEEC 2D380002 */  daddu      $7, $16, $0
    /* 14AEF0 0024AEF0 0000A0AF */  sw         $0, 0x0($29)
    /* 14AEF4 0024AEF4 80000824 */  addiu      $8, $0, 0x80
    /* 14AEF8 0024AEF8 2D480002 */  daddu      $9, $16, $0
    /* 14AEFC 0024AEFC 80000A24 */  addiu      $10, $0, 0x80
    /* 14AF00 0024AF00 5E0A090C */  jal        func_00242978
    /* 14AF04 0024AF04 2D580000 */   daddu     $11, $0, $0
    /* 14AF08 0024AF08 03004304 */  bgezl      $2, .L0024AF18
    /* 14AF0C 0024AF0C 1400038E */   lw        $3, 0x14($16)
    /* 14AF10 0024AF10 0A000010 */  b          .L0024AF3C
    /* 14AF14 0024AF14 2D100000 */   daddu     $2, $0, $0
.align 2
  .L0024AF18:
    /* 14AF18 0024AF18 01000224 */  addiu      $2, $0, 0x1
    /* 14AF1C 0024AF1C 07006214 */  bne        $3, $2, .L0024AF3C
    /* 14AF20 0024AF20 2D106000 */   daddu     $2, $3, $0
    /* 14AF24 0024AF24 2D204002 */  daddu      $4, $18, $0
    /* 14AF28 0024AF28 2D282002 */  daddu      $5, $17, $0
    /* 14AF2C 0024AF2C 8E2A090C */  jal        func_0024AA38
    /* 14AF30 0024AF30 02000624 */   addiu     $6, $0, 0x2
    /* 14AF34 0024AF34 1400038E */  lw         $3, 0x14($16)
    /* 14AF38 0024AF38 2D106000 */  daddu      $2, $3, $0
.align 2
  .L0024AF3C:
    /* 14AF3C 0024AF3C 4000BFDF */  ld         $31, 0x40($29)
    /* 14AF40 0024AF40 3000B2DF */  ld         $18, 0x30($29)
    /* 14AF44 0024AF44 2000B1DF */  ld         $17, 0x20($29)
    /* 14AF48 0024AF48 1000B0DF */  ld         $16, 0x10($29)
    /* 14AF4C 0024AF4C 0800E003 */  jr         $31
    /* 14AF50 0024AF50 5000BD27 */   addiu     $29, $29, 0x50
endlabel func_0024AEA0
    /* 14AF54 0024AF54 00000000 */  nop
```
