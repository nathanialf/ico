
---

## Attempt at 2026-05-08

**Reason parked:** ee-gcc 2.9 fuses 2<=v1<4 range via addiu+sltiu; original uses slti+slti; also missing D_00633C38=0 epilogue store

Seed: `tough_nuts/func_00117768/017768.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_00117768; check asm/matchings/cod/017768/)
```
