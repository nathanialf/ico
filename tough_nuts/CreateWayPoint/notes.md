# CreateWayPoint — parked

VRAM: 0x00202F00 (file_off 0x102F00)
Asm source: asm/aug6/nonmatchings/fumi/src/way_llf/CreateWayPoint.s

## Attempt at 2026-06-11

**Reason parked:** rc5 fresh: element-ptr + null-guard + movz. if(a0){body}else{ret=0} fixes ret coloring to $4 (a0-reuse). Residual=coupled coloring+layout: element-addu steals beqz delay slot (ROM has ret=0 there) + separate else block + b. sched2/dbr tie, ~30 forms all rc5-9. reorg-tail permuter class.

**TU:** `fumi/src/way_llf.c`

**Seed:** `tough_nuts/CreateWayPoint/CreateWayPoint.c`

Disassembly:

```
.align 3
nonmatching CreateWayPoint, 0x3C

glabel CreateWayPoint
    /* 102F00 00202F00 2D288000 */  daddu      $5, $4, $0
    /* 102F04 00202F04 4C00023C */  lui        $2, %hi(D_004C6FF0)
    /* 102F08 00202F08 2000A38C */  lw         $3, 0x20($5)
    /* 102F0C 00202F0C 34000424 */  addiu      $4, $0, 0x34
    /* 102F10 00202F10 F06F4224 */  addiu      $2, $2, %lo(D_004C6FF0)
    /* 102F14 00202F14 18186400 */  mult       $3, $3, $4
    /* 102F18 00202F18 21186200 */  addu       $3, $3, $2
    /* 102F1C 00202F1C 0500A010 */  beqz       $5, .L00202F34
    /* 102F20 00202F20 2D200000 */   daddu     $4, $0, $0
    /* 102F24 00202F24 0C00A48C */  lw         $4, 0xC($5)
    /* 102F28 00202F28 0800628C */  lw         $2, 0x8($3)
    /* 102F2C 00202F2C 26108200 */  xor        $2, $4, $2
    /* 102F30 00202F30 0A200200 */  movz       $4, $0, $2
.align 2
  .L00202F34:
    /* 102F34 00202F34 0800E003 */  jr         $31
    /* 102F38 00202F38 2D108000 */   daddu     $2, $4, $0
endlabel CreateWayPoint
    /* 102F3C 00202F3C 00000000 */  nop
```

## Fresh match attempt 2026-06-11: rc8 -> rc5, stall=30 -> permute
Structure: `e=&D_004C6FF0[a0->0x20]; ret = a0 ? (a0->0xC==e->0x8 ? 0 : a0->0xC) : 0` (movz idiom).
Best=rc5 via `if(a0){ret=a0[3];if(a0[3]==e->w[2])ret=0;}else ret=0;` (a0-first if-else colors ret
into $4 = a0's reused arg reg). The DEFAULT `int ret=0;` form gives rc8 (ret->$6, wrong coloring).
Residual rc5 = COUPLED coloring+layout: gcc's dbr fills the beqz delay with the element-addu
(deferred, $3 used only inside the if) while ROM puts ret=0 there; the if-else then needs a separate
else block + `b` to merge vs ROM's ret=0-in-delay + shared return. sched2 schedules ret=0 early
(no deps) so it's never the dbr delay candidate. ~30 distinct hand forms (ternary/movn/sub-cmp/
goto/decl-order/branch-direction/ptr-vs-arr) all rc5-13. Permuter (reorg-tail class).

## Permuter harvest 2026-06-11: nothing below rc5 -> (b)
Permuter ran ~6000 iters, best score 180 (base 220) BUT diff --dry: output-180-1/185-1=rc7,
190-1=rc9, 205-1=rc8 — all WORSE than parked rc5 (score/real_count anti-correlation; the
"wins" are broken `ret=ret` uninitialized-else mutations). Nothing beats rc5. RESOLUTION (b).
Re-attack future resume with a fresh idea to get ret=0 into the beqz delay slot (vs the
deferred element-addu) without the separate else block.

