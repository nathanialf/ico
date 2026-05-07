
---

## Attempt at 2026-05-07

**Reason parked:** ee-gcc 2.9-991111 doesn't emit 'lwu' — the compiler always picks 'lw' (sign-extending) where the original uses 'lwu' (zero-extending). The dsll32/dsra32 sign-ext pair after lwu in expected can't be reproduced from C. Likely compiler-version mismatch.

Seed: `tough_nuts/func_0015F208/05F208.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_0015F208; check asm/matchings/cod/05F208/)
```
