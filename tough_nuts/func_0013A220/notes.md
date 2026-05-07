
---

## Attempt at 2026-05-07

**Reason parked:** ee-gcc 2.9 emits 'jr ra' + nop delay slot at function end. Expected falls-through into next function for the delay slot. Compiler-blocked: gcc has no inter-procedural delay-slot knowledge.

Seed: `tough_nuts/func_0013A220/03A220.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_0013A220; check asm/matchings/cod/03A220/)
```
