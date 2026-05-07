
---

## Attempt at 2026-05-07

**Reason parked:** Function ends with jr ra (no addiu sp epilogue), like 094398. Falls through to neighbor function for sp restore. C body always emits full epilogue.

Seed: `tough_nuts/func_00194400/094400.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_00194400; check asm/matchings/cod/094400/)
```
