
---

## Attempt at 2026-05-08

**Reason parked:** DMA-tag setup buffer wrapper: ee-gcc -O2 schedules sw a0/sw a1/move a1=sp differently than original

Seed: `tough_nuts/func_00101AA0/001AA0.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_00101AA0; check asm/matchings/cod/001AA0/)
```

---

## Attempt at 2026-05-09

**Reason parked:** syscall wrapper: schedule of sw v0,12(sp) into delay slot doesn't match (close but final 5-insn block differs)

Seed: `tough_nuts/func_00101AA0/001AA0.c.new`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_00101AA0; check asm/matchings/cod/001AA0/)
```
