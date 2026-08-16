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
| F1 | `func_00244958` | `src/cod/vendor_2418A0` | 10 | 4 (opus, fable, opus, opus) | no match; best crutch-free rc3/sites3, best-overall rc2/sites2 but crutched. Re-enters the queue. Not parked, no floor claimed. |
| F2 | `fzShowV` | `src/fuzio` | 15 | 1 (opus) | **MATCHED** `3c0c6b00`, first compile rc0 |
| F3 | `func_001AE420` | `src/haveParentSimpleObj` | 16 | 1 (opus) | **MATCHED** `7a8bd3bb`, first compile rc0 |
| F4 | `func_001EACE8` | `src/spider` | 16 | 1 (opus) | running |

---

## F2 — `fzShowV` (`src/fuzio`, 15 insns)

ROM (read this session, `asm/nonmatchings/src/fuzio/fzShowV.s`, 0x3C bytes): materialises
`&DrawCollisionRay` and `&MakeExitAttributeIndex`, stores them to the gp-rel pair
`D_006323F0`/`D_006323F4`, and if the argument is non-zero overwrites the same pair with
`&func_00169F80`/`&func_0016A058`; returns 0. The second store of the pair sits in the `beq` delay
slot, so both arms write both words.

Prior work (found before launch): `decomp/port_ledger.md:1709` — an aug6 port was reverted with
"insn 9: expected `addiu v0,v0,0` built `addiu v0,v0,6448`", i.e. insn 9 came out as a literal where
ROM has a relocated symbol address. The next function in the TU, `fzShowM` @ 0x00168690, ported
successfully and is a close structural twin.

| # | edit | base | outcome |
|---|---|---|---|
| 1 | launch opus convergence worker, frozen brief, no target named, prior-port datum attached as a pointer | `INCLUDE_ASM` stub at `src/fuzio.c:22`, tree green at `fbf50c75…` | **MATCHED, rc0 on the first compile.** Committed `3c0c6b00`. |
| 1a | **supervisor verification (mine, not the self-report):** `rm build/src/fuzio.o` then full `.venv/bin/ninja` — ninja tracks neither the generated `.s` nor `compile_c.sh`, so a stale `.o` would have made the gate meaningless | worker's landed TU | `verify_elf: OK (fbf50c75cd5911273511c4f9af90503ff8423582)`. Oracle `status match / real_count 0 / diff_sites 0`. Crutch grep over the TU (pins, `__asm__`, register-vars): none. Sibling `func_0016A158` re-measured, still rc0. |

**Data model recovered.** `D_006323F0` / `D_006323F4` are a pair of collision-dispatch function
pointers, already typed as `int (*)(void *obj, int opcode)` in `src/fieldCollision.c:205,259` and
called there with opcodes 0–0x10. `fzShowV(mode)` is the debug-visualisation toggle for that pair:
it stores the plain implementations `DrawCollisionRay` / `MakeExitAttributeIndex`, then overwrites
both with `func_00169F80` / `func_0016A058` when `mode != 0` — and those two are wrappers that `jal`
the plain function and then draw a sprite (`gif_SpriteOffset`, sprite data at
`D_00559280`/`D_005592A0`). That is why ROM's "store the default pair unconditionally, then
conditionally store the debug pair" is the shape the dev wrote, with no reordering and no ternary.
The four stores are stores to real globals — the function's actual output — so they are legitimate,
not the dead-store class.

**The prior-port datum, explained.** `port_ledger.md:1709`'s "insn 9: expected `addiu v0,v0,0` built
`addiu v0,v0,6448`" is the signature of the callee addresses being written as integer constants
rather than as function designators. Declaring the four targets as real `extern` functions and
casting the designator makes gcc emit `lui %hi` / `addiu %lo` relocations, which is what ROM has.
No other lever was needed. Durable rule for the corpus: a literal where ROM has a relocation means
the symbol reached C as a number, not as a name.

The round also removed a now-redundant cast at the `D_006323F0` call site in the already-matched
`func_0016A158`; re-measured at rc0.

