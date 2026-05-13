
---

## Attempt at 2026-05-12

**Reason parked:** scheduler chooses mov.s f16 vs addiu a1,1 in j delay slot; body matches, 1 op different

Seed: `tough_nuts/func_00180550/080550.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_00180550; check asm/matchings/cod/080550/)
```

---

## Attempt at 2026-05-13

**Reason parked:** near-miss: a1 setup before mov.s in built, expected has a1 in jal delay slot

Seed: `tough_nuts/func_00180550/080550.c.new`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_00180550; check asm/matchings/cod/080550/)
```
