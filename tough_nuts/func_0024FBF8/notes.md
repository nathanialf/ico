
---

## Attempt at 2026-05-08

**Reason parked:** ee-gcc -O2 emits 'move s1,a0;andi s1,s1,0xFFFF' (2 insns) where expected uses 'andi s1,a0,0xFFFF' (1 insn); function-pointer locals don't reduce

Seed: `tough_nuts/func_0024FBF8/14FBF8.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_0024FBF8; check asm/matchings/cod/14FBF8/)
```
