
---

## Attempt at 2026-05-12

**Reason parked:** two-entry-point function (1F2370 + 1F2388 alabel); separate C funcs don't merge into single .text block

Seed: `tough_nuts/func_001F236C/0F236C.c`

Disassembly excerpt:

```
glabel func_001F236C
    /* F236C 001F236C 00000000 */  nop
endlabel func_001F236C
```
