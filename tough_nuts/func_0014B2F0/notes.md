# func_0014B2F0 — parked

VRAM: 0x0014B2F0 (file offset 0x04B2F0)
Asm source: `asm/cod/04B270.s`

## Attempt at 2026-05-08

**Reason parked:** ee-gcc 2.9 emits the bit-test (`1 << idx & low32`) in 8 instructions versus the expected 10. The compiler folds the `(1 << idx) & val ? 1 : 0` ternary into shift+and+movz, but the original codegen also has an explicit ld of the qword field at 0x58 and a separate sllv on the constant 1. Likely needs `(long long)` types or volatile qword load to match.

Seed: `tough_nuts/func_0014B2F0/04B2F0.c`

---

## Attempt at 2026-05-08

**Reason parked:** leaf bitfield-test: ee-gcc emits dsrav+andi (8 insns); original sllv+and+movz (10 insns) — bit-extract idiom diff

Seed: `tough_nuts/func_0014B2F0/04B2F0.c.new`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_0014B2F0; check asm/matchings/cod/04B2F0/)
```
