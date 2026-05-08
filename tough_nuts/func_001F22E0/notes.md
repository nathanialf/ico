
---

## Attempt at 2026-05-08

**Reason parked:** func_00203B40 wrapper: ee-gcc emits sw s0,0x20(v0) before sw zero,0(s0); expected order is reversed with daddu v1,v0,0 intermediate (v0->v1 move)

Seed: `tough_nuts/func_001F22E0/0F22E0.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_001F22E0; check asm/matchings/cod/0F22E0/)
```
