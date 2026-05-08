
---

## Attempt at 2026-05-08

**Reason parked:** ee-gcc 2.9 -O2 emits beqz with v1 as ret temp; expected uses bnez with daddu v0,zero,zero in delay slot before branch + a1=s0 in jal delay slot

Seed: `tough_nuts/func_00265B28/165B28.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_00265B28; check asm/matchings/cod/165B28/)
```
