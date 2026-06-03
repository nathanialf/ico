# func_0025CC70 — parked

VRAM: 0x0025CC70 (file_off 0x15CC70)
Asm source: asm/aug6/nonmatchings/common/src/PObj/func_0025CC70.s

## Attempt at 2026-06-03

**Reason parked:** rc2 fabsf bit-twiddle (mfc1+lui 0x7fff+ori+and+mtc1 $f0). Pure-C plateau at 30/30: gcc emits 'mfc1 a0; move v1,a0' where ROM has 'mfc1 v1' directly — a coalescing miss between the mfc1-result pseudo and the and-chain pseudo. INVARIANT to source shape: tried 30 distinct forms incl __builtin_fabsf (itself rc2), static-inline helper, every union member/order, two-union, pointer-union, struct-cast, address-of-param, CFG wrappers (do-while/if/comma), mask lowerings (~0x80000000, >>1, named-var, static-const), 64-bit width, writeback. Cookbook 7.3 fingerprint — historically FABSF_BIT_TWIDDLE (retired). No FP reg pin per fp-licm playbook. Left for offline auto_permute.

**TU:** `common/src/PObj.c`

**Seed:** `tough_nuts/func_0025CC70/func_0025CC70.c`

Disassembly:

```
.align 3
nonmatching func_0025CC70, 0x1C

glabel func_0025CC70
    /* 15CC70 0025CC70 00600344 */  mfc1       $3, $f12
    /* 15CC74 0025CC74 FF7F023C */  lui        $2, (0x7FFFFFFF >> 16)
    /* 15CC78 0025CC78 FFFF4234 */  ori        $2, $2, (0x7FFFFFFF & 0xFFFF)
    /* 15CC7C 0025CC7C 24186200 */  and        $3, $3, $2
    /* 15CC80 0025CC80 00008344 */  mtc1       $3, $f0
    /* 15CC84 0025CC84 0800E003 */  jr         $31
    /* 15CC88 0025CC88 00000000 */   nop
endlabel func_0025CC70
    /* 15CC8C 0025CC8C 00000000 */  nop
```

## In-loop permuter shot (full park procedure) — FAILED to run
Fired the Step-4 10-min permuter shot at park (CFLAGS = exact quick_diff flags).
It could not even compile the base: `Error: unrecognized opcode 'endlabel
func_002484A4'` — the permuter's standalone assembler doesn't define the repo's
`endlabel` asm-macro present in the extracted PObj TU context. Exited "no
permutation matched (permuter exit=0)". This is a permuter-infra limitation for
this coalesced TU, NOT a matching result. offline auto_permute will likely hit
the same import error. Hand 30-stall stands (mfc1 reg-pick invariant; even
__builtin_fabsf is rc2). §7.3 fabsf — needs the retired FABSF_BIT_TWIDDLE idiom.

## Resume 2026-06-03 (aug6 /loop)
Re-applied seed; baseline rc2 confirmed. Three fresh distinct attempts:
ptr-cast-on-param `*(int*)&a0` (rc3, spills f12→stack, loses mfc1),
`static inline` helper via RTL inliner (rc2), `~0x80000000` complement
mask (rc2, folds to same lui 0x7FFF/ori). Structural read: diff is a gcc-2.9
cross-class-move (FP→GP) coalescing miss — `mfc1` dest pseudo won't coalesce
into the and-result reg, so it parks in a0 + adds `daddu v1,a0,zero`. MIPS
`and` is 3-operand so even killing the copy only reaches rc1; the `mfc1 a0`
vs `mfc1 v1` choice is the irreducible part. Resume permuter shot (Step 0.3)
NOT runnable: permuter standalone-as lacks the `endlabel` macro for this TU
(documented above). Left parked for offline auto_permute; no new clean-C lever.

## Resume 2026-06-03 (cont.) — RIGOROUS codegen characterization
Reproduced exact build codegen fast via ee-gcc 2.9-991111 + real CFLAGS
(`-O2 -mips3 -fno-builtin -fdata-sections -G8`). Findings (all measured):
- Clean fabs-via-union at **-mips3 -O2** ALWAYS emits:
  `mfc1 $4,$f12 ; li $2 ; ori $2 ; move $3,$4 ; and $3,$3,$2 ; mtc1 $3` (=rc2).
- **-mips2/-mips1** emit `li $2 ; mfc1 $4 ; ori ; and $4,$4,$2 ; mtc1 $4`
  (no move, in-place) — but li-FIRST and reg $4. ROM is mfc1-FIRST (=-mips3
  order) with reg $3 → ROM is **-mips3 with the mfc1 result COALESCED into $3**.
  So it is NOT an arch-flag swap (-mips2 mismatches order+reg).
