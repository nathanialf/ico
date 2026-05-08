# func_001E9950 — parked

VRAM: 0x001E9950 (file offset 0x0E9950)
Asm source: `asm/cod/0E994C.s`

## Attempt at 2026-05-08

**Reason parked:** counter-increment + tail-call wrapper compiles to 9 instructions instead of expected 12. ee-gcc 2.9 picks tighter regalloc (skipping the `daddu v0, v1, 0` save before increment+slti) and inlines the increment into the delay slot of bnez. Original has explicit save-then-increment-then-compare structure that the simple C body doesn't reproduce. Try `int v_inc = v + 1; ... = v_inc;` or volatile reads.

Seed: `tough_nuts/func_001E9950/0E9950.c`
