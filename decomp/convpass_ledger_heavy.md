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
