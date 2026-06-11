# isysGObjProcessAlloc (fumi/isys/gobj_process) — parked at rc7, permuter-class

Big allocator (0x244, 9 params s0-s7): free-slot scan over the D_0062BFB0
array (count D_0062BFB4, stride 0x94) → if full, double assert + per-entry
assert loop → else thread-spawn (iosThreadWakeup/Join) when a3&0xFF==0, or
slot[0x1C]=a2 when set → sorted doubly-linked insert into mgr(a0) head@0x2C/
tail@0x30 by key a4 (slot fields next@0x8 prev@0xC owner@0x4 id@0x14...).

## Reconstruction: 44 → 7 true diffs (all structural matching DONE)
Key levers found this session:
- list/array key compares are UNSIGNED → `(unsigned)a4 < (unsigned)node[5]` (sltu).
- flag check INVERTED: `if (flag==0){thread}else{slot[0x1C]=a2}` (bnez flag→
  flag-path target, thread fall-through).
- assert per-entry loop must be a guarded **do-while** (not for) → counter
  coalesces into s1 (the slot reg). 27→17.
- assert element addr **product-first**: `(int)(j*0x94 + (int)D_0062BFB0)`
  fixes base/product reg swap ($2/$3). 15→11.
- empty-list init order `slot[3]=0;slot[2]=0;mgr[0xB]=slot;mgr[0xC]=slot`. 28→15.
- head-insert order `slot[2] before slot[3]`. 28→27.
- load `head = mgr[0xB]` EARLY (before the slot-init stores) → bne (not bnel)
  with slot[0x14] in the delay. 11→9.
- head-insert: read mgr[0xB] once into a FRESH local `h` (NOT the early
  `head` — that swaps s2/s3). 9→7.

## Residual rc7 (permuter-class scheduling/coalescing ties)
1. Scan (~3): `daddu a2,count` count-copy + `addiu i,i,1` (i++) vs my i=1 —
   a coalescer live-range-split (loop bound vs post-loop count), same class as
   isysGObjProcAdd's $5 copy.
2. Head load scheduled 1 position early (gcc hoists `lw head` above the `=1`
   const setup); source position doesn't move it (~2).
3. Head-insert mgr[0xB] load 1 position early (~2).

~40 distinct hand shapes tried (scan forms, init orders, head caching, msg
hoist). Residual is gcc hoisting/coalescing — hand-unreachable. Seed = the
rc7 form. Permuter (correct aug6 compiler via compile_c.sh) should perturb
the count-copy split + head-load hoist.

## Permuter shot (this session) — beat nothing (rc7 stands)
Fired at stall=32/32 (correct aug6 compiler via compile_c.sh). ~6 min, slow
per-iteration on this 145-instr func (~10 iters). Best by internal score 335
vs base 525 — the `new_var=count` count-copy form — but harvests to **rc7**
under match_diff (score != real_count, same caveat as isysGObjProcAdd). No
real improvement. (b) parked at rc7. Resume: longer permuter run, or hand-
crack the count-copy live-range split + head-load hoist.
