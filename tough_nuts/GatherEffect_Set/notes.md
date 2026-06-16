# GatherEffect_Set (ito/src/gather_effect) — rc13, §3.10 non-global indexed scan

Particle-layout accumulator: `InitParticleLayoutGeo(a0)` -> p; OR all
`entries[i].f0` (stride 0x70, count=p->0x30, base=p->0x24); return `acc==0`.
Special: a0<0 -> return 1; p==0 -> return 1 (direct, not via sltiu).

## Residual (rc13): cookbook §3.10 indexed-table-search, NON-GLOBAL base
- ROM keeps the per-iter `mult i,0x70` (NOT strength-reduced) with a SINGLE
  in-loop `addiu v0,zero,0x70` and cached base (a2). count=a3, base=a2, i=a1.
- ee-gcc strength-reduces `base + i*0x70` to a pointer walk for ANY clean form
  (plain do-while, for-loop, int-array-index, no-cache-base).
- The §3.10 in-loop stride-reassign DOES keep the mult, but without a REG pin
  the hoisted `int stride=0x70` emits a DOUBLED `addiu ...,0x70` (ROM has one).
- §3.10's CLEAN fix (direct global index, no cache) only works for a GLOBAL
  array (constant %hi/%lo address never forms a GIV). Here base = p->0x24 is a
  runtime register pointer -> always inducts. So the clean trick doesn't apply.
- Also: count reg a2-vs-a3 and `blezl` (annulled) vs ROM `blez` (plain, i=0 in
  delay) — a branch-likely reorg tie that likely cascades from the loop regalloc.

Pin-requiring per the cookbook; pins are banned -> permuter case. Seed above is
the mult-KEEPING stride-reassign form (has the structural feature, per the
"seed with the shape that has the feature" rule).
