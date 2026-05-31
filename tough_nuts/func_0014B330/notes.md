# func_0014B330 — parked

VRAM: 0x0014B330 (file_off 0x04B330)
Asm source: asm/matchings/cod/04B330/func_0014B330.s

## Attempt at 2026-05-31

**Reason parked:** crutch-removal: deleting bucket A/B matching macros (DEFEAT_TCO)

**TU:** `src/act-parallel-control.c`

**Seed:** `tough_nuts/func_0014B330/func_0014B330.c`

Disassembly:

```
.align 3
nonmatching func_0014B330, 0x28

glabel func_0014B330
    /* 4B330 0014B330 6401838C */  lw         $3, 0x164($4)
    /* 4B334 0014B334 7006638C */  lw         $3, 0x670($3)
    /* 4B338 0014B338 5400628C */  lw         $2, 0x54($3)
    /* 4B33C 0014B33C 2B10A200 */  sltu       $2, $5, $2
    /* 4B340 0014B340 03004014 */  bnez       $2, .L0014B350
    /* 4B344 0014B344 00000000 */   nop
    /* 4B348 0014B348 540065AC */  sw         $5, 0x54($3)
    /* 4B34C 0014B34C 58006CE4 */  swc1       $f12, 0x58($3)
.align 2
  .L0014B350:
    /* 4B350 0014B350 0800E003 */  jr         $31
    /* 4B354 0014B354 00000000 */   nop
endlabel func_0014B330
```
