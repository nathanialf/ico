
---

## Attempt at 2026-05-08

**Reason parked:** near-miss: gas pulls daddu $a1,$sp into jal delay slot instead of sw zero,4($sp); 1-instr scheduling diff

Seed: `tough_nuts/func_0017CB20/07CB20.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_0017CB20; check asm/matchings/cod/07CB20/)
```

---

## Attempt at 2026-05-08

**Reason parked:** buf-pack 2-call: ee-gcc swaps daddu a1 vs sw zero in jal delay slot vs original

Seed: `tough_nuts/func_0017CB20/07CB20.c.new`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_0017CB20; check asm/matchings/cod/07CB20/)
```