## RETRY IDEA (from DeleteStreamMotionManager match 2026-06-11)
The both-arms-set-default lever [[feedback_both_branches_set_default_late_reg]] cracked the sibling
default-in-delay tie rc12->0. Retry: `if(a0){ret=a0[3];if(a0[3]==e->w[2])ret=0;}else{ret=0;}` is the
rc5 form; try variants where the ELSE also redundantly sets ret and the body re-sets it, to push
ret=0 into the beqz delay reusing $4.

## Pass 2 (2026-06-11): resume, ~30 fresh shapes -> rc5 floor, stall=30 -> permute
Side-by-side confirms: the both-arms if-else rc5 ALREADY has correct $4(a0) ret coloring (movz a0;
daddu a0). The ONLY residual is a dbr delay-slot choice: gcc fills the beqz delay with the SUNK
element-addu (addu v1,v1,v0) + a separate else-block `b zero,zero`; ROM puts ret=0 (daddu a0,zero)
in the beqz delay and falls through to a SHARED return (no b). gcc sinks the addu because e is only
used in the if-arm. Fresh shapes ALL rc5 (struct-preserving) or worse: char-base/idx-mult-temp/
int-ptr/ptr-arr e forms; eager e->w[2] load(rc9); neg-guard(rc8); e-after-a03(rc15); ret uint;
a0-struct; eq-temp; while-once; comma-cond; do-while-0 return; both-arms-bodyret0 movn(rc9). The
goto-end CFG that would share the return BREAKS the $4 coloring->$6 (rc8). Coupled coloring(needs
if-else)+delay-fill(needs goto/shared-return) tension. This is the permuter reorg-tail/delay-store
class [[feedback_permuter_cracks_reorg_tail]] (beqz delay candidate selection). Firing permuter pass 2.

---

## Attempt at 2026-06-11

**Reason parked:** rc5 reorg-tail: both-arms if-else has right $4 coloring but gcc sinks element-addu into beqz delay + extra else-block b vs ROM ret=0-in-delay+shared-return; goto fixes CFG but breaks coloring. ~30 fresh shapes rc5. Pass 2.

**TU:** `fumi/src/way_llf.c`

**Seed:** `tough_nuts/CreateWayPoint/CreateWayPoint.1.c`

Disassembly:

```
.align 3
nonmatching CreateWayPoint, 0x3C

glabel CreateWayPoint
    /* 102F00 00202F00 2D288000 */  daddu      $5, $4, $0
    /* 102F04 00202F04 4C00023C */  lui        $2, %hi(D_004C6FF0)
    /* 102F08 00202F08 2000A38C */  lw         $3, 0x20($5)
    /* 102F0C 00202F0C 34000424 */  addiu      $4, $0, 0x34
    /* 102F10 00202F10 F06F4224 */  addiu      $2, $2, %lo(D_004C6FF0)
    /* 102F14 00202F14 18186400 */  mult       $3, $3, $4
    /* 102F18 00202F18 21186200 */  addu       $3, $3, $2
    /* 102F1C 00202F1C 0500A010 */  beqz       $5, .L00202F34
    /* 102F20 00202F20 2D200000 */   daddu     $4, $0, $0
    /* 102F24 00202F24 0C00A48C */  lw         $4, 0xC($5)
    /* 102F28 00202F28 0800628C */  lw         $2, 0x8($3)
    /* 102F2C 00202F2C 26108200 */  xor        $2, $4, $2
    /* 102F30 00202F30 0A200200 */  movz       $4, $0, $2
.align 2
  .L00202F34:
    /* 102F34 00202F34 0800E003 */  jr         $31
    /* 102F38 00202F38 2D108000 */   daddu     $2, $4, $0
endlabel CreateWayPoint
    /* 102F3C 00202F3C 00000000 */  nop
```

