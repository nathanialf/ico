
---

## Attempt at 2026-05-08

**Reason parked:** ee-gcc -O2 picks a0 for loop temp + nop scheduling differs from original (lw s0, .. + s0-init in delay slot of beqz)

Seed: `tough_nuts/func_00135BB8/035BB8.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_00135BB8; check asm/matchings/cod/035BB8/)
```
