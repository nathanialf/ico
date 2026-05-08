
---

## Attempt at 2026-05-07

**Reason parked:** 5-arg via $t0: sw zero schedule diff (delay-slot of jal vs before).

Seed: `tough_nuts/func_0024D9B8/14D9B8.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_0024D9B8; check asm/matchings/cod/14D9B8/)
```

---

## Attempt at 2026-05-08

**Reason parked:** scheduling: target sd ra+sw zero before t0 setup; gcc emits t0 setup first

Seed: `tough_nuts/func_0024D9B8/14D9B8.c.new`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_0024D9B8; check asm/matchings/cod/14D9B8/)
```
