# func_0013ECA8 — parked

VRAM: 0x0013ECA8 (file_off 0x03ECA8)
Asm source: asm/matchings/isys/gobj/func_0013ECA8.s

## Attempt at 2026-05-31

**Reason parked:** crutch-removal: bucket A/B macros (ANCHOR,NOP)

**TU:** `isys/gobj.c`

**Seed:** `tough_nuts/func_0013ECA8/func_0013ECA8.c`

Disassembly:

```
/* Symbols accessed via $gp register */
.extern D_00633CA0, 1
.extern D_00633CA4, 1

.align 3
nonmatching func_0013ECA8, 0x4C

glabel func_0013ECA8
    /* 3ECA8 0013ECA8 B4B3828F */  lw         $2, %gp_rel(D_00633CA4)($gp) /* gp_rel: (D_00633CA4) */
    /* 3ECAC 0013ECAC 74010324 */  addiu      $3, $0, 0x174
    /* 3ECB0 0013ECB0 B0B3848F */  lw         $4, %gp_rel(D_00633CA0)($gp) /* gp_rel: (D_00633CA0) */
    /* 3ECB4 0013ECB4 18104300 */  mult       $2, $2, $3
    /* 3ECB8 0013ECB8 8CFE8324 */  addiu      $3, $4, -0x174
    /* 3ECBC 0013ECBC 8CFE4224 */  addiu      $2, $2, -0x174
    /* 3ECC0 0013ECC0 21208200 */  addu       $4, $4, $2
    /* 3ECC4 0013ECC4 07006410 */  beq        $3, $4, .L0013ECE4
    /* 3ECC8 0013ECC8 74016324 */   addiu     $3, $3, 0x174
    /* 3ECCC 0013ECCC 00000000 */  nop
.align 2
  .L0013ECD0:
    /* 3ECD0 0013ECD0 0000628C */  lw         $2, 0x0($3)
    /* 3ECD4 0013ECD4 05004014 */  bnez       $2, .L0013ECEC
    /* 3ECD8 0013ECD8 2D106000 */   daddu     $2, $3, $0
    /* 3ECDC 0013ECDC FCFF6414 */  bne        $3, $4, .L0013ECD0
    /* 3ECE0 0013ECE0 74016324 */   addiu     $3, $3, 0x174
.align 2
  .L0013ECE4:
    /* 3ECE4 0013ECE4 0800E003 */  jr         $31
    /* 3ECE8 0013ECE8 2D100000 */   daddu     $2, $0, $0
.align 2
  .L0013ECEC:
    /* 3ECEC 0013ECEC 0800E003 */  jr         $31
    /* 3ECF0 0013ECF0 00000000 */   nop
endlabel func_0013ECA8
    /* 3ECF4 0013ECF4 00000000 */  nop
```
