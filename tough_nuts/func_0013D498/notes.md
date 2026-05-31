# func_0013D498 — parked

VRAM: 0x0013D498 (file_off 0x03D498)
Asm source: asm/nonmatchings/ios/thread/func_0013D498.s

## Attempt at 2026-05-31

**Reason parked:** crutch-removal: bucket A/B macros (ANCHOR)

**TU:** `ios/thread.c`

**Seed:** `tough_nuts/func_0013D498/func_0013D498.c`

Disassembly:

```
/* Symbols accessed via $gp register */
.extern D_00632000, 1

.align 3
nonmatching func_0013D498, 0x9C

glabel func_0013D498
    /* 3D498 0013D498 D0FFBD27 */  addiu      $29, $29, -0x30
    /* 3D49C 0013D49C 0000B0FF */  sd         $16, 0x0($29)
    /* 3D4A0 0013D4A0 1000B1FF */  sd         $17, 0x10($29)
    /* 3D4A4 0013D4A4 6A00103C */  lui        $16, %hi(D_006A6F30)
    /* 3D4A8 0013D4A8 306F1026 */  addiu      $16, $16, %lo(D_006A6F30)
    /* 3D4AC 0013D4AC 2000BFFF */  sd         $31, 0x20($29)
    /* 3D4B0 0013D4B0 0401040C */  jal        func_00100410
    /* 3D4B4 0013D4B4 2D888000 */   daddu     $17, $4, $0
    /* 3D4B8 0013D4B8 80100200 */  sll        $2, $2, 2
    /* 3D4BC 0013D4BC 21105000 */  addu       $2, $2, $16
    /* 3D4C0 0013D4C0 0000508C */  lw         $16, 0x0($2)
    /* 3D4C4 0013D4C4 4800028E */  lw         $2, 0x48($16)
    /* 3D4C8 0013D4C8 0F004054 */  bnel       $2, $0, .L0013D508
    /* 3D4CC 0013D4CC 4C00048E */   lw        $4, 0x4C($16)
    /* 3D4D0 0013D4D0 01000224 */  addiu      $2, $0, 0x1
    /* 3D4D4 0013D4D4 5500063C */  lui        $6, %hi(D_005578D0)
    /* 3D4D8 0013D4D8 1097848F */  lw         $4, (D_00632000) /* gp_rel: (D_00632000) */
    /* 3D4DC 0013D4DC D078C624 */  addiu      $6, $6, %lo(D_005578D0)
    /* 3D4E0 0013D4E0 480002AE */  sw         $2, 0x48($16)
    /* 3D4E4 0013D4E4 50000524 */  addiu      $5, $0, 0x50
    /* 3D4E8 0013D4E8 3EE8040C */  jal        func_0013A0F8
    /* 3D4EC 0013D4EC DE010724 */   addiu     $7, $0, 0x1DE
    /* 3D4F0 0013D4F0 2D204000 */  daddu      $4, $2, $0
    /* 3D4F4 0013D4F4 08000624 */  addiu      $6, $0, 0x8
    /* 3D4F8 0013D4F8 4C0002AE */  sw         $2, 0x4C($16)
    /* 3D4FC 0013D4FC 94E8040C */  jal        func_0013A250
    /* 3D500 0013D500 30008524 */   addiu     $5, $4, 0x30
    /* 3D504 0013D504 4C00048E */  lw         $4, 0x4C($16)
.align 2
  .L0013D508:
    /* 3D508 0013D508 2D282002 */  daddu      $5, $17, $0
    /* 3D50C 0013D50C 6EE9040C */  jal        func_0013A5B8
    /* 3D510 0013D510 2D300000 */   daddu     $6, $0, $0
    /* 3D514 0013D514 5500043C */  lui        $4, %hi(D_00557970)
    /* 3D518 0013D518 2000BFDF */  ld         $31, 0x20($29)
    /* 3D51C 0013D51C 1000B1DF */  ld         $17, 0x10($29)
    /* 3D520 0013D520 2D284000 */  daddu      $5, $2, $0
    /* 3D524 0013D524 0000B0DF */  ld         $16, 0x0($29)
    /* 3D528 0013D528 70798424 */  addiu      $4, $4, %lo(D_00557970)
    /* 3D52C 0013D52C 8A9B0608 */  j          func_001A6E28
    /* 3D530 0013D530 3000BD27 */   addiu     $29, $29, 0x30
endlabel func_0013D498
    /* 3D534 0013D534 00000000 */  nop
```
