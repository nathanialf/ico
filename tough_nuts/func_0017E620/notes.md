
---

## Attempt at 2026-05-08

**Reason parked:** ee-gcc 2.9 emits bnel v0,zero+lw delay (branch-likely-then-deref); original separates daddu v1,v0+beq+delay-zero+lw

Seed: `tough_nuts/func_0017E620/07E620.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_0017E620; check asm/matchings/cod/07E620/)
```

---

## Attempt at 2026-05-08

**Reason parked:** early-exit + xor compare: ee-gcc keeps ret in v0 (no copy); original copies v0->v1 first

Seed: `tough_nuts/func_0017E620/07E620.c.new`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_0017E620; check asm/matchings/cod/07E620/)
```
