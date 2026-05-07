
---

## Attempt at 2026-05-07

**Reason parked:** for(;;) compiles to 5 nops + b-to-start (loops through all 5). Expected has 5 nops once then b self-loop. Different semantics; needs entry-point trick or naked attribute (ee-gcc 2.9 doesn't support naked).

Seed: `tough_nuts/func_001AD748/0AD748.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_001AD748; check asm/matchings/cod/0AD748/)
```
