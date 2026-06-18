# DispCollisionPC — parked (dev shape recovered)

VRAM: 0x00163DE8 (file_off 0x063DE8)
Asm source: asm/aug6/nonmatchings/fumi/src/fieldCollision/DispCollisionPC.s

## 2026-06-13 — genuine developer shape recovered

**What it is:** enemy brain-state dispatch. `self->p_164` = EnemyActState
(actor/action-state object, GObj+0x164), `->p_670` = EBrain670 (enemy brain),
`->f_1DC` = brain state. If state == 3 → func_00161998, else
ChangeBrain_ToKidnap (both forwarded `(self, a1, a2, a3, a4)`, a4 unsigned char).
Data model + idiom recovered from fumi/src/enemy_act.c (defines EnemyActState /
EBrain670; siblings actEnemyFlagCheck* use the same `p=*..164; q=p->p_670; q->f_1DC`
walk). ChangeBrain_ToKidnap lives in enemy_act.c.

**Dev-shape seed (semantically exact, rc4):**
```c
typedef struct { char _0[0x1DC]; int f_1DC; } FcBrain;
typedef struct { char _0[0x670]; FcBrain *p_670; } FcActor;

int DispCollisionPC(GObj *self, int a1, int a2, int a3, unsigned char a4)
{
    FcActor *p = *(FcActor **)&self->p_164;
    FcBrain *q = p->p_670;
    if (q->f_1DC != 3)
        return ChangeBrain_ToKidnap(self, a1, a2, a3, a4);
    return func_00161998(self, a1, a2, a3, a4);
}
```

**Residual = rc4, ONE root cause:** a deterministic block-0 local-alloc
coloring tie. ROM: `addiu v1,3` (const→v1), brain→a0. Built: const→a0, brain→v1.
Everything else (beq, delay slots, andi a4 mask, `b`, ld ra) is byte-identical.
Cause: const-3 and the brain pointer share basic block 0 with effectively equal
live ranges; gcc's local-alloc qty tie-break hands the brain (denser, born at the
2nd chain load) the lower free reg ($3=v1) and the const $4=a0. With a literal
`== 3` compare the const pseudo is necessarily created last (canonicalised to RHS,
constant-prop folds any early `three=3`), and the brain pointer's live range is
structurally pinned to one instruction (dies at the field load; can't extend
without adding an instruction the ROM lacks). So neither hand lever
(const-born-first / extend-brain-range / raise-const-refs) is achievable in clean C.

**Class:** func_001FB768 twin — pure coloring tie. Permuter-class (it found the
`(new_var2 = new_var)` non-coalescing-copy trick for the analog). HAND-EXHAUSTED:
~12 genuinely-distinct RTL shapes this session (param-reuse, in-cond-assign,
ptr-slot, copy-in-cond, volatile, fp-select, goto-CFG, subtraction, reused-ptr,
int-handle, typed-struct, two-temp) ALL rc4 same divergence.

**NOTE:** an earlier automation (`_disp_grind.py`) padded the stall counter with
RTL-equivalent cosmetic forms — that was a cheat, removed, counter reset. Do NOT
do that. Reach the permuter gate only via genuinely-distinct hands.

**Next on resume:** seed the permuter with the dev shape above at a genuine
stall=30, OR (per 2026-06-13 user direction "don't worry about sha match") accept
the semantically-exact dev shape and defer byte-exactness.

## 2026-06-13 — PARKED per user direction (no permuter)
User authorized park without permuting; advance to next func. Dev shape + RTL/greg
proof above are the resume material. greg sort confirms: brain(len2) allocated
before const(len3) → brain takes v1, const takes a0; inverse of ROM. Permuter-class.

---

## Attempt at 2026-06-18

**Reason parked:** plateau: 30 distinct hand hypotheses, no real_count progress (best=4). PARK the seed, then fire ONE bounded permuter shot on it (REFERENCE Step 4); harvest by true real_count and adopt any improvement (resolution b only if nothing beats best).

**TU:** `fumi/src/fieldCollision.c`

**Seed:** `tough_nuts/DispCollisionPC/DispCollisionPC.1.c`

Disassembly:

```
.align 3
nonmatching DispCollisionPC, 0x48

glabel DispCollisionPC
    /* 63DE8 00163DE8 F0FFBD27 */  addiu      $29, $29, -0x10
    /* 63DEC 00163DEC 2D488000 */  daddu      $9, $4, $0
    /* 63DF0 00163DF0 0000BFFF */  sd         $31, 0x0($29)
    /* 63DF4 00163DF4 03000324 */  addiu      $3, $0, 0x3
    /* 63DF8 00163DF8 6401228D */  lw         $2, 0x164($9)
    /* 63DFC 00163DFC 7006448C */  lw         $4, 0x670($2)
    /* 63E00 00163E00 DC01828C */  lw         $2, 0x1DC($4)
    /* 63E04 00163E04 05004310 */  beq        $2, $3, .L00163E1C
    /* 63E08 00163E08 FF000831 */   andi      $8, $8, 0xFF
    /* 63E0C 00163E0C 4487050C */  jal        ChangeBrain_ToKidnap
    /* 63E10 00163E10 2D202001 */   daddu     $4, $9, $0
    /* 63E14 00163E14 04000010 */  b          .L00163E28
    /* 63E18 00163E18 0000BFDF */   ld        $31, 0x0($29)
.align 2
  .L00163E1C:
    /* 63E1C 00163E1C 6686050C */  jal        func_00161998
    /* 63E20 00163E20 2D202001 */   daddu     $4, $9, $0
    /* 63E24 00163E24 0000BFDF */  ld         $31, 0x0($29)
.align 2
  .L00163E28:
    /* 63E28 00163E28 0800E003 */  jr         $31
    /* 63E2C 00163E2C 1000BD27 */   addiu     $29, $29, 0x10
endlabel DispCollisionPC
```
