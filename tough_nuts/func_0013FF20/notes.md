# func_0013FF20 — parked

VRAM: 0x0013FF20 (file_off 0x03FF20)
Asm source: asm/nonmatchings/sound/adpcm_init/func_0013FF20.s

## Attempt at 2026-05-31

**Reason parked:** crutch-removal: bucket A/B macros (ANCHOR)

**TU:** `sound/adpcm_init.c`

**Seed:** `tough_nuts/func_0013FF20/func_0013FF20.c`

Disassembly:

```
.align 3
nonmatching func_0013FF20, 0x5C

glabel func_0013FF20
    /* 3FF20 0013FF20 2800023C */  lui        $2, %hi(D_00281A70)
    /* 3FF24 0013FF24 2D280000 */  daddu      $5, $0, $0
    /* 3FF28 0013FF28 701A4624 */  addiu      $6, $2, %lo(D_00281A70)
    /* 3FF2C 0013FF2C 00000000 */  nop
.align 2
  .L0013FF30:
    /* 3FF30 0013FF30 0000C38C */  lw         $3, 0x0($6)
    /* 3FF34 0013FF34 08006010 */  beqz       $3, .L0013FF58
    /* 3FF38 0013FF38 2D100000 */   daddu     $2, $0, $0
    /* 3FF3C 0013FF3C 0000628C */  lw         $2, 0x0($3)
.align 2
  .L0013FF40:
    /* 3FF40 0013FF40 05004410 */  beq        $2, $4, .L0013FF58
    /* 3FF44 0013FF44 2D106000 */   daddu     $2, $3, $0
    /* 3FF48 0013FF48 1000638C */  lw         $3, 0x10($3)
    /* 3FF4C 0013FF4C FCFF6054 */  bnel       $3, $0, .L0013FF40
    /* 3FF50 0013FF50 0000628C */   lw        $2, 0x0($3)
    /* 3FF54 0013FF54 2D100000 */  daddu      $2, $0, $0
.align 2
  .L0013FF58:
    /* 3FF58 0013FF58 06004014 */  bnez       $2, .L0013FF74
    /* 3FF5C 0013FF5C 0100A524 */   addiu     $5, $5, 0x1
    /* 3FF60 0013FF60 0800A228 */  slti       $2, $5, 0x8
    /* 3FF64 0013FF64 F2FF4014 */  bnez       $2, .L0013FF30
    /* 3FF68 0013FF68 0400C624 */   addiu     $6, $6, 0x4
    /* 3FF6C 0013FF6C 0800E003 */  jr         $31
    /* 3FF70 0013FF70 2D100000 */   daddu     $2, $0, $0
.align 2
  .L0013FF74:
    /* 3FF74 0013FF74 0800E003 */  jr         $31
    /* 3FF78 0013FF78 00000000 */   nop
endlabel func_0013FF20
    /* 3FF7C 0013FF7C 00000000 */  nop
```
