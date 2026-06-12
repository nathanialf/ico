# func_0024B010 — parked

VRAM: 0x0024B010 (file_off 0x14B010)
Asm source: asm/aug6/nonmatchings/common/src/PObj/func_0024B010.s

## Attempt at 2026-06-12

**Reason parked:** recovered from cancelled bulk campaign (near-miss); re-verify before integrating

**TU:** `common/src/PObj.c`

**Seed:** `tough_nuts/func_0024B010/func_0024B010.c`

Disassembly:

```
.align 3
nonmatching func_0024B010, 0xD8

glabel func_0024B010
    /* 14B010 0024B010 B0FFBD27 */  addiu      $29, $29, -0x50
    /* 14B014 0024B014 7100033C */  lui        $3, %hi(D_007115C0)
    /* 14B018 0024B018 3000B2FF */  sd         $18, 0x30($29)
    /* 14B01C 0024B01C 08000224 */  addiu      $2, $0, 0x8
    /* 14B020 0024B020 2000B1FF */  sd         $17, 0x20($29)
    /* 14B024 0024B024 2D908000 */  daddu      $18, $4, $0
    /* 14B028 0024B028 1000B0FF */  sd         $16, 0x10($29)
    /* 14B02C 0024B02C 2D88A000 */  daddu      $17, $5, $0
    /* 14B030 0024B030 C0157024 */  addiu      $16, $3, %lo(D_007115C0)
    /* 14B034 0024B034 4000BFFF */  sd         $31, 0x40($29)
    /* 14B038 0024B038 C01562AC */  sw         $2, %lo(D_007115C0)($3)
    /* 14B03C 0024B03C 0C000726 */  addiu      $7, $16, 0xC
    /* 14B040 0024B040 040012AE */  sw         $18, 0x4($16)
    /* 14B044 0024B044 2D280000 */  daddu      $5, $0, $0
    /* 14B048 0024B048 080011AE */  sw         $17, 0x8($16)
    /* 14B04C 0024B04C 00000000 */  nop
.align 2
  .L0024B050:
    /* 14B050 0024B050 2110C500 */  addu       $2, $6, $5
    /* 14B054 0024B054 2120E500 */  addu       $4, $7, $5
    /* 14B058 0024B058 00004390 */  lbu        $3, 0x0($2)
    /* 14B05C 0024B05C 0100A524 */  addiu      $5, $5, 0x1
    /* 14B060 0024B060 0600A228 */  slti       $2, $5, 0x6
    /* 14B064 0024B064 000083A0 */  sb         $3, 0x0($4)
    /* 14B068 0024B068 F9FF4014 */  bnez       $2, .L0024B050
    /* 14B06C 0024B06C 00000000 */   nop
    /* 14B070 0024B070 7100043C */  lui        $4, %hi(D_00711280)
    /* 14B074 0024B074 0000A0AF */  sw         $0, 0x0($29)
    /* 14B078 0024B078 80128424 */  addiu      $4, $4, %lo(D_00711280)
    /* 14B07C 0024B07C 01000524 */  addiu      $5, $0, 0x1
    /* 14B080 0024B080 2D300000 */  daddu      $6, $0, $0
    /* 14B084 0024B084 2D380002 */  daddu      $7, $16, $0
    /* 14B088 0024B088 80000824 */  addiu      $8, $0, 0x80
    /* 14B08C 0024B08C 2D480002 */  daddu      $9, $16, $0
    /* 14B090 0024B090 80000A24 */  addiu      $10, $0, 0x80
    /* 14B094 0024B094 5E0A090C */  jal        func_00242978
    /* 14B098 0024B098 2D580000 */   daddu     $11, $0, $0
    /* 14B09C 0024B09C 03004304 */  bgezl      $2, .L0024B0AC
    /* 14B0A0 0024B0A0 1400038E */   lw        $3, 0x14($16)
    /* 14B0A4 0024B0A4 0A000010 */  b          .L0024B0D0
    /* 14B0A8 0024B0A8 2D100000 */   daddu     $2, $0, $0
.align 2
  .L0024B0AC:
    /* 14B0AC 0024B0AC 01000224 */  addiu      $2, $0, 0x1
    /* 14B0B0 0024B0B0 07006214 */  bne        $3, $2, .L0024B0D0
    /* 14B0B4 0024B0B4 2D106000 */   daddu     $2, $3, $0
    /* 14B0B8 0024B0B8 2D204002 */  daddu      $4, $18, $0
    /* 14B0BC 0024B0BC 2D282002 */  daddu      $5, $17, $0
    /* 14B0C0 0024B0C0 8E2A090C */  jal        func_0024AA38
    /* 14B0C4 0024B0C4 02000624 */   addiu     $6, $0, 0x2
    /* 14B0C8 0024B0C8 1400038E */  lw         $3, 0x14($16)
    /* 14B0CC 0024B0CC 2D106000 */  daddu      $2, $3, $0
.align 2
  .L0024B0D0:
    /* 14B0D0 0024B0D0 4000BFDF */  ld         $31, 0x40($29)
    /* 14B0D4 0024B0D4 3000B2DF */  ld         $18, 0x30($29)
    /* 14B0D8 0024B0D8 2000B1DF */  ld         $17, 0x20($29)
    /* 14B0DC 0024B0DC 1000B0DF */  ld         $16, 0x10($29)
    /* 14B0E0 0024B0E0 0800E003 */  jr         $31
    /* 14B0E4 0024B0E4 5000BD27 */   addiu     $29, $29, 0x50
endlabel func_0024B010
```
