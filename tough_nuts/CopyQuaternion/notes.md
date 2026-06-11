# CopyQuaternion — parked (b) rc1

VRAM 0x0010DB88. Local-buffer wrapper (like _ACTMotDirSmzDirect / MatrixDrive):
a0 saved in s0; func_00118AF0(local, a1) fills a 0x40 stack buffer (sp+0);
GetQuaternionFromMatrix(a0, local) reads it.

## Pass 2 (2026-06-08): empty seed -> rc1
Best clean form (void, no return) misses ONE insn: ROM emits `daddu v0,sp`
(redundant &local into v0) BEFORE the GetQ call. `return local` adds v0=sp but
at the END (rc2, wrong position). Permuter (180s, no mode-TI) found NO rc0.
RESUME: the v0=sp-before-GetQ is a regalloc artifact — try func_00118AF0 returning
void* (the buffer) reused as GetQ's arg + returned; or a 3rd local materialization.
## Fire 6: re-attack rc1 dead-daddu-v0,sp artifact; void* return/voidptr-reuse/getq-return all rc2; ~30 distinct all rc1; stall=32 permute, valid run (3 out) no rc0. (b)

---

## Attempt at 2026-06-11

**Reason parked:** rc1: dead pre-call daddu v0,sp (move v0,sp) before GetQ in a VOID fn — regalloc rematerialize of &local CSE dead-def. 18 distinct hand shapes this session (typed/union/struct-ret/void*-ret/return-local/comma/arg-order) all rc1-3; callees confirmed 2-arg void; matched sibling _ACTMotDirSmzDirect(identical idiom) has NO dead-v0. Permuter pass 3.

**TU:** `sugipon/src/quaternion.c`

**Seed:** `tough_nuts/CopyQuaternion/CopyQuaternion.1.c`

Disassembly:

```
.align 3
nonmatching CopyQuaternion, 0x38

glabel CopyQuaternion
    /* DB88 0010DB88 A0FFBD27 */  addiu      $29, $29, -0x60
    /* DB8C 0010DB8C 4000B0FF */  sd         $16, 0x40($29)
    /* DB90 0010DB90 2D808000 */  daddu      $16, $4, $0
    /* DB94 0010DB94 5000BFFF */  sd         $31, 0x50($29)
    /* DB98 0010DB98 BC62040C */  jal        func_00118AF0
    /* DB9C 0010DB9C 2D20A003 */   daddu     $4, $29, $0
    /* DBA0 0010DBA0 2D200002 */  daddu      $4, $16, $0
    /* DBA4 0010DBA4 2D10A003 */  daddu      $2, $29, $0
    /* DBA8 0010DBA8 5636040C */  jal        GetQuaternionFromMatrix
    /* DBAC 0010DBAC 2D28A003 */   daddu     $5, $29, $0
    /* DBB0 0010DBB0 5000BFDF */  ld         $31, 0x50($29)
    /* DBB4 0010DBB4 4000B0DF */  ld         $16, 0x40($29)
    /* DBB8 0010DBB8 0800E003 */  jr         $31
    /* DBBC 0010DBBC 6000BD27 */   addiu     $29, $29, 0x60
endlabel CopyQuaternion
```

## Pass 3 (2026-06-11): resume, 18 distinct hand shapes -> rc1 floor, stall=30 -> permute
Grounded the callees: func_00118AF0($4=dst,$5=src) is a 0x40 qword memcpy (void);
GetQuaternionFromMatrix($4=dst quat a0, $5=src matrix local) reads both, void. So the
seed `func_00118AF0(local,a1); GetQuaternionFromMatrix(a0,local);` is semantically exact.
Matched SIBLING _ACTMotDirSmzDirect (fumi/commonact.c:265, `int local[4]; ChangeMailInLadder(local,a0); dispPlane(a0,local);`)
is the SAME idiom and has NO dead-v0 -> the dead `daddu v0,sp` (move v0,sp) is a
CopyQuaternion-specific regalloc rematerialize of the &local CSE: gcc puts &local in v0
(caller-saved) then rematerializes daddu $5,$29 at the GetQ arg, leaving v0 dead.
It is PRE-CALL and DEAD (GetQ clobbers v0) so NO return-value shape can place it (return
local -> v0=sp at END = rc2). Confirmed rc1 with: typed Mtx/Quat structs, union local,
double[8]/int[16], &local[0], two-var d/m, arg-order swap, char* params, comma operator,
nested func ret, void* return reuse (rc2), struct-return (hidden ptr -> $4 not v0, rc3).
Firing permuter pass 3 at the genuine stall=30.

