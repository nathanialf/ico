
---

## Attempt at 2026-05-08

**Reason parked:** swc1+sw_zero+lw a0 scheduling order differs from target

Seed: `tough_nuts/func_0017E838/07E838.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_0017E838; check asm/matchings/cod/07E838/)
```

---

## Attempt at 2026-05-08

**Reason parked:** 3-float pack: ee-gcc reorders sw zero before swc1 + interleaves lw a0; original keeps source order

Seed: `tough_nuts/func_0017E838/07E838.c.new`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_0017E838; check asm/matchings/cod/07E838/)
```
