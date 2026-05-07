
---

## Attempt at 2026-05-07

**Reason parked:** ld + andi 0xFF + andi 0x1 + negu pattern. Compiler folds 0xFF&1 → 1 and adds dsll32/dsra32 sign-ext for the (int) cast. Likely wants a u64 bit-field or unusual idiom.

Seed: `tough_nuts/func_00137EF0/037EF0.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_00137EF0; check asm/matchings/cod/037EF0/)
```