## Pass 3 harvest (2026-06-11): permuter score-85 outputs measure rc2/rc3 by true real_count
Permuter ran ~10k iters, best score=85 (base 115) BUT `diff --dry` shows output-85-1=rc2,
output-85-2=rc3 — WORSE than parked rc1 (score/real_count anti-correlation). Idea it surfaced:
`GetQuaternionFromMatrix(a0, new_var2 = local)` (assign-in-arg) — but cleaned to semantics it
optimizes away (rc1); verbatim only "wins" by mis-passing a0 to func1. Nothing beats rc1.
RESOLUTION (b): permuter-exhausted pass 3. Re-attack future resume with a FRESH hand idea on
the dead pre-call v0=sp regalloc rematerialize.

## Pass 4 (2026-06-11): resume, reset stall, ~30 NEW distinct clean shapes -> rc1 floor, stall=30 -> permute
Re-confirmed the ONLY diff is a single DEAD `daddu v0,sp,zero` at exp_index 7 (between the two
calls, after `daddu a0,s0`); built is otherwise byte-identical. The v0 copy is provably DEAD:
GetQuaternionFromMatrix clobbers v0, so it cannot be a live return value — it is a reload/dbr
rematerialize ghost with NO source-level meaning. `return local`-family puts the SAME insn at
exp_index 11 (END), where it IS the live return value (rc2). Cookbook has a dedicated CRUTCH
macro `DEAD_DADDU_V0_SP(a)` (matching.h) that injects exactly this `daddu $2,$29,$0` — its very
existence is the repo's admission no clean C reproduces it (and the differ rejects the crutch).

NEW shapes ruled out this pass (all fold to the clean one-step `daddu a1,sp`, rc1 unless noted):
CqMatrix struct + &local; single `char *p` reused; nested `GetQ(a0, func1ret(local,a1))`
(void* return -> a1,v0 rc2); temp-renames (src/dst/both); a0-cast; volatile-local; nested-scope;
u64[8]; alloca (rc12, frame-ptr); 2d-array `local[0]`; ptr-to-array `*pa`; deref `&*local`;
comma-nest call1-inside-GetQ-arg (x2); a0-reload; noproto-both; union{b[];p} member; float* sig;
static-inline identity (rc4); ptr-3use w/ dead branch (rc15); xor-self-addr; second-buffer (rc10).
gcc collapses every address expression to a single rematerializable leaf -> never a held pseudo
-> never the two-step (set v0 P)(set a1 v0) that orphans v0. Mechanism needs register PRESSURE to
spill &local, but the 14-insn budget admits no extra live value. Firing permuter pass 4 at stall=30.

---

## Attempt at 2026-06-11

**Reason parked:** rc1 floor: single DEAD daddu v0,sp reload ghost between 2 calls (GetQ clobbers v0 -> not a return value); ~30 distinct clean shapes all fold to one-step daddu a1,sp; needs reg-pressure spill the 14-insn budget can't supply; DEAD_DADDU_V0_SP crutch exists for this exact pattern. Pass 4.

**TU:** `sugipon/src/quaternion.c`

**Seed:** `tough_nuts/CopyQuaternion/CopyQuaternion.2.c`

Disassembly:

