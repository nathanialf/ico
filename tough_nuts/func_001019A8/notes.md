
---

## Attempt at 2026-05-08

**Reason parked:** varargs forwarder; ee-gcc 2.9 lacks va_list typedef and __builtin_next_arg(last) returns post-frame ptr instead of start-of-spill (sp+0x58); needs proper varargs idiom or permuter exploration

Seed: `tough_nuts/func_001019A8/0019A8.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_001019A8; check asm/matchings/cod/0019A8/)
```
