# func_0013B858 — parked

VRAM: 0x0013B858 (file_off 0x03B858)
Asm source: asm/matchings/ios/pad/func_0013B858.s

## Attempt at 2026-05-31

**Reason parked:** crutch-removal: bucket A/B macros (REG)

**TU:** `ios/pad.c`

**Seed:** `tough_nuts/func_0013B858/func_0013B858.c`

Disassembly:

```
/* Symbols accessed via $gp register */
.extern D_00633C90, 1

.align 3
nonmatching func_0013B858, 0xC

glabel func_0013B858
    /* 3B858 0013B858 01000224 */  addiu      $2, $0, 0x1
    /* 3B85C 0013B85C 0800E003 */  jr         $31
    /* 3B860 0013B860 A0B382AF */   sw        $2, %gp_rel(D_00633C90)($gp) /* gp_rel: (D_00633C90) */
endlabel func_0013B858
    /* 3B864 0013B864 00000000 */  nop
```