```
.align 3
nonmatching CopyQuaternion, 0x38

glabel CopyQuaternion
    /* DB88 0010DB88 A0FFBD27 */  addiu      $29, $29, -0x60
    /* DB8C 0010DB8C 4000B0FF */  sd         $16, 0x40($29)
    /* DB90 0010DB90 2D808000 */  daddu      $16, $4, $0
    /* DB94 0010DB94 5000BFFF */  sd         $31, 0x50($29)
    /* DB98 0010DB98 BC62040C */  jal        func_00118AF0
    /* DB9C 0010DB9C 2D20A003 */   daddu     $4, $29, $0
    /* DBA0 0010DBA0 2D200002 */  daddu      $4, $16, $0
    /* DBA4 0010DBA4 2D10A003 */  daddu      $2, $29, $0
    /* DBA8 0010DBA8 5636040C */  jal        GetQuaternionFromMatrix
    /* DBAC 0010DBAC 2D28A003 */   daddu     $5, $29, $0
    /* DBB0 0010DBB0 5000BFDF */  ld         $31, 0x50($29)
    /* DBB4 0010DBB4 4000B0DF */  ld         $16, 0x40($29)
    /* DBB8 0010DBB8 0800E003 */  jr         $31
    /* DBBC 0010DBBC 6000BD27 */   addiu     $29, $29, 0x60
endlabel CopyQuaternion
```

## Pass 4 harvest (2026-06-11): permuter base=115, NO sub-base, exhausted -> (b)
Ran ~9min (-j4, --stop-on-zero), best score=115 (== base, NO improvement). Only sub-base score
outputs were output-85-{1,2}; by TRUE real_count (diff --dry) they are rc2/rc3 (WORSE than rc1) —
both "win" their score by mis-routing a0 into func_00118AF0's 2nd arg (semantically broken, the
same anti-correlated score trap as pass 3). Nothing beats parked rc1. RESOLUTION (b) pass 4.
Future resume: the dead daddu v0,sp is a reload/dbr ghost needing a held &local pseudo + extra
reg pressure; no clean 14-insn shape supplies it. Try a fundamentally different angle (e.g. is
func_00118AF0 actually a 3-arg/return-buffer fn whose retval legitimately occupies v0 pre-GetQ?).

