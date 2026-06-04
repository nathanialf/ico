# func_0023FFC8 — parked

VRAM: 0x0023FFC8 (file_off 0x13FFC8)
Asm source: asm/aug6/nonmatchings/common/src/PObj/func_0023FFC8.s

## Attempt at 2026-06-04

**Reason parked:** rc1 VU0 near-miss: lerp *a0=a1*t+a2*(1-t). ROM has mfc1->qmtc2 adjacent (noreorder, no hazard nop) AND the final sqc2 in the jr-delay. Bare asm fills the jr-delay but inserts the mfc1->qmtc2 hazard nop (rc1); .set noreorder avoids the hazard nop but leaves a jr-delay nop (rc2); the two are incompatible across the gcc-jr / asm-block boundary. Permuter/future target.

**TU:** `common/src/PObj.c`

**Seed:** `tough_nuts/func_0023FFC8/func_0023FFC8.c`

Disassembly:

```
.align 3
nonmatching func_0023FFC8, 0x28

glabel func_0023FFC8
    /* 13FFC8 0023FFC8 0000A4D8 */  lqc2       $vf4, 0x0($5)
    /* 13FFCC 0023FFCC 0000C5D8 */  lqc2       $vf5, 0x0($6)
    /* 13FFD0 0023FFD0 00600844 */  mfc1       $8, $f12
    /* 13FFD4 0023FFD4 0030A848 */  qmtc2.ni   $8, $vf6
    /* 13FFD8 0023FFD8 C301004B */  vaddw.x    $vf7, $vf0, $vf0w
    /* 13FFDC 0023FFDC 2C3A064B */  vsub.x     $vf8, $vf7, $vf6
    /* 13FFE0 0023FFE0 BC21E64B */  vmulax.xyzw $ACC, $vf4, $vf6x
    /* 13FFE4 0023FFE4 482AE84B */  vmaddx.xyzw $vf9, $vf5, $vf8x
    /* 13FFE8 0023FFE8 0800E003 */  jr         $31
    /* 13FFEC 0023FFEC 000089F8 */   sqc2      $vf9, 0x0($4)
endlabel func_0023FFC8
```
