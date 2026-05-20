# Matching notes

Per-function deferred targets and tough nuts. Empty at init; populated as
matching work proceeds.

Each entry should record:

- The function (VRAM address, name if known).
- The failure mode (regalloc divergence, scheduling, missing opcode in
  m2c, …).
- The best diff state achieved (permuter plateau score if applicable).
- Structural hints learned from the asm.
- Where the current best attempt is parked (`tough_nuts/<name>/`).

## Parked

- **func_00105278** / **func_00105290** — array-base + index-shifted
  address pattern. ee-gcc emits 64-bit `la` macro expansion (daddiu/
  daddu); original uses 32-bit addiu/addu with different instruction
  order. Likely needs a non-ee-gcc compiler (Pro-DG/wcc or CodeWarrior)
  or a gas option to force 32-bit `la`. See
  `tough_nuts/func_00105278/notes.md`.

## Skipped

Entries here are functions whose match was reverted with an explicit
"do not re-attempt this way" tag. Don't pick these up without first
reading the skip rationale and addressing it.

- **func_00198218** (`src/itou_boss.c`, capsule-array initializer) —
  reverted in commit `c5d5bf6` (revert of `634bfd3`). The C body in
  the reverted commit was structurally correct (alloc via
  `func_0013A0F8`, then `func_00202208(self)` + `func_00202148(self)`
  + `func_001A6E28("N_CAPSULE %d\n", 53)`, then a 53-iter loop over
  `D_006D35F0[i*0x40]` / `D_0055B030[i*0x40]` / `D_0055BD40[i*0x10]`
  with conditional capsule-state init), but it only byte-matched with
  a per-function postprocess (`tools/postprocess_itou_boss.py`) that
  collapsed `addiu $tN, $tN, %lo(SYM); move $sM, $tN` into
  `addiu $sM, $tN, %lo(SYM)`. That fold is **unsafe in general**: it
  leaves `$tN` holding only the high half of SYM, so any later read
  of `$tN` (e.g. a peer `addu $sP, $tN, K`) would compute the wrong
  address. It only worked for this function because the C's REG pins
  happened to make `$tN` dead immediately after the move — a
  precondition the rewriter doesn't verify, and any future edit to
  the C body could silently break the load addresses elsewhere.

  Acceptable resolutions for a future attempt:
  1. Make the postprocess safe in general — scan forward from the
     move to confirm `$tN` is dead before collapsing, OR scope the
     match tighter than basename-based dispatch (e.g. a sed gated on
     a specific surrounding context).
  2. Find a C structure / gcc flag combination that emits the
     expected `lui $temp; addiu $sM, $temp, lo` shape natively. The
     reverted attempt used `register T *base REG("$3")` plus
     `KEEP_LIVE(base)` after the s0 assignment — got the address-mat
     shape right but left a ~8-byte gap on prologue instruction
     count that no other C reformulation closed.
  3. Switch this TU to a different compiler if/when a non-ee-gcc
     compiler matches the rest of the codebase — see the
     `func_00105278` note above for the same hypothesis.

  Diff at last attempt was ~10 instructions of pure scheduling order
  (prologue save sequence, address-materialization layout, loop-body
  delay-slot fill). C body + postprocess were reverted together so
  the next attempt starts from a clean slate; don't re-introduce the
  current `postprocess_itou_boss.py` without fixing the safety gap.
