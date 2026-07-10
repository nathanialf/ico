# enemy_dodge — in-flight near-miss (resume 2026-07-10)

**best rc=30** (was rc41), TU=enemy_act. Seed = full enemy_act.c body at rc30
(`tough_nuts/enemy_dodge/enemy_dodge.c`). Driver best.c also banked at
`build/match_loop/enemy_dodge.best.c` (stall was 11/30 when parked for context).

## Root cause (SOLE): s2/s4 param-coloring tie — permuter territory
- ROM colors `p1(a1)->s4`, `out(a0)->s2`; my build swaps them (`out->s4, p1->s2`).
  ALL ~20 of the original 41 diffs were this one swap (`lwc1 4(s4)` vs `4(s2)`,
  prologue `daddu s4,a1` vs `daddu s4,a0`, etc.). The branch-likely `bc1tl`
  scheduling diff (neg.s-in-delay vs p1[1]-load-in-annulled-delay) and the
  early out->s2 copy placement ALL cascade from this coloring — every branch-form
  / loop-form / store-order reshape canonicalizes (re-demand), confirming they are
  downstream of the coloring, not independent.
- It is a razor-thin global-alloc priority tie (freq/live-length): `out` (12 static
  store refs, long range) vs `p1` (5 reloads + 2 calls, loop-weighted, shorter
  range, reused as `best2` in loop2). Driver tags it **regalloc-swap + fp-licm** =
  permuter territory.

## What got rc41 -> rc30 (KEEP): cache p1[1] once
- `float py = ((float *)p1)[1];` at top, used at all 5 `f1 = p1[1]` sites. This
  cut p1's integer ref count below `out`, flipping the coloring CORRECTLY
  (regalloc-swap tag DISAPPEARS at rc30). Residual 14 diffs are now purely the
  side-effect: `py` is held in callee-saved `$f20` (fp-licm) because it lives
  across the La68 `HandyCamera(p1,p2)` call, whereas ROM RELOADS `lwc1 $f1,4(s4)`
  each time and keeps only the p1 POINTER in s4 across the call.

## The knot (why it's permuter-domain)
- ROM: reloads p1[1] 5x (no value caching) AND coloring is correct.
- My reload form (rc41): coloring WRONG (p1 out-ranks out by a hair).
- My cache form (rc30): coloring RIGHT but py pinned to $f20.
- Tried & FAILED to get "reload + correct coloring": mixed cache/reload at Laa8
  (rc71), per-branch caching (rc79), top-load of pz=p2[2] (rc69), hoist p1->q
  (coalesced=re-demand), shared i/best decls (rc73), drop-src (rc42/47). The exact
  non-caching lever that flips ONLY the coloring (leaving 5 reloads intact) was not
  found by hand — this is the permuter's job (it brute-forces the priority tie;
  cf. func_001FB768 `if((n2=n)>=K)` crack).

## Next worker
- Resume rc30 seed, drive DISTINCT shapes to stall=30 -> driver fires permuter on
  the rc30 seed. The permuter should resolve the coloring tie. Genuine dev-C
  hypotheses are largely explored; remaining hand-shapes are combinatorial padding
  (int-copy stores, double temps advance the stall but are not the dev's C).
- Alternative: run permuter directly on the banked rc30 best.c seed.
