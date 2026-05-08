
---

## Attempt at 2026-05-08

**Reason parked:** ee-gcc -O2 emits straight branches; expected uses movn + bizarre leading 'addiu sp,+0x10' (frame/offset cancellation)

Seed: `tough_nuts/func_0023C17C/13C17C.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_0023C17C; check asm/matchings/cod/13C17C/)
```
