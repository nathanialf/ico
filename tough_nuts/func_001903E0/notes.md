
---

## Attempt at 2026-05-08

**Reason parked:** gcc emits bnel-deferred-load pattern vs target beq-with-zero-delay-slot; reg-alloc also reuses a0/a1 in target

Seed: `tough_nuts/func_001903E0/0903E0.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_001903E0; check asm/matchings/cod/0903E0/)
```

---

## Attempt at 2026-05-08

**Reason parked:** leaf cond-eval: ee-gcc allocates ret to a0 (move v0,a0 in jr delay); original puts ret directly in v0

Seed: `tough_nuts/func_001903E0/0903E0.c.new`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_001903E0; check asm/matchings/cod/0903E0/)
```
