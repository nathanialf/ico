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
