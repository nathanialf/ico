
---

## Attempt at 2026-05-08

**Reason parked:** volatile pointer-pointer forces 4 reloads but regalloc differs (target alternates v1/v0; gcc uses v0/v1/a1/a2)

Seed: `tough_nuts/func_001CE6F0/0CE6F0.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_001CE6F0; check asm/matchings/cod/0CE6F0/)
```

---

## Attempt at 2026-05-08

**Reason parked:** 4-store + tail-call: ee-gcc saves self via move v0,a0; original uses daddu a1,a0,zero

Seed: `tough_nuts/func_001CE6F0/0CE6F0.c.new`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_001CE6F0; check asm/matchings/cod/0CE6F0/)
```
