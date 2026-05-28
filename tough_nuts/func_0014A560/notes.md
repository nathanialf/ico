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
