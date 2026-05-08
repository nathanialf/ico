
---

## Attempt at 2026-05-08

**Reason parked:** func_0017DF38 wrapper: ee-gcc skips dead sw $a0,0($sp) and uses smaller frame; original spills caller's first arg without using it (varargs-like? param-spill quirk)

Seed: `tough_nuts/func_0023AD08/13AD08.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_0023AD08; check asm/matchings/cod/13AD08/)
```
