
---

## Attempt at 2026-05-08

**Reason parked:** scheduling: target emits a2/a1/a1-lo before jal with a0=2 in delay slot; gcc emits a0/a2 before jal with a1-lo in delay slot

Seed: `tough_nuts/func_0011FF30/01FF30.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_0011FF30; check asm/matchings/cod/01FF30/)
```

---

## Attempt at 2026-05-08

**Reason parked:** 3-call wrapper: ee-gcc emits args a0,a2,a1 (in delay); original a2,a1,a0 (a0 in delay)

Seed: `tough_nuts/func_0011FF30/01FF30.c.new`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_0011FF30; check asm/matchings/cod/01FF30/)
```
