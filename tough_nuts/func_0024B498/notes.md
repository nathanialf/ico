# func_0024B498 — parked

VRAM: 0x0024B498 (file_off 0x14B498)
Asm source: asm/aug6/nonmatchings/common/src/PObj/func_0024B498.s

## Attempt at 2026-06-12

**Reason parked:** recovered from cancelled bulk campaign (matched, unverified-in-TU); re-verify before integrating

**TU:** `common/src/PObj.c`

**Seed:** `tough_nuts/func_0024B498/func_0024B498.c`

Disassembly:

```
.align 3
nonmatching func_0024B498, 0x68

glabel func_0024B498
    /* 14B498 0024B498 D0FFBD27 */  addiu      $29, $29, -0x30
    /* 14B49C 0024B49C 7100023C */  lui        $2, %hi(D_007115C0)
    /* 14B4A0 0024B4A0 1000B0FF */  sd         $16, 0x10($29)
    /* 14B4A4 0024B4A4 0D000624 */  addiu      $6, $0, 0xD
    /* 14B4A8 0024B4A8 C0155024 */  addiu      $16, $2, %lo(D_007115C0)
    /* 14B4AC 0024B4AC 2000BFFF */  sd         $31, 0x20($29)
    /* 14B4B0 0024B4B0 040004AE */  sw         $4, 0x4($16)
    /* 14B4B4 0024B4B4 7100033C */  lui        $3, %hi(D_00711280)
    /* 14B4B8 0024B4B8 C01546AC */  sw         $6, %lo(D_007115C0)($2)
    /* 14B4BC 0024B4BC 01000524 */  addiu      $5, $0, 0x1
    /* 14B4C0 0024B4C0 80126424 */  addiu      $4, $3, %lo(D_00711280)
    /* 14B4C4 0024B4C4 0000A0AF */  sw         $0, 0x0($29)
    /* 14B4C8 0024B4C8 2D300000 */  daddu      $6, $0, $0
    /* 14B4CC 0024B4CC 2D380002 */  daddu      $7, $16, $0
    /* 14B4D0 0024B4D0 80000824 */  addiu      $8, $0, 0x80
    /* 14B4D4 0024B4D4 2D480002 */  daddu      $9, $16, $0
    /* 14B4D8 0024B4D8 80000A24 */  addiu      $10, $0, 0x80
    /* 14B4DC 0024B4DC 5E0A090C */  jal        func_00242978
    /* 14B4E0 0024B4E0 2D580000 */   daddu     $11, $0, $0
    /* 14B4E4 0024B4E4 02004304 */  bgezl      $2, .L0024B4F0
    /* 14B4E8 0024B4E8 0C00028E */   lw        $2, 0xC($16)
    /* 14B4EC 0024B4EC 2D100000 */  daddu      $2, $0, $0
.align 2
  .L0024B4F0:
    /* 14B4F0 0024B4F0 2000BFDF */  ld         $31, 0x20($29)
    /* 14B4F4 0024B4F4 1000B0DF */  ld         $16, 0x10($29)
    /* 14B4F8 0024B4F8 0800E003 */  jr         $31
    /* 14B4FC 0024B4FC 3000BD27 */   addiu     $29, $29, 0x30
endlabel func_0024B498
```
