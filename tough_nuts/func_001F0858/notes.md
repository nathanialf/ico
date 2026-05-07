
---

## Attempt at 2026-05-07

**Reason parked:** if/else with one branch tail-calling: ee-gcc 2.9 doesn't TCO; emits jal + sd/ld ra setting up a stack frame both branches share. Expected has zero frame. Tried both condition orders.

Seed: `tough_nuts/func_001F0858/0F0858.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_001F0858; check asm/matchings/cod/0F0858/)
```
