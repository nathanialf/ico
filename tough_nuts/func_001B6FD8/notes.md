# func_001B6FD8 — parked

VRAM: 0x001B6FD8 (file_off 0x0B6FD8)
Asm source: asm/matchings/src/layout_texture/func_001B6FD8.s

## Attempt at 2026-05-31

**Reason parked:** crutch-removal: deleting bucket A/B matching macros (REG)

**TU:** `src/layout_texture.c`

**Seed:** `tough_nuts/func_001B6FD8/func_001B6FD8.c`

Disassembly:

```
/* Symbols accessed via $gp register */
.extern D_00633158, 1
.extern D_0063315C, 1
.extern D_0063314C, 1
.extern D_00633EC0, 1

.align 3
nonmatching func_001B6FD8, 0x64

glabel func_001B6FD8
    /* B6FD8 001B6FD8 F0FFBD27 */  addiu      $29, $29, -0x10
    /* B6FDC 001B6FDC 68A8838F */  lw         $3, (D_00633158) /* gp_rel: (D_00633158) */
    /* B6FE0 001B6FE0 0000BFFF */  sd         $31, 0x0($29)
    /* B6FE4 001B6FE4 02000224 */  addiu      $2, $0, 0x2
    /* B6FE8 001B6FE8 04006214 */  bne        $3, $2, .L001B6FFC
    /* B6FEC 001B6FEC 2D308000 */   daddu     $6, $4, $0
    /* B6FF0 001B6FF0 5CA8828F */  lw         $2, (D_0063314C) /* gp_rel: (D_0063314C) */
    /* B6FF4 001B6FF4 0500C254 */  bnel       $6, $2, .L001B700C
    /* B6FF8 001B6FF8 5CA8848F */   lw        $4, (D_0063314C) /* gp_rel: (D_0063314C) */
.align 2
  .L001B6FFC:
    /* B6FFC 001B6FFC 3A000224 */  addiu      $2, $0, 0x3A
    /* B7000 001B7000 0C00C214 */  bne        $6, $2, .L001B7034
    /* B7004 001B7004 0000BFDF */   ld        $31, 0x0($29)
    /* B7008 001B7008 5CA8848F */  lw         $4, (D_0063314C) /* gp_rel: (D_0063314C) */
.align 2
  .L001B700C:
    /* B700C 001B700C 2D28C000 */  daddu      $5, $6, $0
    /* B7010 001B7010 0ED7060C */  jal        func_001B5C38
    /* B7014 001B7014 D0B586AF */   sw        $6, (D_00633EC0) /* gp_rel: (D_00633EC0) */
    /* B7018 001B7018 6CA8838F */  lw         $3, (D_0063315C) /* gp_rel: (D_0063315C) */
    /* B701C 001B701C 01000224 */  addiu      $2, $0, 0x1
    /* B7020 001B7020 02006214 */  bne        $3, $2, .L001B702C
    /* B7024 001B7024 03000224 */   addiu     $2, $0, 0x3
    /* B7028 001B7028 05000224 */  addiu      $2, $0, 0x5
.align 2
  .L001B702C:
    /* B702C 001B702C 68A882AF */  sw         $2, (D_00633158) /* gp_rel: (D_00633158) */
    /* B7030 001B7030 0000BFDF */  ld         $31, 0x0($29)
.align 2
  .L001B7034:
    /* B7034 001B7034 0800E003 */  jr         $31
    /* B7038 001B7038 1000BD27 */   addiu     $29, $29, 0x10
endlabel func_001B6FD8
    /* B703C 001B703C 00000000 */  nop
```
