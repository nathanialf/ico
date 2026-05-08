
---

## Attempt at 2026-05-08

**Reason parked:** dual D_ check + bne 0x2D: ee-gcc emits beql (branch-likely) folding lw into delay slot; original uses bne+nop+lw

Seed: `tough_nuts/func_001545F8/0545F8.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_001545F8; check asm/matchings/cod/0545F8/)
```
