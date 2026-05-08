
---

## Attempt at 2026-05-08

**Reason parked:** 5-arg wrapper for func_0013F3F0 — ee-gcc 2.9 schedules daddu t1,t0 before addiu sp,-16 (expected: after andi a3,a2,0xff)

Seed: `tough_nuts/func_0013F7A8/03F7A8.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_0013F7A8; check asm/matchings/cod/03F7A8/)
```

---

## Attempt at 2026-05-08

**Reason parked:** 6-arg forward: ee-gcc reorders move t1,t0 vs sp adjust between original

Seed: `tough_nuts/func_0013F7A8/03F7A8.c.new`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_0013F7A8; check asm/matchings/cod/03F7A8/)
```
