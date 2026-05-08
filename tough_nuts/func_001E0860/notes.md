
---

## Attempt at 2026-05-08

**Reason parked:** ee-gcc 2.9 emits separate ld ra/ld s0 epilogue blocks for early-return paths; original has shared restore via two labels (.L48: ld ra; .L4c: ld s0)

Seed: `tough_nuts/func_001E0860/0E0860.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_001E0860; check asm/matchings/cod/0E0860/)
```
