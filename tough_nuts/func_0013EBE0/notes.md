# func_0013EBE0 — parked

VRAM: 0x0013EBE0 (file_off 0x03EBE0)
Asm source: asm/nonmatchings/isys/gobj/func_0013EBE0.s

## Attempt at 2026-05-31

**Reason parked:** crutch-removal: bucket A/B macros (ANCHOR,REG)

**TU:** `isys/gobj.c`

**Seed:** `tough_nuts/func_0013EBE0/func_0013EBE0.c`

Disassembly:

```
/* Symbols accessed via $gp register */
.extern D_006321C0, 1
.extern D_00633CA4, 1
.extern D_00633CA0, 1

.align 3
nonmatching func_0013EBE0, 0x70

glabel func_0013EBE0
    /* 3EBE0 0013EBE0 D098828F */  lw         $2, (D_006321C0) /* gp_rel: (D_006321C0) */
    /* 3EBE4 0013EBE4 18004010 */  beqz       $2, .L0013EC48
    /* 3EBE8 0013EBE8 2D308000 */   daddu     $6, $4, $0
    /* 3EBEC 0013EBEC B4B3828F */  lw         $2, (D_00633CA4) /* gp_rel: (D_00633CA4) */
    /* 3EBF0 0013EBF0 74010324 */  addiu      $3, $0, 0x174
    /* 3EBF4 0013EBF4 B0B3848F */  lw         $4, (D_00633CA0) /* gp_rel: (D_00633CA0) */
    /* 3EBF8 0013EBF8 2D28C000 */  daddu      $5, $6, $0
    /* 3EBFC 0013EBFC 18104300 */  mult       $2, $2, $3
    /* 3EC00 0013EC00 8CFE4224 */  addiu      $2, $2, -0x174
    /* 3EC04 0013EC04 21208200 */  addu       $4, $4, $2
    /* 3EC08 0013EC08 0B00C410 */  beq        $6, $4, .L0013EC38
    /* 3EC0C 0013EC0C 0C00C38C */   lw        $3, 0xC($6)
    /* 3EC10 0013EC10 01000624 */  addiu      $6, $0, 0x1
    /* 3EC14 0013EC14 7401A524 */  addiu      $5, $5, 0x174
.align 2
  .L0013EC18:
    /* 3EC18 0013EC18 0400A28C */  lw         $2, 0x4($5)
    /* 3EC1C 0013EC1C 04004614 */  bne        $2, $6, .L0013EC30
    /* 3EC20 0013EC20 00000000 */   nop
    /* 3EC24 0013EC24 0C00A28C */  lw         $2, 0xC($5)
    /* 3EC28 0013EC28 05004310 */  beq        $2, $3, .L0013EC40
    /* 3EC2C 0013EC2C 00000000 */   nop
.align 2
  .L0013EC30:
    /* 3EC30 0013EC30 F9FFA414 */  bne        $5, $4, .L0013EC18
    /* 3EC34 0013EC34 7401A524 */   addiu     $5, $5, 0x174
.align 2
  .L0013EC38:
    /* 3EC38 0013EC38 0800E003 */  jr         $31
    /* 3EC3C 0013EC3C 2D100000 */   daddu     $2, $0, $0
.align 2
  .L0013EC40:
    /* 3EC40 0013EC40 0800E003 */  jr         $31
    /* 3EC44 0013EC44 2D10A000 */   daddu     $2, $5, $0
.align 2
  .L0013EC48:
    /* 3EC48 0013EC48 0800E003 */  jr         $31
    /* 3EC4C 0013EC4C 3C00C28C */   lw        $2, 0x3C($6)
endlabel func_0013EBE0
```
