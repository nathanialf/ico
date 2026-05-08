# func_0017D0F8 — parked

VRAM: 0x0017D0F8 (file offset 0x07D0F8)
Asm source: `asm/cod/07D0F8.s`

## Attempt at 2026-05-08

**Reason parked:** 3-step null-check chain compiles to 9 instructions instead of expected 12. ee-gcc consolidates the early returns into a shared epilogue branch; original has each null-check fall through separately with its own jr.

Seed: `tough_nuts/func_0017D0F8/07D0F8.c`
