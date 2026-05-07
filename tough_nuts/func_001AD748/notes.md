
---

## Attempt at 2026-05-07

**Reason parked:** 5 nops + b self + nop. Inline-asm body matches the loop, but compiler always emits jr ra epilogue (with or without noreturn). The 5 leading nops might be alignment padding the compiler can't reproduce.

Seed: `tough_nuts/func_001AD748/0AD748.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_001AD748; check asm/matchings/cod/0AD748/)
```
