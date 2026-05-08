
---

## Attempt at 2026-05-07

**Reason parked:** gp_rel/lui+lo schedule mismatch.

Seed: `tough_nuts/func_0024BBC0/14BBC0.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_0024BBC0; check asm/matchings/cod/14BBC0/)
```

---

## Attempt at 2026-05-08

**Reason parked:** conditional table base: ee-gcc emits lui in bgez delay (12 insns); original puts sll v1,a0,3 in delay (10 insns)

Seed: `tough_nuts/func_0024BBC0/14BBC0.c.new`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_0024BBC0; check asm/matchings/cod/14BBC0/)
```
