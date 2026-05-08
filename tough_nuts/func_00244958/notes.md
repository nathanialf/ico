
---

## Attempt at 2026-05-08

**Reason parked:** ee-gcc 2.9 -O2 emits 'addiu v1,zero,-1' + extra 'move a1,a0' to preserve a0 across delay-slot read; expected uses 'lui v1,0xFFFF; ori v1,v1,0xFFFF' for -1 and lets dummy read clobber v0 directly

Seed: `tough_nuts/func_00244958/144958.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_00244958; check asm/matchings/cod/144958/)
```
