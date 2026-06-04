# func_0011F1C8 — parked

VRAM: 0x0011F1C8 (file_off 0x01F1C8)
Asm source: asm/aug6/nonmatchings/seki/src/RegistPacket/func_0011F1C8.s

## Attempt at 2026-06-04

**Reason parked:** rc2 scheduler near-miss: independent 'move a2,zero' (const-0 3rd arg to pac_getWeight) placed in the dsll->dsra32 latency gap vs after dsra32 in ROM. Structure byte-identical otherwise. 10 distinct clean-C forms (inline/temp/union/int*/longlong-cast/load-order/split) all invariant; arg-position lever needs a float (all-int call); aug6 lever-reorder/sched_diff not aug6-aware. Permuter target.

**TU:** `seki/src/RegistPacket.c`

**Seed:** `tough_nuts/func_0011F1C8/func_0011F1C8.c`

Disassembly:

```
.align 3
nonmatching func_0011F1C8, 0x28

glabel func_0011F1C8
    /* 1F1C8 0011F1C8 600082DC */  ld         $2, 0x60($4)
    /* 1F1CC 0011F1CC 2D38A000 */  daddu      $7, $5, $0
    /* 1F1D0 0011F1D0 6000848C */  lw         $4, 0x60($4)
    /* 1F1D4 0011F1D4 2D40C000 */  daddu      $8, $6, $0
    /* 1F1D8 0011F1D8 F8160200 */  dsll       $2, $2, 27
    /* 1F1DC 0011F1DC 3F100200 */  dsra32     $2, $2, 0
    /* 1F1E0 0011F1E0 2D300000 */  daddu      $6, $0, $0
    /* 1F1E4 0011F1E4 01008430 */  andi       $4, $4, 0x1
    /* 1F1E8 0011F1E8 24640408 */  j          pac_getWeight
    /* 1F1EC 0011F1EC 03004530 */   andi      $5, $2, 0x3
endlabel func_0011F1C8
```