---

## F3 — `func_001AE420` (`src/haveParentSimpleObj`, 16 insns)

ROM (read this session): saves `s0`/`s1`/`ra`, moves `a1`→`s0` and `a2`→`s1`, tail-calls
`func_001ADED8` with `a1` replaced by `a3`, copies the result `v0`→`v1`, stores `s0` to `0x30(v1)`
and `s1` to `0x34(v1)`, and returns the result. No prior work exists on it.

| # | edit | base | outcome |
|---|---|---|---|
| 1 | launch opus convergence worker, frozen brief, no target named | `INCLUDE_ASM` stub, tree green at `fbf50c75…` | **MATCHED, rc0 on the first compile.** Committed `7a8bd3bb`. |
| 1a | **supervisor verification (mine):** `rm build/src/haveParentSimpleObj.o` then full `.venv/bin/ninja` | worker's landed TU | `verify_elf: OK (fbf50c75…)`; oracle `status match / rc 0 / diff_sites 0`; body is plain C, no pins, no dead stores. |

```c
extern int *func_001ADED8(int *self, int a1);

int *func_001AE420(int *self, int a1, int a2, int a3)
{
    int *p = func_001ADED8(self, a3);
    p[0xC] = a1;
    p[0xD] = a2;
    return p;
}
```

**Two reusable reads recovered here:**

- **Callee arity is 2, not 3.** ROM leaves `$6` untouched across the `jal`, which reads like a third
  argument being passed through. Reading the callee's own body settles it — `func_001ADED8` consumes
  only `$4` and `$5` (`sw $5,0xC($29)`); `$6` survives merely because a2 had already been copied to
  `$17`. Guessing three args would have produced a spurious arg-setup instruction.
- **`daddu $3,$2,$0` with `$2` never rewritten afterwards is what `return p;` compiles to**, NOT
  evidence of a void function storing directly off `$2`, and not an uncoalesced copy needing a
  move-back. The call result is already in the return register so the return copy is deleted, and
  the copy that survives is the *store base*. Reusable for the
  `p = f(...); p->a = x; p->b = y; return p;` shape.

Call-site evidence for the signature: `src/enemy_act.c:467` and `src/boyact.c:923` call it as
`(self, 7, 0, D_00631990)` / `(x, 0, 0, D_00631990)`, so a3 is the id the callee stores at `0xC($sp)`.
Field note: the object's `0x30`/`0x34` word pair is the start of a sub-struct, not two unrelated
scalars — matched sibling `func_001AE460` passes `result + 0x30` as arg 0 to the per-type handler at
`D_002A31B8[obj->0xC * 0x64] + 0x3C`. `int *p` with `p[0xC]`/`p[0xD]` matched, so no struct type was
needed.

**Measurement trap confirmed in this TU:** `quick_diff` showed one residual line,
`jal 0 <func_001AE420>` vs `jal 1a20 <func_001ADED8>`. That is the in-TU relocation false-negative —
`func_001ADED8` is still `INCLUDE_ASM` in the same TU, so the built side resolves the call locally
while the target `.s` carries an unresolved reloc. `match_diff` scored it
`raw_count 1 / real_count 0 / diff_sites 0` and ninja confirmed. Do not chase that line on other
functions in this TU that call `func_001ADED8`.

---

## F4 — `func_001EACE8` (`src/spider`, 16 insns)

ROM (read this session): loads `0x15C(a0)` then `0x800` off that, stores 1 to `0x3C` of the result,
calls `func_001AE460`, then tail-calls `debug_assertMessage(&D_006335E0, a0->0x8)` via `j`. No prior
work exists on it.

