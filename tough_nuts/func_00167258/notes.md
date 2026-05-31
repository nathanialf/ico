# func_00167258 — parked

VRAM: 0x00167258 (file_off 0x067258)
Asm source: asm/nonmatchings/src/fieldCollision/func_00167258.s

## Attempt at 2026-05-31

**Reason parked:** crutch-removal: deleting bucket A/B matching macros (NOP)

**TU:** `src/fieldCollision.c`

**Seed:** `tough_nuts/func_00167258/func_00167258.c`

Disassembly:

```
/* Symbols accessed via $gp register */
.extern D_006323C0, 1
.extern D_006323C7, 1

.align 3
nonmatching func_00167258, 0x20

glabel func_00167258
    /* 67258 00167258 2D108000 */  daddu      $2, $4, $0
    /* 6725C 0016725C 940040AC */  sw         $0, 0x94($2)
    /* 67260 00167260 D79A836B */  ldl        $3, (D_006323C7) /* gp_rel: (D_006323C7) */
    /* 67264 00167264 D09A836F */  ldr        $3, (D_006323C0) /* gp_rel: (D_006323C0) */
    /* 67268 00167268 930043B0 */  sdl        $3, 0x93($2)
    /* 6726C 0016726C 8C0043B4 */  sdr        $3, 0x8C($2)
    /* 67270 00167270 849B0508 */  j          func_00166E10
    /* 67274 00167274 00000000 */   nop
endlabel func_00167258
```
