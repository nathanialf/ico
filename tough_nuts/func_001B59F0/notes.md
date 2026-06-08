# func_001B59F0 (common/src/staffroll) — parked

VRAM: 0x001B59F0
Asm source: asm/aug6/nonmatchings/common/src/staffroll/func_001B59F0.s
TU: common/src/staffroll.c
Retail twin: func_001B84C8 (src/staffroll.c)

## Parked 2026-06-08 (deferred from retail-port; NOT a 30-stall floor)

This is a **retail-port candidate that needs real matching work**, not a clean
port. Two blockers:

1. **jtbl carve needed** (mechanical, easy): the func has a switch jump table
   `jtbl_0060FD90` at rom `[0x50FD90, 0x50FDB0)` (next sym = string
   "Masatsuka Saeki"). Carve it like the other jtbls — split the `.rodata` blob
   in `config/ico.aug6.yaml` and add a dot-form subseg
   `[0x50FD90, .rodata, common/src/staffroll]`. See
   `feedback_jtbl_rodata_carve` memory for the recipe.

2. **crutch-free rederivation needed** (the real work): the retail body (seed
   below) matches only WITH crutches the project wants gone —
   `register float __asm__("$f1")`, `register int __asm__("$2")` pins and a
   `*(volatile unsigned char *)` store. Porting as-is would inject crutches.
   Rederive the matching shape in clean C (see
   `deterministic_source_shape_not_floors` memory).

## Seed

`tough_nuts/func_001B59F0/func_001B59F0.c` — the retail body rebound to aug6
symbols (CARRIES CRUTCHES; use as a structural reference, strip the pins).
