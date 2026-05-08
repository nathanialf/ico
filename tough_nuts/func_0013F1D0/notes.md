
---

## Attempt at 2026-05-08

**Reason parked:** early-return + tail-call: ee-gcc reorders daddu v0,a0 after beqz a1 instead of before, eliminating one prologue insn

Seed: `tough_nuts/func_0013F1D0/03F1D0.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_0013F1D0; check asm/matchings/cod/03F1D0/)
```
