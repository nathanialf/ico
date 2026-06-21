# func_0025A968 — parked

VRAM: 0x0025A968 (file_off 0x15A968)
Asm source: asm/aug6/nonmatchings/common/src/PObj/func_0025A968.s

## Attempt at 2026-06-21

**Reason parked:** override=permute

**TU:** `common/src/PObj.c`

**Seed:** `tough_nuts/func_0025A968/func_0025A968.c`

Disassembly:

```
.align 3
nonmatching func_0025A968, 0x128

glabel func_0025A968
    /* 15A968 0025A968 90FFBD27 */  addiu      $29, $29, -0x70
    /* 15A96C 0025A96C 5800B5E7 */  swc1       $f21, 0x58($29)
    /* 15A970 0025A970 5000B4E7 */  swc1       $f20, 0x50($29)
    /* 15A974 0025A974 466D0046 */  mov.s      $f21, $f13
    /* 15A978 0025A978 3000B0FF */  sd         $16, 0x30($29)
    /* 15A97C 0025A97C 6000B6E7 */  swc1       $f22, 0x60($29)
    /* 15A980 0025A980 4000BFFF */  sd         $31, 0x40($29)
    /* 15A984 0025A984 E86C090C */  jal        func_0025B3A0
    /* 15A988 0025A988 06650046 */   mov.s     $f20, $f12
    /* 15A98C 0025A98C 6300023C */  lui        $2, %hi(D_00629998)
    /* 15A990 0025A990 9899508C */  lw         $16, %lo(D_00629998)($2)
    /* 15A994 0025A994 FFFF0324 */  addiu      $3, $0, -0x1
    /* 15A998 0025A998 35000312 */  beq        $16, $3, .L0025AA70
    /* 15A99C 0025A99C 86050046 */   mov.s     $f22, $f0
    /* 15A9A0 0025A9A0 5E73090C */  jal        func_0025CD78
    /* 15A9A4 0025A9A4 06AB0046 */   mov.s     $f12, $f21
    /* 15A9A8 0025A9A8 32004014 */  bnez       $2, .L0025AA74
    /* 15A9AC 0025A9AC 06B00046 */   mov.s     $f0, $f22
    /* 15A9B0 0025A9B0 5E73090C */  jal        func_0025CD78
    /* 15A9B4 0025A9B4 06A30046 */   mov.s     $f12, $f20
    /* 15A9B8 0025A9B8 2E004014 */  bnez       $2, .L0025AA74
    /* 15A9BC 0025A9BC 06B00046 */   mov.s     $f0, $f22
    /* 15A9C0 0025A9C0 00008044 */  mtc1       $0, $f0
    /* 15A9C4 0025A9C4 32A80046 */  c.eq.s     $f21, $f0
    /* 15A9C8 0025A9C8 00000000 */  nop
    /* 15A9CC 0025A9CC 29000245 */  bc1fl      .L0025AA74
    /* 15A9D0 0025A9D0 06B00046 */   mov.s     $f0, $f22
    /* 15A9D4 0025A9D4 32A00046 */  c.eq.s     $f20, $f0
    /* 15A9D8 0025A9D8 00000000 */  nop
    /* 15A9DC 0025A9DC 25000045 */  bc1f       .L0025AA74
    /* 15A9E0 0025A9E0 06B00046 */   mov.s     $f0, $f22
    /* 15A9E4 0025A9E4 D080090C */  jal        func_00260340
    /* 15A9E8 0025A9E8 06A30046 */   mov.s     $f12, $f20
    /* 15A9EC 0025A9EC 06AB0046 */  mov.s      $f12, $f21
    /* 15A9F0 0025A9F0 D080090C */  jal        func_00260340
    /* 15A9F4 0025A9F4 0800A2FF */   sd        $2, 0x8($29)
    /* 15A9F8 0025A9F8 1000A2FF */  sd         $2, 0x10($29)
    /* 15A9FC 0025A9FC 6300033C */  lui        $3, %hi(D_00629490)
    /* 15AA00 0025AA00 2D100000 */  daddu      $2, $0, $0
    /* 15AA04 0025AA04 01000424 */  addiu      $4, $0, 0x1
    /* 15AA08 0025AA08 90946324 */  addiu      $3, $3, %lo(D_00629490)
    /* 15AA0C 0025AA0C 1800A2FF */  sd         $2, 0x18($29)
    /* 15AA10 0025AA10 0000A4AF */  sw         $4, 0x0($29)
    /* 15AA14 0025AA14 02000224 */  addiu      $2, $0, 0x2
    /* 15AA18 0025AA18 0400A3AF */  sw         $3, 0x4($29)
    /* 15AA1C 0025AA1C 05000212 */  beq        $16, $2, .L0025AA34
    /* 15AA20 0025AA20 2000A0AF */   sw        $0, 0x20($29)
    /* 15AA24 0025AA24 6872090C */  jal        func_0025C9A0
    /* 15AA28 0025AA28 2D20A003 */   daddu     $4, $29, $0
    /* 15AA2C 0025AA2C 06004014 */  bnez       $2, .L0025AA48
    /* 15AA30 0025AA30 2000A28F */   lw        $2, 0x20($29)
.align 2
  .L0025AA34:
    /* 15AA34 0025AA34 F880090C */  jal        func_002603E0
    /* 15AA38 0025AA38 00000000 */   nop
    /* 15AA3C 0025AA3C 21000324 */  addiu      $3, $0, 0x21
    /* 15AA40 0025AA40 000043AC */  sw         $3, 0x0($2)
    /* 15AA44 0025AA44 2000A28F */  lw         $2, 0x20($29)
.align 2
  .L0025AA48:
    /* 15AA48 0025AA48 05004010 */  beqz       $2, .L0025AA60
    /* 15AA4C 0025AA4C 00000000 */   nop
    /* 15AA50 0025AA50 F880090C */  jal        func_002603E0
    /* 15AA54 0025AA54 00000000 */   nop
    /* 15AA58 0025AA58 2000A38F */  lw         $3, 0x20($29)
    /* 15AA5C 0025AA5C 000043AC */  sw         $3, 0x0($2)
.align 2
  .L0025AA60:
    /* 15AA60 0025AA60 D27D090C */  jal        func_0025F748
    /* 15AA64 0025AA64 1800A4DF */   ld        $4, 0x18($29)
    /* 15AA68 0025AA68 03000010 */  b          .L0025AA78
    /* 15AA6C 0025AA6C 4000BFDF */   ld        $31, 0x40($29)
.align 2
  .L0025AA70:
    /* 15AA70 0025AA70 06B00046 */  mov.s      $f0, $f22
.align 2
  .L0025AA74:
    /* 15AA74 0025AA74 4000BFDF */  ld         $31, 0x40($29)
.align 2
  .L0025AA78:
    /* 15AA78 0025AA78 3000B0DF */  ld         $16, 0x30($29)
    /* 15AA7C 0025AA7C 6000B6C7 */  lwc1       $f22, 0x60($29)
    /* 15AA80 0025AA80 5800B5C7 */  lwc1       $f21, 0x58($29)
    /* 15AA84 0025AA84 5000B4C7 */  lwc1       $f20, 0x50($29)
    /* 15AA88 0025AA88 0800E003 */  jr         $31
    /* 15AA8C 0025AA8C 7000BD27 */   addiu     $29, $29, 0x70
endlabel func_0025A968
```
