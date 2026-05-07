
---

## Attempt at 2026-05-07

**Reason parked:** ee-gcc emits macro 'sw $X, D($Y)' (lui+daddu+sw) for indexed sdata store; original uses explicit 'la D' (lui+addiu) into $v0 then 'sll $a0,2; addu $a0+$v0; sw' for the same effect. Macro form is shorter but encodes differently

Seed: `tough_nuts/func_001AE880/0AE880.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_001AE880; check asm/matchings/cod/0AE880/)
```
