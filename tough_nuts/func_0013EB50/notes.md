# func_0013EB50 — parked

VRAM: 0x0013EB50 (file_off 0x03EB50)
Asm source: asm/nonmatchings/isys/gobj/func_0013EB50.s

## Attempt at 2026-05-31

**Reason parked:** crutch-removal: bucket A/B macros (NOP,REG)

**TU:** `isys/gobj.c`

**Seed:** `tough_nuts/func_0013EB50/func_0013EB50.c`

Disassembly:

```
/* Symbols accessed via $gp register */
.extern D_006321C0, 1
.extern D_00633CA4, 1
.extern D_00633CA0, 1

.align 3
nonmatching func_0013EB50, 0x8C

glabel func_0013EB50
    /* 3EB50 0013EB50 D098828F */  lw         $2, (D_006321C0) /* gp_rel: (D_006321C0) */
    /* 3EB54 0013EB54 18004010 */  beqz       $2, .L0013EBB8
    /* 3EB58 0013EB58 2D288000 */   daddu     $5, $4, $0
    /* 3EB5C 0013EB5C B4B3828F */  lw         $2, (D_00633CA4) /* gp_rel: (D_00633CA4) */
    /* 3EB60 0013EB60 74010324 */  addiu      $3, $0, 0x174
    /* 3EB64 0013EB64 B0B3848F */  lw         $4, (D_00633CA0) /* gp_rel: (D_00633CA0) */
    /* 3EB68 0013EB68 18104300 */  mult       $2, $2, $3
    /* 3EB6C 0013EB6C 8CFE8324 */  addiu      $3, $4, -0x174
    /* 3EB70 0013EB70 8CFE4224 */  addiu      $2, $2, -0x174
    /* 3EB74 0013EB74 21208200 */  addu       $4, $4, $2
    /* 3EB78 0013EB78 0B006410 */  beq        $3, $4, .L0013EBA8
    /* 3EB7C 0013EB7C 01000624 */   addiu     $6, $0, 0x1
    /* 3EB80 0013EB80 74016324 */  addiu      $3, $3, 0x174
    /* 3EB84 0013EB84 00000000 */  nop
.align 2
  .L0013EB88:
    /* 3EB88 0013EB88 0400628C */  lw         $2, 0x4($3)
    /* 3EB8C 0013EB8C 04004614 */  bne        $2, $6, .L0013EBA0
    /* 3EB90 0013EB90 00000000 */   nop
    /* 3EB94 0013EB94 0C00628C */  lw         $2, 0xC($3)
    /* 3EB98 0013EB98 05004510 */  beq        $2, $5, .L0013EBB0
    /* 3EB9C 0013EB9C 00000000 */   nop
.align 2
  .L0013EBA0:
    /* 3EBA0 0013EBA0 F9FF6414 */  bne        $3, $4, .L0013EB88
    /* 3EBA4 0013EBA4 74016324 */   addiu     $3, $3, 0x174
.align 2
  .L0013EBA8:
    /* 3EBA8 0013EBA8 0800E003 */  jr         $31
    /* 3EBAC 0013EBAC 2D100000 */   daddu     $2, $0, $0
.align 2
  .L0013EBB0:
    /* 3EBB0 0013EBB0 0800E003 */  jr         $31
    /* 3EBB4 0013EBB4 2D106000 */   daddu     $2, $3, $0
.align 2
  .L0013EBB8:
    /* 3EBB8 0013EBB8 FFFFA224 */  addiu      $2, $5, -0x1
    /* 3EBBC 0013EBBC 4300422C */  sltiu      $2, $2, 0x43
    /* 3EBC0 0013EBC0 F9FF4010 */  beqz       $2, .L0013EBA8
    /* 3EBC4 0013EBC4 6B00023C */   lui       $2, %hi(D_006A93D0)
    /* 3EBC8 0013EBC8 80180500 */  sll        $3, $5, 2
    /* 3EBCC 0013EBCC D0934224 */  addiu      $2, $2, %lo(D_006A93D0)
    /* 3EBD0 0013EBD0 21186200 */  addu       $3, $3, $2
    /* 3EBD4 0013EBD4 0800E003 */  jr         $31
    /* 3EBD8 0013EBD8 0000628C */   lw        $2, 0x0($3)
endlabel func_0013EB50
    /* 3EBDC 0013EBDC 00000000 */  nop
```
