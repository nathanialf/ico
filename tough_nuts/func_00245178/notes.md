
---

## Attempt at 2026-05-08

**Reason parked:** GIF-tag wrapper (0x70000000 const): ee-gcc 2.9 -O2 collapses (p+1)+1 to addiu v0,a0,8 instead of split addiu a0,a0,4; addiu v0,a0,4

Seed: `tough_nuts/func_00245178/145178.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_00245178; check asm/matchings/cod/145178/)
```
