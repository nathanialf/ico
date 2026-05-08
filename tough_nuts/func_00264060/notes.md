
---

## Attempt at 2026-05-08

**Reason parked:** varargs forwarder; ee-gcc 2.9 lacks va_list typedef and __builtin_next_arg(last) returns post-frame ptr instead of start-of-spill (sp+0x50); needs proper varargs idiom or permuter exploration

Seed: `tough_nuts/func_00264060/164060.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_00264060; check asm/matchings/cod/164060/)
```
