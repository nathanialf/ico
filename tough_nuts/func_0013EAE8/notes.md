# func_0013EAE8 — parked

VRAM: 0x0013EAE8 (file_off 0x03EAE8)
Asm source: asm/matchings/isys/gobj/func_0013EAE8.s

## Attempt at 2026-05-31

**Reason parked:** crutch-removal: bucket A/B macros (ANCHOR,REG)

**TU:** `isys/gobj.c`

**Seed:** `tough_nuts/func_0013EAE8/func_0013EAE8.c`

Disassembly:

```
/* Symbols accessed via $gp register */
.extern D_00633CA0, 1
.extern D_00633CA4, 1

.align 3
nonmatching func_0013EAE8, 0x64

glabel func_0013EAE8
    /* 3EAE8 0013EAE8 B4B3888F */  lw         $8, %gp_rel(D_00633CA4)($gp) /* gp_rel: (D_00633CA4) */
    /* 3EAEC 0013EAEC 15000011 */  beqz       $8, .L0013EB44
    /* 3EAF0 0013EAF0 2D300000 */   daddu     $6, $0, $0
    /* 3EAF4 0013EAF4 B0B3878F */  lw         $7, %gp_rel(D_00633CA0)($gp) /* gp_rel: (D_00633CA0) */
    /* 3EAF8 0013EAF8 74010224 */  addiu      $2, $0, 0x174
    /* 3EAFC 0013EAFC 00000000 */  nop
.align 2
  .L0013EB00:
    /* 3EB00 0013EB00 1818C200 */  mult       $3, $6, $2
    /* 3EB04 0013EB04 21286700 */  addu       $5, $3, $7
    /* 3EB08 0013EB08 0000A38C */  lw         $3, 0x0($5)
    /* 3EB0C 0013EB0C 09006010 */  beqz       $3, .L0013EB34
    /* 3EB10 0013EB10 01000224 */   addiu     $2, $0, 0x1
    /* 3EB14 0013EB14 0400A38C */  lw         $3, 0x4($5)
    /* 3EB18 0013EB18 07006214 */  bne        $3, $2, .L0013EB38
    /* 3EB1C 0013EB1C 0100C624 */   addiu     $6, $6, 0x1
    /* 3EB20 0013EB20 0800A28C */  lw         $2, 0x8($5)
    /* 3EB24 0013EB24 05004414 */  bne        $2, $4, .L0013EB3C
    /* 3EB28 0013EB28 2B10C800 */   sltu      $2, $6, $8
    /* 3EB2C 0013EB2C 0800E003 */  jr         $31
    /* 3EB30 0013EB30 2D10A000 */   daddu     $2, $5, $0
.align 2
  .L0013EB34:
    /* 3EB34 0013EB34 0100C624 */  addiu      $6, $6, 0x1
.align 2
  .L0013EB38:
    /* 3EB38 0013EB38 2B10C800 */  sltu       $2, $6, $8
.align 2
  .L0013EB3C:
    /* 3EB3C 0013EB3C F0FF4014 */  bnez       $2, .L0013EB00
    /* 3EB40 0013EB40 74010224 */   addiu     $2, $0, 0x174
.align 2
  .L0013EB44:
    /* 3EB44 0013EB44 0800E003 */  jr         $31
    /* 3EB48 0013EB48 2D100000 */   daddu     $2, $0, $0
endlabel func_0013EAE8
    /* 3EB4C 0013EB4C 00000000 */  nop
```
