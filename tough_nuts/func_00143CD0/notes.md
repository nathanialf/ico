# func_00143CD0 — parked

VRAM: 0x00143CD0 (file_off 0x043CD0)
Asm source: asm/nonmatchings/sound/s_init/func_00143CD0.s

## Attempt at 2026-05-31

**Reason parked:** crutch-removal: bucket A/B macros (REG)

**TU:** `sound/s_init.c`

**Seed:** `tough_nuts/func_00143CD0/func_00143CD0.c`

Disassembly:

```
.align 3
nonmatching func_00143CD0, 0x44

glabel func_00143CD0
    /* 43CD0 00143CD0 6B00023C */  lui        $2, %hi(D_006A95B0)
    /* 43CD4 00143CD4 0000848C */  lw         $4, 0x0($4)
    /* 43CD8 00143CD8 B0954524 */  addiu      $5, $2, %lo(D_006A95B0)
    /* 43CDC 00143CDC 0003A724 */  addiu      $7, $5, 0x300
    /* 43CE0 00143CE0 2D30A000 */  daddu      $6, $5, $0
    /* 43CE4 00143CE4 00000000 */  nop
.align 2
  .L00143CE8:
    /* 43CE8 00143CE8 0000A28C */  lw         $2, 0x0($5)
    /* 43CEC 00143CEC 07004410 */  beq        $2, $4, .L00143D0C
    /* 43CF0 00143CF0 2D18C000 */   daddu     $3, $6, $0
    /* 43CF4 00143CF4 3000A524 */  addiu      $5, $5, 0x30
    /* 43CF8 00143CF8 2A10A700 */  slt        $2, $5, $7
    /* 43CFC 00143CFC FAFF4014 */  bnez       $2, .L00143CE8
    /* 43D00 00143D00 30006624 */   addiu     $6, $3, 0x30
    /* 43D04 00143D04 0800E003 */  jr         $31
    /* 43D08 00143D08 2D100000 */   daddu     $2, $0, $0
.align 2
  .L00143D0C:
    /* 43D0C 00143D0C 0800E003 */  jr         $31
    /* 43D10 00143D10 2D10C000 */   daddu     $2, $6, $0
endlabel func_00143CD0
    /* 43D14 00143D14 00000000 */  nop
```
