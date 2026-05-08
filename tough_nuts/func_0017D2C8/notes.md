
---

## Attempt at 2026-05-08

**Reason parked:** float-vs-void return ambiguity; target sets f0=0 only in v==0 path; v!=0 path returns without setting f0 (TCO-of-float vs partial-init unclear)

Seed: `tough_nuts/func_0017D2C8/07D2C8.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_0017D2C8; check asm/matchings/cod/07D2C8/)
```
