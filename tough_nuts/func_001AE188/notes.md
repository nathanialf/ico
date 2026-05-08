
---

## Attempt at 2026-05-08

**Reason parked:** ee-gcc 2.9 -O2 emits bne+regular delay slot; expected uses bnel (branch-likely) with lw v0 in annulable delay slot for shared use across both paths

Seed: `tough_nuts/func_001AE188/0AE188.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_001AE188; check asm/matchings/cod/0AE188/)
```
