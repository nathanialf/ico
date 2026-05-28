# func_0014A560 — view-check predicate (act-game)

VRAM 0x0014A560. TU: src/act-game.c (coalesced). Asm:
asm/nonmatchings/src/act-game/func_0014A560.s

Best real_count: **12** (branch-likely floor, see below).

## What it does
Predicate returning 0/1 on the player D_00631AE4:
- player == 0 -> 0
- state = player->_164->_30; if state not in {0x4B, 0x55} -> 0
- sub = player->_15C; entry = (char*)D_00565060 + sub->_4A0 * 0x190;
  return entry->_15C == 1
(D_00565060 is the 0x190-stride _E190 array; see siblings func_00149EF8,
func_00149F20 in the same TU for the indexing idiom.)

## Levers that WORKED (21 -> 12)
1. goto-CFG with a SHARED out-of-line return-0 (`goto ret0`/`end`) — fixes
   the player==0 branch direction to `beq a0,zero,<end>` (natural
   `if(player==0)return 0` inverts it to bnel). 21->18.
2. `register int rv REG("$2")` (TU idiom, cf. func_00149E70/func_0014A0A8)
   — keeps the result in v0, kills the spurious `daddu v0,a2,zero` move.
   18->12.

## RESIDUAL 12 diffs (branch-likely floor + cascade)
The state checks: original emits `beql a1,0x4B` (sub-load in the annulled
delay) and `bnel a1,0x55` (rv=0 in the annulled delay). Every structure I
tried gives plain `beq`/`bne` OR an inverted `beql` — ee-gcc's
branch-likely heuristic, NOT source-controllable (cf.
[[branch_likely_emission]]; the sibling func_001177C8 is the same
confirmed floor). The branch-type mismatch cascades into the entry-block
regalloc (sub in v0 vs a0, the 400 const in a0 vs a3).

Structures ruled out: natural early-return (rc21, player branch inverted);
natural `||` (rc29, got the first beql but messy entry regalloc);
duplicated sub-load if/else-if (rc14, first beql + extra `b`); goto +
rv-pin (rc12, BEST).

## Next: permuter / fresh idea
Branch-likely heuristic floor. Permuter is the tool if anything (it can
reshape to hit the beql/bnel), but low-probability at 12. Seed is the
rc12 goto+rv-pin form. CFLAGS = exact quick_diff CFLAGS (no per-file flag).

---

## Attempt at 2026-05-28

**Reason parked:** rc10 (improved from prior rc12). 13 distinct hyps this session. ROOT: gcc 2.9 deterministically emits beql(0x4B)+beql(0x55)->body (both tests positive to body, neither-case returns 0) instead of target's beql(0x4B)+bnel(!=0x55)->exit + standalone sub-load. Tried: duplicated sub-load, goto-have_sub single load, combined && guard, direct return 0, sub-before-tests(sink), MEM_BARRIER, ANCHOR(sub), -fno-thread-jumps, -fno-cse-follow-jumps -- ALL beql+beql. Body regalloc (idx/400/base = a1/v1/a0 vs target v1/a0/a1) is CASCADE-LOCKED by the wrong branch: base+product REG($5)/REG($3) pins PROVABLY IGNORED (3 pin variants -> byte-identical body). Branch-layout = permuter domain. NOT a proven floor; resume next fire or promote permuter score-0. Seed has idx-pin body form.

**TU:** `src/act-game.c`

**Seed:** `tough_nuts/func_0014A560/func_0014A560.1.c`

Disassembly:

```
/* Symbols accessed via $gp register */
.extern D_00631AE4, 1

.align 3
nonmatching func_0014A560, 0x60

glabel func_0014A560
    /* 4A560 0014A560 F491848F */  lw         $4, (D_00631AE4) /* gp_rel: (D_00631AE4) */
    /* 4A564 0014A564 13008010 */  beqz       $4, .L0014A5B4
    /* 4A568 0014A568 4B000324 */   addiu     $3, $0, 0x4B
    /* 4A56C 0014A56C 6401828C */  lw         $2, 0x164($4)
    /* 4A570 0014A570 3000458C */  lw         $5, 0x30($2)
    /* 4A574 0014A574 0500A350 */  beql       $5, $3, .L0014A58C
    /* 4A578 0014A578 5C01828C */   lw        $2, 0x15C($4)
    /* 4A57C 0014A57C 55000224 */  addiu      $2, $0, 0x55
    /* 4A580 0014A580 0D00A254 */  bnel       $5, $2, .L0014A5B8
    /* 4A584 0014A584 2D100000 */   daddu     $2, $0, $0
    /* 4A588 0014A588 5C01828C */  lw         $2, 0x15C($4)
.align 2
  .L0014A58C:
    /* 4A58C 0014A58C 5600053C */  lui        $5, %hi(D_00565060)
    /* 4A590 0014A590 90010424 */  addiu      $4, $0, 0x190
    /* 4A594 0014A594 6050A524 */  addiu      $5, $5, %lo(D_00565060)
    /* 4A598 0014A598 A004438C */  lw         $3, 0x4A0($2)
    /* 4A59C 0014A59C 01000624 */  addiu      $6, $0, 0x1
    /* 4A5A0 0014A5A0 18186400 */  mult       $3, $3, $4
    /* 4A5A4 0014A5A4 2128A300 */  addu       $5, $5, $3
    /* 4A5A8 0014A5A8 5C01A48C */  lw         $4, 0x15C($5)
    /* 4A5AC 0014A5AC 02008610 */  beq        $4, $6, .L0014A5B8
    /* 4A5B0 0014A5B0 01000224 */   addiu     $2, $0, 0x1
.align 2
  .L0014A5B4:
    /* 4A5B4 0014A5B4 2D100000 */  daddu      $2, $0, $0
.align 2
  .L0014A5B8:
    /* 4A5B8 0014A5B8 0800E003 */  jr         $31
    /* 4A5BC 0014A5BC 00000000 */   nop
endlabel func_0014A560
```
