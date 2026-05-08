
---

## Attempt at 2026-05-08

**Reason parked:** 2-jal volatile-spill+reload: ee-gcc -O2 schedules s0 load AFTER first jal (uses v1, no callee-save spill); expected pre-call load via s0 + sd s0/ld s0 epilogue

Seed: `tough_nuts/func_00164F40/064F40.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_00164F40; check asm/matchings/cod/064F40/)
```
