
---

## Attempt at 2026-05-08

**Reason parked:** ee-gcc 2.9 schedules gp_rel sw before lui+sw store of D_00274EEC[0]; original interleaves differently in regalloc and store order

Seed: `tough_nuts/func_001B4E78/0B4E78.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_001B4E78; check asm/matchings/cod/0B4E78/)
```
