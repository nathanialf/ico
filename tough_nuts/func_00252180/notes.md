
---

## Attempt at 2026-05-08

**Reason parked:** if-else with two tail-call branches; ee-gcc 2.9 picks different regalloc (a0 vs v0 for compare const) and consolidates ld ra at shared epilogue while original keeps per-branch ld ra

Seed: `tough_nuts/func_00252180/152180.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_00252180; check asm/matchings/cod/152180/)
```
