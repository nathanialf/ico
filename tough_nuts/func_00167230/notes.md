# func_00167230 — parked

VRAM: 0x00167230 (file_off 0x067230)
Asm source: asm/nonmatchings/src/fieldCollision/func_00167230.s

## Attempt at 2026-05-31

**Reason parked:** crutch-removal: deleting bucket A/B matching macros (NOP)

**TU:** `src/fieldCollision.c`

**Seed:** `tough_nuts/func_00167230/func_00167230.c`

Disassembly:

```
/* Symbols accessed via $gp register */
.extern D_006323C0, 1
.extern D_006323C7, 1

.align 3
nonmatching func_00167230, 0x28

glabel func_00167230
    /* 67230 00167230 2D108000 */  daddu      $2, $4, $0
    /* 67234 00167234 B00040AC */  sw         $0, 0xB0($2)
    /* 67238 00167238 940040AC */  sw         $0, 0x94($2)
    /* 6723C 0016723C 880040AC */  sw         $0, 0x88($2)
    /* 67240 00167240 D79A836B */  ldl        $3, (D_006323C7) /* gp_rel: (D_006323C7) */
    /* 67244 00167244 D09A836F */  ldr        $3, (D_006323C0) /* gp_rel: (D_006323C0) */
    /* 67248 00167248 870043B0 */  sdl        $3, 0x87($2)
    /* 6724C 0016724C 800043B4 */  sdr        $3, 0x80($2)
    /* 67250 00167250 849B0508 */  j          func_00166E10
    /* 67254 00167254 00000000 */   nop
endlabel func_00167230
```
