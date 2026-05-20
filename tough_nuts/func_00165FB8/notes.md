# func_00165FB8 — parked

VRAM: 0x00165FB8 (file_off 0x065FB8)
Asm source: asm/matchings/src/cod/065FB8/func_00165FB8.s

## Attempt at 2026-05-20

**Reason parked:** branch beq-vs-bne + andi delay-slot placement. Got reg-alloc and frame matching (18 vs 18 insns) with 5-arg signature + DEFEAT_TCO + `register int three REG("$3")` pin, but gcc reorder pass put EQ-case fall-through (mine) where target had EQ-case at label. Could not coax beq emission via __builtin_expect (emits xori+bne) or natural reorder.

**Seed:** `tough_nuts/func_00165FB8/065FB8.c`
