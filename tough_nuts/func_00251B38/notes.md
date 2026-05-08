
---

## Attempt at 2026-05-08

**Reason parked:** ee-gcc -O2 reorders stores: source E4,D8,DC,B0,E0 → built E4,D8,E0,DC,jal+B0(delay); expected E4,D8,DC,B0,jal+E0(delay)

Seed: `tough_nuts/func_00251B38/151B38.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_00251B38; check asm/matchings/cod/151B38/)
```
