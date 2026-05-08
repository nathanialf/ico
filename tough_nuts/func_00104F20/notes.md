
---

## Attempt at 2026-05-07

**Reason parked:** regalloc swap (a1 vs v1) + addu/j scheduling. Permuter target.

Seed: `tough_nuts/func_00104F20/004F20.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_00104F20; check asm/matchings/cod/004F20/)
```

---

## Attempt at 2026-05-08

**Reason parked:** tail-call ++ counter: ee-gcc puts addu in j delay; original places j as last with delay slot from next function

Seed: `tough_nuts/func_00104F20/004F20.c.new`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_00104F20; check asm/matchings/cod/004F20/)
```