| # | edit | base | outcome |
|---|---|---|---|
| 1 | launch opus convergence worker, frozen brief, no target named; in-TU `jal` false-negative noted in the measurement traps | `INCLUDE_ASM` stub, tree green at `fbf50c75…` | pending |

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
| 2 | relaunch on **fable** — the user's escalation rule for stuck, and this is the "constraint known, form unknown" case: the round left a sharp, fully-characterised live-range question rather than an open search | frontier above (rc2/sites2, crutched) with the TU at `INCLUDE_ASM` | **rc3 / sites3, size 11 vs ROM's 10.** Crutch-free (the volatile MMIO body) but a regression on both sites and size. Stashed, not committed. |
| 2a | **supervisor re-measurement + CORRECTION.** The worker reported "the built stream is the SAME 10 instructions as ROM… a pure permutation"; its own inline code comment in the same round said "12 insns vs ROM's 10". Both are wrong. I ran `quick_diff` on its state: built is **11** instructions, ROM is 10. | worker's landed TU state | The extra insn is the `beq`'s empty delay slot: built emits `lw v0,0(v0)` *before* the `beq`, then `nop` in the slot, then `nop` again after `jr`. Not a permutation — a real +1. |
| 2b | STRUCTURAL RULING (mine, on the round's own evidence): the volatile branch is a **dead end**, not the standing crutch-free state the worker proposed | both frontiers | The round source-read `reorg.c:262-271` + `resource.c:223` and established that `resource_conflicts_p` conflicts on `volatil` on *either* side, so a volatile trial insn can NEVER fill any delay slot. ROM's slot is filled. Therefore the volatile shape cannot reach 0 by its own measured mechanism, at any count. Per structure-over-count, the live branch is the NON-volatile one from round 1, which already reproduces the filled slot. Declining the "adopt volatile as standing state" proposal. |
| 2c | TU restored to `INCLUDE_ASM`; crutch-free frontier stashed at `tough_nuts/delayslot_unfilled/vendor_2418A0_func_00244958_frontier_rc3_volatile_CRUTCHFREE.c` | — | Tree was RED under the worker's state (`actual ed9063ed…` vs `expected fbf50c75…`) — a non-matching body cannot be left in the tree. After restore: `verify_elf: OK (fbf50c75…)`. |

**Round 2 durable mechanisms** (source-read or compiled; notes + dumps at `scratchpad/r958c/`):

- `mips.h CONST_COSTS` hardwires CONST_INT cost to 0 (non-MIPS16), so cse always canonicalises a
  computable pointer value to `(set p CONST_INT)`. No cost escape. Label opacity is not available
  under ROM's single-branch CFG either — a `do{}while(0)` label dies at `jump1` (compiled).
- `gcse.c cprop_insn` propagates only CONST_INT / CONST_DOUBLE / reg-copy sources. A `symbol_ref`
  def is cprop-invisible but materialises as `lui/addiu`, and ROM's byte is `ori` (opcode 0x34) —
  so that escape is dead on bytes. `(mem (plus p k))` blocks cprop but shows `k` in the `lw` offset
  field, and ROM's offset is 0.
- The `reorg.c` / `resource.c` volatile veto above. (`resource.c:223` is `=` not `|=`, but no MIPS
  single-SET insn carries two MEMs, so that is unexploitable.)
- The rc2 write-back survives to `greg` and is deleted by `reload_cse` as a no-op store; it protects
  the load from combine, and its post-load pointer use is exactly what forfeits the `$2` coalesce.
- Compiled dead this round: DI-carrier addresses (collapse at expand for constants); uninitialised
  `old` (live-at-entry makes `old` conflict with sentinel and pointer, so ROM's `lw v0,0(v0)`
  requires `old` defined on all paths); a 4-byte extern store goes gp-rel under `-G8`.

**Partition the two rounds jointly establish** for the slot insn `lw $2,0($2)`: same-block + dying →
combine folds to the slot-ineligible macro; same-block + live-past → the rc2 conflict (dest ≠ `$2`);
cross-block + B0 def → cprop folds; cross-block + local def → a miniature of the same two;
symbol / plus / DI / volatile → wrong bytes or unslottable. ~60 shapes compiled across four rounds
all land in it. Recorded as a description of what has been compiled, NOT as a boundary — the route
that reconstructs ROM's layout end-to-end (two-arm loads + reorg thread-steal redundancy) has cprop
as its only blocker and was left explicitly open by the round.

| # | edit | base | outcome |
|---|---|---|---|
| 3 | relaunch on **opus** with the corrected size measurement and the volatile-branch ruling | crutched rc2/size-10 and crutch-free rc3/size-11 frontiers, TU at `INCLUDE_ASM`, tree green | `budget: rc3 sites3`, no match. Stub restored by the worker, tree green, probes at `scratchpad/r958d/`. Independently re-derived my 11-vs-10 size figure by assembling the standalone `.s` and objdumping it. |

### Round 3 — my own ruling was partly WRONG, correcting it here

**Row 2b is partly refuted, and the error was mine.** I closed the volatile branch as a "domain
ruling" on the strength of round 2's source read of `reorg.c`/`resource.c`, without measuring it —
exactly the failure the orchestration reference warns about. Round 3 compiled it:

- **REFUTED:** a volatile insn *can* fill a delay slot. `scratchpad/r958d/c.c f2` compiles to
  `bnel $4,$2,$L5` with a **volatile `sw $4,0($5)` in the annulled slot** (the eager/thread path).
  My "never fills any delay slot at any count" was wrong as stated.
- **CONFIRMED for the path that matters:** `fill_simple_delay_slots`' steal-from-before never takes
  a volatile memory op, load or store, across 8 probes (volatile load before `beq`, before `jal`,
  before `j`/tail; volatile store before `jr $31` and before a tail call). The non-volatile twin
  fills every time. Mechanism at `reorg.c:2141` `!insn_references_resource_p(trial,&set,1)` plus
  `resource_conflicts_p`'s unconditional `res1->volatil || res2->volatil`.

So the *conclusion* (the live branch is the non-volatile one) survives, because ROM's slot is filled
by a steal-from-before and not by an annulled branch. The *ruling as I phrased it* did not. Narrow
it to: steal-from-before never takes a volatile memory op.

### Round 3 durable mechanisms

- **NEW — combine reaches only the FIRST same-block use.** `flow.c:3387`
  `if (y && (BLOCK_NUM(y) == blocknum) …)` with `y = reg_next_use[regno]`: LOG_LINKS go to the first
  subsequent use and never cross a basic block. This is *why* the matched sibling `func_00254CF8`
  matches — two same-block uses, so the load is LOG_LINK'd and refused by `added_sets_2`, and the
  store has no LOG_LINK at all, so neither folds. Reusable rule, belongs in the cookbook.
- `explow.c memory_address` force_regs every constant address at expand, so both accesses *start*
  register-form; the macro forms are later folds. Cross-block use → cprop folds it (and cprop folds
  volatile MEMs too, loads and stores, compiled). Same-block use → `combine.c:1600`
  `added_sets_2 = !dead_or_set_p(i3,i2dest)`; when 0 the fold recogs, because `mips.h
  GO_IF_LEGITIMATE_ADDRESS` accepts `CONSTANT_ADDRESS_P` for every mode except
  `TARGET_MIPS5900 && TImode`.
- Same-source A/B proving the register form is what is at stake: `func_00254CF8` verbatim →
  register-form non-volatile `lw`/`sw` with the `sw` in the `jr` slot; the *same body with a branch
  added* → both collapse to the macro form.
- 8 further spellings compiled dead (`scratchpad/r958d/e.c` sA–sH): named pointer, one-variable
  reuse, arm-local pointer, early-return CFG, array-typed extern store, `p[0]`, signed `int`,
  aliased second pointer — all give `lw $3,268492896`.
- Left explicitly open (model-derived, nothing compiled): `res->volatil = MEM_VOLATILE_P(x)` is an
  assignment, not `|=`, so a later-traversed non-volatile MEM in the same insn clears the flag. No
  MIPS single insn carrying a volatile MEM then a non-volatile one could be constructed from C.
- cprop is genuinely blocked when `find_avail_set` finds no set available at the use's block entry,
  which needs ≥2 defs of the pointer reaching that block. ROM itself does this at `func_00254D20`
  0x254D8C/0x254DAC. For *this* function it costs an extra `lui` (11 insns), so it is closed by
  instruction count **for func_00244958 only** — it stays live for family members with room.

### Round 3's biggest finding — an 18-site FAMILY — with my correction

A register-matched ROM scan for a delay-slot memory op whose base is built by a `lui/ori` of a
`0x1xxxxxxx` MMIO constant returns **18 sites in 8 functions, all under `src/cod/vendor_*`**:
`func_00242640` ×11, `func_00244958`, `func_00242F70`, `func_00252C68` ×2, `func_002581C0`,
`func_00257F28`, `func_002525E8`, `func_001010C8`.

**Correction (mine, verified this session):** the round reported "0 of the 8 are matched". That is
wrong, and the exception is the important one. I checked each of the 8 in the TU sources:

| function | insns | state |
|---|---|---|
| `func_001010C8` | 14 | **MATCHED — real C at `src/cod/vendor_100C90.c:127`** |
| `func_00252C68` | 48 | stub, `src/cod/vendor_2517D0.c` |
| `func_002525E8` | 54 | stub, `src/cod/vendor_2517D0.c` |
| `func_00257F28` | 112 | stub, `src/cod/vendor_2575C0.c` |
| `func_002581C0` | 150 | stub, `src/cod/vendor_2575C0.c` |
| `func_00242640` | 239 | stub, `src/cod/vendor_2418A0.c` |
| `func_00242F70` | 491 | stub, `src/cod/vendor_2418A0.c` |

The scan was run over `asm/nonmatchings`, which is never pruned — a matched function keeps a stale
orphan `.s` there (see the `stale_matchings` note), which is how a matched function was counted as
unmatched. **`func_001010C8` is an answer key for this family, not a member of the backlog.**

Its ROM is the same signature — `lui $3,0x1000 / ori $3,$3,0xF130 / lw $2,0($3)` with offset 0, a
poll loop, then `jr $31` with a **non-volatile** `sb $4,0x0($3)` in the slot — and the matching C is:

```c
int func_001010C8(int c) {
    unsigned int base;
    do { base = 0x10000000; } while (*(volatile unsigned int *)(base | 0xF130) & 0x8000);
    *(unsigned char *)(base | 0xF180) = c;
    return c;
}
```

i.e. the address reaches codegen as **`base | offset`, an `ior` of a pseudo with an immediate**, not
as a cast constant. `(mem (ior reg imm))` is not a legitimate address, so the `ior` must be computed
into a register — which is exactly ROM's `ori` + offset-0 memory op, and it is what leaves a plain
non-volatile op for reorg to steal. Note the two rounds disagree about *why* it survives: the TU
comment credits cse + REG_EQUAL + loop.c hoisting + reload rematerialisation, while the 2026-08-05
handoff explicitly corrects that to "`base`'s def sits inside the do-while, the multi-pred loop-top
label ends cse's EBB, so `base` is unknown at the post-loop `ior`". Both accounts agree on the
operative fact — the `ior` survives as a real `(ior reg imm)` — and both are unverified by me.

| # | edit | base | outcome |
|---|---|---|---|
| 4 | relaunch on **opus** carrying the `func_001010C8` answer key and the corrected family table. Justification for a 4th round rather than rotating the chain: this is new structural information no prior round had — a *matched* sibling with this exact ROM signature — and the user's standing rule is that structure wins between rounds. Rotating unconditionally after this one. | both frontiers, TU at `INCLUDE_ASM`, tree green | `budget: rc3 sites3`, no match, nothing banked. TU restored clean, tree green (verified by me). Probes at `scratchpad/r958e/`, including `sib/` with the matched sibling's full `-da` dumps. Densest round so far on mechanism. |

### Round 4 — which pass folds what, finally measured rather than inherited

From `-da` dumps of the plain non-volatile body: the load is still `(mem:SI (reg 85))` at `.cse`,
`.gcse`, `.loop`, `.cse2` and `.flow`, while the store is already `(mem:SI (const_int 268492896))`
at `.gcse`. At `.flow` the load carries `LOG_LINK (insn_list 10)`. So **combine folds the load and
cprop folds the store**, and ROM's asymmetry is exactly "same-block load + cross-block store".
cse leaves a *bare reg* address alone because `find_best_addr` needs a strict cost improvement and
mips `CONST_COSTS` gives CONST_INT cost 0 while `rtx_cost(REG)` is also 0.

**Why `volatile` blocks combine** (source-read, `combine.c:500`/`:678`): `combine_instructions`
calls `init_recog_no_volatile()` on entry, so with `volatile_ok == 0` `general_operand` rejects any
volatile MEM and `recog_for_combine` fails on `(set (reg) (mem/v (const_int)))`. That one line is
the whole reason frontier B keeps register form.

**LOG_LINK is created only for the FIRST use** (`flow.c:3376-3390`): `y = reg_next_use[regno]` and
only `if (y && BLOCK_NUM(y) == blocknum)`. Therefore a use of `p` positioned **before** the load
absorbs the link, blocks combine on the load, and does *not* extend `p` past the load — so
`lw v0,0(v0)` with dest coalesced onto base stays reachable. Compiled proof, `scratchpad/r958e/g.s`
g3 (`*qq = p;` before the load): register-form `lw $6,0($2)` **plus** ROM's `sw $4,268492896` macro
store — ROM's exact asymmetry, non-volatile. It costs an instruction, so it is a proof of the
mechanism, not a match.

**Five non-volatile shapes that produce a register-form, length-1, delay-slot-fillable const
address** via `added_sets_2` (an address pseudo with ≥2 uses), e.g. `g.s` g6
(`li $3,268435456 / ori $3,$3,0xe060 / lw $2,0($3) / j $31 / sw $4,0($3)`). One of them, `w.s`
w3/w4, **reproduces family member `func_00242640`'s `lui/ori/jal/lw $5,0($3)` shape in form** — so
that function's residual is a two-use base pointer, not volatility.

**The `base | offset` mechanism, decoded from the matched sibling** (its C compiled with `-da`,
dumps at `scratchpad/r958e/sib/`): the `ior` is never folded, because cse can't (the ior sits in a
cse block where `base` is unknown), cprop can't (`(ior const const)` fails `iorsi3`'s
`register_operand`), and combine can't (`(mem (ior …))` is not a legitimate MIPS address, and
`base`'s def is cross-block so there is no LOG_LINK). Critically, **the cse-block boundary is a
LABEL / branch TARGET, not a fallthrough** — measured: an ior in the entry block or in the
fallthrough arm folds to the macro; an ior in the branch-*target* arm survives as
`ori $3,$3,0xe060 / lw $2,0($3)`. Consequence: `func_00244958`'s `ori $2,$2,0xE060` is in the
**entry** block and therefore cannot be an unfolded ior — it is the post-reload `large_int`
define_split of `(set p (const_int 0x1000E060))`, sched2-interleaved against the sentinel's split,
which is what produces ROM's `lui/lui/ori/ori` order.

