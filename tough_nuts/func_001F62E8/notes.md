# func_001F62E8 (src/worm.c) — Worm_Create factory — PARKED at rc12

Best `real_count`: **12** (139/151 bytes byte-exact, from 151 raw). Parked after
~40 distinct hand hypotheses + 3 permuter runs (4000+ iters at the rc12 seed,
no improvement) + a survivorship-bias check. Stall 91/75. Genuine floor for the
sanctioned (union + strict-aliasing + default-cflags) approach.

## What it is/does
`int *Worm_Create(self, cfg)` — spawns a segmented shadow-worm with a collision-
capsule chain (the cling/rope family; cf. commonact.c ROPE_GOBJ/cling strings).
`mgr = self->0x15C` (struct Sub). Allocates ctl(0x10) + segs(0x370=11×0x50);
nSeg=cfg->f10?:10, nCap=cfg->f18?:20; per-seg ptr table (nSeg×4); spawn loop
(random jittered positions via rand func_00118A68, VectorCopy func_00105F00,
0xA0 sub-alloc each); terminates segs, `ctl->head = func_001C58C0(segs)` (return
captured, NOT literal -1); resets mgr (frees old fC/f10/f840 with &0x0FFFFFFF
handle-mask, reallocs nCap*64/nCap*16/nCap*0x50); capsule loop resets each
capsule (clear flag bits {1,2,4}@0x38, scale=(1,1,1), identity quat (0,0,0,1)
@0x40-0x4C); mgr->f818=2; returns ctl.

## Cracked levers (in the seed)
- pos Vec4 declared first → frame off 0, no &pos caching. aligned(16) VECTOR copy.
- seg=segs+i*0x50 below the rand calc.
- bare for-loop (no redundant `if(nx>0)`) — fixes callee-saved alloc [PERMUTER].
- `ctl->0 = func_001C58C0(segs)` RETURN value (not literal -1). 55→39.
- **typed `Cap[]` array `mgr->f840[j].field`** → kills j-loop strength-reduction.
- **`union {long long ll; void *p;} f38`** (tagged-pointer flags) → un-combines
  the 3 flag clears AND drives the correct register allocation (LOAD-BEARING:
  plain long long = 79 with a full register cascade). The sanctioned
  -fno-strict-aliasing replacement.
- chained `f48=(f44=0)` in g3 [PERMUTER lever, hand-applied]. 35→16.
- p840 init order 0x20,0x8,0x4,0x0,0x24,0x28.
- `worm` in config/use_old_as.txt (delay-slot nop, blk 8). 16→14.

## Residual (12) — 3 clusters, ALL verified irreducible under the approach
1. blk 23 (f4C): the identity-quat .w lands in g4 not g3 — union CSE-window
   limitation. PROVEN cheapest: cached-pointer fix = 16 (addu cascade); int-cast
   = 54/cascade; the f4C-split is the smallest blk-23 residual.
2. blk 13 (p840 0x20 vs 0x28 float-store order) — scheduler tie-break.
3. blk 18 (`lw size,32(sp)` vs `lw handle,0(gp)` in 2nd realloc) — scheduler hoist.
blk 13/18 are deterministic scheduler tie-breaks; every reorder/typed/struct
variant regresses, and the permuter (thousands of mutations) can't flip them.

## Root cause & the only path to 0
The ROM was built with **-fno-strict-aliasing** (gcc's CSE window then keeps f4C
in g3 AND schedules those loads its way). The scoped union reproduces the
aliasing but not the CSE-window/scheduler behaviour → the 12-byte gap. If
-fno-strict-aliasing is ever allowed for this TU, it goes to 0. (Tested global
-fno-strict-aliasing = 60 because the REST of the function isn't re-derived under
it — a full -fno-strict re-derivation would be needed, not just the flag.)

## Resume
Seed is the rc12 version. DON'T re-run the permuter (3 shots, exhausted). The
open question is the 2 scheduler tie-breaks (blk13/18) — a source perturbation
exists (scheduler is deterministic) but ~40 hand attempts + permuter didn't find
it. use_old_as.txt already has `worm`.
