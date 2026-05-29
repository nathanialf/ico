# func_001B8720 (a_p_1) — parked, best real_count 299, 73 sites / ~39 blocks

Large constructor (allocates `this`=func_0013A0F8(...,0x280,...), inits fields,
two near-identical sub-object init blocks for this[0x194]/this[0x198], a matrix
loop like func_001B9638, and an else-branch search loop). Seed compiles & is
structurally complete (the prior seed had a duplicate-signature paste bug —
fixed in this copy).

## Roots (tags: regalloc-swap, frame-size, §5.7)
1. EXTRA callee-saved: ORIGINAL saves $s8 ($30) and frame = -0xE0 (-224);
   built saves only $16-$23+$31 -> -208. The original keeps one MORE value in
   a callee-saved (built spills/reloads it). Opposite direction from B9638.
2. Pervasive regalloc-swap: `this`/index live in s1/s2 in orig vs s3 in built
   (e.g. blk0 `daddu s1,0,0` vs `daddu s3,0,0`; blk7 `mult v1,s1,a3` vs
   `mult v1,s3,t0` for i*0x50). The s1<->s3 / s2<->s3 swap ripples everywhere.
3. §5.7 far-global: a global (likely D_00623468 / D_004BEC00 / D_004BEA80 /
   D_00282660 / D_004BEBA0) reached via cached ptr vs %hi/%lo — try the
   direct-indexed-array lever (far_global_direct_index_hoists_hi).

## Next levers to try
- Make the §5.7 global a DIRECT indexed array (not cached char*) so gcc hoists
  its %hi into a callee-saved -> may supply the 9th reg the original keeps.
- Consistent `o = (int*)this[0x194/4]` caching: the seed mixes cached `o` and
  re-read `this[0x194/4]`; match the original's choice (it likely keeps `this`
  in a callee-saved and re-indexes, or keeps `o`).
- The matrix loop (func_00104140(&mtx)+func_00118648) may want the B9638
  sel-reuse lever (caller-saved reuse forces &mtx remat) — check frame dir.
- Then chase the s1/s3 swap with REG() pins on `this` / the i*0x50 index.