**TImode quirk** (`mips.h:3004`): `GO_IF_LEGITIMATE_ADDRESS` excludes `TARGET_MIPS5900 && TImode`,
so a 128-bit access to a constant address is forced into a register and **does fill a `jr` slot**,
non-volatile (compiled, `h.s` h3/h4). A general lever for TI-mode MMIO; it does not reach a `lw`.

**Corpus claims refuted by compile this round:**
- "`(mem (plus p k))` with k≠0 blocks cprop" — false. cse's `find_best_addr` prefers the constant
  over `(plus reg const)` because the plus has nonzero cost, so the plus never survives to cprop.
  Only a *bare* reg address survives cse.
- "the volatile veto is total in every filler" — right for a volatile LOAD, wrong for a volatile
  STORE. `resource.c`'s `case SET` in `mark_referenced_resources` marks only the dest MEM's
  *address*, never the MEM, so a volatile store contributes `volatil = 0` there. A volatile load
  gets `volatil = 1` via `case MEM` and is vetoed in every filler.
- The round also retracted one of its own supporting probes (`v.s` v1) as not proving the veto —
  reorg's backward scan took a closer insn and never tried the volatile load.

Shapes closed by compile this round (`scratchpad/r958e/{g,h,w,x,y,z}`), all giving the length-2
dbr-ineligible macro load: plain non-volatile pointer; `x = *(u_int*)x`; separate bare-const store;
struct base+offset; `const`-qualified pointer; pointer-to-array; DI carrier; a second def of `p`
before or after the load; two-arm with the def in B0; two-arm with the def duplicated per arm;
`b=0x10000000; *(u_int*)(b|0xE060)` in the entry block; one pointer variable reassigned before each
of several uses; a `static` helper and two `__inline__` helper spellings. Notable: an out-of-line
`SetReg(u_int *p, u_int v)` helper compiles to **ROM's exact control shape** (`beq $5,$2,$L3` with
`lw $3,0($4)` in the slot, non-volatile) purely because an incoming parameter is unfoldable.