## Pass 5 (2026-06-11): resume, ~30 fresh shapes incl. do-while-0 BB-split lever -> rc1, stall=30 -> permute
Applied the [[feedback_dowhile0_bb_split_sched2_priority]] lever (cracked func_00269480 same session):
do-while-0/if(1)/while-break BB boundaries around either call, both calls, return-style — ALL rc1.
BB-splits move SCHEDULING-priority ties; they do NOT inject a DEAD reload (the v0=&local ghost has
no source basis to reorder). Also fresh this pass: ret-store-dw0(rc2), second-dummy-qword(rc7,frame),
goto-getq, ptr-pre/two-getq-arg, void*/double/int/ll/u128(TI)/struct-member locals, arg-swap,
aligned32, char80, comma/plus0/long-cast arg forms — all rc1. Confirms pass-4 conclusion: the dead
`daddu v0,sp` between the 2 calls is a reload/dbr rematerialize with no clean source basis (GetQ
clobbers v0 so it's not a return value). Firing permuter pass 5 (pass 4 base=115 found only broken-
semantics 85s; a dead-insn INJECTION is not permuter-reorderable, unlike func_00269480's reorder).

---

## Attempt at 2026-06-11

**Reason parked:** rc1 dead daddu v0,sp reload ghost; pass5 ~30 fresh shapes incl do-while-0 BB-split all rc1; permuter pass5

**TU:** `sugipon/src/quaternion.c`

**Seed:** `tough_nuts/CopyQuaternion/CopyQuaternion.3.c`

Disassembly:

```
.align 3
nonmatching CopyQuaternion, 0x38

glabel CopyQuaternion
    /* DB88 0010DB88 A0FFBD27 */  addiu      $29, $29, -0x60
    /* DB8C 0010DB8C 4000B0FF */  sd         $16, 0x40($29)
    /* DB90 0010DB90 2D808000 */  daddu      $16, $4, $0
    /* DB94 0010DB94 5000BFFF */  sd         $31, 0x50($29)
    /* DB98 0010DB98 BC62040C */  jal        func_00118AF0
    /* DB9C 0010DB9C 2D20A003 */   daddu     $4, $29, $0
    /* DBA0 0010DBA0 2D200002 */  daddu      $4, $16, $0
    /* DBA4 0010DBA4 2D10A003 */  daddu      $2, $29, $0
    /* DBA8 0010DBA8 5636040C */  jal        GetQuaternionFromMatrix
    /* DBAC 0010DBAC 2D28A003 */   daddu     $5, $29, $0
    /* DBB0 0010DBB0 5000BFDF */  ld         $31, 0x50($29)
    /* DBB4 0010DBB4 4000B0DF */  ld         $16, 0x40($29)
    /* DBB8 0010DBB8 0800E003 */  jr         $31
    /* DBBC 0010DBBC 6000BD27 */   addiu     $29, $29, 0x60
endlabel CopyQuaternion
```

## Pass 5 harvest (2026-06-11): permuter base=115 no sub-base -> (b)
~2000 iters, best=115 (==base). output-85-1=rc3, output-115-1=rc2 by true real_count (both worse
than rc1; the 85 mis-routes a0 again). Nothing beats rc1. RESOLUTION (b) pass 5. Same as pass 4 —
a dead-insn injection is not permuter-reorderable. Future resume needs a fundamentally new angle on
func_00118AF0's real signature/return (does it return the buffer, legitimately occupying v0 pre-GetQ?).

## Pass 6 (2026-06-11): callee grounded + NEW permuter-seed strategy
GROUNDED callees from asm: func_00118AF0 = void 4x4 matrix TRANSPOSE(dst=$4, src=$5) via
pextlw/pextuw/pcpyld/pcpyud, NO return value (refutes the pass-5 "returns buffer→v0" angle —
the dead v0=&local has NO callee basis). GetQuaternionFromMatrix(dst,src) void. ~30 fresh shapes
(typed Mtx struct, a0/dst/src temps, stmt-expr, transpose-grounded, u64/double/float/int/void*
locals, dw0/goto/while1/if1 CFG, 2d-array, ptr-to-array, union, second-buffer) ALL rc1.
NEW STRATEGY for permuter pass 6: seed with the rc2 `return local` form (void* return) which HAS
the `daddu v0,sp` instruction PRESENT (at function END) — ROM has the SAME insn in the dead MIDDLE
position. Clean rc1 (12 insns) MISSES the insn entirely so the permuter can't inject it; the rc2
seed (13 insns, insn present) lets the permuter REORDER it end→middle = potential rc0. This is a
pure reorder (permuter-tractable) vs injection (not). Passes 4,5 wrongly seeded the clean rc1.

---

## Attempt at 2026-06-11

**Reason parked:** rc1 dead v0=&local; pass6 callee-grounded (func_00118AF0=void transpose, no return); ~30 fresh shapes rc1; NEW permuter strategy: seed rc2 return-local (has v0=sp insn to REORDER not inject)

**TU:** `sugipon/src/quaternion.c`

**Seed:** `tough_nuts/CopyQuaternion/CopyQuaternion.4.c`

Disassembly:

```
.align 3
nonmatching CopyQuaternion, 0x38

glabel CopyQuaternion
    /* DB88 0010DB88 A0FFBD27 */  addiu      $29, $29, -0x60
    /* DB8C 0010DB8C 4000B0FF */  sd         $16, 0x40($29)
    /* DB90 0010DB90 2D808000 */  daddu      $16, $4, $0
    /* DB94 0010DB94 5000BFFF */  sd         $31, 0x50($29)
    /* DB98 0010DB98 BC62040C */  jal        func_00118AF0
    /* DB9C 0010DB9C 2D20A003 */   daddu     $4, $29, $0
    /* DBA0 0010DBA0 2D200002 */  daddu      $4, $16, $0
    /* DBA4 0010DBA4 2D10A003 */  daddu      $2, $29, $0
    /* DBA8 0010DBA8 5636040C */  jal        GetQuaternionFromMatrix
    /* DBAC 0010DBAC 2D28A003 */   daddu     $5, $29, $0
    /* DBB0 0010DBB0 5000BFDF */  ld         $31, 0x50($29)
    /* DBB4 0010DBB4 4000B0DF */  ld         $16, 0x40($29)
    /* DBB8 0010DBB8 0800E003 */  jr         $31
    /* DBBC 0010DBBC 6000BD27 */   addiu     $29, $29, 0x60
endlabel CopyQuaternion
```

## Pass 6 harvest (2026-06-11): rc2-seed base=60, NO sub-base output -> (b)
Permuter ran ~3400 iters from the rc2 return-local seed (base score 60, much closer than the
clean-seed 115). NO output below base — the `daddu v0,sp` in the rc2 seed is the RETURN VALUE,
semantically pinned to the function END; no source mutation moves it to the dead middle without
breaking the return, so the permuter can't reorder it any more than it can inject it. Confirms the
dead v0=&local is genuinely unreachable by clean C OR permuter (both injection AND reorder fail).
RESOLUTION (b) pass 6. This is the strongest-evidenced (b) in the repo now (callee-grounded +
3 permuter strategies exhausted). Future resume: only a fundamentally different model of what the
dead v0 IS (not &local? a frame artifact of a larger original frame?) could open it.

## Pass 7 (2026-06-11): DEV-INTENT grounding of BOTH callees — conclusive (b)
Per user feedback (reason from the dev's data model + the function's GOAL, not syntax), grounded
the second callee for the first time:
- func_00118AF0 = void 4x4 matrix TRANSPOSE (pextlw/pextuw/pcpyld/pcpyud), dst=$4 src=$5, NO return.
- GetQuaternionFromMatrix(dst=$4, matrix=$5) = trace-based quaternion extraction (reads m[0]+m[0x14]
  +m[0x28] diagonal, c.lt.s 0, the classic algo). Its prologue does `sw $2, 0x0($29)` (spills the
  INCOMING $2/v0) but sp+0 is NEVER read back — a dead spill in GetQ's OWN frame, NOT a real v0 param.
GOAL: CopyQuaternion(dst,src) = quaternion-from-transposed-matrix. Tested the semantic hypotheses the
grounding suggested (NOT costumes): GetQ 3rd-arg -> lands in a2($6) not v0 (rc2); func_00118AF0
returns-buffer + ignore -> gcc ELIDES the dead return (rc1, no v0 at all); returns-buffer nested as
GetQ 3rd arg -> daddu a2,v0 (rc1); typed Mtx struct -> rc1. CONCLUSION: the dead `daddu v0,sp` at the
mid position is reachable by NO clean C — v0 is not an arg reg (args go $4-$7/$8-$9 n32), so a value
lands in v0 only as an unconsumed return, which gcc elides. It is a pure reload/regalloc artifact.
This is now the strongest-evidenced (b) in the repo (both callees grounded, all semantic axes ruled
out, 3 permuter strategies exhausted). NOT a costume-floor — a conclusively-grounded compiler artifact.

---

## Attempt at 2026-06-11

**Reason parked:** rc1 dead v0=&local; pass7 DEV-INTENT grounded both callees conclusively (void transpose + trace-quaternion that dead-stores incoming v0); all semantic axes (3rd-arg->a2, retbuf-elided, struct/types) ruled out; reload artifact. Pass 7.

**TU:** `sugipon/src/quaternion.c`

**Seed:** `tough_nuts/CopyQuaternion/CopyQuaternion.5.c`

Disassembly:

```
.align 3
nonmatching CopyQuaternion, 0x38

glabel CopyQuaternion
    /* DB88 0010DB88 A0FFBD27 */  addiu      $29, $29, -0x60
    /* DB8C 0010DB8C 4000B0FF */  sd         $16, 0x40($29)
    /* DB90 0010DB90 2D808000 */  daddu      $16, $4, $0
    /* DB94 0010DB94 5000BFFF */  sd         $31, 0x50($29)
    /* DB98 0010DB98 BC62040C */  jal        func_00118AF0
    /* DB9C 0010DB9C 2D20A003 */   daddu     $4, $29, $0
    /* DBA0 0010DBA0 2D200002 */  daddu      $4, $16, $0
    /* DBA4 0010DBA4 2D10A003 */  daddu      $2, $29, $0
    /* DBA8 0010DBA8 5636040C */  jal        GetQuaternionFromMatrix
    /* DBAC 0010DBAC 2D28A003 */   daddu     $5, $29, $0
    /* DBB0 0010DBB0 5000BFDF */  ld         $31, 0x50($29)
    /* DBB4 0010DBB4 4000B0DF */  ld         $16, 0x40($29)
    /* DBB8 0010DBB8 0800E003 */  jr         $31
    /* DBBC 0010DBBC 6000BD27 */   addiu     $29, $29, 0x60
endlabel CopyQuaternion
```
