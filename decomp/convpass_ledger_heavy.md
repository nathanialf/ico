# conv-heavy ledger (worktree ico-rwt3, branch conv-heavy)

Scope: hardest sets — src/act-env.c (6 funcs incl. func_001FCA20, the largest
retail function), then shiftMotionOrientEndFunc, pool.c, boyact.c.

## Counterpart identification (position/size, all confirmed)

| retail | insns | aug6 twin (fumi/src/act-env.c) | aug6 state |
|---|---|---|---|
| func_001FC6C8 | 46  | func_001FA078 | INCLUDE_ASM (no source) |
| func_001FC780 | 168 | func_001FA130 | INCLUDE_ASM (no source) |
| func_001FCA20 | 3978| func_001FA3D0 | **MATCHED** (main dc8179be) |
| func_00200848 | 74  | func_001FE0A8 | INCLUDE_ASM |
| func_00200970 | 32  | func_001FE1D0 | INCLUDE_ASM |
| func_002009F0 | 42  | func_001FE250 | INCLUDE_ASM |

Retail-new helper `func_001FC520` (0x001FC520, attributed isys/gobj_cam_dl.c,
106 insns) absorbs the aug6 inline float-table selection (D_004C6EC0..F30) —
those rodata tables have NO retail equivalent inside func_001FCA20.

## func_001FCA20 — convergence state: **pass-deferred at rc 883, structure CONVERGED (+3 insns: built 3981 vs 3978)**

Seed: `tough_nuts/act-env_func_001FCA20/act-env_rc883_seed.c` (drop-in
replacement for src/act-env.c; compiles clean; from-1379-to-701-to-883 —
the 883 is AFTER adding retail-new blocks that aren't letter-perfect yet;
low-water 701 predates the site-1/site-2 chain guards + arm tail).

### How the port was made (repeatable)
1. Temporarily rename retail symbol 0x001FCA20 -> `func_001FA3D0`
   (+ provisional-ordinal tag) in config/symbol_addrs.us.txt and in the
   INCLUDE_ASM line; rm .port_cache/retail_labels.json; `port_from_aug6.py
   scan --force` then a monkeypatched dry-run port (tolerant build_symbol_map
   that RETURNS the partial mapping instead of aborting; PORT_DEBUG_DUMP to
   harvest the spliced TU). 81/93 reloc slots bound mechanically; rest were
   rewritten-region symbols (see below). Scripts in the session scratchpad
   (tolerant_map.py / context_dump.py / worklist.py / imm_census.py pattern —
   trivial to recreate: they wrap port_from_aug6 internals).
2. The splicer misses aug6 MACRO helpers — carry over by hand (rebound):
   EnvCamAngle, EnvCamAngleP, EnvAssistLoop (0x178->0x188 inside!),
   EnvAssistTail, EnvWallAssistVec. Missing them = implicit externs =
   -1.0f promoted to double in $a3 (dli 0xbff0...) + un-inlined arms.
   Adding them alone dropped rc 1026->701.

### VERIFIED retail edit catalog (all occurrence-count-verified vs both ROMs)
Symbol maps: D_0062D9D8->D_00633850(float, far: use
`extern float D_00633850_[] __asm__("D_00633850")`), D_0062D9DC->D_00633854,
D_00629DE4->D_00631AE4, D_00629DE8->D_00631AE8, D_00629C90->D_00631990,
D_00629738->D_00631468(gp float), D_00629754->D_0063146C, D_0055DA10->D_00565060,
D_005EBC48->D_005F2FB8, jals by name incl. func_0023FFF0->func_00243AD0,
func_00240038->func_00243B18, func_0023FDD8->func_002438B8,
func_00191D90->func_00194590, func_00191FD0->func_001947D0,
GetBoxGlobalHoldPoint->func_001C05B8.

Struct offsets:
- gobj+0x15C substruct: +0x10 for 0x170,0x178,0x188,0x490,0x550..0x56C,
  0x594,0x5C0,0x5D0,0x5D4,0x634,0x1C0,0x1D4 (and byte forms 0x177..0x18F).
  arg4's struct: UNCHANGED (copy DESTS stay, only substruct SOURCES shift).
- env struct: 0x110->0x120 (the S chase). env+0x4A0/0x550/0x5A0 unchanged.
- env->0x678 struct: +0x20 for the whole 0x720..0x7A8 store blocks.
- Camera table D_005F2FB8: stride 0x190->0x194, member 0x18C->0x190
  (typedef CamEntry {pad 0x180; float f180; pad 0xC; uint u190}).
  D_00565060 (MotionEntry) stride stays 0x190.
- __LINE__ 0x917 -> 0x978 (x3).

Flag renumbering (bit = as spelled in C):
- env+0x18 (LL): bits >=49 +1 (<<34->35, <<35->36 x2, <<36->37; masks:
  0xDFFF..->0xBFFF..). Bits 24,25,35,36(old refs),47 unchanged.
- env+0x470 (LL): bits >=51 +1 (<<43->44, <<47->48, <<38->39, <<36->37,
  <<37->38, >>58->>59). 0x20000/0x40000/0x80000 chain + low bits unchanged.
- env+0x478 (LL): |=1 stays, |=2->4, |=4->8, <<46->47; at the ==0x37 site
  retail does BOTH `|=8; |=0x10;`. ccat switch REWIRED: case 0x64 -> 0x470
  |= 0x8000LL<<48 (standalone); case 0xC8 -> 0x478 |= 1 (hosts shared
  or-tail); case 0x12C -> 0x478 |= 2 (goto shared tail).
- env+0x468: fully unchanged.
- env+0x20: |=0x20 -> |=0x100; bit15|= -> bit22 (|=0x8000 -> |=0x400000, now
  guarded by `func_00194590(boy, arg2) < 0x2D` — guard already existed);
  <<14>>32 -> <<7>>32 (bit18->25) w/ ~0x40000 -> ~0x2000000; <<13>>32 ->
  <<6>>32 (bit19->26); NEW readers: `<<0x1D>>0x20` (bit3? spelled <<0x1D)
  guard on the f22<50 box block; entry three-way now tests <<0x1B then <<0x1C.
- arg3+8 (word): bits >=16 +1 (0x10000->0x20000, 0x20000->0x40000, <<24->25
  x3, <<25->26, masks FEFF->FDFF etc, 0x400000->0x800000 x3,
  0x800000->0x1000000, >>22->>23); |=0x8000 site -> `(x & 0xFFFEFFFF) |
  (fl40<<16) | 0x8000`; |=0x400 site -> `(x & ~0x400) | (fl40<<10)` where
  **fl40 = (f22 < 40.0f) new flag**; bits 13,14,15 unchanged.
- arg3+4, arg3+0: unchanged EXCEPT arg3+0xC: one of two |=0x10 -> |=0x40
  (the one after the FDFF/FF7F masks).
- Float consts: EnvCamAngleP-region D compare 230.0f->65.0f?? NO — verified
  aligned: 65.0f site pre-existed; real changes: case-0x16 arm ascale
  5.0f->45.0f. Threshold chain 55/105/205 UNCHANGED (early pairwise diffs
  there were difflib slips — ALWAYS occurrence-verify).

Structural (all in the seed):
- NEW `wFlag` (slot 0x1E0, zero-init at entry): set by a NEW plane-test block
  before the f21<20 dispPlane region: if (FI(0x30)==D_00631AE4 && D_00631AE8)
  {3x ContinueCorrectPosition(D_00631AE8)->FF(0x60..0x68);
  d2=HandyCamera_TargetMoveType(FI(0x1C4), FP(0x60));
  rowf=CamEntry(D_005F2FB8)[D_00631990].f180; if (d2 < rowf*rowf) {
  func_00243AE8(FP(0xB0),FP(0x60),FP(0x10)); _OrientGV(FP(0x70),FI(0x1C8));
  fBC=0(int store); func_002438B8(FP(0xC0),FP(0x70),FP(0xB0));
  if (0.0f < FF(0xC8)) wFlag=1; }}. Read later: `f24>350 && wFlag &&
  ACTEnvGetTest()==0` condition.
- aug6 FI(0x1C0) SPLIT: cage-found -> own slot 0x1E4 (w1C0 after wFlag in
  decl), all uses incl. chainbody boy/hit follow it.
- NEW `wPtr20` (0x1EC) = (int)&v02 saved right after w20 setup; used by the
  NEW `func_00194590(FI(0x1C8), wPtr20) < 0x3C` clause appended to the big
  D_00631AE4 condition (before EnableChangeRootUpdateMode).
- `wAang` (0x1F0): aang became memory-resident (read back via lw and
  lwc1+cvt.s.w); FI(0x1D4) (aug6 wall-ptr var) DELETED — its guard
  `EnvSlotDist(FI(0x1D4),..) < D_0062973C` replaced by
  `if (FI(0x1C0)==0) FI(0x1D0)=0;` (movz) + `if (FI(0x1D0))`.
- Frame: dv18 kept + NEW dv19,dv1A (slots 0x180/0x190/0x1A0) — retail
  buffers replacing aug6's reuse of fC0/fD0/fE0 in chainbody/hit-tail
  (FP(0xC0)->v18+v18[1]=0 spelled `sw 0x184`, FP(0xD0)->v19, FP(0xE0)->v1A;
  in the idx-loop arm FP(0xD0)->FP(0x180)). **Slot order = FIRST
  ADDRESS-MATERIALIZATION order; force it with dev-style dead reads**
  (`ccat = *(int*)((char*)&dv19+4);` etc. after the dv18 read) — this is the
  load-bearing trick that moved w190.. to 0x1B0+ (rc 1129->1035).
- Helper-region rewrite (idx-loop): table-select block ->
  `FI(0x194)=0; FI(0x198)=0; func_001FC520(&FI(0x190),&FI(0x194),FP(0x160),
  FP(0x170),&FI(0x198));` + buffer moves FP(0x90)->FP(0x140)(v14),
  FP(0xA0)->FP(0x150)(v15), FF(0xB0..)->w160-as-float (union IFAlias),
  FF(0xC0..)->v17; chainbody p90->v14, g90->FP(0x160), w70->&v15[1]-4,
  d-compare reads w164-as-float; loop gains
  `if (InitPendulum(fnd3)==0) goto next; GetRootMatrixByDObj(FP(0x170),fnd3);
  if (!(func_00194590(FP(0x170), FI(0x1C8)) < 0x2E)) goto next;` prelude;
  fth = D_0063146C.
- stt-machine: case 0x11 calls func_001C05B8; both f22/f21<40 blocks gain
  `D_00631990 ∈ {0x54,3,0x2E}` + `*(FI(0x30)+0xC)==4 -> skip-both` guards
  (site 1 outer compare 40->200 + fl40 computation); case-0x16 arm: ascale
  45.0f + appended `func_00243B18(FV(0x70),arg4,-10.0f);
  func_001945B8(FV(0x70), D_00631450); func_00243AD0(dst,dst,FV(0x70));`.
- 1BC-threshold chain precondition: `FI(0x1BC) && (D_00631AE8==0 ||
  kind(D_00631AE8)!=0x6B || *(+0x134)!=FI(0x30))`.
- entry: bit5/bit4 three-way (f25=0.0/100/300), env0x18 commit before it.

### Residual analysis at rc883 (what a successor should attack)
Structure is aligned to +3 insns. Residual = whole-function coloring family:
1. **Register census rotation**: retail s3=s6var(0x564-load), s4=env,
   s5=arg3, s6=arg4(t0), s7=s7var(0x574-load), s8=boy. Ours: env=s3,
   arg3=s4, s6var=s5, arg4=s6, **s7var SPILLED to a late slot** (and
   `daddu s8,a1` + a1 ALSO homed at 456 = boy gets a param home ROM lacks).
   The boy-home append and the s7var spill are the two anchors; everything
   else letter-rotates off them. s7var dies before the fl40 region (fl40
   lives in $23 there, per ROM). Suspect: priorities shifted by the new
   wFlag/wPtr20/wAang pseudos; try (a) giving s6var an extra early use /
   shortening env's range, (b) making fl40's block-scope explicit, (c) the
   fa3d0 memory's copy-preference/census techniques (COOKBOOK §13, gcc
   internals reference in the decomp-convergence skill).
