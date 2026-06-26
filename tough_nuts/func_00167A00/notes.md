# func_00167A00 — parked

VRAM: 0x00167A00 (file_off 0x067A00)
Asm source: asm/aug6/nonmatchings/fumi/src/fuzio/func_00167A00.s

## Attempt at 2026-06-26

**Reason parked:** plateau: 30 distinct hand hypotheses, no real_count progress (best=6). PARK the seed, then fire ONE bounded permuter shot on it (REFERENCE Step 4); harvest by true real_count and adopt any improvement (resolution b only if nothing beats best).

**TU:** `fumi/src/fuzio.c`

**Seed:** `tough_nuts/func_00167A00/func_00167A00.c`

Disassembly:

```
.align 3
nonmatching func_00167A00, 0x148

glabel func_00167A00
    /* 67A00 00167A00 70FFBD27 */  addiu      $29, $29, -0x90
    /* 67A04 00167A04 2CB4878F */  lw         $7, %gp_rel(D_0062C01C)($28)
    /* 67A08 00167A08 4000B4FF */  sd         $20, 0x40($29)
    /* 67A0C 00167A0C 6000B6FF */  sd         $22, 0x60($29)
    /* 67A10 00167A10 2DA0C000 */  daddu      $20, $6, $0
    /* 67A14 00167A14 5000B5FF */  sd         $21, 0x50($29)
    /* 67A18 00167A18 2D300000 */  daddu      $6, $0, $0
    /* 67A1C 00167A1C 2000B2FF */  sd         $18, 0x20($29)
    /* 67A20 00167A20 2DA8A000 */  daddu      $21, $5, $0
    /* 67A24 00167A24 8000BFFF */  sd         $31, 0x80($29)
    /* 67A28 00167A28 2D908000 */  daddu      $18, $4, $0
    /* 67A2C 00167A2C 7000B7FF */  sd         $23, 0x70($29)
    /* 67A30 00167A30 2DB00000 */  daddu      $22, $0, $0
    /* 67A34 00167A34 3000B3FF */  sd         $19, 0x30($29)
    /* 67A38 00167A38 1000B1FF */  sd         $17, 0x10($29)
    /* 67A3C 00167A3C 3600E018 */  blez       $7, .L00167B18
    /* 67A40 00167A40 0000B0FF */   sd        $16, 0x0($29)
    /* 67A44 00167A44 6A00173C */  lui        $23, %hi(D_006A4B40)
    /* 67A48 00167A48 404BE226 */  addiu      $2, $23, %lo(D_006A4B40)
    /* 67A4C 00167A4C 00000000 */  nop
.align 2
  .L00167A50:
    /* 67A50 00167A50 40180600 */  sll        $3, $6, 1
    /* 67A54 00167A54 21186200 */  addu       $3, $3, $2
    /* 67A58 00167A58 30B4858F */  lw         $5, %gp_rel(D_0062C020)($28)
    /* 67A5C 00167A5C 00006284 */  lh         $2, 0x0($3)
    /* 67A60 00167A60 1C00A48C */  lw         $4, 0x1C($5)
    /* 67A64 00167A64 80100200 */  sll        $2, $2, 2
    /* 67A68 00167A68 21104400 */  addu       $2, $2, $4
    /* 67A6C 00167A6C 0000518C */  lw         $17, 0x0($2)
    /* 67A70 00167A70 25002012 */  beqz       $17, .L00167B08
    /* 67A74 00167A74 0100D324 */   addiu     $19, $6, 0x1
    /* 67A78 00167A78 00002286 */  lh         $2, 0x0($17)
    /* 67A7C 00167A7C 22004004 */  bltz       $2, .L00167B08
    /* 67A80 00167A80 00002396 */   lhu       $3, 0x0($17)
    /* 67A84 00167A84 04000010 */  b          .L00167A98
    /* 67A88 00167A88 00140300 */   sll       $2, $3, 16
    /* 67A8C 00167A8C 00000000 */  nop
.align 2
  .L00167A90:
    /* 67A90 00167A90 30B4858F */  lw         $5, %gp_rel(D_0062C020)($28)
    /* 67A94 00167A94 00140300 */  sll        $2, $3, 16
.align 2
  .L00167A98:
    /* 67A98 00167A98 70000424 */  addiu      $4, $0, 0x70
    /* 67A9C 00167A9C 03140200 */  sra        $2, $2, 16
    /* 67AA0 00167AA0 1400A58C */  lw         $5, 0x14($5)
    /* 67AA4 00167AA4 18104400 */  mult       $2, $2, $4
    /* 67AA8 00167AA8 7400438E */  lw         $3, 0x74($18)
    /* 67AAC 00167AAC 0700A316 */  bne        $21, $3, .L00167ACC
    /* 67AB0 00167AB0 2180A200 */   addu      $16, $5, $2
    /* 67AB4 00167AB4 7800428E */  lw         $2, 0x78($18)
    /* 67AB8 00167AB8 05008216 */  bne        $20, $2, .L00167AD0
    /* 67ABC 00167ABC 2D204002 */   daddu     $4, $18, $0
    /* 67AC0 00167AC0 7C00428E */  lw         $2, 0x7C($18)
    /* 67AC4 00167AC4 0C000252 */  beql       $16, $2, .L00167AF8
    /* 67AC8 00167AC8 02003126 */   addiu     $17, $17, 0x2
.align 2
  .L00167ACC:
    /* 67ACC 00167ACC 2D204002 */  daddu      $4, $18, $0
.align 2
  .L00167AD0:
    /* 67AD0 00167AD0 2D280002 */  daddu      $5, $16, $0
    /* 67AD4 00167AD4 8491050C */  jal        DrawGObjWallCollision
    /* 67AD8 00167AD8 2D300000 */   daddu     $6, $0, $0
    /* 67ADC 00167ADC 06004010 */  beqz       $2, .L00167AF8
    /* 67AE0 00167AE0 02003126 */   addiu     $17, $17, 0x2
    /* 67AE4 00167AE4 940050AE */  sw         $16, 0x94($18)
    /* 67AE8 00167AE8 01001624 */  addiu      $22, $0, 0x1
    /* 67AEC 00167AEC 8C0055AE */  sw         $21, 0x8C($18)
    /* 67AF0 00167AF0 900054AE */  sw         $20, 0x90($18)
    /* 67AF4 00167AF4 880040AE */  sw         $0, 0x88($18)
.align 2
  .L00167AF8:
    /* 67AF8 00167AF8 00002286 */  lh         $2, 0x0($17)
    /* 67AFC 00167AFC E4FF4104 */  bgez       $2, .L00167A90
    /* 67B00 00167B00 00002396 */   lhu       $3, 0x0($17)
    /* 67B04 00167B04 2CB4878F */  lw         $7, %gp_rel(D_0062C01C)($28)
.align 2
  .L00167B08:
    /* 67B08 00167B08 2D306002 */  daddu      $6, $19, $0
    /* 67B0C 00167B0C 2A10C700 */  slt        $2, $6, $7
    /* 67B10 00167B10 CFFF4014 */  bnez       $2, .L00167A50
    /* 67B14 00167B14 404BE226 */   addiu     $2, $23, %lo(D_006A4B40)
.align 2
  .L00167B18:
    /* 67B18 00167B18 2D10C002 */  daddu      $2, $22, $0
    /* 67B1C 00167B1C 8000BFDF */  ld         $31, 0x80($29)
    /* 67B20 00167B20 7000B7DF */  ld         $23, 0x70($29)
    /* 67B24 00167B24 6000B6DF */  ld         $22, 0x60($29)
    /* 67B28 00167B28 5000B5DF */  ld         $21, 0x50($29)
    /* 67B2C 00167B2C 4000B4DF */  ld         $20, 0x40($29)
    /* 67B30 00167B30 3000B3DF */  ld         $19, 0x30($29)
    /* 67B34 00167B34 2000B2DF */  ld         $18, 0x20($29)
    /* 67B38 00167B38 1000B1DF */  ld         $17, 0x10($29)
    /* 67B3C 00167B3C 0000B0DF */  ld         $16, 0x0($29)
    /* 67B40 00167B40 0800E003 */  jr         $31
    /* 67B44 00167B44 9000BD27 */   addiu     $29, $29, 0x90
endlabel func_00167A00
```
