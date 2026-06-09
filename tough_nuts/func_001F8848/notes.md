# func_001F8848 — parked

VRAM: 0x001F8848 (file_off 0x0F8848)
Asm source: asm/aug6/nonmatchings/seki/src/DmaPacket/func_001F8848.s

## Attempt at 2026-06-05

**Reason parked:** rc4 index-scale vs coloring coupling: ROM reads D[idx+1] as idx*4 + load-disp 4 (struct-member offset); simple int[] array D[idx+1] folds to (idx+1)*4 (correct a0/a1 coloring, best=4); struct slots[idx] fixes the scale but flips a0<->v1 %hi/&base coloring (rc10). 30-stall: ~15 distinct shapes (array, ptr-temp, struct x3 orderings, byte-arith, hybrid-cast, union, void-ptr-buf) — index-fix and coloring appear coupled. Permuter-class.

**TU:** `seki/src/DmaPacket.c`

**Seed:** `tough_nuts/func_001F8848/func_001F8848.c`

Disassembly:

```
.align 3
nonmatching func_001F8848, 0x34

glabel func_001F8848
    /* F8848 001F8848 4C00043C */  lui        $4, %hi(D_004C3850)
    /* F884C 001F884C 5038838C */  lw         $3, %lo(D_004C3850)($4)
    /* F8850 001F8850 50388524 */  addiu      $5, $4, %lo(D_004C3850)
    /* F8854 001F8854 01006338 */  xori       $3, $3, 0x1
    /* F8858 001F8858 80100300 */  sll        $2, $3, 2
    /* F885C 001F885C 503883AC */  sw         $3, %lo(D_004C3850)($4)
    /* F8860 001F8860 2110A200 */  addu       $2, $5, $2
    /* F8864 001F8864 0400438C */  lw         $3, 0x4($2)
    /* F8868 001F8868 1C00A0AC */  sw         $0, 0x1C($5)
    /* F886C 001F886C 1000A3AC */  sw         $3, 0x10($5)
    /* F8870 001F8870 1400A0AC */  sw         $0, 0x14($5)
    /* F8874 001F8874 0800E003 */  jr         $31
    /* F8878 001F8878 1800A0AC */   sw        $0, 0x18($5)
endlabel func_001F8848
    /* F887C 001F887C 00000000 */  nop
```

## Convergence log (resolution b, 3 permuter passes this session)

best: rc4 (hand) -> rc3 (permuter pass1, short-index) -> rc2 (hand, narrow-array)
-> rc1 (permuter pass2, zero-reuse store structure). Pass3 (seeded from rc1)
found NOTHING below rc1 -> permuter-exhausted.

**rc1 floor residual:** a single redundant `andi v0,v0,0xfc` (= (idx*4)&252)
inserted AFTER a correct `sll v0,v1,0x2`. ROM has the clean sll2 with no mask.
Present in EVERY rc1 form (int/uint/long/char/short index; ptr/array/struct slot;
all store orders). §5.11-class redundant canonicalization.

**Key lever found (reusable):** the slot read `D[idx+1]` only stops folding to
(idx+1)*4 (and stops the a0/a1 %hi/&base coloring flip) when the four zero stores
are written as `idx = 0; D[5]=idx; D[6]=idx; D[7]=idx;` (reuse the idx register
set to 0) instead of literal `D[5]=0; ...`. That zero-reuse collapsed rc4->rc1.
Resume: re-attack the andi-mask with a §5.11 non-equivalent rewrite.

## Re-confirm 2026-06-08 (this pass)
Resumed; reset; ran ~28 fresh distinct shapes (idx-expr × read-form × zero-store ×
order). Array `D[idx+1]` form = rc4 best (the index/coloring coupling holds);
pointer/`*(D+idx+1)` forms = rc10-11 (fix the scale but flip %hi/&base coloring).
30-stall reached; fired permuter (150s, ~1000 iters), NO rc0. (b) re-confirmed.
Note: ee-gcc 2.9 is C89 — mid-block `int x=0;` is a compile error (rc=-1 false).
## Fire 6: re-attack; base-fold ptr forms rc11 (coloring flip), array form rc4 best hand, ~35 distinct; rc1 is permuter-only §5.11 andi floor; stall=31 permute, valid run no rc0. (b)

## Fire 7 re-attack (2026-06-08, second pass this day) — PRECISE COUPLING MODEL
Reset; ran ~30 fresh distinct shapes via match_loop (stall 30/30, best=4 on aug6).
Harvested ALL existing permuter outputs by true real_count: best is output-220-1
= rc4 (== hand best); output-195-1 = rc6; nothing < rc4. (b) re-confirmed.

