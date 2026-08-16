# Convergence chain ledger — smallest-unmatched (retail `main`)

**Supervisor-only.** Workers may READ this file; only the orchestrator writes to it.
One section per function. Every row is `(edit, base) -> outcome`, base mandatory.
Refutations and inert results are first-class rows.

Chain started 2026-08-16. Policy from the user, verbatim:
> chaining the smallest unmatched funcs on opus (fable if it gets stuck). keep
> ledger entries for each func. dont stop for any reason. no crutches. structure
> wins over any other heuristics between rounds.

## Fixed frame

- Branch `main` (retail, SLUS-20218). Baseline ELF sha1 `fbf50c75cd5911273511c4f9af90503ff8423582`, green at chain start.
- Oracle: `.venv/bin/python tools/match_diff.py <TU> <func>` — `diff_sites` drives, `real_count` weakest.
- Gate: `.venv/bin/ninja` byte-identical ELF. An `INCLUDE_ASM` stub reports rc0/0 sites — verified this
  session on `src/haveParentSimpleObj func_001AE420` (stub) → `"status":"match","real_count":0`. That is
  the measurement trap, not a match.
- Target list: `scratchpad/targets_fresh.txt` (insn-count, TU, func), smallest-first, parked funcs excluded
  (`docs/MATCHING_NOTES.md` func tokens ∪ `config/sweep_parked.txt` ∪ `tough_nuts/*`). 1870 fresh stubs
  total, 174 at ≤30 insns.
- Worker brief frozen at `scratchpad/BRIEF_TEMPLATE.md`; only the base fields are substituted per round.

## Chain roll-up

| # | func | TU | insns | rounds | outcome |
|---|---|---|---|---|---|

---

## F1 — `func_00244958` (`src/cod/vendor_2418A0`, 10 insns)

ROM (read this session, `asm/nonmatchings/src/cod/vendor_2418A0/func_00244958.s`, 0x28 bytes):

```
lui $2,0x1000 / lui $3,0xffff / ori $2,$2,0xe060 / ori $3,$3,0xffff
beq $4,$3,.L00244978
 lw $2,0x0($2)              <- the load is IN the beq delay slot, register-form address
lui $1,0x1001 / sw $4,-0x1FA0($1)
.L00244978: jr $31 / nop
```

Prior work found AFTER launching round 1 (committed `9e029ae0`, `c526fd73` era):
`tough_nuts/delayslot_unfilled/HANDOFF_vendor_2418A0.md`. Its durable measured content, as
recorded there (NOT re-verified by me this session — flagged as inherited):
Rule A, gcc reorg refuses a volatile MEM in a delay slot; Rule B, a *non-volatile* SImode load
from a large constant address folds to the 2-insn gas macro `lw $r,<abs>` and is therefore
reorg-ineligible. The document's own conclusion ("unreachable from plain C", "stays INCLUDE_ASM")
is a prohibition and carries no weight in this chain. It also contains a self-correction
overturning its own earlier `func_001010C8` mechanism claim.

