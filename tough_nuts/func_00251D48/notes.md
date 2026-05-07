
---

## Attempt at 2026-05-07

**Reason parked:** frame size 0x30 vs 0x20: arg-home/padding layout puzzle. local must be at sp+0, dummy[4] at sp+0x10. ee-gcc 2.9 puts arrays/volatiles before scalar locals on stack — declaration order doesn't override

Seed: `tough_nuts/func_00251D48/151D48.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_00251D48; check asm/matchings/cod/151D48/)
```
