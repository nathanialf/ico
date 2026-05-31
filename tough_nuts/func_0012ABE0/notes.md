# func_0012ABE0 — parked

VRAM: 0x0012ABE0 (file_off 0x02ABE0)
Asm source: asm/nonmatchings/src/StageAnimation/func_0012ABE0.s

## Attempt at 2026-05-31

**Reason parked:** crutch-removal: deleting bucket A/B matching macros (REG)

**TU:** `src/StageAnimation.c`

**Seed:** `tough_nuts/func_0012ABE0/func_0012ABE0.c`

Disassembly:

```
/* Symbols accessed via $gp register */
.extern D_00633C54, 1

.align 3
nonmatching func_0012ABE0, 0x44

glabel func_0012ABE0
    /* 2ABE0 0012ABE0 6700023C */  lui        $2, %hi(D_00674058)
    /* 2ABE4 0012ABE4 64B3878F */  lw         $7, (D_00633C54) /* gp_rel: (D_00633C54) */
    /* 2ABE8 0012ABE8 58404824 */  addiu      $8, $2, %lo(D_00674058)
    /* 2ABEC 0012ABEC 0B00E018 */  blez       $7, .L0012AC1C
    /* 2ABF0 0012ABF0 2D300000 */   daddu     $6, $0, $0
    /* 2ABF4 0012ABF4 00000000 */  nop
.align 2
  .L0012ABF8:
    /* 2ABF8 0012ABF8 8002038D */  lw         $3, 0x280($8)
    /* 2ABFC 0012ABFC 5800628C */  lw         $2, 0x58($3)
    /* 2AC00 0012AC00 03008214 */  bne        $4, $2, .L0012AC10
    /* 2AC04 0012AC04 0100C624 */   addiu     $6, $6, 0x1
    /* 2AC08 0012AC08 500065AC */  sw         $5, 0x50($3)
    /* 2AC0C 0012AC0C 64B3878F */  lw         $7, (D_00633C54) /* gp_rel: (D_00633C54) */
.align 2
  .L0012AC10:
    /* 2AC10 0012AC10 2A10C700 */  slt        $2, $6, $7
    /* 2AC14 0012AC14 F8FF4014 */  bnez       $2, .L0012ABF8
    /* 2AC18 0012AC18 90020825 */   addiu     $8, $8, 0x290
.align 2
  .L0012AC1C:
    /* 2AC1C 0012AC1C 0800E003 */  jr         $31
    /* 2AC20 0012AC20 00000000 */   nop
endlabel func_0012ABE0
    /* 2AC24 0012AC24 00000000 */  nop
```
