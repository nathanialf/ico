# func_0025DF38 — PARKED near-miss rc15 (not permuter-run)

VRAM 0x0025DF38. Computes low 64 bits of (long long)a0 * (long long)a1, i.e.
the body of __muldi3, INLINED with EE's two multiply pipes:
  a0_lo*a1_hi (mult), a0_hi*a1_lo (mult1), a0_lo*a1_lo (multu→mflo/mfhi),
  result = lo32(lolo) | ((hi32(lolo) + a0_lo*a1_hi + a0_hi*a1_lo) << 32).

## Status
- `return a0 * a1;` → ee-gcc emits a JAL to __muldi3 (rc23), not the inline.
- Explicit schoolbook (the seed) → rc15: correct opcodes (mult/mult1/multu/
  mflo/mfhi/dsll32/dsrl32/or/and) but wrong register allocation + the lolo
  64-bit recombination sequence differs from gcc's internal __muldi3 lowering.

## RESUME
This is gcc-2.9's inline __muldi3 expansion. To match, either (a) find the
exact C that makes ee-gcc INLINE the 64-bit multiply (a flag/pattern — the ROM
build clearly inlined it), or (b) reproduce the exact internal recombination
(the mflo→dsll32, mfhi→dsll32, or, then dsra32/and/dsll32/or tail) with the
exact reg order. Possibly a math-lib macro in the dev source. Hard hand-match.
