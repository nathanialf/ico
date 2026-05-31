# func_0013F778 — parked

VRAM: 0x0013F778 (file_off 0x03F778)
Asm source: asm/matchings/isys/gobj_process/func_0013F778.s

## Attempt at 2026-05-31

**Reason parked:** crutch-removal: bucket A/B macros (DEFEAT_TCO)

**TU:** `isys/gobj_process.c`

**Seed:** `tough_nuts/func_0013F778/func_0013F778.c`

Disassembly:

```
.align 3
nonmatching func_0013F778, 0x2C

glabel func_0013F778
    /* 3F778 0013F778 2D40E000 */  daddu      $8, $7, $0
    /* 3F77C 0013F77C F0FFBD27 */  addiu      $29, $29, -0x10
    /* 3F780 0013F780 FF00C730 */  andi       $7, $6, 0xFF
    /* 3F784 0013F784 0000BFFF */  sd         $31, 0x0($29)
    /* 3F788 0013F788 2D30A000 */  daddu      $6, $5, $0
    /* 3F78C 0013F78C 00180924 */  addiu      $9, $0, 0x1800
    /* 3F790 0013F790 FCFC040C */  jal        func_0013F3F0
    /* 3F794 0013F794 2D288000 */   daddu     $5, $4, $0
    /* 3F798 0013F798 0000BFDF */  ld         $31, 0x0($29)
    /* 3F79C 0013F79C 0800E003 */  jr         $31
    /* 3F7A0 0013F7A0 1000BD27 */   addiu     $29, $29, 0x10
endlabel func_0013F778
    /* 3F7A4 0013F7A4 00000000 */  nop
```
