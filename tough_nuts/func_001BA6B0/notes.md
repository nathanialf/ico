
---

## Attempt at 2026-05-08

**Reason parked:** ee-gcc 2.9 fuses range-check (2<=x<6) into addiu v1,-2;sltiu v1,4 single compare; original uses two slti+beqz pairs

Seed: `tough_nuts/func_001BA6B0/0BA6B0.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_001BA6B0; check asm/matchings/cod/0BA6B0/)
```
