
---

## Attempt at 2026-05-08

**Reason parked:** two-cmp state-checker: ee-gcc 2.9 emits xori+movn for 'state==3||state==9' instead of two-branch + delay-slot fills (regalloc state→a0 vs v1)

Seed: `tough_nuts/func_0023C148/13C148.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_0023C148; check asm/matchings/cod/13C148/)
```
