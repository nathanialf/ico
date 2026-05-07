
---

## Attempt at 2026-05-07

**Reason parked:** 3-sibling pattern (203EE8, 209F28, 235A18): missing 'lw v0, 0(sp)' before 'lw a0, 0(sp)'. Volatile param triggers single lw, but expected has a redundant v0 load.

Seed: `tough_nuts/func_00203EE8/103EE8.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_00203EE8; check asm/matchings/cod/103EE8/)
```