| # | edit | base | outcome |
|---|---|---|---|
| 1 | launch opus convergence worker, frozen brief, no target named | `INCLUDE_ASM` stub, tree green at `fbf50c75…` | **sites 0→2, rc 2, size 10 == ROM's 10.** Prior rounds' "unreachable from plain C / stays INCLUDE_ASM" verdict REFUTED by compile. |
| 1a | supervisor message: corpus pointer to the prior-round handoff + the standing one-assembler frame (ee-as 2.9-991111 fills no delay slots; a 2.96 explanation is a closed domain) | same | sent mid-round |
| 1b | **supervisor re-measurement (I spliced the worker's seed into the TU myself and ran the oracle — did NOT take the self-report):** `unsigned int func_00244958(unsigned int a0){ unsigned int *p=(unsigned int*)0x1000E060; unsigned int old=*p; *p=old; if(a0!=0xFFFFFFFFu) *p=a0; return old; }` | `INCLUDE_ASM` stub | CONFIRMED `real_count 2 / diff_sites 2`, built stream exactly 10 insns. Insns 1-4 (`lui v0,0x1000 / lui v1,0xffff / ori v0,v0,0xe060 / ori v1,v1,0xffff`), the `beq`, the **`lw` inside the beq delay slot**, and the `$at` macro store `sw a0,-8096(at)` are all byte-identical to ROM. |
| 1c | crutch audit of that seed (mine, against the full CLAUDE.md definition) | seed above | **REJECTED for commit.** `*p = old;` emits ZERO instructions — I diffed the built stream and there is no store insn for it anywhere — while changing register allocation. That is exactly the banned zero-code dead-store class. Worker flagged it itself and did not bank it; correct call. |
| 1d | TU restored to `INCLUDE_ASM`, frontier preserved at `tough_nuts/delayslot_unfilled/vendor_2418A0_func_00244958_frontier_rc2_CRUTCHED.c` | — | `.venv/bin/ninja` → `verify_elf: OK (fbf50c75…)` |

**Residual after round 1, measured by me (expected \| built):**

```
lw   v0,0(v0)      |  lw    a1,0(v0)       <- beq delay slot, both sides
sll  zero,zero,0x0 |  daddu v0,a1,zero     <- jr delay slot
```

Two lines, one cause: the load's destination is not coalesced onto the pointer's hard register,
so the return value needs a copy in the `jr` slot. ROM's `lw v0,0(v0)` proves the pointer is dead
at the load there.

**Mechanism the round established (worker-measured with `-da` dumps kept at `scratchpad/r958b/`;
I verified the end-to-end result, not each dump):**

- The load/store asymmetry ROM shows is a cprop/combine split. `gcse.c cprop_insn` uses
  `find_avail_set` (block-entry availability) and never runs on block 0, so the block-1 store's
  pointer use is folded to `(mem (const_int))` → the `$at` macro store. That is where ROM's macro
  store comes from, and it folds volatile stores too, so volatility is not a lever there.
- The block-0 load is cprop-immune (its def is same-block). Its only enemy is `combine`, via
  `added_sets_2 = !dead_or_set_p(i3, i2dest)`. Any block-0 reference to the pointer besides the
  load flips `added_sets_2` to 1, the resulting `PARALLEL [(set d (mem C)) (set p C)]` fails recog,
  the fold is refused, and the register form survives to reorg — which then takes it, because a
  length-1 non-volatile insn is no longer vetoed by `resource_conflicts_p`.
- Why the crutch works and why it cannot be kept: the dead store is live through
  `combine`/`regmove`/`sched`/`lreg` and is only deleted at `greg`. It blocks the fold *and*
  keeps the pointer live past the load, which is precisely what costs the coalesce.
- Closed by fresh compile in that round (measurements, not prohibitions): shared plain pointer;
  volatile store via pointer; volatile store via bare const; carrier copy after the load; two
  independent const pointers; self-overwrite; write-back placed *before* the load; else-arm
  write-back (emits a real `sw` + `b`); argument-normalise and ternary forms (both collapse to
  `movz`/`movn`, single BB, no branch at all).
- A use placed *between* the const-set and the load blocks combine while the pointer still dies at
  the load (worker probe `pf.c` t6 → `li/ori/lw $2,0($3)`, register form) — but every such use
  constructed either emitted an instruction or got scheduled after the load into the slot.

**Precedent the round found (independently checkable):** `func_00254CF8` at
`src/cod/vendor_2517D0.c:1557` is already byte-matched from plain C with the same ROM signature —
interleaved `lui/lui/ori/ori`, register-form constant address, memory op in a delay slot — as
`int *reg = (int *)0x10002010; *reg = (*reg & 0xFF7FFFFF) | (a0 << 23);`. Its mechanism is the
single-basic-block case (`gcse_main` early-returns on `n_basic_blocks <= 1`, so cprop never runs
and both pointer uses survive). The dev idiom in this vendor library is a plain, **non-volatile**
`int *reg = (int *)ADDR;`. A ROM-wide scan for a register-form constant-address memory op in a
delay slot returned 19 sites, all in `src/cod/vendor_*`.

| # | edit | base | outcome |
|---|---|---|---|
| 2 | relaunch on **fable** — the user's escalation rule for stuck, and this is the "constraint known, form unknown" case: the round left a sharp, fully-characterised live-range question rather than an open search | frontier above (rc2/sites2, crutched) with the TU at `INCLUDE_ASM` | pending |

---

## Round 0 — chain setup (supervisor)

| edit | base | outcome |
|---|---|---|
| `git checkout src/motionFileManager.c` (drop uncommitted ResetStatic2MotionManager body; seed preserved at `tough_nuts/ResetStatic2MotionManager/`) | working tree at `e7c6e38e` + 1205-line uncommitted RSM body | tree clean; `.venv/bin/ninja` → `verify_elf: OK (fbf50c75…)` |
| Target list built: 1929 `INCLUDE_ASM` stubs in `src/`, insn-counted from `asm/nonmatchings/<tu>/<fn>.s`, parked names removed | clean tree | 1870 fresh, 174 at ≤30 insns |
| **BRIEF EDIT (deliberate policy change, logged per doctrine):** added a `{{PRIOR}}` field to the CORPUS section of `scratchpad/BRIEF_TEMPLATE.md` | template as first written (round 1 sent without it) | Cause: round 1 was launched at `func_00244958` before I found two documented prior rounds on it (`tough_nuts/delayslot_unfilled/HANDOFF_vendor_2418A0.md`, committed `9e029ae0`). A missing corpus pointer costs a worker a whole re-derivation. Prior-work index now built by grepping `func_XXXXXXXX` tokens out of all of `tough_nuts/` + `docs/MATCHING_NOTES.md` (958 names); 23 of the 174 ≤30-insn targets carry prior work. Field is a POINTER only — the accompanying text states its conclusions are worth zero. |
