
---

## Attempt at 2026-05-12

**Reason parked:** scheduler hoists D_00631AE4 load before self null check; branch target structure differs

Seed: `tough_nuts/func_00149E70/049E70.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_00149E70; check asm/matchings/cod/049E70/)
```

---

## Attempt at 2026-05-13

**Reason parked:** near-miss: gcc tracks ret in v1+move to v0; expected commits to v0 with v0=0 at fail label

Seed: `tough_nuts/func_00149E70/049E70.c.new`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_00149E70; check asm/matchings/cod/049E70/)
```