**Residual as the round left it.** ROM needs, at combine: `(set p (const_int 0x1000E060))` unfolded,
`p` dying at the load (so `lw v0,0(v0)` coalesces), and the store already `(mem (const_int))`. Two
configurations are known to produce that asymmetry and each pays: (i) volatile pointer — combine
blocked, but reorg vetoes volatile loads, so the fill is lost (= frontier B, sites3); (ii)
non-volatile plus an extra `p`-use *after* the load, deleted at greg by `reload_cse` — the fill
survives but forces `lw a1` + `daddu` (= frontier A, sites2, crutched). The un-searched middle is
finding #4: a `p`-use *before* the load keeps both. None was found that emits no instruction, and
none was compiled. Left open, explicitly labelled as not-compiled.

---

## Chain routing decision after F1 round 4

Rotating the chain, as stated before round 4 was launched. F1 is **not parked** — no floor is being
claimed, both frontiers and the full mechanism map are recorded above, and it re-enters the queue.
Four rounds on one 10-instruction function is already disproportionate against a 151-function
smallest-first queue.

**Ordering rule applied to the 16-instruction tie group** (stated so it is not a silent skip):
`func_002453D0` (`src/cod/vendor_2453C0`) is deferred within its tie group because it is another
`src/cod/vendor_*` MMIO body — a poll loop on `0x1000F000` with three `nop`s — i.e. the same class
the last four rounds failed to crack, and it would re-enter the identical wall immediately. It stays
in the queue, flagged family-class. The non-MMIO members of the tie group go first.