NEW root-cause model (supersedes "index/coloring coupled, permuter-class"):
- The diff is a register-allocation tie on the %hi(D_004C3850) pseudo: expected
  puts %hi->a0 (addresses in a0/a1, data in v0/v1, loaded value REUSES idx's v1);
  every scale-correct form puts %hi->v1.
- WHY: in pointer/address-domain forms (`(D+idx)[1]`, struct `s->buf[idx]`,
  `*(D+idx+1)`, byte-ptr `(char*)D+idx*4+4`, addr-temp `p=D+idx;p[1]`) the
  store-back `D[0]=idx` is scheduled right after the xori, BEFORE the sll, so gcc
  reuses idx's register in-place for `scaled` (sll v0,v0) -> only 3 regs -> %hi=v1.
  Confirmed via tools/sched_diff.py: the store is in the initial stream before the
  sll, not moved by a later pass; no clean lever delays it past the sll.
- The ONLY form that lands %hi->a0 is the bare-array `D[idx+1]`, because the
  `idx+1` temp forces `scaled` into a SEPARATE reg from idx (4 regs) -> %hi=a0 —
  but that same `idx+1` mis-scales to (idx+1)*4 (addiu+sll, lw 0) instead of
  idx*4 + load-disp 4. So coloring (needs the extra idx pseudo) and scale (needs
  address-domain lowering) are mutually exclusive across every C spelling.
- Need: a scale-correct form whose store-back lands BETWEEN the sll and the load
  (idx dies there: scaled separate, loaded value reuses idx's reg, 4 regs, %hi=a0).
  No hand source places it there — the scheduler always hoists the store before
  the sll. Genuine permuter-class register/schedule tie. SEED = rc4 bare-array.

---

## Attempt at 2026-06-08

**Reason parked:** rc4 aug6 hand-best (bare-array form, correct %hi->a0 coloring, residual (idx+1)*4 scale); 30-stall + permuter harvest (all outputs) beat nothing<rc4. Register/schedule tie: scale-correct forms flip %hi->v1.

**TU:** `seki/src/DmaPacket.c`

**Seed:** `tough_nuts/func_001F8848/func_001F8848.1.c`

Disassembly:

```
.align 3
nonmatching func_001F8848, 0x34

glabel func_001F8848
    /* F8848 001F8848 4C00043C */  lui        $4, %hi(D_004C3850)
    /* F884C 001F884C 5038838C */  lw         $3, %lo(D_004C3850)($4)
    /* F8850 001F8850 50388524 */  addiu      $5, $4, %lo(D_004C3850)
    /* F8854 001F8854 01006338 */  xori       $3, $3, 0x1
    /* F8858 001F8858 80100300 */  sll        $2, $3, 2
    /* F885C 001F885C 503883AC */  sw         $3, %lo(D_004C3850)($4)
    /* F8860 001F8860 2110A200 */  addu       $2, $5, $2
    /* F8864 001F8864 0400438C */  lw         $3, 0x4($2)
    /* F8868 001F8868 1C00A0AC */  sw         $0, 0x1C($5)
    /* F886C 001F886C 1000A3AC */  sw         $3, 0x10($5)
    /* F8870 001F8870 1400A0AC */  sw         $0, 0x14($5)
    /* F8874 001F8874 0800E003 */  jr         $31
    /* F8878 001F8878 1800A0AC */   sw        $0, 0x18($5)
endlabel func_001F8848
    /* F887C 001F887C 00000000 */  nop
```

## Fire 7 RESULT: rc4 -> rc2 (permuter, adopted)
The bounded permuter shot (seeded from the rc4 array form) found output-105-1 at
TRUE real_count rc2 (its perm_score 105 is unrelated). Structural idea adopted:
SHORT-narrowed array index `(short)idx + 1` + base-alias `(p = D_004C3850)[...]`.
This is the FIRST form to get BOTH correct %hi->a0 coloring AND correct
scale/addu/disp (lw 4) — see seed header. Residual rc2 = the 2-insn sign-extend
`sll 0x10; sra 0xe` vs ROM's `sll 0x2`. Confirmed irreducible by hand: ~20
post-adopt distinct shapes (2D `int(*)[1]` views rc11, base-alias+int rc11,
ushort rc5, mask 0x7FFF/0xFFFF rc2, short-via-int-var rc2, p-first rc3). The
narrowing is what triggers the disp-fold; removing it loses the fold. New best
seed = rc2. Re-attack on resume: seed permuter from the rc2 short form (better
start than the old rc4) to hunt the sext->sll2 elimination.

## Fire 8 (2026-06-09): rc2 floor re-confirmed, 30 fresh combos
Matched-sibling idiom (func_001F87B0 `(D+idx)[1]`) + addr-temp-before-storeback,
base+1 association `(D+1)[idx]` (NEW: rc11), q-temp `q=D+1` (rc8 but %lo(D+4)
reloc-base ✗), byte-domain × zero-reuse combos (rc11), struct × zero-reuse ×
storeback-position (rc10-11), (long long)/(unsigned) index casts (fold away, rc4),
short × {alias, no-alias, lit0, p-stores, storeback-after, ptr-domain, +0-alias},
ushort/mask+alias+zr (all rc2). Coupling model holds exactly.
NEW CONTEXT (cf. tough_nuts/reg_dispLine/notes.md fire 9): the rc2 residual
(plain `sll 2` + disp-4 fold for an int (idx+1) index, with 4-reg coloring) is a
plausible SECOND fingerprint of the same compiler-sub-build divergence — dev
binary distributes (idx+1)*4 -> idx*4+disp4 for plain int where ours keeps
(idx+1)<<2; our only route to the distribution is a narrowing op whose sext pair
IS the rc2. If a second ee-gcc 2.9-991111 build surfaces, retest plain
`D[idx+1]`.
### Fire 8 permuter shot (2026-06-09) — resolution (b)
Bounded run (~600s) seeded from rc2 short form. ~100 outputs; harvested all
score<=120 by TRUE real_count: best rc2 (output-105-* = the seed form itself);
score-80/85/95 candidates are semantically divergent (e.g. D[4] never written)
and rc4-12 true. No score-0, nothing < rc2. (b) permuter-exhausted.
