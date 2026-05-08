
---

## Attempt at 2026-05-08

**Reason parked:** ee-gcc 2.9 inlines lui+addiu fresh after func_00100410 call instead of hoisting D_006A6F30 to s0 before the call; frame size differs

Seed: `tough_nuts/func_0013D8A0/03D8A0.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_0013D8A0; check asm/matchings/cod/03D8A0/)
```

---

## Attempt at 2026-05-08

**Reason parked:** early-exit + idx-load: ee-gcc uses v1 (no s0 save), 14 insns; original saves s0, 15 insns

Seed: `tough_nuts/func_0013D8A0/03D8A0.c.new`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_0013D8A0; check asm/matchings/cod/03D8A0/)
```
