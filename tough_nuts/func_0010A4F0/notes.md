
---

## Attempt at 2026-05-08

**Reason parked:** 2-call wrapper + dual -1 use: ee-gcc emits both li v1=-1 and li v0=-1 (1 extra insn); original folds to single addiu v0=-1

Seed: `tough_nuts/func_0010A4F0/00A4F0.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_0010A4F0; check asm/matchings/cod/00A4F0/)
```
