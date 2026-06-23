# func_00220918 (st08a) + clones func_002209A8, func_00220A38

Sub-actor registration. Shape (int-cast, gp-first = dev's true store order):
    int s = *(int*)(a0 + 0x164);
    int arg = a0;                       // hoist 2nd volatile read early (deref split)
    D_0062A894 = 1;
    *(int*)(s + 0xB4) = (int)D_004CCAA0;
    D_004CCAA0[1] = (int)actSt05eSolar;
    *(int*)(s + 0xB0) = 0;
    BoxBarSoundOn(arg, 0x189);
    _ACTWait(0);

best real_count: gp-first=10 (CORRECT store order, all stores+loads+liveness match;
ONLY the 6 setup insns [2 lui, 2 addiu, addiu a3=1, addiu a1=393] are ordered
differently: expected breadth-first [lui v0,lui v1,addiu v0,addiu v1,a3,a1] vs built
depth-first with addiu a3=1 grabbing slot2). gp-after-B4=6 (lower count but WRONG
store order: gp store lands 3rd). Tried ~16 distinct shapes: arg/base temp positions,
gp-store position (aliasing-coupled to const-1 placement), struct-typed s (12),
data-local (13), B0/D[1] reorders, split decl. The const-1 (D_0062A894=1) materialize
slot is a pure sched2 tie-break unreachable by clean source: gp-first => const early;
gp-after-B4 => const correct but gp store late. PERMUTER-CLASS once 30-stall reached.
Seed permuter with the gp-first (count-10) version (correct store order).

---

## Attempt at 2026-06-13

**Reason parked:** scheduler filler tie best rc6: D_0062A894=1 const-materialize slot vs gp-store-position mutually exclusive in clean source (gp-first=>const@slot2; gp-late=>store floats). ~30 distinct hand shapes. seed=int-cast arg-temp, all stores/loads/liveness match, only 6 setup insns mis-ordered. clones: func_002209A8, func_00220A38

**TU:** `script/src/st08a.c`

**Seed:** `tough_nuts/func_00220918/func_00220918.1.c`

Disassembly:

```
.align 3
nonmatching func_00220918, 0x58

glabel func_00220918
    /* 120918 00220918 E0FFBD27 */  addiu      $29, $29, -0x20
    /* 12091C 0022091C 4D00023C */  lui        $2, %hi(D_004CCAA0)
    /* 120920 00220920 0000A4AF */  sw         $4, 0x0($29)
    /* 120924 00220924 2200033C */  lui        $3, %hi(actSt05eSolar)
    /* 120928 00220928 1000BFFF */  sd         $31, 0x10($29)
    /* 12092C 0022092C A0CA4224 */  addiu      $2, $2, %lo(D_004CCAA0)
    /* 120930 00220930 0000A58F */  lw         $5, 0x0($29)
    /* 120934 00220934 B0CD6324 */  addiu      $3, $3, %lo(actSt05eSolar)
    /* 120938 00220938 0000A48F */  lw         $4, 0x0($29)
    /* 12093C 0022093C 01000724 */  addiu      $7, $0, 0x1
    /* 120940 00220940 6401A68C */  lw         $6, 0x164($5)
    /* 120944 00220944 89010524 */  addiu      $5, $0, 0x189
    /* 120948 00220948 A49C87AF */  sw         $7, %gp_rel(D_0062A894)($28)
    /* 12094C 0022094C B400C2AC */  sw         $2, 0xB4($6)
    /* 120950 00220950 040043AC */  sw         $3, 0x4($2)
    /* 120954 00220954 F867050C */  jal        BoxBarSoundOn
    /* 120958 00220958 B000C0AC */   sw        $0, 0xB0($6)
    /* 12095C 0022095C 6004080C */  jal        _ACTWait
    /* 120960 00220960 2D200000 */   daddu     $4, $0, $0
    /* 120964 00220964 1000BFDF */  ld         $31, 0x10($29)
    /* 120968 00220968 0800E003 */  jr         $31
    /* 12096C 0022096C 2000BD27 */   addiu     $29, $29, 0x20
endlabel func_00220918
```

---

## Re-confirmation 2026-06-23

Re-derived from scratch (~40 distinct shapes). CONFIRMED permuter-class.
PROOF the clean-source space is exhausted: three semantically-distinct C
spellings of the gp-first body (D[1] via `(int*)((char*)D+4)`, via `D[1]`,
via `s[45]/s[44]` index forms) ALL compile to the IDENTICAL codegen
(rc10). Distinct-codegen space = ~4 outputs total:
  - rc4  : typed DoorSub, D[1]-first  → WRONG store order (gp-store last)
  - rc10 : gp-first int-cast + `int arg=a0` → CORRECT store order; only the
           6 setup insns differ (addiu a3=1 const-1 grabs slot 2 vs ROM's
           lui v1; ROM puts addiu a3=1 at slot 10 after all 4 addr insns)
  - rc11/12/13 : any cb-first / field_B4-first / both-temps → reg-swap v1=D
Root cause: D's register (v0 vs v1) flips based on the POSITION of the
UNRELATED `D_0062A894=1` statement relative to the D-refs — pure uid-driven
regalloc + a const-materialize-slot sched2 tie. Coupled: gp-first⇒const
early; gp-late⇒gp-store floats. No clean-source expression satisfies both.
SEED PERMUTER WITH gp-first rc10 (correct store order), NOT count-min rc4.
NB: driver do_permute seeds from best_src_path (count-min=rc4) — that is the
WRONG seed for this func; the .2.c/.1.c gp-first seeds are the right ones.
Clones func_002209A8, func_00220A38 are byte-identical idioms (same floor).

## BREAKTHROUGH 2026-06-23 — `one` temp lever, rc10/rc4 -> rc6

NEW lever (not in earlier attempts): route the flag const through a temp
`int one = 1; ...; D_0062A894 = one;`. This DECOUPLES the const-1
materialize (addiu a3,1) from the gp-store position — fixes the slot tie
that blocked every prior shape. Best hand floor now rc6 with CORRECT store
order AND correct const placement:
    int s = *(int*)(a0+0x164);
    int arg = a0;
    int one = 1;
    *(int*)(s+0xB4) = (int)D_004CCAA0;   /* field_B4 = &D  */
    D_004CCAA0[1] = (int)actSt05eSolar;  /* D[1] = cb      */
    D_0062A894 = one;                    /* gp flag store  */
    *(int*)(s+0xB0) = 0;                 /* field_B0 = 0 -> jal delay */
    BoxBarSoundOn(arg, 0x189);
    _ACTWait(0);
Residual rc6 = TWO ee-gcc-2.9 prologue scheduler quirks sharing one root:
`addiu v0` (D %lo) is emitted at slot 4 (eager) vs ROM slot 6. That eagerness
(a) puts addiu v0 ahead of `lui v1` (cb %hi) [should be lui v1 @slot4], and
(b) makes the D-stores ready early so the gp-store loses the store tie
(emits 3rd instead of 1st). Deferring addiu v0 by 2 slots fixes BOTH.
No clean-source change defers it (priority: addiu v0 feeds 2 stores > lui v1).
THIS rc6+one shape is the correct PERMUTER SEED (2 quirks from rc0), NOT the
count-min rc4 wrong-order. Apply the same `one` lever to clones
func_002209A8 / func_00220A38.

---

## Attempt at 2026-06-23

**Reason parked:** plateau: 30 distinct hand hypotheses, no real_count progress (best=4). PARK the seed, then fire ONE bounded permuter shot on it (REFERENCE Step 4); harvest by true real_count and adopt any improvement (resolution b only if nothing beats best).

**TU:** `script/src/st08a.c`

**Seed:** `tough_nuts/func_00220918/func_00220918.3.c`

Disassembly:

```
.align 3
nonmatching func_00220918, 0x58

glabel func_00220918
    /* 120918 00220918 E0FFBD27 */  addiu      $29, $29, -0x20
    /* 12091C 0022091C 4D00023C */  lui        $2, %hi(D_004CCAA0)
    /* 120920 00220920 0000A4AF */  sw         $4, 0x0($29)
    /* 120924 00220924 2200033C */  lui        $3, %hi(actSt05eSolar)
    /* 120928 00220928 1000BFFF */  sd         $31, 0x10($29)
    /* 12092C 0022092C A0CA4224 */  addiu      $2, $2, %lo(D_004CCAA0)
    /* 120930 00220930 0000A58F */  lw         $5, 0x0($29)
    /* 120934 00220934 B0CD6324 */  addiu      $3, $3, %lo(actSt05eSolar)
    /* 120938 00220938 0000A48F */  lw         $4, 0x0($29)
    /* 12093C 0022093C 01000724 */  addiu      $7, $0, 0x1
    /* 120940 00220940 6401A68C */  lw         $6, 0x164($5)
    /* 120944 00220944 89010524 */  addiu      $5, $0, 0x189
    /* 120948 00220948 A49C87AF */  sw         $7, %gp_rel(D_0062A894)($28)
    /* 12094C 0022094C B400C2AC */  sw         $2, 0xB4($6)
    /* 120950 00220950 040043AC */  sw         $3, 0x4($2)
    /* 120954 00220954 F867050C */  jal        BoxBarSoundOn
    /* 120958 00220958 B000C0AC */   sw        $0, 0xB0($6)
    /* 12095C 0022095C 6004080C */  jal        _ACTWait
    /* 120960 00220960 2D200000 */   daddu     $4, $0, $0
    /* 120964 00220964 1000BFDF */  ld         $31, 0x10($29)
    /* 120968 00220968 0800E003 */  jr         $31
    /* 12096C 0022096C 2000BD27 */   addiu     $29, $29, 0x20
endlabel func_00220918
```

## PERMUTER RUN 2026-06-23 — PARKED (did not beat rc4)
Driver fired the bounded permuter at stall=30, seeded from the clean rc4.
Best outputs: rc7/rc8/rc12/rc13 — none rc0, NONE beat the rc4 hand floor.
Confirmed permuter-class holdout; PARKED (resolution b). The §2.7
const-arg-vs-store / breadth-first-lui tie is not crackable by clean source
or the bounded permuter. Clean rc4 dev shape (typed DoorSub door idiom,
no temps) is the recovered C. Clones func_002209A8 / func_00220A38 are the
same idiom (different D_/handler symbols) → same outcome expected.