- Only a union containing a **64-bit member** (long long/double/ull/aligned(8))
  makes mfc1 land in $3 — but inseparably drags in dsll/dsra sign-extension
  garbage (5+ extra insns). 8-byte via char[8]/int[2] spills (lw). No clean $3.
- Swept ~30 distinct shapes (named temp, register, two-union, comma, do-while,
  static-inline, member orders, ptr-member, complit, init-cast, mask literals,
  if(1), volatile) — every clean one is byte-identical `mfc1 $4 + move $3,$4`.
CONCLUSION: residual is a -mips3 cross-class-move COALESCE the compiler won't do
for any clean-C source. The exact lever needed = coalesce/split so the mfc1
result is born in $3. This is precisely a permuter live-range-split target
(original notes already said so). Permuter now RUNS once given a MINIMAL
single-func seed (whole-TU seed pulls sibling asm → glabel/endlabel as-errors).
seed: tough_nuts/func_0025CC70/seed_min.c. 5-min resume shot found no real
improvement (its score-100 &u-alias cand was rc2, anti-correlated).

## Resume 2026-06-03 (cont.2) — flag sweep + permuter is FALSE-scoring
- Flag sweep at -O2: -mips3 (move,$4) ; -mips3 -mgp32 (NO move, in-place, but $4) ;
  -mips2/-mips1 (no move, $4, li-first) ; -mfp32/-msingle-float/-mlong32 (=mips3).
  EVERY combo lands the mfc1 result in **$4**, never ROM's **$3**. Project flags
  have NO -mgp32 (so the move is present in the real build). NO flag reproduces
  ROM's `mfc1 $3 ; and $3,$3,$2 ; mtc1 $3`.
- PERMUTER IS UNUSABLE here: a 10-min minimal-seed run hit "score 0" (output-0-1)
  but that source compiles to `mov.s $f0,$f12` (returns a0, semantically WRONG)
  and measures **rc6** via match_loop — the permuter's target.o/CFLAGS are
  misconfigured for this func, so its scores are false. Do NOT trust its score.
- NET: with this compiler the mfc1-result is INVARIANTLY $4 for a float-param
  fabs; ROM's coalesced-$3 needs a lever I could not produce in clean C at the
  project flags. Candidate explanations for the user: (a) this TU compiled with a
  flag delta the project retired; (b) a gcc coalesce trick; (c) known outlier.

## Resume 2026-06-03 (cont.3) — PERMUTER TARGET FIXED
Root-caused the false score-0: generated compile.sh copied EVERY candidate to a
single shared `<dir(OUTPUT)>/PObj.c`; with `-j 4` all workers share the temp dir
→ they overwrote each other's source before compile → the scored .o was another
worker's candidate. A `mov.s` ("return a0") source thus recorded score 0 vs the
correct 7-insn target. FIX (committed, tools/permute_run.sh): per-OUTPUT
`.srcdir/PObj.c` (unique, basename preserved for config lookups). Validated:
24 concurrent compiles no cross-contamination; real run errors 1688→28, NO more
false-0.
With CORRECT scoring the permuter's best valid score is **105 (=rc2)**; sub-105
(100) candidates are all semantically INVALID (read uninit u.i / dead code) and
unusable. So the fixed permuter CONFIRMS the hand finding: no clean-C source at
the project's -mips3 flags byte-matches ROM's `mfc1 $3` (coalesced in-place and).
The remaining lever is the mfc1-result→$3 coalesce, which is unreachable in clean
-mips3 C and not produced by any arch/ABI/opt flag tried → appears to need a
per-TU flag delta or a compiler-version nuance (decision deferred to user;
per-file cflags are retired). Offline auto_permute will now score correctly.

## Resume 2026-06-03 (cont.4) — compiler-version hypothesis TESTED & ruled out
Both available ee-gcc builds tested with the real project flags:
- ee-gcc 2.9-991111 (project default): `mfc1 $4 ; move $3,$4 ; and $3,$3,$2 ; mtc1 $3` (rc2)
- ee-gcc 2.96: STACK SPILL `s.s $f12,0(sp) ; lw $3,0(sp) ; and $3,$3,$2 ; mtc1 $3` + frame (worse)
NEITHER produces ROM's `mfc1 $3 ; and $3,$3,$2 ; mtc1 $3` (in-place coalesce, no frame).
EVERY dimension now exhausted & TESTED (not reasoned): 40+ source shapes, all
arch/ABI/opt flags, both compilers, the (now-fixed) permuter. ROM's exact fabs
bytes are not reproducible with any toolchain config present in the repo →
genuine outlier; the matching toolchain/flag for this object is not in the tree.
TERMINAL for current toolchain. Offline auto_permute will keep it (now scoring
correctly) but cannot reach it in clean C. Needs a user-level toolchain decision.