2. Small structural leftovers (opcode-verified): E~448 wAang abs reload
   shape (6-insn insert; reg-abs-temp spelling made it WORSE, rc+109 —
   don't retry); E~524-537 differ-artifact only; E~1128 case-0x17 store
   order vs S/anch chase (sched); E~2223 8-insn insert near swc1 144(s7)
   region (un-diffed); E~3152; E~3428 `|=8;|=0x10` currently emits ld/or/or/sd
   fused vs ROM ld/or/sd;ld/or/sd — spell as two full statements via
   separate `((union LLAlias*)...)->ll` stores (ours already is — check
   whether volatile-less re-read is being CSE'd; may need the union-store
   pattern from §13); E~3596 jal shape.
3. quick_diff false-negative caveats apply (in-TU calls resolve differently);
   final gate is ninja.

Recommended next session: load the seed, run the census matrix
(hard-reg per-opcode counts vs ROM) per the fa3d0 method, work the boy-home +
s7var-spill pair FIRST (they're the census anchors), THEN re-run the small
structural list. Expect group snaps, not monotone count decline.

## Small siblings

- func_00200970 (32): attempted below.
- func_001FC6C8 (46): called from func_001FCA20 as
  `int func_001FC6C8(void *buf, void *p10, void *pC8, float f12, float f13)`
  (aug6 twin func_001FA078 extern:
  `int (void *a0, void *a1, void *a2, float f12, float f13)`).
- func_001FC780 (168), func_00200848 (74), func_002009F0 (42): not started.

## shiftMotionOrientEndFunc / pool.c / boyact.c

Not reached this session (budget exhausted by the big-func convergence).

## Session results (pass 1 final)

- func_00200970: **MATCHED** (commit d6b2bdf0). Factored env-anchor push
  block; key lever: `void *hp = (void *)*(int *)(bx + 0xC);` temp BEFORE the
  1.0f union store so the arg load precedes it and the swc1 fills the jal
  delay.
- func_002009F0: **MATCHED** (commit aa3e3ad7). Verbatim EnvAssistLoop
  do-while (acc[4] aligned-16 stack buf, i=3 countdown, w+=0x10 in delays)
  + `if (a1) { union-store 1.0f; func_002438B8(dst, *(box0x15C+0xC), dst) }`.
- func_00200848: pass-deferred at rc46 after 3 hypotheses. Structure EXACT;
  residual = uniform one-step register-letter rotation on the six unfolded
  `v |= 0x8000LL << N` const pseudos + accumulator (ROM accum=v0
  consts a2,a3,t0,v1,a0,a1; ours accum=t0 consts a1,a2,a3,v0,v1,a0).
  KEY discoveries that got here: (a) separate `v |= const;` STATEMENTS on a
  local long long do NOT constant-fold (one expression DOES fold to dli);
  (b) mask is ~bit38 = 0xFFFFFFBFFFFFFFFFLL (addiu -0x41 signed build);
  (c) env+0x18 must be READ AFTER the ACTEnvGetTest call (shared load lands
  in the beqz delay; both arms CSE it). Body sits in git history at
  17109860..aa3e3ad7 range (this ledger's diff) — recover via
  `git log -p decomp/convpass_ledger_heavy.md` or rewrite from the catalog
  above. Leading hypothesis for the letter rotation: allocation-order tie —
  try routing the accumulator through the union deref as FIRST pseudo, or
  the [const_temp] early-temp lever on the <<25 const.
- func_001FC6C8 / func_001FC780: not attempted (no aug6 source; 001FC6C8's
  full signature + call context documented above).

## conv-heavy2 session 2 (2026-07-28): func_001FCA20 rc 883 -> 566 (sites 494 -> 344)

Seed = `tough_nuts/act-env_func_001FCA20/act-env_rc883_seed.c` (now the rc566 body;
same file name kept as canonical). Milestones: `act-env_rc566_s344_censusV2.c`
(= seed), `act-env_w70v-remat_v14scalar_rc571_s344.c`, `act-env_w70v-arch_bltzl_rc759.c`
(w70v-restored dead-end branch, kept as labeled fallback).

### Landed levers (all occurrence-verified vs ROM)
1. **w70v REMOVED** (macro FP/FV_0x70 -> &f70 direct): the pointer var was a
   single-set REG_EQUIV pseudo that WON s8 whole-function; ROM has no such
   pseudo (per-site remat `addiu aX,sp,112`). rc 883->725. Census snap:
   env->s4 ✓ROM, arg3->s5 ✓ROM.
2. **p90 removed / v14 -> float scalars w140,w144,w148(,w14C)**: chainbody +
   idx-loop v14 stores now frame-direct like ROM. rc 725->571. CAVEAT: this
   conversion left w14C unplaced — related to the +16 frame regression (see
   residual 1; w14C never touched = only 12B allocated).
3. **fl40 shape**: `fl40 = 1; if (!(f22 < 40.0f)) fl40 = 0;` reproduces ROM's
   bc1t+delay-set1 (FP negation can't invert -> bc1t). The if/else spelling
   gives bc1f (wrong arm taken).
4. **CageFixDL result guard**: `if (CageFixDL(cagem, &f50, found) == 0) continue;`
   in the cage search loop (extern now int) — ROM's beq@180.
5. **wAang abs**: `{ int aat = EnvCamAngle(...); aat = (aat<0)?-aat:aat; wAang = aat; }`
   — ternary on a TEMP folds to ABS rtx -> mips abssi2 = ROM's bltzl/negu, then
   ONE sw. (Ledger's old E~448 "don't retry" note is RESOLVED — the failed try
   was abs-on-the-memory-resident-var; temp+ternary is the shape.)
6. boy late-chain split (`cg` block-local at the cage block) — byte-neutral but
   dev-correct; late `hit` chain was already separate (colors s7-pool in ROM).

### Mechanism map (verified via -dg/-dl greg/lreg dumps, dumps in scratchpad conv2/dumps)
- Priority = floor_log2(refs)*refs/live_length*10000 (ee-gcc global.c
  allocno_compare, CYGNUS range-copy tier first); regs assigned lowest-free in
  REG_ALLOC_ORDER (numeric); pockets time-share letters.
- gcse (want_to_gcse_p accepts ANY non-reg/const expr) is what glues repeated
  `&local` address exprs into multi-set pseudos (no REG_EQUIV -> can never
  remat). ROM's per-site remats mean the retail source never lets two sites'
  spellings unify: `(char*)&f74 - 4`-style offset-fold defeats CROSS-SITE
  unification in the big TU (though NOT in a minimal probe: cse folds const
  chains eagerly there).
- Current mapping at rc566: env=s4✓ arg3=s5✓ arg4=s6✓ movn-pair {s1,s2}✓;
  C-s6var(ld 0x564)=s7 (ROM s3), C-s7var(ld 0x574)=s8 (ROM s7), boy=456(sp)
  memory home (ROM s8, dies asm~552). ROM s8 is boy THEN the lui-%hi table
  base (D_00565060 area) 721-1508 THEN pockets; OUR lui-base remats per site.

### Residual at rc566 (built 3998 vs 3977; frame 752 vs 736) — ATTACK ORDER
1. **frame 752 vs 736 = TWO EXTRA FPR SAVES (f26+f27)**: ours keeps two floats
   alive ACROSS CALLS in the idx-loop `FI(0x194)` copy block (C ~1712-1727):
   `w144/w148 = ((union IFAlias*)&w164/8)->f` values stay in f26/f27 until the
   f21<60 arg4-store block; ROM stores to w144/w148 memory and RE-READS all six
   (lwc1 320..344(sp) -> swc1 96..120(s6), ROM 2984-2998) with NO cross-call
   float pseudo. Find the source spelling that forces the re-read (suspects:
   the two ifs' relationship, or writes via a pointer the second block's reads
   can't forward from). THIS IS THE #1 LEVER: it frees f26/f27, restores
   frame 736, and un-shifts the FPR-save block (every +16 slot diff).
2. **boy/s8/census endgame**: boy (p85: 5 refs, ll 421) blocked from s8 by
   whichever pseudo wins it first; with w70v gone the s8 winner is now
   C-s7var(ld1396). ROM order: s3-blocker pockets put C-s6var on s3, C-s7var
   s7, boy s8, lui-glue s8-mid. Ours' lui base (D_00565060 %hi) must become a
   SHARED callee-saved pseudo 721-1508 like ROM (ours remats per site
   currently!) — check why ROM glues it and ours doesn't (same gcse question
   inverted: ROM's glue = likely a USER-style temp / 3 uses reachable, ours'
   sites got isolated by an extra/missing CFG edge). Boy-home removal collapses
   the +4 slot shift on 456..476 homes.
3. Branch-likely worklist (from full skeleton diff, remaining): ROM
   bne/beq@385/390 vs ours bnel/beql (D_00633850 lui in delay — dbr steal
   context differs); ROM beq@1056 3rd stt-re-read path (coloring-coupled
   cross-jump, source edit re-merged — leave until letters land);
   ours-extra beq@~1496; ROM bnel/bnel/bc1fl@1870 vs ours plain (likely flips);
   bc1f/bc1fl pair @3018/3130; beql+jal@3593 (old E~3596).
4. quick_diff false-positive caveats: gate ninja at the end (in-TU calls).

### Tried and refuted this session (do NOT blind-retry)
- AVEC arrays / struct-of-floats for dv15..dv1A: BOTH scramble frame layout
  (aggregates place differently than TImode scalars; +16 and slot shuffles).
  TI128 + targeted scalar splits is the only placement-safe form found.
- g1A0..g1AC scalar split of dv1A w/ 4 dead reads: slots landed wrong (w190
  cluster moved); reverted.
- float w70b[4] array for the 0x70 buffer: kills the gcse glue beautifully
  (28 direct hard-reg remats, env->s4 held) BUT costs +16 frame vs scalars
  and letters didn't finish; scalars + &f74-4 offset-folds kept instead.
- skip-path third stt re-read (goto L10d): compiler re-merges identical
  copies; the 3-copy shape in ROM is a downstream regalloc artifact.

### Round-2 addendum (same session): f26/f27 characterization sharpened
- The two extra FPR saves carry the `w144/w148 = w164/w168-bits` copy values
  from the FI(0x194) write block ACROSS THE BACKEDGE to the f21<60 arg4-store
  join (write block is laid out after the join; bc1t jumps back up). ROM keeps
  the stores + re-loads all six at the join (lwc1 320..344 -> swc1 96..120(s6),
  and its write block is six direct lwc1/swc1 pairs 352..376 -> 320..344).
- REFUTED vehicles (tried, reverted): int bit-copies `*(int*)&w144 = w164`
  (rc+2, f26/f27 SURVIVE — the carried value is the w164 LOAD, not the store);
  `int w16a[4]` array for the w160 group (array landed at wrong offset,
  rc 992 — arrays are placement-fragile here, same failure family as the
  dv15..dv1A aggregate attempts).
- OPEN leads for the next worker: (a) make the JOIN read six loads by breaking
  the w14X/a15-load equalities (offset-fold spellings ON THE JOIN READS, e.g.
  `*(float*)((char*)&w148 - 4)`, which defeated cross-site unification for
  &f70); (b) reorder the write block to match ROM's six-pair shape (ROM loads
  ALL six THEN stores all six — ours interleaves; a15/a17 copies via pointer
  regs s0/s2 where ROM is sp-direct, so the a15/a17 access spelling
  (TI128-cast) is part of the same knot); (c) check whether ROM's write block
  order = w160-group copies BEFORE a15=a17 copies matches our C statement
  order, and whether v15/v17 need the same scalar treatment as v14 (placement
  via consecutive dead-reads at the dv15 q-pair site, NOT type change).

## conv-heavy2 session 3 (2026-07-28): func_001FCA20 rc 566 -> 528 (sites 344 -> 314)

Canonical seed = `act-env_rc883_seed.c` (= `act-env_x37split_rc528_s314.c`), built
+4 insns vs ROM, crutch-free. Commits: 447bed7f (rc531), this one (rc528).

### Landed levers (occurrence-verified)
1. **0x140-0x178 buffer bank fully scalar + memory-resident** (rc566->531; the
   round's #1 lever, killed f26/f27 + frame 752->736 + un-shifted all +16 slots):
   - dv15/dv17 (TI128) -> float scalars w150,w154,w158(,w15C) / w170,w174,w178
     (,w17C decl-only). Root cause: w144/w148 (and v15/v17 elements) were
     non-addressable -> gcc pseudo-ized them -> the FI(0x194) write block's
     loaded values rode f26/f27 across the backedge to the f21<60 join
     (SEMANTICALLY WRONG on the skip path: callee-written buffer values ignored).
     ROM re-reads all six at the join (lwc1 0x140..0x158 -> swc1 0x60..0x78($22)).
   - Slot placement via the aug6 f90..f9C dead-read idiom (aug6 final source
     lines 813-817): `g90 = (char *)(int)*(long long *)&w140/144/148/14C;` before
     the FP(0x140) use; `q`-reads for w154/w158/w15C after the &w150 pair;
     `ccat = (int)*(long long *)&w174/&w178;` after Lcfix's FP(0x170) call.
     **WIDTH RULE: dead reads MUST be `*(long long *)&x` (wider than the var) —
     `*(int *)&floatvar` folds back to a reg access and does NOT materialize.**
   - Write block + join spelled as 6-temp blocks (t0..t5 loads then 6 stores) =
     ROM's 6-load/6-store clusters; chainbody w14X = 3-temp block (arg4 loads
     cross-base can't reorder; frame-frame CAN, so 6-temp is belt+braces).
2. **join flag `|= 0x20`** (was 0x10; ROM addiu $3,$0,0x20 — flag-renumber site
   the catalog missed).
3. **0x37-site CFG split** (rc531->528): ROM branches around ONLY the `|=8`;
   `|= 0x10` is UNconditional inside `e > 60.0f` (bne jumps INTO the ld/or/sd
   pair; delay-slot ld + re-read after the |=8 store emerge naturally).
   Byte-matches ROM shape now.

### Census/rotation analysis (the remaining big knot — leads, verified numbers)
Mapping (rc528): pair{18,19} s6=$23 s7=$30 boy=456(sp) env=$20 arg3=$21 arg4=$22.
ROM: pair{17,18} s6=$19 env=$20 arg3=$21 arg4=$22 s7=$23 boy=$30(dies ~552, then
lui D_00565060 glue 843-1768, then pockets 3154+/3744+ — our pockets 3-5 already
match). Verified pseudo stats (dumps in scratchpad conv2/, greg3_fca20.txt):
env p202 refs=122 len=3394 (prio 2157, alloc pos 121); arg3 p87 106/3392 (1875,
pos 128); arg4 p88 90/3370 (1602, pos 137); s6 p203 13/700 (557, pos 169);
s7 p204 5/251 (398, pos 176); boy p85 5/418 (239, pos 189). Priority formula
confirmed from ee-gcc global.c allocno_compare (staged src, 04159692 scratchpad:
eegcc_src/global.c:794): REG_N_RANGE_COPY_P tier (inactive; only range.c sets
it) then floor_log2(refs)*refs/len*10000; find_reg = lowest-free in
REG_ALLOC_ORDER THEN copy-preference/preference override (global.c:1443+).
- s6 CANNOT outrank env by priority (would need refs x3). ROM's s6=$19 must come
  from $19 being conflict-blocked for env at env's turn: in ROM a HIGH-prio late
  pocket (pos<121) holds $19 with range inside [983..3990] (no overlap with s6
  [54..998] -> s6 takes $19 free later). ROM $19 late = pocket parade (anchor
  +0x4A0 at 1332/1497/1574, i=3 loop 1401-22, dstc arg4+0xC0 1662, flags 1807+,
  &fC0 3160, &w170 3760). Ours under-crowds $16 (census 201 vs ROM 208) and the
  pocket fabric differs -> $19 stays free at env's turn. The rotation will snap
  from SMALL structural classes recoloring pockets, not from one mover.
- **w70v probe (REVERTED, fallback stash act-env_w70v_x37_rc721_fallback.c)**:
  restoring aug6's `char *w70v` + FP/FV_0x70 macros DID snap pair->{17,18},
  s7->$23, arg4->$22 but w70v itself won $30 (p195 refs=31 len=168 prio 7381,
  pos 60 — retail's rewrites removed the late FP(0x70) uses that in aug6 made
  it len~3600/prio~108 -> spilled). It also cost +138 insns: the twin
  EnvWallAssistVec(...,30.0f) arms' locals swapped letters (s1/s2) so
  post-reload cross-jump could NOT merge the arm tails ROM merges. ROM's
  per-site `addiu $4/$5,$29,0x70` remat = RELOAD exploding a SPILLED w70v's
  REG_EQUIV per use (aug6-proven: aug6 w70v spills, boy=$fp wins $30 with prio
  239 vs 108). For retail source the dev's w70v (or equivalent) must be LOW
  priority. Next lever candidates: (a) find retail-real LATE f70-family uses
  (ROM's last sp+0x70 materialization is 1092/1101; $18-local copies at
  227/765) that lengthen w70v; (b) alternatively keep rc528's &f70-direct and
  break ONLY the same-EBB double-use glue at the EnvCamAngle macro sites
  (ROM: 381/386, 411/418, 1071/1080, 1092/1101 = per-call addiu into $4/$5);
  offset-fold `(char*)&f74-4` does NOT work there (same-EBB cse folds it).
- Entry-block nit: ours zeroes s7var in the bne delay (executed both paths);
  ROM zeroes only on fall-through (nop delay) — C shape of the `if (0x188==0)
  {s7=0;s6=0;}` needs the §8.3-family look.
- 195.0f site verified correct (dead `s6=1` store deleted, bare c.lt.s remains
  both sides). dli-vs-addiu/ori-dsll in .s listings assemble identically —
  don't chase them in the .s; trust match_diff.
### Structural leftovers (current --full map, exp-indices at rc528)
exp5/11 prologue boy-home (the rotation); 81/83 sw zero,468 vs 476 (+4 slot
shift from boy home 456); 523 ROM-only 13-insn EnvCamAngle+abs+slti45 block
(ours lacks it THERE — check for a missing retail guard call); 1369-region:
differ mis-alignment around the stt arms (occurrence-verify before touching);
2221/2222 lwc1/swc1 144(s6) 8-insn insert (the old E~2223); 3253/3269/3354/3361
small addiu/lwc1 placement nits near the chainbody loop preamble.

## conv-heavy2 session 4 (2026-07-28): func_001FCA20 rc 528 -> 579 @ sites 314 -> 310 (structure-forward; 14 semantic classes byte-fixed)

Canonical seed = `act-env_rc883_seed.c` (= `act-env_w60fix_rc579_s310.c`). Commits:
0c7a0330 (rc582/s311 semantic batch), this one (w60fix rc579/s310). The raw
count ROSE from 528 because the seed's letter-noise re-aligned; SITES are the
structure metric (310 = all-time best) and 14 previously-wrong semantic sites
now byte-match. Milestones kept: `act-env_semfix_rc582_s311.c`.

### Landed this session (all occurrence-verified vs ROM)
1. Port-miss offsets: env+0x160->0x170 x3 sites (1909/2119/2120-region),
   env+0x130->0x140 (ACTGameCollisionOff site), sub+0x490->0x4A0 (mo3),
   sub+0x558->0x568 (1BC-precondition), h+0x124 -> **g = *(FI(0x30)+0x134)**
   (base AND offset changed; ROM keeps g in s0).
2. arg3+8 flags: the two `|= 0x400000` sites (case 0x70 / case 1,0xF,0x2A)
   -> `|= 0x800000` (ROM lui census 0x80 x5 / 0x40 x3 now exact).
3. PAIR_GetPosition_BOY first arg = (int)ContinueCorrectPosition(g) (was
   FP(0x10)); beql+delay-lw48 shape emerges naturally.
4. p80 = (char *)&dv13 (v13 buffer, ROM addiu s1,sp,304) — was &f84-4.
5. **w60-binding fix (exp1981 region)**: `w60 = (char *)&f6C - 12;` +
   HandyCamera/243AE8 через w60, + a2-arg `(char *)&f50 - 0x40` -> ROM's
   `addiu s0,sp,96` pocket + `daddu a1,s0` x2 + `addiu a2,sp,16` remat ALL
   byte-match. **Rule extracted: pocket-vs-remat is controlled by routing
   through a user var bound with a DISTINCT-anchor offset-fold spelling**
   (`&f6C - 12` style). Direct per-use folds FAIL when cse's value-table
   still holds the entry (folding is VALUE-based, not syntax-based).

### Census/mechanism state at rc579 (dumps: scratchpad conv3/dumps/actenv5.*)
- Snapped and holding: env=$20 arg3=$21 arg4=$22, s2-pocket family x6
  (w70-set regions; positions match ROM's addiu $18,sp,0x70 x6), late s1
  pockets (wt-family, ours 3524/3870 ~ ROM 4044/4446), a0-remat at 1083,
  entry-block CFG (bnez/nop/daddu-zeros + bnez/delay-lw-sub) byte-equal
  modulo letters, L6B4 CageFixDL block (s2/s0/s1=move s1,s2) byte-equal.
- REMAINING KNOT (the only big residual): ours-s1 pockets at built
  330,359,918,936,1131,1200,1279,1347 must become ARG-REMATS (ROM addiu
  $4/$5/$6,sp,0x70 x22); ours-s0 x4 (1751,2021,2184,2316) vs ROM s0 x3
  (2349,2540,2674). These are BLOCK-LOCAL 2-ref temps (e.g. p1397 "2 uses
  across 4 insns", set 1x) created by cse value-unification of the two
  &f70-macro uses around ONE call inside each region; dense+call-crossing
  -> each wins lowest-free callee-saved ($17). Cascade: A-pocket s1 ->
  movn-pair {18,19} -> s6var $23 -> s7var $30 -> boy 456(sp) home ->
  the +4 shift on every 456..520 slot. ROM: those temps DON'T form (its
  cse missed the value reuse — table-flush state differs) OR spill.
- REFUTED this session (do not blind-retry): function-wide `char *w70v`
  restored w/ FV/FP(0x70) macros — entry-set OR mid-set, p197 = 34 refs /
  3418 span, prio ~495 > boy 239 -> WINS a callee-saved (s8), rc 780-961.
  Per-use distinct-anchor folds at A/B args (f74-4/f78-8/f7C-12) — cse
  folds+unifies anyway (value-based) -> same pocket. w34-anchored fold —
  gave w34 a home slot (520) + indirection (NEVER anchor off a
  non-addressable var).
- OPEN leads for round 5, in order:
  (a) read ee-gcc cse.c (staged 04159692 scratchpad) for the table-flush /
      MAX_QTY conditions — the 1981-region fold survived (flush between)
      while A/B folded; find what C shape forces a flush or breaks the
      value chain between use1 and use2 (e.g. an intervening asm-free
      aliasing store, statement order, or block boundary);
  (b) alternatively land the remaining independent structural classes
      first (branch-likely worklist at exp 385/390/1732/1870-82/3018;
      order swaps exp 134/2969; the 2221 8-insn placement; exp 617-696
      store order; exp 1402/2408 letter pattern) — each densifies the
      pocket fabric and may flip the A/B temps to spill on its own;
  (c) boy/s8 + the +4 shift falls out mechanically once A/B temps stop
      taking $17 (movn pair returns to {17,18} etc). Do NOT attack boy
      directly.
- quick_diff false-positive caveat: INCLUDE_ASM stub reads rc0 — always
  confirm the C body is installed before trusting a low number.

### Session-4 late addendum: the &f70 knot MECHANISM (dump-verified, conv3/dumps/)
- `&f70` expansion: gcc2.95 gen_mem_addressof rewrites f70's DECL_RTL to
  (mem (addressof (reg))); every `&f70` returns the SHARED addressof rtx;
  CSE (value-based, survives calls via pseudos) then leaves ~9 pseudo sets
  serving ~47 textual uses. Region temps (e.g. p1397 2-refs/4-insns) are
  cse survivors, dense + call-crossing -> pocket $17 -> the whole cascade.
- w70v-restoration arithmetics (why every variant lost): allocno prio =
  floor_log2(refs)*refs/live_length*1e4. boy = 2*5/419*1e4 = 238. Any
  &f70-pool pseudo measured 34-41 refs (cse absorbs ALL value-equal
  spellings incl. wt/w70 dead-write RHSs — isolating wt via &f74-4 did
  NOT thin it; refs went 34->41 via other absorption). 4*34/3418*1e4 ~ 497
  >> 238 -> wins callee-saved. To spill it needs <=20 refs (4-tier) or
  <=15 (3-tier, robust: 3*15/3418*1e4=132). ROM's arg-remat census = 22
  — the margin vs boy is ~8-19 pts: RAZOR-THIN, so retail's exact ref
  count/lengths matter insn-for-insn. CONCLUSION: do NOT retry w70v until
  the OTHER structural classes have landed (each changes refs/live-lengths);
  then re-run the arithmetic from fresh lreg stats (Register N lines).
- ROM pocket census for sp+0x70 (file lines in the .s): $18 x6 =
  227,765,1184,1399,1664,4377 (ours matches count+region via the w70
  multi-set var ✓); $16 x3 = 2353,2544,2678 (ours has FOUR — one extra);
  $17 x2 = 4048,4450 (ours ✓ 3524/3870-region). Arg-remats x22 =
  381,386,411,418,1071,1080,1092,1101,1260,1369,1371,1445,1449,1535,1537,
  1613,1615,1679,1689,1694,2034,2041,3024 (+ $18@227 dbl-check) — these
  must come from a LOW-PRIO spilled pool pseudo (REG_EQUIV remat) or from
  cse-MISSES retail's source achieves that ours doesn't. The A/B ROM shape
  puts use1 in a bc1f/jal DELAY and use2 in the next jal delay — per-use
  addiu into $4/$5 with NO temp.

## conv-heavy2 session 5 (2026-07-28): func_001FCA20 rc 579 -> 565 (sites 310 -> 304)

Canonical seed = `act-env_rc883_seed.c` (= `act-env_semfix3_rc565_s304.c`),
crutch-free. Three semantic retail-edits landed (occurrence-verified):
1. **env+0x170/0x174 stores DELETED** (rc-2): aug6 lines 844-845
   (`env+0x170 = FF(0x34); env+0x174 = *(sub+0x5E4)`) have NO retail
   counterpart — retail ROM only READS 0x170($20) (another function writes
   it). Removed both statements; kept `c40=40.0f` + guard shape.
2. **arm-A store-block flag |= 0x10 -> |= 0x40** (rc-11, sites-4): the
   FDFF+FBFF mask arm. Retail made BOTH arms 0x40 so gcc cross-jumps the
   whole [swc1 0x90/0x94/0x98($22); ori $4,0xffff; lw 8/C($21); and,and;
   ori 0x40; sw C; sw 8] tail (FBFF and FF7F share low half 0xFFFF; arm A
   jumps into the shared tail at the first swc1 with $4=lui-only). The
   catalog's "one of two |=0x10 -> 0x40" was incomplete — it's both (the
   second one merges).
3. **isysGObjSearchFromObjLayoutID second arg DROPPED** (rc-1, movz block
   restructured to ROM shape): retail calls it `(0x2B)` only — at the jal,
   ROM's $5 holds stale mask junk (0xFEFF... from entry); the movz'd
   FI(0x1BC) is only STORED BACK (sw in jal delay), never passed. aug6
   passed it as arg2 (lw $5,0x1BC / movz $5). Residual there = t0/t1-vs-
   v0/v1 letters (cascade).

### Leads RESOLVED as alignment noise (do not chase):
- exp-523 "ROM-only 13-insn guard block": ours HAS all three abs<45 guard
  blocks; the differ misaligns because ROM guard1 uses boy=$30 and w1C8=456
  while ours loads boy from its 456-home (+4 shifts). Cascade presentation.
- exp-260/295 "21-insn moved block": same content, D_00633850 reload-scratch
  letter (v1 vs a2) in the three-jal chain delays. Cascade presentation.
- exp-385/390 branch-likely: already resolved at rc565 (both plain bne).
- entry zeroing exp-56/59: shape matches (bnez/nop/two-zeroes; s0-reload in
  first bnez delay); letters only.

### Session-5 mechanism yield (dump- and compiler-source-verified; conv4/ dumps)
- **Frame addresses are CONCRETE from expand** (addressable scalars get
  put_var_into_stack immediately): `(char*)&f74 - 4` compiles BYTE-IDENTICAL
  to `&f70` — anchor-fold spelling can NEVER split frame-address value
  classes (probe compiled identical, twice). The w60/wb fold-anchors work
  for a DIFFERENT reason (they name a different slot's address).
- **The A/B $17-thief identified**: p2527 = gcse-pass-1 "reaching_reg" for
  expr (plus fp 112) (= &f70): 27 refs / len 199 / 8 sets / crosses 25
  calls -> prio ~5400 -> $17. Sibling p2526 (same expr, non-call-crossing
  instances): 97 refs / 49 sets -> $7. gcse standardizes every
  participating per-site temp onto ONE pseudo, INFLATING REG_N_REFS.
- **The 2-ref fold rule (the ROM shape's mechanism)**: a single-set
  address temp with EXACTLY 2 refs folds into its use — same-BB by
  combine; cross-BB by local-alloc update_equiv_regs (local-alloc.c:871:
  REG_N_REFS==2 && REG_BASIC_BLOCK<0 -> validate_replace_rtx substitutes
  (plus fp c) INTO the use insn = the `addiu $4/$5,sp,0x70` arg-remat; else
  moves the init to the use). gcse's standardization raises refs past 2 and
  BLOCKS both folds -> [addiu pool; move aX,pool] pairs + call-crossing
  pockets. ROM's 22 arg-remats = sites whose temps stayed 2-ref, i.e.
  gcse did NOT chain them, OR a spilled REG_EQUIV pool rematted by reload.
- **Spill arithmetic for a single-set pool** (w70v-style): allocation order
  is priority-desc; pool spills only if prio < boy's 239 (else it steals
  $23/$30 and re-homes boy) -> refs*floor_log2(refs) <= ~81 at len 3418 ->
  **refs <= 20**. Probes measured 34-41 (gcse absorbs all value-equal
  spellings). Gap ~14 refs.
- **ROM evidence of a partition**: in ONE region (file 374-386) wb=sp+0x60
  POCKETS in $16 while &f70 REMATS per-use — different treatment, same EBB,
  both 2-use-cross-call. And retail stores/reloads OTHER frame addresses
  via POINTER SLOTS (wPtr20 0x1F4/0x204: sw t1,504/520(sp); lw a1,504(sp)
  at the CheckFieldContact block) — the dev demonstrably keeps address
  vars MEMORY-RESIDENT in places. (mem loads are NOT gcse-transparent
  across stores -> no standardization; near a store cse1 refolds the load
  to addiu, far away it stays lw — matches ROM's mixed addiu/lw census.)
- NEXT EXPERIMENT (for round 6): split the f70-family per ROM's census —
  (a) a MEMORY-RESIDENT `char *` pointer slot (dead-read-placed like wPtr20)
  for the far/reloaded uses, (b) plain per-site &f70 macros ONLY where ROM
  remats AND the site count per redundancy chain stays at 2 refs, (c) w70
  var keeps its 6 $18-pocket sets. Verify against the pool-refs<=20 bound
  from fresh lreg stats before full conversion. The pair{17,18}/s6var-$19/
  s7var-$23/boy-$30 rotation should snap as a GROUP when p2527 dissolves
  (two-equilibria model: ours = pool-in-$17 + boy-homed; ROM = pair{17,18}
  + pool dissolved/spilled).

## conv-heavy2 session 6 (2026-07-28): func_001FCA20 sites 304 -> 175 (rc 565 -> 581) — THE POOL KNOT IS CRACKED

Canonical seed = `act-env_rc883_seed.c` (= `act-env_w70vspill_rc581_s175.c`),
crutch-free. Sites nearly HALVED in one group snap; prologue save order now
matches ROM (boy=$30, first_divergence is a lone sched nit at exp3).

### Landed levers (in order)
1. **Guard-CFG fix x2 (rc565->549, s304->297)**: the `D_00631990 in {0x54,3,0x2E}`
   OR only gates the `*(g+0xC)==4` guard — the 0x400 call runs REGARDLESS
   (ROM `bne D,0x2E -> call` jumps PAST the guard), and the guard skips ONLY
   the 0x400 block, landing exactly at the 0xC000 call (`Lp1end:`/`Lp2end:`
   moved before it; both Enable- and Disable- sites). ROM re-reads 48(sp) per
   use because the call block head is a multi-pred label (EBB break kills cse).
2. **w70v RESTORED + ref-partition (s297->175)**: `char *w70v` decl + entry
   set `w70v = (char *)&f70;` before the w70 sets (aug6 line 590 idiom) +
   FV/FP_0x70 -> w70v. THEN shed w70v refs 34 -> 11 by literalizing
   (`(float *)&f70` / `(void *)&f70`) a PARTITION of use sites: the 4 pair
   sites' SECOND use (571-ret=HCC, 583 HCC, 1128 HCC — EnvCamAngle/P
   hand-expanded to 43B18(macro)+HCC(literal) — and 1221 2438B8), both
   EnvPushPlane args (854/856, different arms = different EBBs), 907
   moveBoxAutoMatic, 883 union-store deref, 1003 EnvPushAvg, the
   EnvAssistTail 43AD0 operand (macro def now takes 43B18(tmp_)+43AD0(&f70)),
   and 950. Result: w70v = 11 refs / 3424 len -> prio ~96 < boy 239 ->
   **boy allocates first, takes $30; w70v SPILLS; reload remats
   `addu $4/$5,sp,112` per use = ROM's 22-remat shape.**

### The mechanism (dump-verified, conv5/ in session scratchpad)
- **gcse NEVER RUNS in this compiler build** (-dG dump empty, -fgcse output
  byte-identical). All prior "gcse reaching_reg" attributions were mislabels:
  the pools are CSE (EBB-path-limited) + expand-level var pseudos.
- cse CANNOT unify a literal `&f70` with w70v outside the entry EBB (w70v's
  value is opaque there) — so a literal use makes a fresh 2-ref temp that
  combine folds into its use insn (same bytes as a reload remat!), while a
  macro use is a w70v pseudo ref. TWO SAME-EBB LITERALS UNIFY (3-ref pocket —
  the old s1-pocket x8 bug), so each EBB may hold at most one literal; pairs
  must be macro+literal mixed. THE PARTITION IS BYTE-INVISIBLE except through
  the allocno arithmetic: keep w70v refs*floor_log2(refs)/len*1e4 < boy's
  prio (239) => refs <= ~20 at len ~3400 (ours now 11, margin comfortable).
- The whole downstream cascade (movn pair, s6var/s7var letters, boy home,
  +4 slot shift, prologue order) snapped as ONE GROUP when boy won $30 —
  two-equilibria model CONFIRMED.
- aug6 cross-check: its w70v = 30 refs/4464 len (spans past the late $30
  pockets -> spilled at prio 269 despite outranking boy). Retail's shorter
  span (FI(0x1D4)/EnvSlotDist use deleted) forces the refs<=20 road instead.
- D_00565060 shared-lui glue: cse2 in BOTH compiles unifies the 3 highs into
  one pool + 2 copies (dump-proven); aug6's wins $30 (copies coalesce -> ROM
  1-lui shape), ours still spills it (exp720 residual) — expected to need the
  $30 range [721..1508] free, which boy's death at 552 now provides; check
  why it still remats (likely a pocket now holds $30 in that range, or the
  glue pool's copies got separate letters).

### Residual at s175 (attack order for the next round)
1. exp 1499-1511 ROM-only 12-insn block (k-switch case -1: andi 0xFF/beqz/
   thr=30.0f region — ours transformed differently; read ROM 1490-1520).
2. The 60.0f flag family (c60_100/150/230): ROM re-evaluates the 60< compare
   per flag with separate `li 1` speculative sets (exp 1562-1587); ours
   cross-jumps/shares (bc1f/bc1tl into shared labels). Likely each flag needs
   its own EBB shape (order/spelling of the pair tests) so cse can't share
   the c.lt.s.
3. exp 720 glue lui (see above) + its `lw v1,348(a3)` re-read (ours CSEs an
   earlier sub load; ROM re-reads *(gb+0x15C) fresh).
4. exp 115 EnvCopy32 ldl/ldr letter rotation (t0,t1,v1,a3 vs v1,a3,t0,t1);
   exp 263/295 21-insn D_00633850-chain placement (was ruled cascade at rc528
   — re-examine now that letters snapped); exp 1052 goto+delay pair; 3018
   bc1f/bc1fl; 3570 bnel; plus ~160 small letter/sched sites — re-run
   match_diff --full, the map is much cleaner now.
5. quick_diff caveat: in-TU calls resolve differently; final gate ninja.

### Session-6 addendum: c60/c130 flag family LANDED (region 1530-1660 byte-clean)
Seed = `act-env_flagblock_rc581_s175.c` (canonical). The winning shape
(all occurrence-verified):
```c
float a34 = FF(0x34);
c130_170 = 0;
if (130.0f <= a34) { if (a34 < 170.0f) c130_170 = 1; }
c60_100 = 0;
if (60.0f < FF(0x34)) { if (FF(0x34) < 100.0f) c60_100 = 1; }
... (same for 150/230)
```
Mechanism: nested ifs (NOT &&-chains — those cross-jump into the set-1-first
form); set-0 lands in each bc1f delay, set-1 in the bc1tl delay; the 60-tests
re-read w34 MEMORY per flag — cse converts the redundant loads into the
surviving `mov.s $f2,$f1` copy (placed in flag1's bc1f delay) and all
re-reads ride $f2 while the cached a34 keeps $f1. A reg-copy spelling
(`b34 = a34`, or reusing thr) gets copy-propagated/coalesced away — the
MEMORY respelling is what keeps two distinct FPR pseudos. Flag letters now
$19/$18/$16/$17 = ROM.

### Residual after flag-land (s175, fresh map conv5_full5.json)
- exp 720 glue: STILL rematted. Blocker identified = p840 (the s18 flag,
  2 sets/4 refs/144 len) sits on $30 inside the glue's [721..1508] range;
  ROM's s18 = $18 (set in the u186&7 beqz delay). Ours' s18 pushed to $30 =
  $16..$23 busy in ITS range — suspect a w70-segment overlap difference
  (ours' w70-set at the 0x11-arm ~asm900 vs s18 last use ~880). Fix s18's
  letter -> glue takes $30 -> exp720/1508-family snaps.
- exp 115 EnvCopy32 ldl/ldr letters; exp 263/295 21-insn placement; exp 1052;
  3018 bc1f/bc1fl; 3570 bnel; k-switch case -1 alignment (12-insn differ slip
  + ROM nop-delay at the beq $3,$2 default-arm vs ours 60.0f-in-delay);
  ~160 letter/sched singles.

## conv-heavy2 session 7 (2026-07-28): func_001FCA20 sites 175 -> 197 @ rc 581 -> 294 (raw HALVED; arm knot cracked)

Canonical seed = `act-env_rc883_seed.c` (= `act-env_wflag70_s6cache_rc294_s197.c`),
crutch-free. Milestones: `act-env_pushplane_w70v_rc575_s167.c`,
`act-env_assisttail_tmp_rc289_s196.c` (rc-count best), current seed
(structure-forward: +5 raw over 289 but wFlag-block = ROM shape + S6 cache).

### Landed levers (in order)
1. **EnvPushPlane tA -> w70v x2** (rc581->575, s175->167): the 854/856 twin
   arms' `(float *)&f70` tA (used TWICE inside the inline: GetRootMatrixByDObj
   + 243AD0) expand-shared into a callee-saved pocket; via w70v (spilled) both
   uses reload-remat `addiu aX,sp,112` = ROM. Region 911-940 byte-clean;
   env=s4 held (w70v 11->13 refs, still under budget).
2. **EnvAssistTail 3rd operand &f70 -> (tmp_)** (rc575->289!!, s167->196):
   the arm-tail literal cse-unified ACROSS THE FALL-THROUGH-CONNECTED ARM
   CHAIN into pocket $19; ROM has NO literal there - the tail's 243AD0 operand
   is w70v (reload remat, same bytes as a folded 2-ref literal). Session-6's
   hand-split "43B18(tmp_)+43AD0(&f70)" was budget-motivated at 34 refs and is
   WRONG at 13 refs. w70v now 17 refs, still spills. The whole 1131-1378
   pseudo-block-order chaos was THIS (differ misalignment from the pocket).
3. **wFlag-block w70 restored** (structure-forward +3 raw): `w70=(char*)&f74-4;
   _OrientGV(w70,..); 2438B8(FP(0xC0), w70, FP(0xB0))` -> ROM's
   `addiu sX,sp,112` + daddu copies shape (exp2002-2005 shape-exact, letters
   pending). FP(0x70)-macro/literal spelling there was wrong (remats).
4. **S6 cache at the ==4/==3/<180 chain** (line ~1186): `char *S6=FI(0x30)`
   caching across the three derefs = ROM keeps S in $6 across the chain
   (its bnel/bnel/bc1fl annul-necessity comes from the TARGET's lui landing
   on $6-while-live; ours' plain bne = target lui got a3 = letter cascade,
   NOT a control-shape difference - do NOT chase the likelies directly).

### Mechanism found this session (updates session-6 partition rule)
- **The expand-level pool: multiple textual `&f70` LITERALS inside ONE
  expansion region share ONE pseudo at EXPAND time** (gen_mem_addressof
  shared rtx), regardless of EBBs - macro-vs-inline is irrelevant for
  literals. The arms' &f80 (FV(0x80)=t80w VAR) worked because t80w is
  a SPILLED single-set var (reload remats), NOT because macros split
  literals. EVERY multi-use frame address in ROM rides either (a) a spilled
  single-set var (w70v/t80w/w60v family: remats + inheritance daddu-copies +
  sp-direct member stores via REG_EQUIV substitution), or (b) a short
  same-call 2-3-ref literal temp (folds to addiu/inherit pair), or (c) a
  multi-set var pocket (w70: real addiu set + daddu copies).
- **0x400 block (exp 1417-1453, ~12 sites) PARKED with exact model**: aug6
  oracle line 1077 = `EnvPushAvg(FV(0x70), ...)` i.e. acc THROUGH w70v +
  `w70=&f74-4` + tails via w70. Retail must be the same, but our w70v at
  +6 acc refs (23 total, loop-weighted more) WINS a callee-saved (rc873
  probe) because retail w70v's len 3424 < aug6's 4464 (retail deleted the
  late FI(0x1D4) use) - it no longer gets crowded out of every s-reg.
  Resume lever: land other classes first (esp. anything that occupies
  s-regs in w70v's 3424-insn span or extends its len), then retry
  acc=FV(0x70). Sibling func_002009F0 proves pure-literal acc CAN give
  ROM's loop shape when no other fp+112 value pollutes the block-pool.
- Entry-block knot (~30 sites, bucket 0): ours' v1-var (p207, sub-ptr) gets
  $9 vs ROM $3; w1B4/w1B8 are multi-set REGISTER pseudos p172/p173 (both
  spill; their reload temps + za's early hoist + the two const-1 births
  differ from ROM's two short const temps). za/1B4/1B8 statement reorders
  are byte-neutral (tried). p207 is GLOBAL-allocated (greg list) despite
  block-local looks; its $3-blocker not yet identified - next tool: read
  greg allocation order around p207's turn in ae.c.greg (dumps in
  scratchpad conv6/dumps/, ae.c = the rc575 TU + edits).
- exp115 EnvCopy32 ldl/ldr rotation = same entry-letter web (temps take
  {v1,a3,t0,t1} vs ROM {t0,t1,v1,a3} because $3/$7 free-ness differs).
- exp263/295 "21-insn move" = differ slip on the lui-scratch letters
  (ROM $3/$5 vs ours $5/$6), NOT a block order issue. Ditto most remaining
  multi-insn sites; the residual is now ~90% ONE whole-function letter
  cascade + the parked 0x400 block + exp720 glue + exp1852-region sched nit.

### Residual at rc294/s197 (attack order for next round)
1. Entry knot via greg-order forensics (p207/$3-blocker) - expect a large
   group snap (buckets 0-3 + exp115 + lui-scratch families).
2. exp720 glue (s8 lui) - re-measure after (1); the s18/p840-on-$30 blocker
   may have moved with the arm-knot crack.
3. 0x400 block resume (model above).
4. exp1852 const-vs-load sched order; 2016 wFlag=1 const letter; k-switch
   case -1 12-insn block (exp 1499-1511 old map - re-diff).
5. quick_diff caveats: INCLUDE_ASM stub reads rc0; gate ninja at the end.

### Session-7 addendum: rc 294 -> 265 (sites 197 -> 171), both all-time bests
Seed = `act-env_cagemloop_rc265_s171.c` (canonical). Two more levers:
1. **v1-var web SPLIT** (rc294->267, s197->173, commit 1e8d5d4d): our `v1`
   user var had a SECOND set at the D_00631AE4-gate block (`v1 = FI(0x30)`)
   -> 2-set global pseudo -> lost $3. Renamed that web `v1b` (block-scoped)
   -> entry v1 is single-set block-local -> local-alloc gives $3 = ROM.
   THE WHOLE ENTRY KNOT SNAPPED: exp3-115 (const-1 births, za hoist, movn
   a1/a3, FP(0x10)/0x20 pocket letters, EnvCopy32 ldl/ldr rotation) now
   byte-clean. LESSON: a "letter cascade" root can be a VARIABLE-NAME REUSE
   merging two unrelated webs (dev had two distinct locals).
2. **cagem set moved INSIDE the search loop** (rc267->265): ROM re-sets the
   &f40 pointer per-iteration (addiu s1,sp,64 in the 0x16C-guard beqz delay).
   Caveat: in-loop `(char*)&f54 - 20` does NOT const-fold (2 insns,
   exp166/175 residual pair); `(char *)&dv04` direct is WORSE (rc280 - it
   becomes dv04's first address-materialization and MOVES ITS SLOT). The
   remaining 2-insn nit needs a spelling that folds in-loop w/o touching
   dv04 placement.
Remaining top sites: exp134 dsll +-1 sched slot (statement order neutral -
   tried both); exp284-297 lui a1-vs-a0 (f21 loads); exp385/390 ours-bnel vs
   ROM-plain (INVERTED post-split; delay lui letter a1-vs-a2 changes the
   annul decision - letters, not shape); exp398-426 lui/lwc1 letters;
   exp449+ t0/a3 families; exp720 glue; 0x400 block (parked, model in
   session-7 entry); k-arm letter tails.

### Session-7 final state: rc265 / s171 (canonical seed = act-env_cagemloop_rc265_s171.c)
Additional probes this round (all reverted, do not blind-retry):
- me0-web removal at the k-head (rc268): the a3-cache of 48(sp) reads is
  CSE merging textual FI(0x30) macro reads, NOT the me0 var. ROM re-reads
  48(sp) per use in the 673-696 stretch — find what separates ROM's loads
  (EBB break or an intervening memory-invalidating insn) before respelling.
  NOTE me0 still has two webs (1017-area removed was neutral-negative;
  1892 e30-region web remains) — web-split axis stays promising elsewhere:
  audit ALL reused pointer-temp names (m, q, pv, g90, mm, cc) for
  multi-web merges like v1 was. THE BIG LESSON of this session: hidden
  web-merges and wrong literal/var routing are the letter-cascade roots;
  each fix snaps a whole family.
- bit5/mask statement reorder: byte-neutral (sched1 is dep-driven there).
Next-round attack order: (1) var-name web audit (v1-style splits);
(2) exp673-696 FI(0x30) re-read separation; (3) exp720 glue AFTER (2)
(ROM lui s8 shared vs ours t0 remat — s8 free-ness depends on upstream
letters); (4) 0x400 block resume (model in session-7 entry); (5) exp166/175
in-loop &f40 fold spelling; (6) letter families 284-297 (lui a0/a1),
385-426 (annul flips), 449+ (t0/a3).

## conv-heavy2 session 8 (2026-07-28): func_001FCA20 sites 155 -> 146 (rc 206 -> 209)

Gating switched to **DIVERGENT SITES** (user directive this session); rc is a
byproduct and rose 13 on the last lever while sites fell. Canonical seed =
`act-env_scalarzero70_s146_rc209.c`. Milestones: `act-env_scalar1A0_s149_rc198.c`,
`act-env_scalar180-1A0_s147_rc196.c`.

### THE MECHANISM FOUND THIS SESSION (whole-function rule, re-usable)
**A frame address reached through an ADDRESSOF can NEVER produce a direct
`sw/swc1 <K>(sp)` member store for K != 0.** `memory_address()` forces
`plus(ADDRESSOF, K)` into a pseudo, so cse pockets it and purge_addressof can
no longer fold it back. Verified byte-identical across all three spellings:
- `*(float *)((char *)&dv + 4)`   (pointer arithmetic)
- `(*(AVEC *)&dv)[1]`             (ARRAY_REF — the C frontend lowers `a[i]` to
  `*(a+i)` via default_conversion, so it is literally the same tree)
- `((V4 *)&dv)->b`                (COMPONENT_REF — `change_address` calls
  `memory_address` because the addr is not `legitimate_address_p`)
Offset 0 IS direct (explow.c special-cases a bare ADDRESSOF).

**Corollary (audit rule): every ROM `sw`/`swc1`/`sd` at a NON-ZERO sp offset
proves that lane is its OWN scalar local in the dev source.** A 4-float
"vector" local in ROM is four separate `float` decls, not one blob.

Supporting facts (all dump-free, measured):
- Slot pinning: `ccat = (int)*(long long *)&x;` (or `*(int*)((char*)&x + 4)`)
  DOES create the ADDRESSOF + stack slot and pins its assignment order.
  `((union IFAlias *)&x)->i` does NOT (folded away, no slot). Use the
  long-long form — the existing pin blocks at src lines ~442 and ~1643 are
  that idiom.
- `__attribute__((aligned(16)))` on a local is IGNORED: `put_var_into_stack`
  calls `assign_stack_local(mode, size, 0)`, i.e. mode alignment only. A
  16-byte group boundary must be produced by PINNING A FILLER scalar
  (`&w17C`), never by an attribute.
- Declaring these as real arrays (`AVEC v18, v19, v1A;`) is WRONG: arrays are
  BLKmode -> `assign_stack_local` at expand_decl -> the EARLY frame pool ->
  the whole layout shifts (247 sites). Keep them scalars.

### Landed levers (in order)
1. **`TI128 dv1A` -> `float y1A0, y1A4, y1A8, y1AC`** + 4 long-long pins in the
   1643 block. Region exp3349-3367 byte-clean: `swc1 $f0,416/420/424(sp)`
   direct, `addiu s0,sp,400` pocket for dv19 (2 uses), `addiu a1,sp,416` fresh
   for the 1-use arg. sites 155 -> 149.
2. **`TI128 dv18` -> `float w180, w184, w188, w18C`** + `ccat = (int)*(long
   long *)&w17C;` to reclaim 0x17C so the group starts 16-aligned at 0x180.
   `sw zero,388(sp)` direct. sites 149 -> 147.
3. **0x400-block acc zeroing hoisted out of `EnvPushAvg` into scalar stores**
   `FF(0x70)=0; FF(0x74)=0; FI(0x78)=0;` (the inline no longer zeroes; it has
   one caller). ROM's `sw zero,112/116/120(sp)` now byte-exact. sites 147 ->
   146, rc +13 (KEPT: class snapped to ROM).

### Probes reverted (leads, not verdicts)
- `EnvPushAvg((float *)w70v, ...)`: 247 sites. w70v wins a callee-saved reg at
  +6 loop-weighted refs — session-7's model reconfirmed at THIS census.
- `cagem = (char *)&dv04;`: 148 sites. It DOES clean exp166 (ROM `daddu
  s0,v0,zero` fills the b-delay) but exp175 gets worse: &dv04 becomes an
  out-of-loop pocket (`daddu a0,s2,zero`) where ROM has an in-loop
  `addiu s1,sp,64`. dv04 has exactly ONE other reference (the line-444 pin) —
  next idea is to move/remove that pin, or give dv04 a second far-away use, so
  no pre-loop pocket can form.

### Residual at sites146 (attack order for session 9)
1. **Finish the 0x400 block (exp 1417-1453, ~9 sites).** Remaining piece is the
   accumulator ADDRESS form. ROM: `addiu s3,s6,192` (dstc) + `addiu s2,sp,112`
   (the w70 pocket) + `addiu a0,sp,112` / `addiu a1,sp,112` REMATS for the loop
   body and the 0.25f call, with `daddu a1,a0` inheritance inside the loop.
   Ours: `daddu s3,s2,zero` (a copy of the w70 pocket) and dstc in s7. Need an
   acc that is a SPILLED single-set frame-address var. Route: first cut w70v's
   ref count elsewhere (re-derive session-7 lever 2 at the current census),
   THEN retry acc = FV(0x70).
2. **`box` = `460(sp)` reload-letter web, ~45 sites** (the single biggest
   class). `bx = *(int *)(v1 + 0x180)` is memory-resident in BOTH builds; every
   site is a reload register pick plus a few inheritance-pairing differences
   (993/997, 1052/1091/1094, 1171-1174, 1249-1254, 1315-1318). Per
   `order_regs_for_reload` these are whole-function usage-count driven — do NOT
   letter-grind; kill structural diffs and they snap in bulk.
3. **Callee-saved census rotation, ~20 sites.** s0<->s1: 750/752/756,
   1981/1983, 1997, 2002/2005, 2688/2690/2700, 3124/3132/3137, 3201/3203 (ROM
   puts &f60 -> s0 and &fB0 -> s1; ours swapped). s2<->s3: 1961, 2023, 2181,
   2305. s7<->s8 (wFlag): 1392, 1410, 1466, 2016.
4. **Shared-lui glue** exp 720/722 + 1472/1474 + 1507/1511: ROM holds
   `%hi(D_00565060)` in $30/s8 across [721..1508]; ours remats per use.
5. **lui-letter / annul family**: 284-297, 385-426, 472, 494, 621, 1773, 1829,
   1870-1882, 1920/1930, 3570.
6. **Singles**: 134/135 dsll sched slot; 617/1139/1205/1349/3136/3269
   nop-vs-delay-fill; 678/683/684 sched; 1187/1190 (sched1 tie: ROM emits
   `addiu s1,s6,240` before `addiu s2,sp,112`, ours reversed); 1852
   const-vs-load sched; 1991 `addu v0,v0,v1` operand order (commutative/compound
   lever); 3018 extra `lw v0,8(s5)` caused by a bc1fl-vs-bc1f annul flip.

### Next reasoned lever (session 9, do this FIRST)
Run the ADDRESSOF audit function-wide: diff the ROM-vs-ours **frame slot
census** (every `<K>(sp)` MEM reference, both sides) and every `addiu rX,sp,K`.
Any offset ROM references directly that we reach through a pocket/pointer is
the same crack as 0x184/0x1A4/0x1A8/0x74/0x78 — split that lane into its own
scalar local and pin it with the long-long idiom. Scripts used this session
live in the session scratchpad (`rom.py` = ROM index->asm, `sbs.py` = aligned
ROM-vs-built side-by-side by expected index, plus the census one-liners).

### Session-8 addendum: the frame census is now offset-EXACT
After the three levers the ROM-vs-ours `<K>(sp)` slot SET is identical (no
offset present on one side only). Only reference COUNTS differ, and only at
six offsets:
  0x30 arg0-home  ROM 154 / ours 155   (one extra read of the FI(0x30) home)
  0x34 w34        ROM  22 / ours  23
  0x60 f60        ROM   6 / ours   5   <- ROM has ONE MORE ref
  0x64 f64        ROM   8 / ours   7   <- ROM has ONE MORE ref
  0x68 f68        ROM   6 / ours   5   <- ROM has ONE MORE ref
  0x1CC bx/box    ROM  43 / ours  46   (three extra reloads on our side)
The f60/f64/f68 deficit is a whole TRIPLE missing exactly once: ROM has a
fourth store-or-read of the 0x60 vector that we fold away. Our triples live at
src lines 1223-1227 (`FF(0x60..0x68) = pp2[0..8]`), 1286-1288 and 1357-1359
(the `cx/cy/cz` from `FI(0x1A8)` in two sibling arms). Suspect one of the
sibling arms is being cross-jumped/CSE'd into the other, or a fourth triple
was dropped as a semantic port omission. Locate it by scanning the built-vs-ROM
side-by-side for `96/100/104(sp)` refs; this is a cheap, high-signal next probe
and it is a SEMANTIC/insn-count difference, not a letter.

### Session-8 FINAL: sites 145 / rc 194 (both all-time bests)
Canonical seed = `act-env_split70-60acc_s145_rc194.c`.
The census addendum above led straight to a 4th lever: **the two EnvPushAvg
call sites need DIFFERENT zeroing forms.**
- 0x198 site (`EnvPushAvg(FV(0x60), ..., dstc, 0x198)`, src ~1435): acc is
  `w60v`, a SPILLED single-set frame-address var, so `acc[0..2] = 0` through
  the pointer already reload-substitutes REG_EQUIV and emits ROM's
  `sw zero,96/100/104(sp)` DIRECT. Keep the pointer form here.
- 0x188 site (src ~1001, the 0x400 block): acc is a POCKET, so the pointer
  form gives `sw zero,4(sX)`. It needs scalar `FF(0x70)=0; FF(0x74)=0;
  FI(0x78)=0;` — so that site is written out INLINE (loop and all) and
  `EnvPushAvg` is left intact for the 0x60 site.
LESSON: the same helper can require two different spellings at two call sites
because the ADDRESSOF-vs-spilled-var regime of the acc argument differs. Do not
"unify" duplicated dev helpers.

**Frame MEM census after this session** — the slot SET is exact and only three
reference-count deltas remain (all reload/re-read, none structural):
  0x30 arg0-home ROM 154 / ours 155 ; 0x34 w34 ROM 22 / ours 23 ;
  0x1CC box      ROM  43 / ours  46.
That census diff is now a clean convergence gauge: drive those three to zero.

## conv-heavy2 session 9 (2026-07-28): func_001FCA20 sites 145 -> 13 (rc 194 -> 14)

Canonical seed = `act-env_quarter-w70v_s13_rc14.c`. Milestones in
`tough_nuts/act-env_func_001FCA20/`: `_bitguard-scope_s141_rc188`,
`_pendulum-callee_s140_rc188`, `_accw70_s40_rc50`, `_w60split_s37_rc47`,
`_w70f_s28_rc33`, `_g90split_s22_rc27`, `_pvsplit_s20_rc25`,
`_g-from-h_s15_rc17`, `_camrow_s14_rc15`, `_quarter-w70v_s13_rc14`. Crutch-free (only `__asm__`
name aliases).

**All 13 remaining sites are STRUCTURAL. Zero register-letter diffs
remain — the whole-function coloring/reload census is now byte-exact
against ROM.** Built length 3979 vs ROM 3977 (+2).

### Two new whole-function AUDITS (reusable; both found real bugs)
Scripts live in the session scratchpad `s9/`:
1. **`cfg.py` — branch-TARGET audit.** Disassemble both sides with
   addresses, align with difflib, convert every branch target to an
   INDEX, map ours through the alignment, and report where the two
   targets disagree. This is the only cheap way to see a control-flow
   divergence that the instruction differ silently absorbs. It found the
   +47 displacement that turned out to be find (2) below.
2. **`callee.py` — RELOCATION audit.** `objdump -dr` both sides and
   compare the R_MIPS_26 / HI16 / LO16 symbol on each aligned insn.
   **The instruction differ is completely BLIND to callee identity** —
   both sides read `jal 0` with a reloc. A wrong callee is invisible
   until the final link. It found find (2)'s wrong function outright.
   (Known benign hit: in-TU calls resolve to `.text` on our side.)
3. `struct.py` — register-blind skeleton diff (GPR/FPR names → `r`/`f`).
   Separates "structure" from "letters" in one read. This is the right
   residual gauge once the census snaps.

### The four landed finds, in order

1. **The env+0x20 bit guard scopes ONLY the `stt == 0x10` block**
   (sites 145 -> 141). Our C had `if (f22 < 50.0f && !(bit))` wrapping
   the whole 0x10..0x19 state chain. ROM's `bnez` at exp992 lands at
   .L001FDAA0 — *inside* the chain, right before the `stt == 0x11`
   test — while the `f22 < 50` bc1f skips everything. Shape:
   ```c
   if (f22 < 50.0f) {
       int stt;
       if ((int)(*(long long *)(env+0x20) << 0x1D >> 0x20) & 1) goto L10s;
       stt = *(int *)(box + 0xC);
       if (stt == 0x10) { ...; if (rot < fr*fr) { ...; stt = re-read; goto L10d; }
                          goto L10e; }
       goto L10d;
   L10s: stt = *(int *)(box + 0xC); goto L10d;
   L10e: stt = *(int *)(box + 0xC);
   L10d:;
       if (stt == 0x11) ...
   ```
   The three-way `lw $3,0xC(rX)` convergence at FDA98/FDAA0/FDAA8 and
   the *absence* of a re-read on the `stt != 0x10` path (cse kills it,
   no intervening call) pin this exact goto layout: A-block, L10s-block,
   L10e-block, join.

2. **`GetRootPositionHandExtra` + a second guard-scope error** in the
   LayoutID-0x15 loop (sites 141 -> 140, and a *link-breaking* callee
   bug the differ could never show). ROM:
   ```c
   if (InitPendulum(fnd3) != 0) {
       GetRootPositionHandExtra(rt, fnd3);
       if (!(func_00194590(rt, FI(0x1C8)) < 0x2E)) goto Lnext3;
   }
   GetRootMatrixByDObj(g90, fnd3);
   ```
   Ours had `if (InitPendulum(fnd3) == 0) goto Lnext3;` (skips the whole
   iteration) and called `GetRootMatrixByDObj` for BOTH calls.

3. **THE BIG ONE — the 0x400-block accumulator must ride the `w70`
   pocket, not its own `&f70` literal pseudo** (sites 140 -> 40,
   rc 188 -> 50). Derivation: in ROM's `EnableMotionOrientUpdate(...,
   0x400)` block, exactly TWO callee-saved pockets exist — `$19` = dstc
   (`arg4+0xC0`) and `$18` = w70 (`sp+0x70`) — and the accumulator
   address is REMATTED (`addiu a0,sp,112` x3). Ours had THREE:
   `s2 = sp+112`, `s3 = daddu s2` (a *duplicate* of the same value, the
   `&f70` literal pool pseudo), `s7 = arg4+192`. That stray allocno took
   `s3`, which pushed dstc to `s7`, wFlag to `s8`, and left the
   `D_00565060` shared-lui glue pool with **no** callee-saved register —
   ROM holds `%hi(D_00565060)` in `$30` across [720..1508]. Because ROM
   has every one of `$16..$23` plus `$30` occupied in that range, its
   accumulator gets no register and spills.
   Writing the loop and the 0.25f call through `w70` deletes the stray
   allocno, and the ENTIRE downstream census snapped in one edit:
   the ~45-site `460(sp)` box reload web, the glue lui (720/722/1472/
   1507), the bnel/bc1fl annul family (385/390/1870/1876/1882/3018/3570),
   the k-switch letter tails, the s7/s8 wFlag rotation and the 0x400
   block itself — all gone together.
   **Lesson: a duplicated frame-address value is not a "letter"; it is an
   extra ALLOCNO, and one extra allocno in a pressure-saturated range
   re-rotates the whole function.**
   Probed and rejected at the new census (do not blind-retry): acc as
   `&f70` (137 sites), acc as its own `char *acc = (char*)&f74-4` local
   (identical to w70 — cse1 unifies the textual spelling), mixed
   spellings loop-vs-0.25f (109/114), an in-loop-body `char *ac` (114).

4. **Name-web splits** (the session-7 `v1` lesson, applied
   systematically; sites 40 -> 20). One C variable standing in for N
   unrelated dev locals forces all N segments onto ONE hard register.
   Landed: `w60` -> w60a/b/c/d (all four groups, 40->37);
   `w70` -> `w70f` at the HandyCamera/_OrientGV block only (37->28);
   `g90` -> `gH` (the FP(0x90) pb block) + `gI` (the FP(0x140)
   GetRootMatrixByDObj block) (28->22); `pv` -> `pC` (FP(0x130)) +
   `pD` (FP(0x150)) (22->20).
   Measured individually and REJECTED (the web is genuine there): the
   other 8 `w70` groups, the other 11 `g90` groups, `pv` groups A/B/E,
   and splits of `m`, `me0`, `t80v`, `head`, `hit`.

5. **`g = *(char **)(h + 0x134)`, NOT `*(FI(0x30) + 0x134)`**
   (sites 20 -> 15). Proof is the ANNULLED `bnel` at exp3573: its
   delay-slot `lw $4,0x30($29)` is a copy of the .L002002AC insn on the
   TAKEN path, so on fall-through it is nullified and `$4` still holds
   `h` from the `lw $4,0x164($2)` at exp3571. This *reverses* a
   session-4 "semantic port fix" — annul semantics are load-bearing when
   reading data flow off a branch-likely.

6. **CamEntry row base as a compound base-adjust** (sites 15 -> 14):
   `{ char *cb = (char *)D_005F2FB8; cb -= -(D_00631990 * 0x194);
      rowf = ((CamEntry *)cb)->f180; }` so the `addu` dest is the BASE
   register (ROM `addu v0,v0,v1`), per COOKBOOK §[swap_addu].

### 7. The 0.25f call's accumulator is `w70v`, not `w70` (sites 14 -> 13)
`func_00243B18((float *)dstc, (float *)w70v, 0.25f);` — `w70v` is the
entry-block SPILLED single-set frame-address var, so reload remats
`addiu a1,sp,112` = ROM exp1447. This is the ledger's rule (a) and it
RE-OPENS session-7/8's "w70v acc" reject: the reject is real only for
the LOOP-BODY uses (loop-weighted refs push w70v over the budget and it
wins a callee-saved reg -> 218 sites); the single post-loop use is free.
The same helper argument therefore needs THREE different vehicles at its
three call sites — pointer/w70/w70v — which extends session-8's
"do not unify duplicated dev helpers" rule.

### Residual at sites 13 / rc 14 — ALL structural, no letters
1. **exp 1434/1436/1442 (3 sites, the biggest class): the 0x400 loop
   accumulator REMAT.** ROM `addiu a0,sp,112` (preheader) / `daddu
   a1,a0,zero` / `addiu a0,sp,112` (re-established in the bgez delay
   each iteration); ours copies from the `w70` pocket (`daddu
   a0,s2,zero`). ROM's loop acc is a SPILLED pseudo rematted at each
   reload. Every spelling that creates a second allocno here wins `s3`
   and detonates find (3). Rejected at this census: `&f70` (137),
   own-local `(char*)&f74-4` (== w70), in-loop-body `char *ac` (114),
   `w70v` in the loop (218), and a long-range entry-block `accv =
   (char *)&f70` (216 — it perturbs the entry pin block/frame).
   **Next lever: stop trying to spell a second value and instead RAISE
   the register pressure in [1417..1455] so the second allocno cannot be
   coloured** — ROM occupies `$16..$23` + `$30` there; take a `-dg` greg
   dump (recipe below) and find which of our s-regs is idle across that
   range, i.e. which dev local ROM keeps live there that we do not have
   at all. Alternative: shrink `w70v`'s loop-weighted ref budget
   elsewhere so it can also take the loop body (session-7's model).
   `-dg`/`-dl` recipe used this session (dumps kept in `s9/dumps/`):
   `tools/cc/ee-gcc2.9-991111/ee-gcc -B <gcc-lib> -S -G 8 -O2 -mips3
    -EL -fno-builtin -nostdinc -fdata-sections -I include -dg -dl
    -o ae.s src/act-env.c`  (run from the dump dir).
2. **exp 166/175 (2 sites, +1 insn): the in-loop `cagem` fold.** ROM
   `addiu s1,sp,64` (one insn, direct sp+0x40) frees a slot for
   `daddu s0,v0,zero`; ours needs `addiu s2,sp,84` + `addiu s1,s2,-20`
   because every `&fXX` in that loop shares one cse'd ADDRESSOF base.
   sp+0x40 is `dv04`'s offset 0. Swept and rejected: `&f58-24`,
   `&f5C-28`, `&f50-16` (all 2-insn, no change), `&dv12/&dv13` (116/118),
   `(char*)&dv04` direct (18 — much better than session-7's 280 but
   still +4; it moves dv04's slot), and dv04-pin removal / long-long pin
   (59). Next lever: give `dv04` a second, EARLIER address use so the
   loop's `&dv04` is no longer its first materialization, then take the
   direct form.
3. **exp 1187/1190 (2 sites): sched2 tie in the `stt==0x16` block.**
   ROM emits `addiu s1,s6,240` (arg4+0xF0) into the beqz delay, ours
   `addiu s2,sp,112` (the `w70 =` statement). The sibling `stt==0x17`
   block is byte-clean and differs only by NOT having a `w70 =`
   statement. Statement reorders (both directions) are byte-neutral;
   hoisting an `anch` temp is worse (21). Next lever: the arg4+0xF0
   materialization must get a LOWER INSN_LUID than w70's addiu — look
   for a spelling of the `EnvWallAssistVec` 4th argument that expands
   before the `w70 =` statement without adding a pseudo.
4. **exp 678/683/684 (3 sites): FF(0x34) hoisted too early.** ROM keeps
   `lwc1 $f1,0x34($29)` for the `bnez` delay at exp690 (the `b6`/`s18`
   block); ours schedules it into the `bc1f` delay at exp678, which
   pushes `lw a0,48(sp)` and `sd v0,24(s4)` one slot each. Retail has NO
   `-fno-strict-aliasing`, so the `((union LLAlias *)(env+0x18))->ll |=`
   store does not block the `float w34` load. Next lever: an alias-set
   spelling of that `|=` (or of the FF(0x34) read) that creates the
   dependency ROM has.
5. **exp 134/135 (2 sites): sched2 interleave** of the `dsll v1,a3,0x1b`
   chain against the `and v0,v0,aX` mask chain (ours one slot early).
6. **exp 617 (1 site, +1 insn): unfilled `bne` delay.** ROM puts
   `daddu a0,a3,zero` in it; ours emits a nop and the daddu after. A
   reorg liveness difference at the branch target.

### Method notes for the next worker
- Re-run all three `s9/` audits FIRST after any edit that changes
  control flow; `callee.py` in particular is the only guard against a
  wrong-callee bug that quick_diff/match_diff cannot see.
- The name-web sweep is cheap and mechanical: enumerate a variable's
  assignment groups, rename ONE group at a time, measure. Most groups
  are neutral or catastrophic; the winners are obvious and additive.
- Gate on `struct.py`'s block count, not raw sites: at sites 13 the
  letter census is already exact, so any edit that reintroduces letters
  is a wrong branch no matter what the count says.

## conv-heavy2 session 10 (2026-07-28): func_001FCA20 sites 13 -> 2 (rc 14 -> 2)

Canonical seed = `act-env_x40scalars_s2_rc2.c`. Milestones in
`tough_nuts/act-env_func_001FCA20/`: `_w70v-liverange_s10_rc10`,
`_llstore_s6_rc6`, `_d16_s4_rc4`, `_x40scalars_s2_rc2`. Crutch-free
(only `__asm__` name aliases + the two ROM-proven `volatile`s, both
re-verified this session: dropping the `D_00631454` one costs 3 sites,
dropping the `*(volatile float *)(pp+8)` one costs 2).

**Built length is now EXACTLY 3977 = ROM. `cfg.py` reports 0
branch-target divergences, `callee.py` only the known benign in-TU
`.text` reloc, `struct.py` ONE block.** Everything except one
within-cycle sched2 swap is byte-identical.

### The four landed finds

1. **The 0x400 loop accumulator IS `w70v` — the blocker was allocno
   PRIORITY, not the vehicle** (sites 13 -> 10). Sessions 7/8/9 all
   rejected `w70v` for the loop body at 218 sites and concluded the
   loop-weighted refs made it "win a callee-save"; that is true but it
   is a *quantity*, not a property. Measured from `-dg`:
   `allocno_compare` priority is `floor_log2(refs)*refs/live_length`.
   - `w70v` = pseudo 207, refs 17, live_length 2972 -> 0.02288.
   - the pseudo that owns `$30` (85 = `boy`/arg1), refs 5, ll 418 -> 0.02392.
   A **4% margin**. The two loop-body refs are loop-weighted (+2 each),
   so refs 17 -> 21 -> 0.02826 -> w70v takes `$30`, `boy` spills, the
   frame rotates, 218 sites.
   The fix is the **live_length axis**: line 1515's bare
   `(float *)&f70` (GetRootMatrixByDObj at exp2589, the LAST sp+0x70
   remat in the function) is the same dev local. Routing it through
   `w70v` stretches the raw range 1486 -> ~2390, which
   `update_equiv_regs` then DOUBLES (`REG_LIVE_LENGTH (regno) *= 2` for
   any pseudo carrying a REG_EQUIV) to ~4780: priority 4*22/4780 =
   0.0184, comfortably under `boy`. w70v stays uncoloured, reload remats
   `addiu a0,sp,112` at every use and `reload_cse_regs` supplies the
   `daddu a1,a0,zero` — ROM exp1434/1436/1442/1447 exactly.
   **RULE: before rejecting a vehicle because "it wins a register",
   read the two competing priorities out of the greg dump. The margins
   here are single-digit percent, and live_length is as steerable as
   refs — a far-away extra USE of the same dev local lowers priority
   even though it raises n_refs.**

2. **A `union` access is an ALIAS-SET-0 BARRIER, not a neutral
   respelling** (sites 10 -> 6, and it also removed the extra insn at
   exp617). `c_get_alias_set` (c-common.c) returns 0 for *any* access
   reached directly through a union — the type-punning escape hatch.
   Alias set 0 conflicts with everything. In the `f22 < 40.0f` block
   `((union LLAlias *)(env + 0x18))->ll |= 0x8000LL << 24;` therefore
   made sched1 give the following `lw a0,0x30(sp)` (the `subCommonIdle`
   argument = the arg0 home) a `true_dependence` on the `sd` — the
   `-dg` dump shows that insn's LOG_LINKS as exactly `(insn_list <sd>)`.
   That serialises the whole block into one chain, so the argument load
   cannot hoist and reorg has nothing to put in the `bc1f` delay.
   Spelling those two `|=` as `*(long long *)(env + 0x18)` gives the
   store the long-long alias set, `DIFFERENT_ALIAS_SETS_P` fires, the
   dependence disappears, sched1 hoists the argument load to the top of
   the block and reorg fills the `bc1f` delay with it and the `jal`
   delay with the `sd` = ROM exp678..690.
   **This is per-SITE, not global**: the very similar
   `((union LLAlias *)(env + 0x18))->ll = ll18;` at src ~480 is
   ROM-PROVEN as a union (de-unioning it costs 51 sites) — there ROM
   needs the barrier. Retail has strict aliasing live, so treat every
   union in this TU as a deliberate scheduling barrier and audit each
   one on its own.

3. **exp1187/1190 was a raw INSN_LUID tie** (sites 6 -> 4). In the
   [1187..1204] block both `addiu s1,s6,240` (EnvWallAssistVec's
   `dst2 = arg4+0xF0`) and `addiu s2,sp,112` (the w70 pocket) have equal
   INSN_PRIORITY and — since neither has a consumer inside the block —
   equal `depend_count`, so `rank_for_schedule` falls through to
   `INSN_LUID (tmp) - INSN_LUID (tmp2)`, i.e. source order. Our `dst2`
   was the macro's third statement. Hoisting it to its own local
   assigned first (`char *d16 = (char *)arg4 + 0xF0;`) swaps the two
   addiu's into ROM's order and moves nothing else.

4. **The 0x40 lane is four scalar floats, not a `TI128`** (sites 4 -> 2).
   `cagem = (char *)&f54 - 20` expands to `plus(ADDRESSOF, -20)`;
   `purge_addressof_1`'s `validate_change` rejects
   `plus(plus(vsv,84),-20)` as an `addsi3`, so `force_operand` SPLITS it
   into `addiu s2,sp,84` + `addiu s1,s2,-20`. loop.c then hoists the
   first out (strict invariant; `threshold*savings*lifetime` is orders of
   magnitude over `insn_count`), which both steals ROM's `b`-delay slot
   at exp166 (ROM copies the loop head there and redirects the branch to
   .L2ac+1) and strands the `-20` at exp175; combine can never re-fold
   them because they end up in different basic blocks.
   A **bare `&local` is ONE insn** (`validate_change` succeeds) and is
   NOT hoisted. dv04 could not supply it: its slot pin
   `*(int *)((char *)&dv04 + 4)` has a NON-ZERO offset, so
   `memory_address` forces the base into a pseudo which cse1 shares with
   `cagem` and materialises at the pin (exp114, 8 sites); pinning dv04 at
   offset 0 instead defers `put_addressof_into_stack` past the f50..f6C
   group and its slot moves to 0x60 (49 sites).
   Resolution: 0x40 is `float x40, x44, x48, x4C` pinned with the
   long-long dead-read idiom (same as the 0x180/0x1A0 lanes in session
   8), plus two filler pins `x38`/`x3C` to restore the 16-byte group
   boundary that TImode alignment used to provide. `cagem = (char *)&x40`
   -> `addiu s1,sp,64`, one insn, inside the loop in the beq delay =
   ROM exp175; exp166 falls out with it.
   **RULE: `plus(ADDRESSOF, K != 0)` is always 2 insns and the base half
   is loop-hoistable. If ROM shows a ONE-insn `addiu rX,sp,K` inside a
   loop, the dev local starts AT K — split the lane into scalars and pin
   the group boundary with fillers.**

### Residual at sites 2 / rc 2 — ONE class, fully characterised
**exp134/135: `dsll v1,a3,0x1b` is emitted one slot early.**
ROM `and v0,v0,a0 ; and v0,v0,a1 ; dsll ; dsra32 ; and v0,v0,a2 ; andi`;
ours `and v0,v0,a0 ; dsll ; and v0,v0,a1 ; dsra32 ; and v0,v0,a2 ; andi`.
Source = the `ll18 &= A/B/C` + `bit5` block at src ~467-480.

Mechanism, read out of `-fsched-verbose-5 -dS -dR` (that flag spelling
works on this cc1; `-fsched-verbose=N` does NOT):
- The EE model is DUAL-ISSUE (`memory` + 2x `alu`), so the visualization
  puts two insns per clock and the ORDER WITHIN A CLOCK is the emission
  order.
- sched2 clock 20 has ready `{and2, dsll}` with INSN_PRIORITY 4 each,
  the same class vs `last_scheduled_insn`, and `depend_count` 2 each
  (every insn in the block lists the branch as a dependent), so
  `rank_for_schedule` falls through to **INSN_LUID = sched1's output
  order**, and sched1 emitted the dsll before and1/and2.
- sched1 emitted it early because at ITS clock 16 both `ld` insns are
  ready (both were released by the EnvCopy32 packed-struct block move,
  alias set 0) and it issues the **b20 load first**, ll18 at 17. dsll
  (dep cost 2 off b20) is then ready at 18 while and1 is ready at 19.
- ARITHMETIC OF THE FIX: and2 is emitted before dsll iff
  `b20_cycle >= ll18_cycle + 2`, or iff they tie at sched1 clock 19 —
  where sched1 (unlike sched2) still applies INSN_REG_WEIGHT, and and2's
  weight is 0 (it kills the mask constant) against the dsll's +1
  (`b20` survives for the bit-4 test), so and2 would win. **So the whole
  class reduces to: make sched1 issue the ll18 load BEFORE the b20 load.**
- Unexplained residue: the dep table gives prio(ll18 load)=7 >
  prio(b20 load)=6 and the ll18 load has 3 dependents vs 2, yet the b20
  load issues first — so the pick is NOT priority/depend_count. Next
  worker should read `actual_hazard`/`schedule_select` for the pair
  against the preceding BLKmode block move (insn 289 in the sv2 dump) —
  the ll18 load is very likely being skipped for a 1-cycle unit hazard,
  which would make the lever "put a third memory op between the block
  move and the loads" or "change what insn 289 blocks on".

Measured and REVERTED this round (leads, not verdicts): swapping the two
`long long` declarations; moving the `b20` load after the first `&=`;
moving `bit5` between the 2nd and 3rd `&=`; computing `bit5` first;
inlining `bit5` into the `if`; reading `b20` and/or `ll18` through
`union LLAlias`. All byte-NEUTRAL, which is itself the evidence that the
tie is decided upstream in sched1's clock-16 memory-unit pick and not by
source order in this block. Flattening the three `&=` into one
expression is 93 sites (the chain must stay three statements).

### Tools added this session
`s10/dump.sh` (one-shot `-dg -dl -dS -dj` dump into a named dir),
`s10/disp.py` (greg "Register dispositions" -> per-hard-reg allocno list
with refs/live_length and the computed priority — this is the tool that
cracked find 1), `s10/o.sh` (oracle one-liner: `sitesN rcN` + the site
list), `s10/pk.py` (raw index-aligned ROM-vs-ours print),
`s10/scan.py` (regex scan of both sides' insn streams, e.g. every
`addiu ?,sp,K`), `s10/p70.py` (the sp+0x70 vehicle census).
The `-fsched-verbose-5` + `-dS`/`-dR` trace is the decisive tool for any
remaining within-cycle order diff.

## conv-heavy2 session 11 (2026-07-28): func_001FCA20 — the exp134/135 tie MECHANISM is solved (sched1 `adjust_priority`/`birthing_insn_p`), two flips proven, ROM-consistent vehicle still open

Committed TU is UNCHANGED at **sites 2 / rc 2** (canonical seed
`act-env_x40scalars_s2_rc2.c`, crutch-free). The session's product is a
compiler-source-verified mechanism plus a proof-of-concept seed that
makes the WHOLE instruction-order residual vanish:
`tough_nuts/act-env_func_001FCA20/act-env_s11_orderfixed_s4_rc14.c`
(**sites 4 / rc 14, ZERO order divergences — every remaining site is a
pure register-name diff**). It is saved but NOT adopted, because one of
its four sites proves its `b20` vehicle is not ROM's shape (below).

### THE MECHANISM (haifa-sched.c, source-verified — supersedes session 10's "unexplained residue")

Session 10 correctly reduced exp134/135 to "sched1 must issue the ll18
load (insn 365, `ld v0,24(s4)`) before the b20 load (insn 368,
`ld a3,32(s4)`)", and correctly noted that the dep table gives
prio(365)=7 > prio(368)=6 yet 368 issues first. The cause is NOT
`actual_hazard`/`schedule_select`. It is **`adjust_priority()`**, called
from `schedule_insn()` on every insn whose dependences resolve:

```c
/* haifa-sched.c */
adjust_priority (prev) {
  if (reload_completed == 0) {           /* sched1 ONLY, never sched2 */
    n_deaths = <count of REG_DEAD notes>;/* ALWAYS 0: find_pre_sched_live
                                            already UNLINKED them */
    switch (n_deaths) { ... case 0:
        if (birthing_insn_p (PATTERN (prev))) {
            int max = max_priority;
            if (max > INSN_PRIORITY (prev)) INSN_PRIORITY (prev) = max; }
    }}}
birthing_insn_p (pat) {   /* dest must be a REG that is */
   if (REGNO_REG_SET_P (bb_live_regs, i))   /* LIVE AT BLOCK END, and */
     return (REG_N_SETS (i) == 1); }        /* SET EXACTLY ONCE */
```
and in `schedule_insn`, just before the dependent loop:
`max_priority = MAX (INSN_PRIORITY (ready[0]), INSN_PRIORITY (insn))`.

Applied to our block 11 (both loads are released by the EnvCopy32
BLKmode block move, insn 289, at clock 14, cost 2):
- `max_priority` = prio(289) = **9**.
- **368 (b20)**: dest is `b20`, single-set, and LIVE-OUT (the bit-4 test
  `dsll v0,a3,0x1c` is in the successor block 13) → birthing → its
  priority is **bumped 6 → 9**.
- **365 (ll18)**: dest is the `ll18` accumulator, set 4 times (load +
  three `&=`) → `REG_N_SETS != 1` → no bump → stays **7**.
- 9 > 7, so 368 issues at clock 16 and 365 at 17. dsll becomes ready
  before and1/and2 and wins the sched2 within-cycle LUID tie at exp134.

Three corollaries worth keeping:
- `bb_live_regs` at `schedule_block` time is the **live-at-block-END**
  set (`find_pre_sched_live` walks the bb forward from
  `global_live_at_start`, setting on each SET and clearing on each
  REG_DEAD/REG_UNUSED, and `schedule_region` comments it as
  "compute live-regs at block end"). So "birthing" == *single-set AND
  live out of its basic block*.
- The `ready` array is sorted ASCENDING by priority and the issue loop
  runs `for (i = n_ready-1; i >= 0; i--)`, so **the LAST insn printed in
  `;; Ready list (t = N):` is the one that issues first**. (`cost == 1`
  from `actual_hazard` is neither scheduled nor queued — the insn is
  silently skipped for that cycle. Watch for it.)
- `max_priority` = prio(the releasing insn) ≥ prio(365) + 2 **always**
  (289's own priority is computed as `cost(289→365) + prio(365)`), so
  raising 365's priority can NEVER out-run the bump. The class is
  binary: either kill 368's bump, or earn one for 365.

### The two proven flips (both measured, both fix the class)

**Route A — make the b20 pseudo multi-set** (`REG_N_SETS != 1`), so 368
is not birthing and the raw 7 > 6 decides. Three independent vehicles
all flipped exp134/135:
  1. `b20 <<= 0x1C` inside the else-if (comma operator) — sites 6.
  2. `b20` hoisted to function scope and reused for the line-430
     `*(long long*)(env+0x18)` read — sites 7.
  3. `b20` hoisted to function scope and reused for the line-890
     `*(long long*)(env+0x20)` read — sites 6, then **sites 4** after
     the follow-on fix below.

**Route B — make the ll18 load birthing** (SSA-spell the three masks so
the load's dest is single-set, then give it a live-out use). Verified
with a throwaway `FI(0x1BC) = 1 | (int)ll18;` in the else arm: the load
order flips (sites 93 — the fake use wrecks the coloring, it is a
diagnostic only). With both loads bumped to 9 the tie falls through
REG_WEIGHT (1 == 1) and the `last_scheduled_insn` class (1 == 1) to
**depend_count**, where 365 has 3 dependents vs 368's 2 → 365 wins.

### The follow-on class this EXPOSED (and its fix) — a genuine stall reset

Once the loads swap, exp134/135 is byte-clean and the NEXT within-cycle
tie appears one slot later: ROM `dsra32 ; and v0,v0,a2`, ours
`and v0,v0,a2 ; dsra32`. Same analysis, different decider: at sched1
neither insn is birthing, priorities tie at 3, REG_WEIGHT ties at 0 and
depend_count ties at 2, so `rank_for_schedule` falls all the way through
to **INSN_LUID = source order**. Fix: **move the `bit5 = ...` statement
between the 2nd and 3rd `&=`** so the dsll/dsra32/andi chain is emitted
before the third `and`. sites 6 → **4**.
(Session 10 measured this same edit as byte-NEUTRAL and filed it under
"do not retry". It was neutral only because the loads were still in the
wrong order — a textbook case of a prior null result being void once the
upstream class lands.)

### Why the saved seed is NOT adopted — the ROM register audit that kills route A

`objdump` of the ROM shows the env+0x20 value in **a3 in exactly one
region** (`ld a3,32(s4)` @0x210, `dsll v1,a3,0x1b` @0x21c,
`dsll v0,a3,0x1c` @0x240) and **every other `long long` read of
env+0x20 in the function is in v0** (@0x8ac, @0xa78, @0xf70). One pseudo
gets one hard register, so ROM's b20 cannot be the same C variable as
any other env+0x20 read. Consequently every route-A vehicle costs at
least one site at the partner read; the line-890 vehicle costs exactly
one (exp988 `ld v0,32(s4)` → `ld a3,32(s4)`).

The other three sites of the saved seed (exp97/114/127) are a v0↔v1
swap between the `sub` pseudo and the `FI(0x30)` temp in the block-move
region. **It is not caused by pseudo renumbering** — hoisting the
`long long b20;` declaration to function scope WITHOUT the merge is
byte-neutral (sites 2), so the renumbering is innocent. It is a
whole-function `hard_reg_n_uses` / local-alloc census effect of the
changed sched1 order: the two pseudos have identical refs/live_length
and identical positions (96 and 1075) in the greg sorted order in both
builds, so only the pre-seeded usage histogram can have moved them.
Probes that were byte-neutral on it: inlining `sub` into the block-move
expression; hoisting `FI(0x30)` into its own named local.

### The open contradiction — read this before proposing anything

ROM's register audit says b20 is single-set and live-out ⇒ birthing ⇒
bumped ⇒ 368 should issue first ⇒ ROM's own emission order should be
ours. It is not. So one premise above is wrong, and finding which one IS
the remaining work. Ruled out this session, with reasons:
- the `sd v0,24(s4)` is in block 11 (reorg cannot fill a non-annulling
  `beq` delay slot from the fall-through thread), so ll18's pseudo
  cannot be live at block end via the store;
- block 13 (the bit-4 test, `.L` target 0x240) is a real successor, so
  b20 really is live-out;
- there is no reg-reg copy and no second `ld` in ROM between 0x210 and
  0x240, so the gcse-`reaching_reg`-copy story (a copy that coalesces to
  `daddu a3,a3,zero` and is deleted by `delete_noop_moves`) has no
  trace — and spelling both flag tests as independent memory reads
  (no shared local) is byte-neutral: cse1 walks block 11 → block 13 as
  one path and substitutes the pseudo directly, no copy is ever created;
- `n_deaths` can never be non-zero (find_pre_sched_live unlinks the
  REG_DEAD notes first), so the `>>= 1` arm of `adjust_priority` is
  unreachable;
- raising prio(365) is provably useless (see the corollary above).

### Next reasoned lever (highest-value first)

1. **The release-clock axis, untested.** The priority bump only matters
   because both loads become ready in the SAME clock (16). If the ll18
   load were ready at clock 15 and the b20 load at 16, the bump is
   irrelevant and the order is forced. Today both are released by insn
   289 with cost 2. Look for a source shape that gives the two loads
   DIFFERENT release times without moving either out of its ROM slot —
   note that the memory unit is idle at clocks 11/13/15, so simply
   freeing the ll18 load from the block move sends it to clock 11 (too
   early); what is wanted is a shape where it is released at clock 14
   (e.g. by insn 283, the `sub` load at clock 12, cost 2) and loses that
   clock to 289 on priority (8 > 7), issuing at 15. That is an
   alias-regime asymmetry question about the `EnvCopy32` copy's alias
   set vs the two loads'.
2. **Re-audit the premise list above rather than re-deriving it.** The
   most suspect entry is "289 is the releasing insn for both loads in
   ROM"; the second most suspect is the assumption that ROM's block 11
   is its own single-block scheduling region (if it were part of a
   multi-block region, `find_pre_sched_live` runs for every bb before
   any bb is scheduled and `bb_live_regs` ends up holding the LAST bb's
   live set — which would make b20 non-birthing for free).
3. **If route A ever becomes tenable**, the residual is only the
   v0↔v1 census swap (exp97/114/127) plus the partner-read site; start
   from `act-env_s11_orderfixed_s4_rc14.c`.

### Tools added this session
`s11/sd.sh` — one-shot `-fsched-verbose-5 -dS -dR` dump into a named dir
(the `.sched` file carries both the dependence table AND the full
per-clock ready-list/issue trace for sched1; `.sched2` the same for
sched2, where `insn:TI` marks the first insn of each cycle so the
within-cycle grouping can be read off directly).
The ee-gcc 2.9 source tree used for the verification above is staged at
`/tmp/claude-1005/-primary-dev-ico/fd7bfd8a-.../scratchpad/eegcc_src/`
(`haifa-sched.c`); re-stage it rather than re-deriving from memory.

### Session-11 addendum: the "zero-code second set" hunt (all null, with reasons)

`count_reg_sets()` counts **CLOBBER as a set**, so a `(clobber (reg X))`
would give `REG_N_SETS(b20) == 2` with zero emitted code — the ideal
route-A vehicle. Tried and byte-neutral (sites 2, no order change):
- `union LLAlias b20; b20.ll = *(long long*)(env+0x20);` with both flag
  tests through `b20.ll`. An 8-byte union is DImode and a whole-member
  store is a plain `emit_move_insn` — no clobber. (A wider aggregate
  would go to memory, so this axis has no headroom on MIPS.)
- `long long b20 = 0; b20 |= *(long long*)(env+0x20);` — combine folds
  `0 | x` and flow deletes the dead first set before `REG_N_SETS` is
  recomputed, so it is genuinely one set again.
- Spelling the bit-4 test as a fresh `*(long long*)(env+0x20)` read (with
  or without a `b20` local for bit-5): cse1 treats block 11 → block 13 as
  one path and substitutes the existing pseudo — no gcse `reaching_reg`
  copy is created, so the "copy that coalesces to a deleted no-op move"
  route has no entry point here.
Also byte-neutral, on the *other* residual (the v0↔v1 census swap in the
order-fixed seed): inlining `sub` into the block-move expression, and
hoisting `FI(0x30)` into its own named local.

## conv-heavy2 session 12 (2026-07-28): func_001FCA20 — the exp134/135 class is now bounded by THREE proofs; the census swap is re-classified as a FALSIFICATION TEST for candidate flip vehicles

Committed TU is UNCHANGED at **sites 2 / rc 2** (canonical seed
`act-env_x40scalars_s2_rc2.c`, crutch-free, tree clean, TU == seed).
The session's product is negative-space: three hard proofs that close
whole axes, one new empirical law, and a re-framing of the residual.

### PROOF 1 — the sched2 clock-20 tie can ONLY be broken by INSN_LUID (closes the "fix it at sched2" axis)

Re-derived from the real `-fsched-verbose-5` trace (s12/base), not from
the ledger. sched2 block 11 issues `365 (ld ll18)` @17, `368 (ld b20)`
@18, `373 (and1)` @19, then clock 20 has ready `{378 (and2), 386 (dsll)}`
with **INSN_PRIORITY 4 == 4**, the same `last_scheduled_insn` class (both
class 3 vs 373), and `depend_count` 2 == 2 → `rank_for_schedule` falls
through to `INSN_LUID`, and sched1 put 386 first.

A priority-based fix is **provably impossible**:
`prio(378) = 1 + prio(383)` and `prio(386) = 1 + prio(389)`, so
`prio(378) > prio(386) ⟺ prio(383) > prio(389)`. But clock 21 has ready
`{383, 389}` and ROM emits `dsra32 (389)` BEFORE `and3 (383)` — which
requires `prio(389) ≥ prio(383)`. The two requirements are mutually
exclusive, so the clock-20 order is *necessarily* a LUID decision and
**sched1 must emit 378 before 386.**

### PROOF 2 — that forces the sched1 load order (closes "keep 368 first")

At sched1, `386_clock = 368_clock + 2` (ld→dsll latency 2) and
`378_clock = 365_clock + 3` (ld→and1 = 2, and1→and2 = 1). Both latencies
are fixed by ROM's own instruction set in the block, and the ALU can
never be saturated at clocks 18/19 (the only other alu work in block 11
— the three mask constants, prio 6/5/4 — is released by the call at
clock 9 and is consumed at clocks 10/11 with the machine idle at 12/13/15).
Therefore `378 < 386` ⟺ **`368_clock ≥ 365_clock + 1`**: the ll18 load
must issue no later than the b20 load. There is no third option.

### PROOF 3 — the `max_priority` corollary, tightened

`ADJUST_COST` (mips.h) is `if (REG_NOTE_KIND (LINK) != 0) COST = 0`, and
`insn_cost` then clamps to 1 — so an anti/output dependence costs 1 and a
true dependence costs `result_ready_cost` (2 for the loads). Hence
`max_priority = INSN_PRIORITY (289) ≥ cost(289→365) + prio(365) ≥ prio(365) + 1`
**always**. A birthing 368 is therefore *always* bumped strictly above
365. The class stays binary: kill 368's bump (route A) or earn one for
365 (route B) — and note that route A wins **outright** (raw 7 > 6, no
tie needed), while route B wins on the `depend_count` tie-break (365 has
3 dependents, 368 has 2).

### THE NEW LAW — flip ⟹ census swap, in EVERY vehicle (this is the key result)

Three structurally independent flip vehicles were built and measured:
- **A1** `b20 <<= 0x1C` in the else-if (comma operator) + the bit5 move → **sites 4 / rc 14**, sites `[97, 114, 127, 144]`
- **A2** `b20` hoisted to function scope and reused for the line-890
  `*(long long*)(env+0x20)` read (= session-11's saved seed) → **sites 4 / rc 14**, sites `[97, 114, 127, 988]`
- **B**  SSA-spelled masks + a throwaway live-out use of the load's dest → sites 105, whose site list **still contains 97, 114, 127**

All three produce the *same* 3-site census swap: exp97/114/127, where the
`sub` pointer (r261) and the `FI(0x30)` temp (r263) exchange `v0`/`v1`
and the block move's 3rd scratch follows. **ROM has the flipped order AND
r261=v0 / r263=v1** (base, sites 2, matches ROM there).

⇒ **exp97/114/127 is not a separate class to clean up afterwards — it is
the signature of a WRONG flip vehicle.** Any candidate that reproduces it
is refuted by construction. This is the cheapest available oracle for the
next attempt: build the vehicle, look for 97/114/127, discard if present.

Measured neutral ON TOP of the flip (so the swap is not local to them):
inlining `sub` into the block-move expression; a named `h30` temp; a named
`srcp`; hoisting the `dst` pointer; a fresh `sub2` name; `((char**)FI(0x30))[0x57]`;
a `char **h30` double-deref; naming the three mask constants as locals;
inlining the `p10`/`FI(0x1C4)` block; deleting `w20 = 0;`; moving `w20 = 0;`.

### Axes CLOSED this session (do not re-derive)

1. **Multi-block scheduling regions are impossible here.** All **693**
   `--- Region Dependences ---` headers in the whole TU are `bb 0`;
   `schedule_insns` takes the `find_single_block_region()` path for every
   block. So `bb_live_regs` really is block 11's live-at-END, and
   session-11 lever 2's "last-bb live set" story is dead.
2. **The zero-code CLOBBER (free route-A second set) is dead.**
   `store_constructor` (expr.c) really does emit `(clobber (target))` for
   a UNION/RECORD constructor into a register — confirmed in the `-dr`
   dump as `(insn 367 365 369 (clobber (reg/v:DI 299)))` for
   `union LLAlias b20 = { *(long long*)(env+0x20) };`. But flow's
   `insn_dead_p` returns 1 for *"a CLOBBER of a pseudo-register that is
   dead"*, so it is deleted before `REG_N_SETS` is computed. Measured
   byte-neutral (sites 2), and the `-df` dump shows the clobber gone.
   For a clobber to survive, the pseudo must be live AFTER it — which
   requires a prior real set, i.e. no longer free. `struct { long long ll; } b20 = {...}`
   behaves identically.
3. **No route-A merge partner exists anywhere in the function.** An
   exhaustive scan of every insn writing `$7` in ROM's `func_001FCA20`
   (78 sites) shows the ONLY 64-bit `ld` into `a3` is our 0x210 load;
   everything else is `lw`/`li`/`addiu`/`move`/`slti`/`bne` or a block-move
   `ldl/ldr` scratch. Every env+0x20 read elsewhere (0x8ac, 0xa78, 0xf70,
   0x1fa8, 0x1fc8) and every env+0x18 read (0x108, 0x5cc, 0x670, 0x77c,
   0xa9c, 0xacc, 0x2018) is in `v0`. So every route-A merge costs ≥1 site
   at the partner — generalises session-11's audit to the whole function.
4. **Moving either load across the block move is catastrophic**: hoisting
   the ll18 load above the `EnvCopy32` copy = sites 90; hoisting the b20
   load = sites 134. Both loads must stay memory-dependent on insn 289,
   confirming the dependence premise from the other side.

### A FREE structural degree of freedom found (use it)

**SSA-spelling the three masks is byte-NEUTRAL** (sites 2):
```c
long long t0 = *(long long *)(env + 0x18);
long long t1 = t0 & 0xFFFFFF7FFFFFFFFFLL;
long long t2 = t1 & 0xFFFFFEFFFFFFFFFFLL;
long long t3 = t2 & 0xBFFFFFFFFFFFFFFFLL;
((union LLAlias *)(env + 0x18))->ll = t3;
```
verified in the `-dl` dump: the load's dest becomes **single-set**
(`REG_N_SETS == 1`), yet the emitted bytes are identical. So **route B
now needs exactly ONE more thing: a live-out use of `t0`.** That is the
whole remaining gap on that route.

Also byte-neutral (sites 2, all measured): `const long long b20`; b20 read
through `union LLAlias`; `*(volatile long long *)`; an explicit copy
`b20b = b20` for the bit-4 test; two independent re-reads with no shared
local; `struct {long long ll;} b20 = {...}`; and moving the b20 load to
*after* the ll18 store.

### Residual at sites 2 / rc 2 — unchanged, but now sharply posed

Still only exp134/135 (`dsll v1,a3,0x1b` one slot early). The open
question is no longer "how do I flip the loads" (three ways are known) but:

> **What source shape flips the sched1 load order while leaving
> `block_alloc`'s $2/$3 choice for r261 (`sub`) and r263 (`FI(0x30)`) alone?**

### Why the order-fixed seed was NOT adopted (re-evaluated, structure-over-count)

`act-env_s11_orderfixed_s4_rc14.c` has zero instruction-order divergences,
which is superficially the stronger structure. It was still rejected,
for a *new* reason: by the law above, its 3 census sites are the
fingerprint of a wrong mechanism, not incidental noise — ROM reaches the
same instruction order **without** disturbing the census. The base keeps
ROM's register census byte-exact everywhere and differs only by one
within-cycle swap; the seed trades a real class for a mechanism the ROM
register audit (closed axis 3) already refutes. Base is the better
platform; the seed stays on disk as a waypoint.

### Next reasoned lever (highest value first)

1. **Read `block_alloc`'s SUGGESTED-register first pass** — the census
   flip is decided there, and analysis of the ordinary path *cannot*
   explain it. Measured from the `-dl` RTL, r261 and r263 have identical
   positions in base and in every flipped build (insn indices 172 / 176 /
   177), identical `REG_N_REFS` (2 each), identical modes, and their
   `qty_birth/qty_death` windows ([2·172, 2·176) and [2·176, 2·178)) do
   not overlap under `post_mark_life` (`while (birth < death)`) — so
   `QTY_CMP_PRI` (`floor_log2(n_refs)·n_refs·size / (death − birth)`)
   gives r261 4× the priority of r263 in BOTH builds and cannot produce
   the exchange. The only remaining mechanism in `block_alloc` is the
   pre-pass `if (qty_phys_num_sugg[q] != 0 || qty_phys_num_copy_sugg[q] != 0)`
   ordered by `qty_sugg_compare`, fed by `combine_regs`. Find which of
   the two picks up a suggestion and why it changes with the load order —
   that is very likely the same property the correct flip vehicle has.
2. **Route B's last mile**: a live-out use of `t0` (the raw env+0x18
   value) in block 12 or 13 that emits no code. SSA spelling is already
   free, so this single find completes route B — and route B does not
   need any second set of `b20`, so it is the vehicle most likely to
   leave block-11's local-alloc census untouched.
3. **The clock-14 releaser idea (untested, cheap to reason about)**: if
   368's LAST dependence were resolved by an ALU insn at clock 14 (the
   ALU is IDLE at clock 14 while 289 occupies memory) with
   `prio ≤ 7`, then `max_priority` for the bump is that insn's priority,
   368 never out-runs 365, and `INSN_TICK(368)` is still 16. Look for an
   output-dependence vehicle (a set of the b20 pseudo) that schedules
   into that free clock-14 ALU slot.

### Tools added this session
`s12/t.sh`, `s12/t2.sh` (sd.sh + block-11 clock table + oracle in one shot),
`s12/drive.py` / `s12/drive2.py` (variant drivers: substitute a source
block, run `match_diff`, print `sites/rc` + the site-index list — ~1 s per
variant, which is what made the 30-odd measurements above affordable).
`s12/dl_base`, `s12/dl_g2` (`-dg -dl -dS -dj` dumps of the base and of the
A1 flip vehicle, for the local-alloc comparison). gcc-2.95.3 `expr.c`,
`stmt.c`, `optabs.c`, `explow.c`, `function.c`, `emit-rtl.c`, `jump.c`
staged under `s12/src/` (the `store_constructor` clobber was found there).

### Session-12 addendum: why the CLOBBER axis is closed for good (not just "the constructor one is")

`count_reg_sets_1` / `mark_set_1` both strip `SUBREG/ZERO_EXTRACT/
SIGN_EXTRACT/STRICT_LOW_PART` and then do `REG_N_SETS (regno)++`, and
they are called for CLOBBERs as well as SETs — so *any* surviving clobber
of the b20 pseudo would give `REG_N_SETS == 2` and kill the birthing bump
with zero emitted bytes. The axis is nevertheless closed by a semantic
argument, not just by the one measurement:

- Placed BEFORE the load, the pseudo is not live after the clobber, so
  flow's `insn_dead_p` (*"A CLOBBER of a pseudo-register that is dead
  serves no purpose"*) deletes it. Measured: the `-dr` dump has
  `(insn 367 365 369 (clobber (reg/v:DI 299)))`, the `-df` dump does not.
- Placed AFTER the load and before a use, flow keeps it (the pseudo is in
  `needed`) — but the clobber then *kills* the loaded value, so the load
  itself becomes a dead store and is deleted instead. Either way the
  emitted code changes or the second set disappears.

So a zero-code second set of `b20` does not exist in this compiler. Route
A therefore *always* costs at least one real insn or one register-name
site, which — combined with closed axis 3 (no 64-bit `a3` merge partner
anywhere in the function) — is a strong argument that **ROM's vehicle is
route B, not route A**, and that the remaining find is the zero-code
live-out use of the ll18 load's dest.

## conv-heavy2 session 13 (2026-07-28): func_001FCA20 — the exp97/114/127 census swap is SOLVED (local-alloc `fake_birth/fake_death`), session-12's "NEW LAW" is REFUTED, and the residual is now a two-line arithmetic condition

Committed TU is UNCHANGED at **sites 2 / rc 2** (canonical seed
`act-env_x40scalars_s2_rc2.c`, crutch-free, tree clean, TU == seed).
The session's product is the *cause* of the census swap — it is not a
property of the flip vehicle at all — plus a proof-of-mechanism
measurement and a sharply-posed residual.

### THE FIND — the census swap is a local-alloc lifetime-extension collision, not a vehicle fingerprint

`block_alloc` (local-alloc.c) does **not** allocate with a qty's real
live range on its first try. Under `INSN_SCHEDULING` it first tries an
*extended* range:

```c
  int fake_birth = MAX (0, qty_birth[q] - 2 + qty_birth[q] % 2);
  int fake_death = MIN (insn_number * 2 + 1, qty_death[q] + 2 - qty_death[q] % 2);
  if (flag_schedule_insns_after_reload && !optimize_size && !SMALL_REGISTER_CLASSES)
    { qty_phys_reg[q] = find_free_reg (..., fake_birth, fake_death);
      if (qty_phys_reg[q] >= 0) continue; }          /* real range only as FALLBACK */
```
(`/* We try to avoid using hard registers allocated to qtys which are
born immediately after this qty or die immediately before this qty. */`)
and `find_free_reg` both *reads* `regs_live_at[born..death-1]` and
*marks* the winner with `post_mark_life (regno, mode, 1, born_index,
dead_index)` — i.e. with the **fake** indices. Every qty's footprint is
therefore one insn wider on each side.

Apply that to block 11 (indices are `2 * insn_number` within the block):

- `r298` (the ll18 accumulator: `refs 8, live_length 8`) has by far the
  highest `QTY_CMP_PRI` (`floor_log2(8)*8/len ≈ 17100` vs r261's `10000`
  and r263's `2500`), so it is allocated **first** and marks `$2` over
  `[2*n365 - 2, 2*n394 + 2)`.
- `r261` (`sub`, dies at the `EnvCopy32` block move 289) is allocated
  next and ORs `regs_live_at[2*n283 - 2 .. 2*n289 + 1]`.

⇒ **r261 keeps `$2` iff `2*n365 - 2 > 2*n289 + 1`, i.e. iff
`n365 >= n289 + 2`** — at least ONE insn between the block move and the
ll18 load *in the sched1 chain*.

- **base**: chain is `289, 368, 365` — the b20 load sits between them,
  `n365 = n289 + 2`, no overlap, `r261=$2 / r263=$3` = ROM. ✔
- **every flip vehicle**: chain becomes `289, 365, 368`, `n365 = n289+1`,
  the two fake windows overlap on exactly TWO index units, `r261` is
  pushed to `$3` and `r263` then takes the vacated `$2`. That is
  precisely exp97/114/127, in the observed direction. ✔

**⇒ Session 12's "NEW LAW" (`flip ⟹ census swap ⟹ the vehicle is
refuted by construction`) is WRONG and must not be used as an oracle.**
The swap is a knife-edge side effect of chain adjacency; the flip
vehicles were never implicated. All of A1 / A2 / route-B are re-opened.

### PROOF (measured, s13)

Diagnostic **D4** = A1 flip + one extra insn placed so sched1 issues it
at clock 15 (a store with an *output* dependence on the block move —
`ADJUST_COST` clamps it to 1, so it is released at 14 and issued at 15,
landing between `289` and `365` in the chain):

```c
*(EnvCopy32 *)((char *)arg4 + 0x170) = *(EnvCopy32 *)(sub + 0x180);
*(int *)((char *)arg4 + 0x170) = 0;          /* THROWAWAY DIAGNOSTIC */
```
→ **sites 5**, site list `[131, 136, 137, 144]` + the store itself.
**97 / 114 / 127 are GONE.** A1 alone is sites 6 `[97,114,127,136,137,144]`.

Control **D3** = the same idea but the extra insn *consumes* `sub`
(`w20v = sub + 0x180;`): the insn does land at clock 14 next to 289, but
it also moves `r261`'s death one insn later, so the windows overlap
again → 97/114/127 still present. **The gap insn must not reference
`sub`.**

### The residual, now a two-line condition

sched1 must simultaneously satisfy
1. **365 before 368** (session-12 PROOF 1/2, unchanged — else the sched2
   clock-20 LUID tie emits `dsll` before `and2` = exp134/135), and
2. **`n365 >= n289 + 2`** — at least one insn between the block move and
   the ll18 load in the sched1 chain.

and block 11's ROM insn set appears to contain no insn that can occupy
that slot. Exhaustively, for X to sit there it must be issued at clock
14 (2nd slot) or 15, i.e. released at 12-14:
- the three mask constants are released by the CALL at clock 9 (the call
  is a full barrier: its dependent list is literally every following insn
  in the block) and are consumed at clocks 10-11 by the 2-wide issue —
  nothing can defer one of them without a second SET of the same pseudo,
  which ROM refutes ($4/$5/$6 are three distinct registers);
- an ALU insn released by `283` at cost 2 (ready 14) must *use* `r261`,
  which is exactly what control D3 shows is self-defeating;
- an insn released by `289` at cost 1 needs an anti/output dependence on
  the copy, i.e. it writes `r88`/`r261` or writes memory — the memory
  case is D4 (an extra store ROM does not have);
- `281`/`283`/`394`/`397` are pinned by their own dependences.

So one further premise is still wrong. **The unexamined ones, in order:**

1. **`qty_phys_sugg` / `qty_phys_copy_sugg`.** A qty that carries a
   register *suggestion* is allocated in `block_alloc`'s FIRST pass with
   its **REAL** `qty_birth/qty_death` (`find_free_reg (..., /*just_try_
   suggested=*/1, qty_birth[q], qty_death[q])`) — the fake extension is
   skipped entirely. If ROM's `r261` (or the accumulator) picks up a
   suggestion, the 1-unit collision never happens and the flip is free.
   Suggestions are created ONLY by `combine_regs` on a hard-reg↔pseudo
   pair, i.e. a reg-reg copy with a hard register (`(set (reg $2) (reg
   P))` or `(set (reg P) (reg $2))` — a call return value, an outgoing
   argument, a return). Insns `243`/`263` in this very block already do
   this for `p10`/`w20` ($4). **Find the dev shape that routes `sub` (or
   the flag accumulator) through such a copy.** This is the single
   highest-value open lead.
2. **`REG_BASIC_BLOCK`.** A pseudo referenced in >1 basic block is not a
   local qty at all, so it never marks `regs_live_at`. Measured this
   session (see below): making the accumulator multi-block DOES kill the
   census swap, but hands `$2` to the bit5 `dsll` temp instead. Making
   `sub` multi-block is catastrophic (it then crosses a call).
3. **`depend_count` at sched2 clock 20** — the only way to break the
   `{378, 386}` tie *without* touching the sched1 load order. Both sides
   currently have exactly 2 dependents (`{383,397}` / `{389,397}`). A
   third dependent for `378` (an anti-dependence from a later insn that
   writes `$5`, or any extra consumer of the 2nd `and` result) would win
   it outright. Nothing in ROM's block-11 tail writes `$5` — but this
   axis has never been attacked from the *source* side.

### Measured this session (all leads, none adopted)

| variant | sites | note |
|---|---|---|
| base | 2 | `[134,135]` |
| SSA masks (`t0..t3`) | 2 | byte-neutral, confirms session 12 |
| A1 (`b20 <<= 0x1C`) | 6 | `[97,114,127,136,137,144]` |
| SSA + A1 | 6 | identical — SSA does NOT split the accumulator qty (local-alloc `combine_regs` ties `t0..t3` back into one qty) |
| **A1 + D4 gap store** | **5** | **97/114/127 gone — the proof** |
| A1 + D3 (`w20v = sub+0x180`) | 37 | gap present but `r261` death moves → swap persists |
| `ll18` shared with the 0x0008.. `\|=` site (→ multi-block) | **2** | `[131,133]`: census CLEAN, `b20 = a3` ✔, but the accumulator gets **v1** (the bit5 `dsll` temp takes `$2`) and the order stays unflipped |
| `ll18` shared with the b18 site | 4 | census clean AND the emitted load order flips, but accumulator→`a3`, b20→`v1` |
| `ll18` shared with 2+ sites | 3-11 | the `\|=`→read/modify/write respelling costs sites at the partner |
| `sub` hoisted to function scope (shared) | 121 | it then crosses `func_0014B358` → callee-saved reg, catastrophic |
| `b20` as a 16-byte union/struct (to get a `(set (subreg:DI (reg:TI …)) …)` dest, which `birthing_insn_p` rejects) | 496 | 16-byte aggregates go to memory on this target — axis dead |
| A1 + `w20 = 0` after the copy / pin block before the copy / `char**` double-deref copy | 6 | all byte-neutral on the census |

### Why the "accumulator is multi-block" branch is worth a second look

`ll18` shared with the line-602 site gives **sites 2** with a completely
different residual: the whole block-11 register census is ROM's *except*
that the flag accumulator and the bit5 `dsll` temp exchange `v0`/`v1`
(and the load order is still unflipped). ROM's own evidence supports the
data model — **every** `env+0x18` read in the function is in `v0` (0x108,
0x210, 0x5cc, 0x670, 0x77c, 0xa9c, 0xacc, 0x2018), which is exactly what
ONE function-wide `long long` dev variable allocated by global-alloc
looks like. That branch needs only one more thing: keep the bit5
`dsll`/`dsra32`/`andi` temps off `$2`. Under the mechanism above they
take `$2` because, with the accumulator gone from local-alloc, nothing
else owns `$2` across `[n386..n391]`.

### Tools added this session
`s13/drive.py` (variant driver over the current TU: substitutes the ll18
head block and/or the `else if` line, runs `match_diff`, prints
`sites/rc` + the site-index list), `s13/mk.py`, `s13/mk2.py` (partner-site
builders for the shared-`ll18` data model), `s13/a1`, `s13/a1d3`,
`s13/sh1` (`-fsched-verbose-5` dumps of the A1 flip, the D3 control and
the shared-`ll18` build). The ee-gcc 2.9 source tree is re-staged at
`scratchpad/eegcc_src/` (`local-alloc.c` is the file that cracked this;
`haifa-sched.c` for the sched1 half).

### Session-13 addendum: how a qty actually acquires a suggestion (lever 1, made concrete)

`block_alloc`'s tying loop calls `combine_regs (r1, r0, may_save_copy,
…)` for **every** insn whose operand 0 is a REG with an `'='`
constraint, pairing it with each other REG operand — not only for
reg-reg moves. When either side is a HARD register, `combine_regs`
records it in `qty_phys_copy_sugg` (if `may_save_copy`, i.e. a plain
move or a `must_match_0` operand) or else in `qty_phys_sugg`, and
**either one is enough** to route the qty through the first pass
(`if (qty_phys_num_sugg[q] != 0 || qty_phys_num_copy_sugg[q] != 0)`),
which calls `find_free_reg (…, just_try_suggested=1, qty_birth[q],
qty_death[q])` — the **real** window, no fake extension.

Block 11 already exhibits this: insns `232 r188=$1+0x10` and
`252 r189=$1+0x20` are `(set (reg P) (plus (reg HARD) K))`, so `p10` and
`w20` pick up a suggestion for that hard reg. It is the frame/arg
pointer, which `find_free_reg` excludes via `ELIMINABLE_REGS`, so the
first pass returns −1 and they fall back into the main loop **with the
fake window** — i.e. an *unusable* suggestion buys nothing.

So the lever is precise: **`sub`'s pseudo (or the flag accumulator) must
be an operand of an insn that also mentions hard register `$2`, with the
pseudo as operand 0.** On this ABI `$2` = `v0` = the return-value
register, so the shapes that produce it are: the value comes from a call
(`(set (reg P) (reg $2))` — a copy that `delete_noop_moves` will erase
once P is coloured `$2`, i.e. ZERO emitted bytes), or the value is
computed as `(plus (reg $2) K)` off a call result. If ROM's dev C makes
`sub` (or the flag word) flow from a call return in either form, `sub`
is allocated in the first pass with its real `[2*n283, 2*n289)` window,
the 2-unit collision with the accumulator's fake window never happens,
`r263` is still pushed off `$2` by `sub`'s real range, and **the flip
becomes free**. Verify the candidate against `n365`/`n289` in the
`-fsched-verbose-5` block-11 clock table and against exp97/114/127.

What was ruled out for the gap route, exhaustively: the three mask
constants cannot be deferred past clock 11 (released by the call, which
depends-on-everything, and consumed by the 2-wide issue), an ALU insn
released by `283` necessarily consumes `sub` and moves its death
(control D3), an insn released by `289` at cost 1 needs an anti/output
dependence on the copy (memory only = an extra store, diagnostic D4),
and `281`/`283`/`394`/`397` are pinned by their own dependences. Also
re-verified byte-neutral this session: the fully memory-resident flag
model (three `&=` straight on `*(long long*)(env+0x18)`, cse folds the
reloads) and moving the `b20` load after the three `&=` — both sites 2.

## conv-heavy2 session 14 (2026-07-28): func_001FCA20 — the exp134/135 ORDER class is SOLVED (two working flip vehicles + the follow-on tie), and the residual is reduced to two precisely-stated ZERO-BYTE requirements

Committed TU is UNCHANGED at **sites 2 / rc 2** (canonical seed
`act-env_x40scalars_s2_rc2.c`, crutch-free, tree clean, TU == seed).
Neither vehicle is adopted: each is refuted as ROM's data model by a
register audit (below), and each costs exactly one extra site.

### THE FIND — `birthing_insn_p` has TWO independent kill switches, and the liveness one is new

`birthing_insn_p` (haifa-sched.c:4198) returns, for a `(set (reg D) …)`:

```c
  if (REGNO_REG_SET_P (bb_live_regs, REGNO (dest)))
      return (REG_N_SETS (REGNO (dest)) == 1);
  return 0;                       /* NOT live  =>  no bump */
```

and `bb_live_regs` is **frozen during scheduling at the block's LIVE-OUT
set** (`find_pre_sched_live` copies `global_live_at_start` and walks the
block head→tail; `find_post_sched_live` only runs afterwards). So the
`env+0x20` load (368) is bumped to `max_priority` iff its pseudo is
**live out of block 11 AND single-set**. Session 11 had only the
`REG_N_SETS` half.

Measured proof of the liveness half — diagnostic **E1** (replace the
`else if` condition so `b20` is not used after block 11): the loads flip
(the exp97/114/127 census fingerprint appears, exp134/135 disappear).

### TWO WORKING FLIP VEHICLES (both kill the bump via `REG_N_SETS != 1`)

| vehicle | sites | residual |
|---|---|---|
| base | 2 | `[134,135]` |
| **P1** — `} else if ((b20 <<= 0x1C, (int)(b20 >> 0x20) & 1)) {` | **4** | `[97,114,127,144]` |
| **M** — `b20` shared with the line-890 `env+0x20` read (2nd set there) | **4** | `[97,114,127,988]` |
| P1 + `ll18` shared with the line-602 `\|=` site | **3** | `[131,133,144]` |
| M + same | 3 | `[131,133,988]` |

With P1 the **whole exp131-140 instruction ORDER is ROM-exact**
(`ld/ld/and/and/dsll/dsra32/and/andi/beq/sd`) and the flag-block register
census is ROM-exact (`acc=v0, b20=a3, bit5 temp=v1`). With P1+602 the
order AND the sub/FI(0x30) census are both ROM-exact.

**The follow-on tie is also solved.** Once the loads flip, the next
divergence is `and3`-vs-`dsra32` (session 11 predicted it). Fix = move
the `bit5 = …` statement anywhere among the first three mask lines
(`bit5pos` 0/1/2 all work; position 3 = the old one leaves it). This is
the "move bit5 between the 2nd and 3rd mask" edit session 10 had filed
as do-not-retry.

### THE RESIDUAL — exactly two zero-byte requirements

1. **A zero-byte flip vehicle.** Both vehicles cost 1 site because they
   need a 2nd SET of the `b20` pseudo and ROM has no spare site for one.
2. **A zero-byte gap insn** between `289` (the EnvCopy32 block move) and
   `365` (the `env+0x18` load) in the **sched1 output order**, so that
   `n365 >= n289 + 2` and local-alloc's fake window does not steal `$2`
   from `sub` (session-13 mechanism, re-confirmed here: diagnostic T5,
   a throwaway `*(int*)((char*)arg4+0x170)=0` right after the move,
   removes 97/114/127).

### ROM REGISTER AUDITS (these close three data models)

- **`a3` holds a DImode value at exactly three ROM instructions in the
  whole function** (`ld a3,32(s4)`, `dsll v1,a3,0x1b`, `dsll v0,a3,0x1c`).
  Every other `env+0x20` access in ROM (0x22c/0x29c/0x3dc/0x7f4/0x7fc…,
  i.e. exp 556/558/671/673/989/2027/2035/2039) is in **v0**. ⇒ `b20`'s
  pseudo is used ONLY here ⇒ the line-890 merge (vehicle M) is refuted,
  and any 2nd set of `b20` must live inside this region.
- **The `ll18` accumulator is a LOCAL qty in ROM.** If it were multi-block
  (global), nothing would own `$2` across the bit5 `dsll/dsra32/andi`
  window and that temp would take `$2`; ROM has it in `v1` and the
  accumulator in `v0`. Measured: the 602-merge build does exactly that
  (acc→v1, temp→v0, sites `[131,133]`). ⇒ the `ll18` cross-site merge is
  refuted as ROM's data model even though it cleans the census.
- ROM emits **nothing** between the block move (exp 130 `sdr a3,392(s6)`)
  and exp 131 `ld v0,24(s4)` ⇒ the gap insn emits zero bytes.

### THE CONTRADICTION TO BREAK NEXT (state it, don't paper over it)

Four premises, each independently supported, cannot all be true:

- **P-a** `bb_live_regs` during sched1 = block-11 live-out (source-read;
  E1-confirmed).
- **P-b** ROM's `b20` pseudo is single-set (the a3 audit above) and
  live-out (ROM's `dsll v0,a3,0x1c` in the else block reads a3) ⇒
  `birthing_insn_p` fires ⇒ 368 is bumped to `prio(289)=9` > `prio(365)=7`
  ⇒ sched1 emits 368 first.
- **P-c** sched1's output order IS sched2's `INSN_LUID` order.
- **P-d** the sched2 clock-20 `{378,386}` tie falls through priority
  (4=4), the `last_scheduled_insn` class test (both class 3, since
  `insn_cost(373→378)==1`) and `depend_count` (2=2 — and ROM has no insn
  that could be a 3rd dependent of `378`: only `383` writes `v0` and
  nothing rewrites `a1`) to LUID; ROM needs `378` first ⇒ sched1 emitted
  `378` before `386` ⇒ the loads DID flip.

P-b and P-d are mutually exclusive. **One of P-a…P-d is wrong; find which.**
Ranked suspicions for session 15:
1. **P-b's "single-set"** — `count_reg_sets_1` (flow.c:4775) strips
   `SUBREG`/`ZERO_EXTRACT`/`SIGN_EXTRACT`/`STRICT_LOW_PART` and
   `count_reg_sets` counts a **CLOBBER** as a set. Find the dev shape
   whose expansion emits a partial-set or a `(clobber (reg b20))` in the
   same PARALLEL — that makes `REG_N_SETS == 2` for free.
2. **P-b's "live-out"** — a zero-byte copy `(set r_new (reg r299))` in
   block 11 with the else block reading `r_new` kills the live-out AND is
   a gap-insn candidate. cse normally collapses it because it FOLLOWS the
   conditional jump; `cse_end_of_basic_block` (cse.c:8394) only follows
   when **`LABEL_NUSES (JUMP_LABEL) == 1`** and the label is preceded by a
   BARRIER. Find a CFG spelling that makes the else-if label have a 2nd
   use or removes the barrier without changing bytes. (gcse is already
   proven dead on this function — session 6 — so nothing else would
   propagate the copy away.)
3. **P-d's `depend_count`** — an anti/output dependence on `378` gives it
   a 3rd dependent and wins the tie with NO flip and therefore NO census
   problem. Tried and failed this session (W1/W2: reusing the mask2 C
   variable for the bit5 temp) because **constant propagation folds the
   mask variable away and the `and` reads a fresh `force_reg` pseudo** —
   the anti-dep never forms. Needed: a mask operand that is a real
   variable cprop cannot fold, or an accumulator respelling that puts a
   post-`378` write on `r298` other than `383`.

### The gap-insn analysis, exhausted from the release-time side

For X to sit between 289 and 365 in the sched1 chain it must issue at
clock 14 (2nd slot) or 15. Everything ready by 13 is issued by 13 (the
issue rate is 2 TOTAL, and t12 has one free slot, t13 two). So X is
released either by `283` at cost 2 (⇒ X reads `sub` ⇒ moves `sub`'s death
⇒ self-defeating, session-13 control D3 — and this holds for any number
of such insns, since the LAST insn before 365 must not read `sub`) or by
`289` at cost 1, i.e. via an **anti/output dependence on the block move**:
X writes `arg4` (r88), writes `sub` (r261), or writes memory. Memory ⇒
bytes. Writing `sub` ⇒ a 2nd set, same death problem. ⇒ **X is a
coalesced reg-reg copy that writes `arg4`.** All no-op spellings of that
(`arg4 = (char*)arg4 + 0`, `arg4 = &((char*)arg4)[0]`, `arg4 = arg4`,
`me0` round-trip) are folded away at expand/cse — measured byte-neutral.

Also measured neutral this session (do not re-run verbatim; the axes stay
open): re-reading `env+0x20` in the `else if` (cse folds it), both bit
tests as direct memory reads, `EnvCopy32` copy respellings (typed dst,
`EnvCopy32*` indexed, inline double-deref, braces removed), swapping the
two load statements, `w20 = 0` moved after the block move, SSA-spelled
accumulator with the flip (sites 6), a fully memory-resident accumulator
with the flip (sites 53), mask-constants-as-variables.

### Tools added this session
`s14/drive.py` (variant runner), `s14/mk.py` (`build(flip=P1|M|None,
ll18=602|618|653|None, bit5pos=0..3)` — composes any flip vehicle with any
`ll18` merge partner and bit5 position), `s14/base/` and `s14/p1/`
(`-fsched-verbose-5 -dS -dR` dumps of the base and of the P1 flip).
Seeds saved: `tough_nuts/act-env_func_001FCA20/act-env_s14_flipP1_s4.c`,
`…_flipP1_ll18_602_s3.c`, `…_flipM890_s4.c`.

## conv-heavy2 session 15 (2026-07-28): func_001FCA20 — a THIRD flip vehicle found and measured (the ll18 load can be made to birth), and it independently proves which of the four premises is false

Committed TU is UNCHANGED at **sites 2 / rc 2** (canonical seed
`act-env_x40scalars_s2_rc2.c`, crutch-free, tree clean, TU == seed).
This was a data-model round per the orchestrator's brief; it produced a
new flip vehicle, a ROM audit that closes it as ROM's data model, and two
new (untested) routes around the census constraint.

### The residual restated exactly (sched dumps, base)

sched1 block 11 emits `289, 368, 365, 386, 373, 389, 378, 391, 383, 394, 397`.
sched2 re-orders to `365, 368, 373, **386, 378**, 389, 383, 391, 394, 397`;
ROM wants `… 373, **378, 386**, 389 …`. **The entire 2-site residual is the
single sched2 clock-20 tie `{378 (and2), 386 (dsll)}`.** Every other insn
in the block, in both passes, is already ROM-exact.

`rank_for_schedule` verified line-by-line against the dumps at that tie:
priority 4 == 4 → `INSN_REG_WEIGHT` skipped (`reload_completed`) → same BB
→ `last_scheduled_insn` = 373, both class 3 (`insn_cost(373→378) == 1`)
→ `depend_count` 2 == 2 (`{397,383}` vs `{397,389}`) → **falls to
`INSN_LUID`**, i.e. the sched1 output order. P-c and P-d re-confirmed.

Also nailed down: MIPS `ADJUST_COST` (mips.h:3917) sets an anti/output
dep cost to **0**, and `insn_cost` then clamps `ncost <= 1` to **1** — so
anti/output deps cost exactly 1 (session 12's number was right, its
mechanism was not).

### R1 is unavoidable: the sched1 flip is the ONLY way to get 378 before 386

386 is released 2 cycles after 368; 378 is released 3 cycles after 365
(365→373 cost 2, 373→378 cost 1). So:

- **368 first** ⇒ 386 issues 2 clocks later, 378 four ⇒ 386 always precedes.
- **365 first** ⇒ 373 at +2, and 378 and 386 both become ready at +3 ⇒ a
  sched1 tie, broken by `INSN_REG_WEIGHT` (378: mask2 dies ⇒ weight 0;
  386: b20 survives ⇒ weight 1; smaller weight preferred) ⇒ **378 first**.

The only alternative — delaying 386 by two clocks so it lands with 378 at
the base's clock 20 — requires an anti/output dependence on **373**, i.e.
386's dest pseudo must be the accumulator (serialises 378/383/394 wrongly)
or the mask1 constant (forces `dsll a0,…` where ROM has `dsll v1,…`).
Both are register-refuted. ALU-contention delay needs 3 extra ALU insns.

Also re-derived independently: while 368 births it **cannot** be beaten —
`max_priority = INSN_PRIORITY(289) = 2 + max(prio 365, prio 368) >=
prio(365) + 2`.

### THE FIND — flip vehicle #3: make the `env+0x18` LOAD birth too

Sessions 11-14 only ever tried to *kill* 368's bump. If **365 also
births**, both loads reach `max_priority = 9`, the tie falls through
`INSN_REG_WEIGHT` (1 == 1) and the `last_scheduled_insn` class (both
class 1 w.r.t. 289) to **`depend_count`**, where 365 has 3 dependents
`{397,394,373}` against 368's 2 `{397,386}` ⇒ **365 wins**.

Two requirements on the load's dest pseudo:

1. **single-set** — free: SSA-spell the three masks
   (`m1 = r18 & M1; m2 = m1 & M2; m3 = m2 & M3;`). Measured **byte-neutral**
   (variants A0 / A0b, sites 2 / rc 2). `combine_regs` still ties all four
   pseudos into one qty, so the local-alloc census is unchanged.
2. **live out of block 11** — the open half.

**Measured (diagnostic A1** = SSA + an artificial `env+0x470 = r18` after
the chain): `[134,135]` DISAPPEAR, the exp131-140 order becomes ROM-exact
except the known follow-on `and3`/`dsra32` tie. Mechanism CONFIRMED.

Why this vehicle matters: it **does not touch `b20` at all**, so it is the
only known flip that is compatible with the session-14 `a3` register audit
that refuted vehicles P1 and M.

### …and the ROM audit that closes it — which is why P-b is the false premise

Audited every use of the raw `env+0x18` value in ROM: all three arms
(exp 140-155) and the join block (exp 156-166) are constants /
`f25` / `sw …,476(sp)` / the `D_00631AE8` xor-movz — **nothing reads it**;
and the whole function has 8 × `ld …,0x18($20)` against 8 × `sd`, i.e.
every later site re-loads. **The raw value has no post-block-11 use in
ROM**, so under P-a (re-verified below) 365 cannot birth in ROM either.

Combined with R1 above, this is an *independent second proof* that the
false premise in the session-14 contradiction is **P-b**: ROM's `b20`
pseudo must NOT be single-set. Since it is provably live-out (`a3` crosses
into block 13) and has no second visible set anywhere (`a3` appears in
exactly 3 insns; every other `env+0x20` access is `v0`, and a shared
variable would be `REG_BLOCK_GLOBAL` ⇒ one hard reg function-wide), **ROM
must contain a zero-byte second SET or CLOBBER of that pseudo.**

### P-a re-verified, and the exact place it is established

`schedule_region` (haifa-sched.c:7608) runs `find_pre_sched_live(bb)` for
**all** blocks of the region *before* any `schedule_block`. For a
single-block region (all of them in this TU) that leaves `bb_live_regs` =
that block's live-out; nothing in `schedule_block` updates it
(`sched_note_set` is called only from `find_pre_sched_live` /
`find_post_sched_live`). P-a is solid.

### The census constraint (R2) re-derived from source, and TWO NEW WAYS AROUND IT

`block_alloc` (local-alloc.c:1414): `fake_birth = qty_birth-2+qty_birth%2`,
`fake_death = qty_death+2-qty_death%2`; `post_mark_life` marks
`[birth,death)` and `find_free_reg` scans `[born,dead)`.
`wipe_dead_reg`'s `output_p` stays **0** for `sub` at the block move
(r261 appears only in the PARALLEL's SOURCE, never a dest) ⇒
`qty_death(sub) = 2*n289`, `fake_death = 2*n289+2`. The ll18 qty marks
`$2` from `2*n365-2`. ⇒ **`sub` keeps `$2` iff `n365 >= n289+2`** —
session 13's rule, now independently source-derived. Every flip puts 365
at `n289+1`, hence the 97/114/127 class.

Two routes NOT yet tried (both would dissolve R2 outright):

- **A hard-register suggestion.** `block_alloc`'s FIRST allocation pass
  (local-alloc.c:1337-1348) allocates any qty with `qty_phys_num_sugg` or
  `qty_phys_num_copy_sugg` != 0 using its **REAL** window, skipping the
  fake extension. If either `sub`'s qty or the ll18 qty carries a `$2`
  suggestion, the windows no longer overlap for any `n365 >= n289+1`.
  `combine_regs` records one when a hard reg is an operand of an insn
  whose operand 0 is the pseudo — canonically `(set P (reg $2))`, a copy
  off a call result. (An *eliminable* suggestion such as `$1` buys
  nothing: `find_free_reg` excludes eliminables and the qty falls through
  to the fake-window pass.)
- **The allocation ORDER.** `QTY_CMP_PRI = floor_log2(refs)*refs*size /
  (death-birth) * 10000`. ll18 acc: refs 8, size 1, life 2*(n394-n365)
  ⇒ ~13.3k-15k. `sub`: refs 2, life 2 ⇒ 10k. **`sub` needs exactly ONE
  more reference (refs 3 ⇒ 15k) to be allocated first**, after which the
  fake window is irrelevant. Note `count_reg_sets_1` (flow.c:4780) bumps
  **both** `REG_N_SETS` and `REG_N_REFS` for a **CLOBBER** — so a single
  surviving clobber of `sub` would do it. Symmetrically, dropping the
  ll18 qty to 6 refs also flips the order.

### Why every copy vehicle folds — cse's follow-jump condition, pinned

`cse_end_of_basic_block` (cse.c:8394) extends the cse path across the
`if (bit5)` branch iff `LABEL_NUSES(JUMP_LABEL) == 1` **and** the first
non-NOTE insn before the label is a `BARRIER` (the backward scan also
stops on a `CODE_LABEL` with `LABEL_NUSES != 0`). Both hold here, so cse
canonicalises any `b20b`-style copy back to `b20` and the copy dies.
Breaking either half (a second use of the else-if label, or a used
`CODE_LABEL` immediately before it) costs a branch, i.e. bytes.

### The union CONSTRUCTOR clobber: emitted, then deleted — now with the insn number

`union LLAlias b20u = { *(long long *)(env + 0x20) };` **does** emit
`(insn 367 365 369 (clobber (reg/v:DI 299)))` — visible in the `-dj` dump
(`s15/u1dump/U1.c.jump:711`). It is **gone by sched1** (`-dS` dump has no
clobber of 299; insn 369 still issues first at clock 16), because reg 299
is dead at that point and flow's `insn_dead_p` deletes it before
`REG_N_SETS` is counted. **Next lever for this axis: make the clobber land
where the pseudo is LIVE** — `store_constructor` emits the clobber
immediately before the initialising stores, so a union re-initialised
while its old value is still live is the shape to find (C89 blocks the
obvious spellings; a loop body or a nested-scope union whose value feeds
the else-if are the untried ones).

### Measured neutral this session (do not re-run verbatim; the axes stay open)

`union LLAlias` constructor for b20 (U1); `b20b = b20` copy + else-if on
`b20b` (C1); load-into-`b20b`-then-copy-to-`b20` (V1) and the same with
the copy after the store (V2); re-read `env+0x20` into `b20` in the
else-if (R1); `unsigned long long b20` (T2); dead-first-set `b20 = 0 / 1 /
ll18` before the load (S1/S2/S4); union-member and union-constructor copy
partners for the else-if (W1/W2); `arg4 = (char*)arg4 + 0` after the block
move, the `me0` round-trip, `sub = (char*)arg4`, `sub = env; env = sub`
(g1-g4, all on the P1 harness — 97/114/127 unmoved).
`TI128`-union `b20` (SUBREG dest, which *would* make `birthing_insn_p`
return 0 on the outer `if`) **explodes**: sites 496 — a register pair is
forced. Re-measured: P1 at `bit5pos` 0/1/2 all give sites 4
`[97,114,127,144]` (order ROM-exact); `bit5pos=3` gives sites 6.
`ll18` merged with 602 / 618 / 653 with and without P1: best sites 3
(acc→v1, temp→v0 — the census is cleaned but the register census is wrong).
`sub` name-web merges (making it `REG_BLOCK_GLOBAL` so local-alloc skips
it): +569 ⇒ sites 4 `[97,114,134,135]`, +612 ⇒ 10, +416 or all ⇒ 121+.
Global allocation does **not** give `sub` `$2`.

### State of the two zero-byte requirements after this session

1. **Flip.** Three vehicles now known. #1 P1 (`b20 <<= 0x1C`) and #2 the
   890-merge each cost 1 site and are register-refuted. #3 (365 births) is
   register-CLEAN but needs a live-out for the raw `env+0x18` value, which
   the ROM audit above says does not exist. ⇒ the remaining target is a
   **zero-byte second SET or CLOBBER of `b20`'s pseudo**, per the P-b
   conclusion. The clobber path is the most concrete lead (see above).
2. **Census.** Still `n365 >= n289+2`, but no longer only solvable by a gap
   insn: the **suggestion pass** and the **`QTY_CMP_PRI` ordering** (one
   extra `sub` reference, or one fewer ll18 reference) are two untested,
   fully source-derived alternatives. A `-dl`/`-dg` read of the actual qty
   order and ref counts on the P1 build would settle which is reachable —
   that is the cheapest high-information next measurement.

### Tools added this session
`s15/drive.py` (variant runner over the current base; ~1 s per oracle read),
`s15/gap.py` (gap-insn harness layered on session 14's `mk.build`),
`s15/u1dump/` (`-dg -dl -dS -dj` dumps of the union-constructor variant —
the dump that shows insn 367's clobber and its disappearance).
No seeds overwritten; no new seed earned.

### Session-15 addendum — the `QTY_CMP_PRI` ordering route is REFUTED; only two census routes survive

Worked the arithmetic through: with `n365 = n289+1` the two fake windows
`sub = [2*n283-2, 2*n289+2)` and `ll18 = [2*n365-2, …) = [2*n289, …)`
**overlap by two index units regardless of which qty is allocated first**.
Whoever runs first takes `$2` and the other is pushed off it — and ROM has
BOTH in `$2` (`lw v0,348(v1)` at exp 114 and `ld v0,24(s4)` at exp 131).
So changing the allocation order (extra `sub` reference / fewer ll18
references) cannot help; it only decides *which* of the two loses `$2`.
Scratch that route.

That leaves exactly two ways to satisfy the census with a flipped
schedule:

1. **A real gap insn** so `n365 >= n289+2` (zero bytes; must have an
   anti/output dep on 289 — i.e. write `arg4`/`sub`/289's source memory —
   and must not be a `sub`-reading insn in the last slot before 365).
2. **A `$2` hard-register suggestion on EITHER qty**, which routes it
   through `block_alloc`'s first pass with its REAL window: ll18 real
   `[2*n365, …) = [2*n289+2, …)` clears `sub`'s fake window, and `sub`'s
   real `[2*n283, 2*n289)` clears ll18's fake window. Either direction
   works. The suggestion must be `$2` specifically (`just_try_suggested`
   restricts `find_free_reg` to the suggested set), which means an insn
   of the form `(set P (reg $2))` / `(set (reg $2) P)` — a call-result
   copy or a returned value. Neither `sub` nor `ll18` is one today; the
   open question is whether a dev data model exists in which one of them
   is.

Also note the byte-free-gap search space is now fully characterised on the
release-time side (session 14) **and** on the deletion side: the insn only
has to exist at sched1 and be gone by sched2, so a pseudo-to-pseudo copy
coalesced by `combine_regs` into a noop move is the canonical candidate —
but every such copy measured so far is folded by cse (whose follow-jump
condition is pinned above) or by expand.

## conv-heavy2 session 16 (2026-07-28): func_001FCA20 — **the zero-byte GAP INSN is FOUND** (a `(clobber (mem))` from an aggregate constructor). sites 2 → **sites 1 / rc 2**; the census requirement R2 is permanently solved and the residual collapses to ONE precisely-stated aliasing property

Committed TU is left at the canonical crutch-free seed
(`act-env_x40scalars_s2_rc2.c`, **sites 2 / rc 2**) because the sites-1
build still carries two placeholder spellings (below). Two new seeds are
saved. **This is the session that cracked the five-session census wall.**

### THE FIND — a lone `(clobber (mem …))` is never deleted by flow, and it schedules into the gap

`store_constructor` (gcc-2.95 `expr.c:4134`) emits, for a **UNION**-typed
CONSTRUCTOR, `emit_insn (gen_rtx_CLOBBER (VOIDmode, target))`
**unconditionally**, before any element stores — and with an *empty*
initializer `= {}` the element loop runs zero times, so the clobber is the
only insn produced.

`insn_dead_p` (`flow.c`) then keeps it:

```c
  /* A CLOBBER of a pseudo-register that is dead serves no purpose. ... */
  else if (code == CLOBBER && GET_CODE (XEXP (x, 0)) == REG
           && REGNO (XEXP (x, 0)) >= FIRST_PSEUDO_REGISTER
           && ! REGNO_REG_SET_P (needed, REGNO (XEXP (x, 0))))
    return 1;
  /* We do not check other CLOBBER or USE here.  An insn consisting of just
     a CLOBBER or just a USE should not be deleted.  */
  return 0;
```

**That asymmetry is the whole trick**: a CLOBBER of a dead *pseudo* is
deleted (exactly what killed session 15's `U1` union, whose 8-byte union
went to a REG), but a lone CLOBBER of a **MEM** is *never* deleted.

At sched1 it is a memory WRITE, so `sched_analyze_1` gives it an
`output_dependence` on insn 289 (the `EnvCopy32` block move) → `ADJUST_COST`
anti/output → **cost 1 → released at clock 15**, which is precisely the
empty slot between 289 (clock 14) and the loads (clock 16/17). It carries
`code -1`, `unit none` and emits **zero bytes** (`final_scan_insn` skips
CLOBBER).

Measured (`-dS` dump of the P1+clobber build, block 11):

```
;;  Ready list (t = 14):  289   --> scheduling insn <<<289>>> on unit memory
;;  Ready list (t = 15):  294   --> scheduling insn <<<294>>> on unit none
;;  Ready list (t = 16):  372  369  --> 369 (ld 0x18) ; t=17 --> 372 (ld 0x20)
   289  294  0  4  9  1  ... none : 401 398 376 372 369
```

⇒ sched1 chain `… 283, 289, <clobber>, ld18, ld20 …`, i.e. **`n365 = n289+2`**
— session 13's census condition R2 satisfied. `97 / 114 / 127` never appear.

### THE SPELLING CONSTRAINT: the aggregate must be ZERO-SIZED

The frame has **no slack** (736 bytes, exp0 `addiu sp,sp,-736`); any added
addressable local grows it:

| gap form | sites (with the P1 flip) | note |
|---|---|---|
| `union { char c[0]; } uz = {};` | **1** `[144]` | BLKmode size 0 → MEM → clobber survives, frame unchanged |
| `union { char c[1]; } uz = {};` | 4 `[97,114,127,144]` | QImode → REG → clobber of a dead pseudo → deleted |
| `union { char c[3\|4\|8\|16]; } uz = {};` | 459-492 | frame 736 → 752, whole prologue shifts |

Member type is irrelevant (`char/long long/float/int/short [0]` all identical),
so the clobber's MEM behaves as **alias set 0** — it conflicts with *both*
`env+0x18` and `env+0x20`. That matters, see the residual below.

### RESULT — sites 2 → **sites 1 / rc 2**

`gap clobber` + the session-14 **P1** flip (`b20 <<= 0x1C`) + `bit5pos = 2`:
**sites 1 / rc 2**, residual = `exp 144` only
(ROM `dsll v0,a3,0x1c ; dsra32 v0,v0,0` vs built `dsll a3,a3,0x1c ; dsra32 v0,a3,0`
— the P1 vehicle writing into `b20`'s own register).
Seed: `tough_nuts/act-env_func_001FCA20/act-env_s16_gapclobber_P1_s1_rc2.c`.

**Every flip vehicle now costs exactly its own single site** (the census tax
is gone in all of them):

| flip vehicle | sites | residual |
|---|---|---|
| P1 `b20 <<= 0x1C` | **1** | `[144]` |
| `b20` shared with the line-890 read | **1** | `[988]` |
| `b20` shared with line 1290 | **1** | `[2026]` |
| `b20` shared with line 675 / 765 | 1 | `[554]` / `[669]` (rc 4) |
| `b20` shared with line 430 / 1300 | 2 / 1 | `[66,71]` / `[2054]` |

Every *merge* fails for one identical reason: `b20` becomes a
`REG_BLOCK_GLOBAL` allocno pinned to **a3 function-wide**, while ROM's
partner site is **v0** (`ld v0,32(s4)` / `ld v0,24(s4)`). Session 14's a3
audit is re-confirmed from the other direction.

### A SECOND, COMPLETELY FLIP-FREE CONFIGURATION (no second set of `b20` at all)

A **second** zero-size union clobber placed *between the two load
statements* makes the `env+0x20` load a dependent of it, so it simply cannot
be scheduled before the `env+0x18` load — the loads flip with **no** touch to
`b20`. Seed: `act-env_s16_gapclobber_dbl_noflip_s2.c`, **sites 2**, residual
`[136,137]`.

It fails only on the follow-on tie: the second clobber costs **two** clocks
(ld18@16, clobber@17, ld20@18) where the flip needs **one**, so the
`dsll/dsra32` chain runs one clock behind the `and` chain and the sched2
`{and3, dsra32}` LUID tie inverts (`bit5pos` 0/1/2/3 all measured — no effect
here; the bit5pos lever only works when ld20 is at ld18+1).

A full sweep of clobber positions (before ld18 / between the loads / after
both loads / after each of the three masks / after the store / before the
`if`), single and paired, at `bit5pos` 2 and 3: **only** the between-loads
position changes anything. Everything else is byte-neutral.

### THE RESIDUAL, SHARPENED TO ONE PROPERTY

**A gap insn that conflicts with `[env+0x20]` but NOT with `[env+0x18]` solves
the whole function in one stroke.** Derivation:

1. it is a memory write ⇒ output-dep on 289 ⇒ cost 1 ⇒ **clock 15** ⇒ census ✓
2. `ld18`'s dep count then resolves at **289** (t=14) ⇒
   `max_priority = prio(289) = 9`; `ld18` does not birth ⇒ stays at **7**
3. `ld20`'s resolves at the **clobber** (t=15) ⇒
   `max_priority = prio(clobber) = 1 + prio(ld20) = 7` ⇒ the
   `birthing_insn_p` bump lands exactly **on 7** ⇒ **TIE**
4. `rank_for_schedule`: priority 7=7 → `INSN_REG_WEIGHT` 1=1 → class
   (w.r.t. the clobber) 3=3 → `depend_count` **3 vs 2** ⇒ **`ld18` wins** ✓
   — the flip, with no second set of `b20` and no partner-site cost.

**And the general law that closes every symmetric alternative:** whenever
289 (or a 289-dependent that both loads depend on) is the resolver of BOTH
loads, `max_priority >= prio(ld18) + 1` **always** — `prio(289) = 2+prio(ld18)`
and `prio(gap) = 1+prio(ld18)` — so the bump always beats `ld18` by at least
one. A *symmetric* gap insn can never make the flip free. **The asymmetry is
the entire remaining requirement.**

Two ways to get it, both untried:
- an aggregate whose `store_constructor` target MEM is `env+0x20` itself
  (C89 puts CONSTRUCTORs only in declarations, so this needs a decl whose
  `DECL_RTL` is that MEM — or another RTL source of `(clobber (mem X))`);
- a nonzero, *distinct* alias set on the clobber's MEM vs the `long long`
  reads. Measured: the zero-size union's MEM behaves as alias set 0, so the
  member type does not discriminate. `DIFFERENT_ALIAS_SETS_P` needs BOTH
  sides nonzero and different — so the lever is on the **load** side
  (retype one of the two reads) combined with a nonzero-set clobber.

### Also nailed down this session (source-read, re-usable)

- **`birthing_insn_p` has a THIRD kill switch**: a **SUBREG** `SET_DEST`
  makes the leading `if` fail and the function `return 0` outright — no
  `REG_N_SETS` test at all. Tried via `union { TI128 t; long long ll; }`
  (a TImode/DImode union to get `(set (subreg:DI (reg:TI …)) …)`):
  **497 sites** — the 16-byte union is forced to memory and the frame grows.
  Session 13's verdict re-confirmed; the switch itself stays open for any
  spelling that keeps the pseudo in registers.
- **`adjust_priority`'s `n_deaths` switch is DEAD CODE here**:
  `find_pre_sched_live` discards every REG_DEAD note before scheduling
  (haifa-sched.c:5111), so `n_deaths` is always 0 and the
  `INSN_PRIORITY >>= 1/2/3` halving levers are unreachable. Do not plan
  around them.
- `reg_is_set` (local-alloc.c) gives a CLOBBER birth `2*n - 1` (odd), but
  `fake_birth = birth - 2 + birth%2` yields the same `2n-2` as a plain set —
  a clobber birth does **not** shift the fake window.
- `block_alloc`'s fake-window fallback (`find_free_reg` with the real
  window) is unreachable in practice: the fake pass only returns −1 when
  *no* register at all is free, so "sub allocated first" simply pushes the
  `ll18` accumulator off `$2` (addendum-15 re-derived independently, and the
  full four-qty allocation order — acc 17142 → bit5-chain 12000 → sub 10000
  → r263 2500 — was hand-simulated and reproduces ROM's census exactly on the
  base and the observed swap on every flip).

### Measured neutral / rejected this session (do not re-run verbatim)

`unsigned long long b20` + P1; `((b20 <<= 0x1C) >> 0x20)` re-parenthesised;
re-reading `env+0x20` inside the `else if` (cse folds); computing `bit4` in
block 11 (sites 2 / rc 17 — the three insns move out of block 12);
`struct{}` / `struct{char c[0];}` / `float az[0]` / `struct{int d;}` gap
forms; SSA-spelled masks + gap (sites 2) and the same with an artificial
`env+0x470` live-out (sites 102 — the extra store shifts everything);
moving a 16-byte local group's declaration (`y1A0`/`w180`/`dv19`/`w170`/
`w150`/`w140`) into the gap block (their later uses fall out of scope, and
the slot would move to the frame end regardless).

### Tools added this session
`s16/drive.py` (variant runner with a `gap=` insertion point right after the
`EnvCopy32` move, `bit5pos`, `flip='P1'`), `s16/sweep.py` (clobber-position
sweep), `s16/dump.sh` (`-dS -dj -dl -fsched-verbose-5` dumps with the exact
project CFLAGS), `s16/g1dump/`, `s16/dbldump/`.

### Seeds saved
- `tough_nuts/act-env_func_001FCA20/act-env_s16_gapclobber_P1_s1_rc2.c`
  — **sites 1 / rc 2**, best-ever. Two placeholder spellings:
  `union { char c[0]; } uz = {};` (the gap clobber — the *mechanism* is
  ROM-proven, the spelling is anachronistic and wants a real dev aggregate)
  and the P1 flip (`b20 <<= 0x1C`, which costs exp 144).
- `tough_nuts/act-env_func_001FCA20/act-env_s16_gapclobber_dbl_noflip_s2.c`
  — sites 2, **flip-free** (no second set of `b20`), residual `[136,137]`.

### Session-17 attack order
1. **The asymmetric gap insn** (the derivation above) — one insn solves both
   halves. Hunt an RTL source of `(clobber (mem …))` whose MEM is
   `env+0x20`, or a nonzero-alias-set clobber paired with a retyped
   `env+0x18` read.
2. **A dev-plausible spelling of the zero-size aggregate.** The `found = …`
   dead-read block sits exactly at the gap point and is itself a
   reconstruction placeholder — the dev's real code there is very plausibly
   a nested-scope aggregate declaration *with an initializer*, whose
   `store_constructor` clobber IS the gap insn. Find the aggregate that
   costs no frame (a group already declared last, or one whose stores are
   themselves ROM insns we currently spell differently).
3. Only then the flip: the `[144]` cost of P1 is 2 instructions; a second
   set of `b20` that does not become the `dsll` dest would land the match.

## conv-heavy2 session 17 (2026-07-29): func_001FCA20 — **MATCHED**. sites 2 → **sites 0 / rc 0**, `ninja` byte-identical (`build/ico.rom` sha1 `fbf50c75cd5911273511c4f9af90503ff8423582`)

The free flip vehicle sessions 11–16 were hunting is a **volatile PAIR**:
`alias.c:read_dependence()` is the ONLY dependence test in the scheduler that
can order two READS, and it fires **iff both MEMs are volatile**.

### The residual, restated exactly (measured, not inferred)

`-fsched-verbose-8` dep table, block 11, sched1 (`d8_base/v_base.c.sched`):

```
;;      insn  code  bb  dep  prio  cost  units
;;      289   294    0   2     9    2    memory : 397 394 368 365     <- EnvCopy32 block move
;;      365   244    0   2     7    2    memory : 397 394 373         <- ld  env+0x18
;;      368   244    0   2     6    2    memory : 397 386             <- ld  env+0x20
;;      373   153    0   3     5    1    alu    : 397 378             <- and1
;;      378   153    0   3     4    1    alu    : 397 383             <- and2
;;      383   153    0   3     3    1    alu    : 397 394             <- and3
;;      386   315    0   2     4    1    alu    : 397 389             <- dsll (bit5)
;;      389   180    0   2     3    1    alu    : 397 391             <- dsra32
```

At `t=14` insn 289 issues; **both** loads' `INSN_DEP_COUNT` hits 0 there, so
`schedule_insn` sets `max_priority = MAX(INSN_PRIORITY(ready[0]), prio(289)) = 9`
and `adjust_priority` bumps the *birthing* 368 from 6 to 9 — 368 beats 365 (7)
and sched1 emits `ld20, ld18, dsll, and1, dsra32, and2, andi, and3`. The two
sched2 dual-issue ALU ties then break on `INSN_LUID` (= the sched1 order):
`t=20 {and2,dsll}` and `t=21 {and3,dsra32}`. ROM needs `and2` first at t=20 —
which needs `LUID(and2) < LUID(dsll)` — which needs `ld18` first at sched1.

`prio(289) = insn_cost(289→365) + prio(365) = 2 + prio(365)`, so **no** insn
that resolves 365 can ever have priority ≤ prio(365): raising 365 raises 289
in lockstep. That is session 12's law, re-derived from the dump.

### THE FIX — a read-after-read anti-dependence

```c
long long ll18 = *(volatile long long *)(env + 0x18);
long long b20  = *(volatile long long *)(env + 0x20);
```

`sched_analyze_2`'s MEM case walks `pending_read_insns` and calls
`read_dependence (pending_mem, x)`, whose entire body is

```c
  return MEM_VOLATILE_P (x) && MEM_VOLATILE_P (mem);
```

With both reads volatile it returns 1 and `add_dependence (ld20, ld18,
REG_DEP_ANTI)` fires. Consequences, all of them exactly what was needed:

* **ld18 is scheduled first by DEPENDENCE** — the priority contest is bypassed
  entirely, so `birthing_insn_p` never has to be defeated.
* MIPS `ADJUST_COST` zeroes anti/output cost, so `INSN_TICK(ld20)` is unchanged
  (16); but a newly-readied insn cannot issue in the cycle that readied it
  (`for (i = n_ready-1; i >= 0 && can_issue_more; i--)` never revisits the
  slots `schedule_insn` appends), so ld20 lands at **t+1 exactly** — the
  ld18@16 / ld20@17 timing every other vehicle needed.
* **Zero instruction cost.** `volatile` changes no bytes for a plain `ld`.

Control rows (all with the session-16 gap clobber, bit5pos=2):

| vol(env+0x18) | vol(env+0x20) | gap | result |
|---|---|---|---|
| 1 | 1 | yes | **MATCH sites 0 / rc 0** |
| 1 | 1 | no  | sites 3 `[97,114,127]` (pure census class) |
| 0 | 1 | yes | sites 2 `[134,135]` (no read-read edge) |
| 1 | 0 | yes | sites 2 `[134,135]` (no read-read edge) |

Only-one-volatile is a no-op — the tell that this is `read_dependence` and not
some side effect of `volatile` on cse/regalloc.

### The gap clobber is still required, and still does only what session 16 said

Session 16's zero-size union CONSTRUCTOR clobber supplies session 13's census
insn (`n365 = n289+2`). Without it the volatile pair alone reads sites 3 with
exactly `[97,114,127]` — the `sub`/`ll18` `$2`↔`$1` swap. Final spelling:

```c
{ union { char c[0]; } uz = {0}; }
```

`= {0}` is accepted silently by ee-gcc 2.9 and is equivalent to `= {}` here
(the element loop still runs zero times for a zero-size union), so the GNU
empty-brace extension is not needed.

### `bit5pos = 2` is load-bearing

With ld18@16 / ld20@17: and1@18, `{and2,dsll}`@19, `{and3,dsra32}`@20 — both
pairs are exact `INSN_PRIORITY` ties (4=4, 3=3) that fall through REG_WEIGHT,
the last-scheduled class and `depend_count` to `INSN_LUID`, i.e. to source
order. Putting the `bit5` statement between the 2nd and 3rd mask gives
`and1 < and2 < dsll < dsra32 < andi < and3`, which is ROM. `bit5pos=3` reads
sites 2 `[136,137]`.

### The ROM also PINS the write-back as non-volatile

Making the store volatile too (`*f18 = ll18` through the volatile pointer)
scores sites 3: gcc's dbr pass refuses to put a volatile insn in a branch
delay slot, so it emits `sd v0,24(s4)` *before* `beq` and fills the delay from
the target block. ROM has the `sd` in the delay slot ⇒ **the reads are
volatile, the write is not.** That asymmetry is ROM-derived, not a choice.

### Session 16's "asymmetric gap" property is provably unreachable — closed

The residual session 16 stated (a gap insn conflicting with `env+0x20` but not
`env+0x18`) cannot exist in this compiler, for four independent reasons, all
read out of the staged 2.95 sources:

1. `c_get_alias_set` returns **0** for every `RECORD_TYPE`/`UNION_TYPE`, and
   `store_constructor`'s unconditional CLOBBER only exists for unions ⇒ the
   clobber MEM is always alias set 0 ⇒ `DIFFERENT_ALIAS_SETS_P` (which needs
   *both* sets nonzero) can never fire. Arrays would inherit the element type's
   set, but the ARRAY branch (`expr.c:4338`) forces `need_to_clear` for a
   zero-size domain (`4*0 >= 3*0`) and emits `clear_storage`, no clobber.
2. `true_dependence` returns 1 unconditionally when either mode is BLKmode,
   which a zero-size union always is.
3. `base_alias_check` returns 1 as soon as *either* base is unknown, and `env`
   is loaded from memory (`find_base_value` returns 0 for a MEM) — so the
   frame-based clobber conflicts with both loads. Making `env`'s base known
   would kill *both* edges (the stack-reference rule), not one.
4. `fixed_scalar_and_varying_struct_p` would need the clobber MEM to be
   `MEM_SCALAR_P`, but `expand_decl` does `MEM_SET_IN_STRUCT_P (DECL_RTL,
   AGGREGATE_TYPE_P (type))`, so a union decl is always IN_STRUCT.

Also refuted this session: `RTX_UNCHANGING_P` is unreachable from C here
(`expr.c:6355` ANDs `TREE_READONLY` with `TREE_STATIC`; `stmt.c:3649`'s const-
local path is inside `#if 0`), so the `write_dependence_p` early-out is dead.

The answer was never an asymmetric *write*. It was the read-after-read edge.

### Measured and rejected this session

`union { long long ll; TI128 t; }` for b20 (to hit `birthing_insn_p`'s SUBREG
kill switch): **496 sites** — the TImode union is forced to memory.
Forcing the `env+0x18` load to birth (SSA-spelled masks + a live-out use of
the raw value in block 12): the flip DOES happen at sched1 (verified in the
`-dS` dump: `t=16 --> 369`), but the extra live 64-bit value across block 12
costs **101 sites** — so route (B) is mechanically real and economically dead.
`bit4` computed in block 11 (kills b20's live-out): sites 2 / rc 17 — the
three bit4 insns move out of block 13. Re-reading `env+0x20` in the `else if`:
byte-neutral (cse folds). Swapping the two load statements: byte-neutral.
`restrict` on both pointers: sites 53 alone, sites 2 with the gap.
`ef[0]`/`ef[1]` (ARRAY_REF form of the volatile pair): **132 sites** — the
ARRAY_REF MEM flags differ; the pointer-deref form is required.

### Dev-form assessment (honest)

* The **volatile pair** is ROM-proven in the strict sense: ROM's instruction
  order requires a read-after-read edge, and `read_dependence` is the only
  producer of one. The `env` flag words being volatile (touched by the
  collision/IK side) with a plain write-back is a coherent, if slightly
  unusual, data model, and the ROM pins both halves of it.
* The **zero-size union** is the one construct that stays mechanism-derived
  rather than recovered: the bytes constrain it only up to "some union with a
  zero-size layout and an initializer", because every such declaration
  compiles to the identical single `(clobber (mem))`. It is not a pin/barrier
  and emits nothing, but it is not recovered dev C either. Flagged, not hidden.

### Tools
`s17/d.py` (variant driver), `s17/sw.py` (clobber-slot + SSA sweeper),
`s17/dump8.sh` (`-dS -fsched-verbose-8` — the dep table with priorities is
what cracked this), `s17/d8_base`, `s17/d8_p1`, `s17/d8_diagB`,
`s17_show.py` / `s17_win.py` / `s17_exp.py` (expected-vs-built windows).

### Seed
`tough_nuts/act-env_func_001FCA20/act-env_s17_MATCH_volatile_pair_gapclobber.c`