---

## Round 0 — chain setup (supervisor)

| edit | base | outcome |
|---|---|---|
| `git checkout src/motionFileManager.c` (drop uncommitted ResetStatic2MotionManager body; seed preserved at `tough_nuts/ResetStatic2MotionManager/`) | working tree at `e7c6e38e` + 1205-line uncommitted RSM body | tree clean; `.venv/bin/ninja` → `verify_elf: OK (fbf50c75…)` |
| Target list built: 1929 `INCLUDE_ASM` stubs in `src/`, insn-counted from `asm/nonmatchings/<tu>/<fn>.s`, parked names removed | clean tree | 1870 fresh, 174 at ≤30 insns |
| **BRIEF EDIT (deliberate policy change, logged per doctrine):** added a `{{PRIOR}}` field to the CORPUS section of `scratchpad/BRIEF_TEMPLATE.md` | template as first written (round 1 sent without it) | Cause: round 1 was launched at `func_00244958` before I found two documented prior rounds on it (`tough_nuts/delayslot_unfilled/HANDOFF_vendor_2418A0.md`, committed `9e029ae0`). A missing corpus pointer costs a worker a whole re-derivation. Prior-work index now built by grepping `func_XXXXXXXX` tokens out of all of `tough_nuts/` + `docs/MATCHING_NOTES.md` (958 names); 23 of the 174 ≤30-insn targets carry prior work. Field is a POINTER only — the accompanying text states its conclusions are worth zero. |
