
---

## Attempt at 2026-05-08

**Reason parked:** scheduling differs: target lwc1 f12 first then lw a0 in delay slot; gcc reverses to lw a0 first then lwc1 f12 in delay slot

Seed: `tough_nuts/func_001B5958/0B5958.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_001B5958; check asm/matchings/cod/0B5958/)
```

---

## Attempt at 2026-05-08

**Reason parked:** if-then-call: ee-gcc reverses lw a0 / lwc1 f12 order vs original (1-byte diff in delay slot fill)

Seed: `tough_nuts/func_001B5958/0B5958.c.new`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_001B5958; check asm/matchings/cod/0B5958/)
```
