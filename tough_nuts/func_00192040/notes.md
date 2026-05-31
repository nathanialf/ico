# func_00192040 — parked

VRAM: 0x00192040 (file_off 0x092040)
Asm source: asm/matchings/cod/092040/func_00192040.s

## Attempt at 2026-05-31

**Reason parked:** crutch-removal: deleting bucket A/B matching macros (REG)

**TU:** `src/fightSound.c`

**Seed:** `tough_nuts/func_00192040/func_00192040.c`

Disassembly:

```
/* Symbols accessed via $gp register */
.extern D_00632780, 1

.align 3
nonmatching func_00192040, 0xC

glabel func_00192040
    /* 92040 00192040 01000224 */  addiu      $2, $0, 0x1
    /* 92044 00192044 0800E003 */  jr         $31
    /* 92048 00192048 909E82AF */   sw        $2, %gp_rel(D_00632780)($gp) /* gp_rel: (D_00632780) */
endlabel func_00192040
```
