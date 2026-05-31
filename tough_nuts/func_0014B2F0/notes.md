# func_0014B2F0 — parked

VRAM: 0x0014B2F0 (file_off 0x04B2F0)
Asm source: asm/matchings/cod/04B2F0/func_0014B2F0.s

## Attempt at 2026-05-31

**Reason parked:** crutch-removal: deleting bucket A/B matching macros (REG)

**TU:** `src/act-parallel-control.c`

**Seed:** `tough_nuts/func_0014B2F0/func_0014B2F0.c`

Disassembly:

```
.align 3
nonmatching func_0014B2F0, 0x28

glabel func_0014B2F0
    /* 4B2F0 0014B2F0 6401838C */  lw         $3, 0x164($4)
    /* 4B2F4 0014B2F4 06006010 */  beqz       $3, .L0014B310
    /* 4B2F8 0014B2F8 2D100000 */   daddu     $2, $0, $0
    /* 4B2FC 0014B2FC 01000224 */  addiu      $2, $0, 0x1
    /* 4B300 0014B300 580063DC */  ld         $3, 0x58($3)
    /* 4B304 0014B304 0420A200 */  sllv       $4, $2, $5
    /* 4B308 0014B308 24188300 */  and        $3, $4, $3
    /* 4B30C 0014B30C 0A100300 */  movz       $2, $0, $3
.align 2
  .L0014B310:
    /* 4B310 0014B310 0800E003 */  jr         $31
    /* 4B314 0014B314 00000000 */   nop
endlabel func_0014B2F0
```