## Pass 2 harvest (2026-06-11): permuter best score 180 (base 220), all worse -> (b)
output-180-1=rc7, output-190-1=rc9 by true real_count (score/real_count anti-correlation again).
Nothing beats rc5. RESOLUTION (b) pass 2. The reorg-tail delay-slot candidate (ret=0 vs sunk
element-addu in the beqz delay) was not crackable by permuter this pass. Future resume: a fresh
CFG idea that keeps $4 ret-coloring (needs the both-arms if-else) AND forces ret=0 into the beqz
delay with a shared return (the goto-merge breaks coloring to $6 — that coupling is the knot).

## Pass 3 (2026-06-11): rc5->rc1 via do-while-0, but rc1 is a .p2align DEAD-END
KEY FINDING: `do{ret=0;}while(0)` BB-barrier placed AFTER `e=&D[a0[8]]` and BEFORE the `if`
FIXES the element-addu sink (rc5->rc1): gcc now emits the addu EAGER + ret=0 in the beqz delay +
shared return — STRUCTURALLY EXACT. BUT the do-while loop makes gcc align $L34 (beqz target) with
`.p2align 3` (8B); $L34 sits at func+0x34 (4-mod-8) so it PADS one nop -> ninja MISMATCH. The
loop-free both-arms form (rc5) emits `.p2align 2` (4B, == ROM .align 2, NO pad) but SINKS the addu.
COUPLED: every loop construct (do-while-0/for-once/while-once) = eager-addu + p2align3-nop (rc1);
every non-loop (block/goto/plain ret=0) = addu-sink (rc5/8). The addu-sink is a dbr eager-fill
heuristic diff (the dev's gcc filled the beqz delay from the TARGET=ret0; my ee-gcc fills SIMPLE
from before=addu). demote_p2align would fix the rc1 nop but is RETIRED per-func machinery
(config/demote_p2align.txt + postprocess_demote_p2align.py absent from aug6 tree). No clean source
breaks the coupling. SEEDS: best=rc1 do-while-0 (p2align dead-end); RESUME from the rc5 both-arms
(genuine clean form, correct alignment) and attack the dbr eager-fill. Permuter pass 3 seeded with
both-arms rc5 (looking for a non-loop reorder that triggers eager-fill -> rc0 with correct p2align2).

---

## Attempt at 2026-06-11

**Reason parked:** rc1 do-while-0 (eager-addu but .p2align3 nop dead-end) / rc5 both-arms (clean .p2align2 but dbr addu-sink); coupled loop-vs-alignment; demote_p2align retired. Pass 3.

**TU:** `fumi/src/way_llf.c`

**Seed:** `tough_nuts/CreateWayPoint/CreateWayPoint.2.c`

Disassembly:

```
.align 3
nonmatching CreateWayPoint, 0x3C

glabel CreateWayPoint
    /* 102F00 00202F00 2D288000 */  daddu      $5, $4, $0
    /* 102F04 00202F04 4C00023C */  lui        $2, %hi(D_004C6FF0)
    /* 102F08 00202F08 2000A38C */  lw         $3, 0x20($5)
    /* 102F0C 00202F0C 34000424 */  addiu      $4, $0, 0x34
    /* 102F10 00202F10 F06F4224 */  addiu      $2, $2, %lo(D_004C6FF0)
    /* 102F14 00202F14 18186400 */  mult       $3, $3, $4
    /* 102F18 00202F18 21186200 */  addu       $3, $3, $2
    /* 102F1C 00202F1C 0500A010 */  beqz       $5, .L00202F34
    /* 102F20 00202F20 2D200000 */   daddu     $4, $0, $0
    /* 102F24 00202F24 0C00A48C */  lw         $4, 0xC($5)
    /* 102F28 00202F28 0800628C */  lw         $2, 0x8($3)
    /* 102F2C 00202F2C 26108200 */  xor        $2, $4, $2
    /* 102F30 00202F30 0A200200 */  movz       $4, $0, $2
.align 2
  .L00202F34:
    /* 102F34 00202F34 0800E003 */  jr         $31
    /* 102F38 00202F38 2D108000 */   daddu     $2, $4, $0
endlabel CreateWayPoint
    /* 102F3C 00202F3C 00000000 */  nop
```
