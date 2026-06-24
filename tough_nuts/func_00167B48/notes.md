# func_00167B48 — parked

VRAM: 0x00167B48 (file_off 0x067B48)
Asm source: asm/aug6/nonmatchings/fumi/src/fuzio/func_00167B48.s

## Attempt at 2026-06-24

**Reason parked:** plateau: 30 distinct hand hypotheses, no real_count progress (best=5). PARK the seed, then fire ONE bounded permuter shot on it (REFERENCE Step 4); harvest by true real_count and adopt any improvement (resolution b only if nothing beats best).

**TU:** `fumi/src/fuzio.c`

**Seed:** `tough_nuts/func_00167B48/func_00167B48.c`

Disassembly:

```
.align 3
nonmatching func_00167B48, 0x140

glabel func_00167B48
    /* 67B48 00167B48 70FFBD27 */  addiu      $29, $29, -0x90
    /* 67B4C 00167B4C 2CB4878F */  lw         $7, %gp_rel(D_0062C01C)($28)
    /* 67B50 00167B50 5000B5FF */  sd         $21, 0x50($29)
    /* 67B54 00167B54 6000B6FF */  sd         $22, 0x60($29)
    /* 67B58 00167B58 2DA8C000 */  daddu      $21, $6, $0
    /* 67B5C 00167B5C 4000B4FF */  sd         $20, 0x40($29)
    /* 67B60 00167B60 2DB0A000 */  daddu      $22, $5, $0
    /* 67B64 00167B64 2000B2FF */  sd         $18, 0x20($29)
    /* 67B68 00167B68 2D300000 */  daddu      $6, $0, $0
    /* 67B6C 00167B6C 8000BFFF */  sd         $31, 0x80($29)
    /* 67B70 00167B70 2D908000 */  daddu      $18, $4, $0
    /* 67B74 00167B74 7000B7FF */  sd         $23, 0x70($29)
    /* 67B78 00167B78 2DA00000 */  daddu      $20, $0, $0
    /* 67B7C 00167B7C 3000B3FF */  sd         $19, 0x30($29)
    /* 67B80 00167B80 1000B1FF */  sd         $17, 0x10($29)
    /* 67B84 00167B84 3400E018 */  blez       $7, .L00167C58
    /* 67B88 00167B88 0000B0FF */   sd        $16, 0x0($29)
    /* 67B8C 00167B8C 6A00173C */  lui        $23, %hi(D_006A4B40)
    /* 67B90 00167B90 404BE226 */  addiu      $2, $23, %lo(D_006A4B40)
    /* 67B94 00167B94 00000000 */  nop
.align 2
  .L00167B98:
    /* 67B98 00167B98 40180600 */  sll        $3, $6, 1
    /* 67B9C 00167B9C 21186200 */  addu       $3, $3, $2
    /* 67BA0 00167BA0 30B4858F */  lw         $5, %gp_rel(D_0062C020)($28)
    /* 67BA4 00167BA4 00006284 */  lh         $2, 0x0($3)
    /* 67BA8 00167BA8 1C00A48C */  lw         $4, 0x1C($5)
    /* 67BAC 00167BAC 80100200 */  sll        $2, $2, 2
    /* 67BB0 00167BB0 21104400 */  addu       $2, $2, $4
    /* 67BB4 00167BB4 0000518C */  lw         $17, 0x0($2)
    /* 67BB8 00167BB8 23002012 */  beqz       $17, .L00167C48
    /* 67BBC 00167BBC 0100D324 */   addiu     $19, $6, 0x1
    /* 67BC0 00167BC0 00002286 */  lh         $2, 0x0($17)
    /* 67BC4 00167BC4 20004004 */  bltz       $2, .L00167C48
    /* 67BC8 00167BC8 00002396 */   lhu       $3, 0x0($17)
    /* 67BCC 00167BCC 04000010 */  b          .L00167BE0
    /* 67BD0 00167BD0 001C0300 */   sll       $3, $3, 16
    /* 67BD4 00167BD4 00000000 */  nop
.align 2
  .L00167BD8:
    /* 67BD8 00167BD8 30B4858F */  lw         $5, %gp_rel(D_0062C020)($28)
    /* 67BDC 00167BDC 001C0300 */  sll        $3, $3, 16
.align 2
  .L00167BE0:
    /* 67BE0 00167BE0 70000224 */  addiu      $2, $0, 0x70
    /* 67BE4 00167BE4 031C0300 */  sra        $3, $3, 16
    /* 67BE8 00167BE8 1400A48C */  lw         $4, 0x14($5)
    /* 67BEC 00167BEC 18186200 */  mult       $3, $3, $2
    /* 67BF0 00167BF0 0F00053C */  lui        $5, (0xF0000 >> 16)
    /* 67BF4 00167BF4 0200063C */  lui        $6, (0x20000 >> 16)
    /* 67BF8 00167BF8 21808300 */  addu       $16, $4, $3
    /* 67BFC 00167BFC 6000028E */  lw         $2, 0x60($16)
    /* 67C00 00167C00 24104500 */  and        $2, $2, $5
    /* 67C04 00167C04 0B004610 */  beq        $2, $6, .L00167C34
    /* 67C08 00167C08 2D204002 */   daddu     $4, $18, $0
    /* 67C0C 00167C0C 2D280002 */  daddu      $5, $16, $0
    /* 67C10 00167C10 8491050C */  jal        DrawGObjWallCollision
    /* 67C14 00167C14 2D300000 */   daddu     $6, $0, $0
    /* 67C18 00167C18 07004050 */  beql       $2, $0, .L00167C38
    /* 67C1C 00167C1C 02003126 */   addiu     $17, $17, 0x2
    /* 67C20 00167C20 940050AE */  sw         $16, 0x94($18)
    /* 67C24 00167C24 01001424 */  addiu      $20, $0, 0x1
    /* 67C28 00167C28 8C0056AE */  sw         $22, 0x8C($18)
    /* 67C2C 00167C2C 900055AE */  sw         $21, 0x90($18)
    /* 67C30 00167C30 880040AE */  sw         $0, 0x88($18)
.align 2
  .L00167C34:
    /* 67C34 00167C34 02003126 */  addiu      $17, $17, 0x2
.align 2
  .L00167C38:
    /* 67C38 00167C38 00002286 */  lh         $2, 0x0($17)
    /* 67C3C 00167C3C E6FF4104 */  bgez       $2, .L00167BD8
    /* 67C40 00167C40 00002396 */   lhu       $3, 0x0($17)
    /* 67C44 00167C44 2CB4878F */  lw         $7, %gp_rel(D_0062C01C)($28)
.align 2
  .L00167C48:
    /* 67C48 00167C48 2D306002 */  daddu      $6, $19, $0
    /* 67C4C 00167C4C 2A10C700 */  slt        $2, $6, $7
    /* 67C50 00167C50 D1FF4014 */  bnez       $2, .L00167B98
    /* 67C54 00167C54 404BE226 */   addiu     $2, $23, %lo(D_006A4B40)
.align 2
  .L00167C58:
    /* 67C58 00167C58 2D108002 */  daddu      $2, $20, $0
    /* 67C5C 00167C5C 8000BFDF */  ld         $31, 0x80($29)
    /* 67C60 00167C60 7000B7DF */  ld         $23, 0x70($29)
    /* 67C64 00167C64 6000B6DF */  ld         $22, 0x60($29)
    /* 67C68 00167C68 5000B5DF */  ld         $21, 0x50($29)
    /* 67C6C 00167C6C 4000B4DF */  ld         $20, 0x40($29)
    /* 67C70 00167C70 3000B3DF */  ld         $19, 0x30($29)
    /* 67C74 00167C74 2000B2DF */  ld         $18, 0x20($29)
    /* 67C78 00167C78 1000B1DF */  ld         $17, 0x10($29)
    /* 67C7C 00167C7C 0000B0DF */  ld         $16, 0x0($29)
    /* 67C80 00167C80 0800E003 */  jr         $31
    /* 67C84 00167C84 9000BD27 */   addiu     $29, $29, 0x90
endlabel func_00167B48
```
