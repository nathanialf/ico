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
| F4 | `func_001EACE8` | `src/spider` | 16 | 1 (opus) | **MATCHED** `8b518218`, first compile rc0 |
| F5 | `reallocseki` | `src/Basic` | 17 | 1 (opus) | **MATCHED** `337953bb`, first compile rc0 |
| F6 | `func_0010EC08` | `src/DisplayP2O` | 18 | 1 (opus) | **MATCHED** `7d7c4a7d`, first compile rc0 |
| F7 | `func_001186C8` | `src/MicroCode` | 18 | 1 (opus) | **MATCHED** `a5226391`, first compile rc0 |
| F8 | `func_0023B170` | `src/access` | 18 | 1 (opus) | **MATCHED** `05a8dc8f`, first compile rc0 |
| F9 | `src/access` family (19 stubs, 18–48 insns) | `src/access` | — | 1 (opus) | **ALL 19 MATCHED** `6c0c0e47`; TU now 100% C |
| F10 | `src/st05d` family (9 stubs) | `src/st05d` | — | 1 (opus) | **ALL 9 MATCHED** `06e290fe`; TU now 100% C |
| F11 | `src/st17a` family (26 stubs) | `src/st17a` | — | 1 (opus) | **25 of 26 MATCHED** `36b2a88b` |
| F12 | `func_0022DBC8` | `src/st17a` | 132 | 1 (opus) | **MATCHED** `42f45a6c`; `src/st17a.c` now 26/26 |
| F13 | `src/keyInput` family (17 stubs) | `src/keyInput` | — | 1 (opus) | **10 of 17 MATCHED** `68a23262` |
| F14 | `src/keyInput` remaining 7 | `src/keyInput` | — | 1 (opus) | **1 MATCHED** `aa7c8fae`; 6 left |
| F15 | `src/st24a` family (15 stubs) | `src/st24a` | — | 1 (opus) | running |

### F14 result — `func_00104940` matched, and the register-variable question settled properly

**Verification (mine):** `rm build/src/keyInput.o`, full ninja → `verify_elf: OK (fbf50c75…)`;
6 stubs left.

**Mechanism.** `local-alloc.c:block_alloc` records a hard-reg *suggestion* on **every** operand of an
insn whose operand 0 is a hard register — `combine_regs` returns 0 for a hard `setreg`, so the
operand loop never `break`s. The suggestion pass is sorted by
`QTY_CMP_SUGG = num_copy_sugg ? num_copy_sugg : num_sugg * FIRST_PSEUDO_REGISTER`, **lowest first**.
With `register float dot __asm__("$f20")`, `neg.s pseudo,$f20` gives the neg-result qty a *second*
suggestion, so it sorts at 152 against the zero constant's 76 — the zero is allocated first, steals
`$f12`, and the neg falls through to `$f0`. Removing the hard-reg **source** of the `neg` fixes it.

**The fix is also the cleanest available form.** Binding the result through a real operand-carrying
asm lets gcc pick the registers itself:

```c
float dot; int v0;
__asm__ __volatile__("qmfc2.ni %0, $vf3" : "=r"(v0));
__asm__ __volatile__("mtc1 %1, %0" : "=f"(dot) : "r"(v0));
```

**Supervisor follow-up: I converted the other two VU0 leaves to this form and re-verified.** Both
`func_001048C8` and `func_001049C0` stayed byte-identical (forced rebuild after each), and
`src/keyInput.c` now contains **zero** register variables. So the ruling in F13 stands but is now
moot for this TU — nothing in it sits anywhere near the pin ban. Committed `9c9bcd17`.

**Standing preference from here:** read a VU0 result through an operand-carrying `__asm__` with
ordinary locals, not a `register T x __asm__("$fN")` variable. Added to the worker brief.
The committed precedents in `src/pool.c` and `src/clothTest.c` still use the register form, and
`src/pool.c:26` uses the **initialized** spelling which is the banned one — untouched here, recorded
as debt.

**`ExecKeyInput` went 4 sites → 3 with the structure now exact**, via a genuinely new finding:
`simple_memory_operand` (`mips.c`) returns `SYMBOL_REF_FLAG(addr)` for a bare `SYMBOL_REF`, but its
`case CONST:` is inside a `#if 0` — so a **symbol+offset address falls through to `return 0`**,
constraint `R` fails, `movsf_internal1` takes the `Fm` alternative at length 2, and the insn becomes
ineligible for any delay slot, while gas still emits one gp-relative instruction. Declaring the pair
as one array (`extern float D_00630904[2];`, size 8 ≤ the `-G8` threshold so `SYMBOL_REF_FLAG` stays
set) reproduces ROM's empty slot and nop placement exactly. A *sized-less* incomplete array is not a
substitute: `int_size_in_bytes` returns −1, `ENCODE_SECTION_INFO` clears the flag, and gcc emits
`lui %hi` + `%lo` as two real insns.

Its remaining 3 sites are an `allocno_compare` tie: `v` refs 6 / ll 5 vs `hi` refs 6 / ll 4 →
24000 vs 30000, invariant across **twelve** spellings. The round *proved a tie is sufficient* — a
probe adding one insn inside `hi`'s live range flips the dispositions to ROM's. So the lever is one
more insn inside `hi`'s range or one fewer in `v`'s, with no byte change; `sched1` defeats the
obvious placement by always hoisting the `hi` store to the front of its block.

`func_00104AF0` is nailed to one gate: `;; Procedure interblock/speculative motions == 2/2` in the
`.sched` dump — haifa hoists both call-arg copies above the `beq`, so the child pseudo is live across
the set of hard `$5` and is exiled to `$2`. Region size, `SRC_PROB` (50 ≥ `MIN_PROBABILITY` 40) and
`add_branch_dependences` were all read and checked; **the one remaining gate is `check_live_1`** —
the motion is blocked iff the hard reg being set is live at the start of a split block. Compiled and
identical: inverted guard with `goto skip`, `do{}while`, re-reading the child at the call site.
Reusing `idx` as the child variable regresses to 7 sites.

Remaining 6 with current numbers: `ExecKeyInput` 3 sites · `func_00104A48` rc11/6 ·
`func_00104AF0` 2 sites · `func_00104B98` rc20/10 · `func_001050E0` rc33/17 · `func_00104C80` rc73/31.

---

## F15 — the `src/st24a` family (15 stubs, 19–180 insns)

Rotating off `src/keyInput` after two rounds (10 matched, then 1 — the remainder are its hard core,
and all six have sharp characterised residuals recorded above, so re-entry is cheap). `src/st24a.c`
is back in the actor/stage layer where the three cleared TUs' idioms are strong priors.

| # | edit | base | outcome |
|---|---|---|---|
| 1 | launch opus worker scoped to the TU family; brief now also carries the operand-asm preference for VU0 results | `src/st24a.c` clean at HEAD, tree green at `fbf50c75…` | pending |

### F13 result — `src/keyInput.c`, 10 of 17

**Verification (mine):** `rm build/src/keyInput.o`, full ninja → `verify_elf: OK (fbf50c75…)`; 7
stubs left. **Supervisor cleanup:** dropped 4 exact-duplicate `extern` lines, byte-neutral,
re-verified.

**Data model.** `D_00275250` is a **2-element pad-state array, stride 0x58**: `+0x00` buttons,
`+0x04/+0x08` stick, `+0x0C` repeat bitmask (also reachable as the separate symbol `D_0027525C`),
`+0x10` previous buttons, `+0x14…0x50` sixteen `unsigned` per-bit hold counters, `+0x54…0x57` four
actuator bytes. `D_0065FA40` is a matrix stack of stride 0x40 indexed by the gp-rel depth
`D_00631B40`; `D_002758E0/920/960/9A0` are four scratch 4×4 matrices.

**Mechanisms measured (all compiled):**
- **Matrix-store source order is DESCENDING index.** `[5],[6],[9],[10]` and `[5],[10],[6],[9]` both
  emit the two cos stores in the wrong order; `[10],[9],[6],[5]` matches, and the same descending
  order matched two more functions first try.
- **Pointer carrier for a second stack buffer.** ROM addresses `buf[3]` through the register already
  carrying `&buf` where gcc emits `28(sp)`; routing every use through `float *m = buf;` matched two
  functions. The carrier is genuinely used 3–4 times, so this is the re-association side of
  COOKBOOK §13.19, not an orphan carrier.
- **`mult1` gating, probed directly** (`scratchpad/probe/m1.c`–`m3.c`): ee-gcc 2.9-991111 emits
  `mult1` **only when both multiplies live in ONE assignment expression**. Split into two statements,
  or joined by a comma operator, gives `mult` + `mult` plus an assembler hazard `nop`. This is
  **narrower than the `auto_mult1` note implies** — worth propagating back to that note.
- **A `goto` loop suppresses `loop.c` invariant hoisting** (`func_00104AF0`): with `do{}while`, gcc
  hoists `addiu s4,zero,-1` into the prologue; ROM has it inside the loop.
- **The offset-0 store is what creates a spurious address carrier** (`func_001050E0`):
  `cse.c:canon_reg` unifies the `(plus sp 0x20)` inside `*(float*)(m+0) = c` with the same address
  passed as a call argument. Diagnostic, compiled: moving that one store to a non-zero offset makes
  the extra `addu $17,$29,32` disappear entirely.
- **`allocno_compare` read via `-dg`/`-dl`:** `pri = floor_log2(n_refs)·n_refs/live_length`, with
  `n_refs` weighted ×2 inside a loop, ties broken to the lower pseudo. Recipe: compile the isolated
  function and read `Pass 1 registers to be allocated in sorted order` + `Register dispositions`.
- `const` on an extern float is **not** the LICM lever — it hoists *both* bounds and adds a `mov.s`.

### CRUTCH RULING — `register float dot __asm__("$fN")` in the two VU0 leaves: ACCEPTED

The round flagged this itself rather than claiming clean, which is the right instinct. I ruled on it
by reading the code rather than the argument.

**Accepted, and here is the distinction that decides it.** `VU0_MTC1(v0, 12)` expands to a
bare-string `mtc1 $v0, $f12` — a real instruction that writes hard register `$f12`. The declaration
introduced here is **uninitialized**:

```c
register float dot __asm__("$f12");   /* no initializer */
…
VU0_QMFC2_NI(v0, 3);
VU0_MTC1(v0, 12);
_PushVu0Registers(buf, a1, -dot);
```

It carries no value from C. Its only job is to give a C name to the hard register the inline asm just
wrote, because the `VU0_*` macros take register-name *tokens*, not operands — there is no other way
to read a `qmfc2`/`mtc1` result. That is **operand binding, not allocation steering**, and it fails
the crutch test's premise: the construct does not exist to move a value into a register, it names a
register the emitted `mtc1` already fixed.

CLAUDE.md's banned spelling is `register int x __asm__("$3") = ...` — **with an initializer**, i.e. a
value arriving from ordinary C that is being forced into a register. That is the pin. I verified no
initialized form was introduced here (`grep 'register .*__asm__.*='` is empty). The same uninitialized
idiom is already committed and matched in `src/pool.c:28` and `src/clothTest.c:105`, and CLAUDE.md's
legitimate list names the VU0 whole-function exception.

**Debt flagged, not propagated:** `src/pool.c:26` also contains
`register float thr __asm__("$f20") = threshold;` — the *initialized* form, which is the banned
spelling. It predates this chain and I am not touching it here, but it should not be used as
precedent for new code, and it belongs on the crutch-debt inventory.

---

## F14 — `src/keyInput`, the remaining 7

Relaunching on the same TU rather than rotating: the round left seven sharply-characterised
residuals with the data model complete, which is the cheapest state a follow-on ever gets. Residuals
as the round measured them (leads, not verdicts):

| func | best | residual |
|---|---|---|
| `ExecKeyInput` | 2 FP letters + 1 delay slot | `-dg` shows `hi` (refs 6, live_length 4) sorting before `v` (refs 6, ll 5); five spellings all gave identical 6/6 refs |
| `func_00104940` | 2 sites | `local-alloc` ties the `add.s` hard-reg dest to the LAST dying input; seven spellings identical |
| `func_00104AF0` | 2 sites | `sched1` **interblock** speculatively hoists the call's arg copies above the `beq`, so the value conflicts with hard `$5` and is exiled to `$2`; ROM has no hoist |
| `func_00104A48` | ~4 sites | same interblock class, plus a `v0/v1` swap on two loop-invariant address roots |
| `func_00104B98` | rc21 / 9 sites | needs both multiplies in ONE assignment (see `mult1` gating above), plus a separately-materialised base for five `base+K` invariants |
| `func_001050E0` | rc33 / 17 sites | structure, frame `0xF0` and call sequence correct; the offset-0-store carrier above, a `c2`/`s2` letter swap, and a store-pair order |
| `func_00104C80` | rc73 / 31 sites, frame `0x160` matches | full semantics decoded including the `unsigned` hold counters and the signed button word; built spills two buffer addresses where ROM spills one |

| # | edit | base | outcome |
|---|---|---|---|
| 1 | relaunch opus on the same TU with the seven residuals as a map | `src/keyInput.c` at `68a23262`, tree green | pending |

### F12 result — `src/st17a.c` cleared 26/26, and the best mechanism chain of the run

**Verification (mine):** `rm build/src/st17a.o`, full ninja → `verify_elf: OK (fbf50c75…)`; zero
`INCLUDE_ASM` left; crutch scan clean; the sibling `func_0022DDD8` re-measured at rc0. Pushed
`9b37ae01..42f45a6c`.

**The two residual classes were one problem, and the fix was a single statement:** `sub += 0x24;`
before the loop became `iosSemaWait(sub + 0x24, 0x22)` at the use site. The derivation, read off the
compiler sources and `-da` dumps and then verified in one edit:

1. `reorg.c:mostly_true_jump` returns `-1` only when the branch's `LABEL_REF` carries
   `LABEL_OUTSIDE_LOOP_P`; otherwise it bottoms out at `case NE: return 1` (both sides give
   `rare_destination == 0`). A positive prediction makes `fill_eager_delay_slots` steal from the
   **target** — the built duplicated `xori` and retargeted branch. A non-positive one steals from the
   **fall-through**, which is ROM's `lui $3,%hi(D_00275254)`.
2. `LABEL_OUTSIDE_LOOP_P` is set by `loop.c:mark_loop_jump`, so it needs real `NOTE_INSN_LOOP_BEG/END`
   — which the previous round's goto-built loop provably cannot have. The `while` form is therefore
   required; confirmed by the `/s` in-struct bit on the `label_ref` in the `.mach` dump.
3. But with LOOP notes, `scan_loop` hoists the `(high (symbol_ref …))` into `s0`, so the
   fall-through's first insn sets `$2` — the branch's needed resource — and the steal dies anyway.
4. **The escape is `scan_loop`'s own "phony" bailout:** if the first non-note insn after `LOOP_BEG`
   is not a `CODE_LABEL`, it returns without moving anything, *while `find_and_verify_loops` has
   already set the label bit*. This very TU proves the mechanism — loop 1 of this function is logged
   `Loop from 10 to 52 is phony` purely because gcse had inserted a `high` set after its `LOOP_BEG`.
5. A source statement always expands *before* `LOOP_BEG`, and `move_movables` inserts before it too,
   so the only thing that can land *after* it is a gcse-PRE `insert_insn_end_bb`. Therefore ROM's
   `addiu $17,$2,0x24` had to be a PRE insertion — i.e. `sub + 0x24` written at the use site.
6. That one placement closes both classes: the loop goes phony (so the `lui` stays inside and the
   `bne` steals it into the delay slot) and the `addiu` becomes the last insn before the `b`, so
   `fill_simple_delay_slots`' backward scan takes it.

Measured ladder: inherited goto-form rc8/6 → `while` form rc10/**5** → statement-order swap
rc10/5 (bit-identical diff) → `iosSemaWait(sub + 0x24, …)` **rc0/0**.

Two side findings worth keeping. **sched1 orders this block by descending `INSN_REG_WEIGHT`, then by
the jump's dependence kind** — the `addu` is TRUE-dep'd from the `b` while the store is only
`REG_DEP_ANTI`, so the store is always scheduled last regardless of source order, which is why the
previous round's three order experiments were all no-ops. And `volatile int D_00633FB4` scored better
(rc8/6) but **broke the already-matched sibling `func_0022DDD8`**, so it is not ROM's declaration —
a good example of why a TU-wide re-check matters after a declaration change.

---

## F13 — the `src/keyInput` family (17 stubs, 21–156 insns)

A different subsystem from the three cleared TUs — an input layer with a pad-state data model rather
than script actors — so the transferred idioms are weaker priors here and the brief says so.

**Brief change, logged as a deliberate policy edit.** Previous family briefs inlined a growing list
of recovered idioms, which is exactly the ratchet the skill's worker-brief reference warns about.
From this round the brief carries a single **READ THE LEDGER FIRST** pointer naming the mechanisms
by topic instead of restating them. Findings live in the ledger; the brief stays flat.

| # | edit | base | outcome |
|---|---|---|---|
| 1 | launch opus worker scoped to the TU family, idioms replaced by a ledger pointer | `src/keyInput.c` clean at HEAD, tree green at `fbf50c75…` | pending |

### F11 result — `src/st17a.c`, 25 of 26

**Verification (mine):** `rm build/src/st17a.o`, full `.venv/bin/ninja` → `verify_elf: OK
(fbf50c75…)`; one `INCLUDE_ASM` left; crutch scan clean; zero duplicate externs; +574 lines.

Five mechanisms, all compiled and ninja-verified:

- **A cross-jumped ternary is an `if`/`else` with INVERTED polarity** (`func_0022ECF0`). A ternary,
  or `id = A; if (!c) id = B;`, both produce `movz`. Two *complete* call statements in
  `if (c == 0) {B-value} else {A-value}` produce ROM's `bne` plus the delay-slot const; the
  "natural" polarity gives `beq` and fails.
- **Pointer TYPE orders the schedule** (`func_0022E9D0`, rc6→0). Declaring the BoxBar table
  `extern int *D_004D3120[]` and the field `void *unkC4` — rather than `int[]` / `int*` — moved
  `sw zero,0x16C(v0)` out of immediately-after-the-call into ROM's slot between the two other
  stores. Retail has strict aliasing live, so int-store vs pointer-store types decide the ordering.
- **An implicit declaration cost three registers** (`func_0022E220`, rc4→0). `func_0017B288` was
  used 250 lines before its `extern`; the implicit `int` return made `v0`/`v1` swap across the whole
  tail. **Extern ORDER in a TU is a codegen lever here, not hygiene.**
- **`c.lt.s`+`bc1f` needs the negated form** `while (!(scpSekizou(K) < -2.0f))`; spelling it
  `>= -2.0f` canonicalizes to `c.le.s`+`bc1t` (`func_0022DAC8`).
- **gcse PRE numbers `reaching_reg` in expression-hash order keyed on the symbol NAME STRING**
  (`func_0022E680` / `E508` vs the already-matching `E398` / `E220`). Measured in `.lreg`: the same
  insn sets pseudo **106** in one and **105** in the other, and the lower pseudo wins `$18`.
  Diagnostics: substituting E398's symbol pair into E680's body flipped it back, while moving the
  extern to the top of the TU did **not** — so it is content-hash, not interning order. Remedy from
  `[[gcse_bucket_name_hash]]`: re-spell the address through **one local** `tbl = &D_004D31E0[16]`
  used twice (same contiguous run: `D_004D31E0 + 0x40 == D_004D3220`), which re-hashes the
  expression with zero byte change. The inline form `&D_004D31E0[16]` used twice does **not** work —
  CSE splits it into base + `64/68(reg)` offsets and breaks the bytes.

The round also corrected its own tooling mid-flight: its first instruction-count regex silently
returned 0 for every file, and it switched to the `nonmatching <name>, 0xSIZE` header line as the
reliable size source.

---

## F12 — `func_0022DBC8` (`src/st17a`, 132 insns)

The one stub F11 did not land. Whole-function structure recovered and judged correct; best attempt
`rc8 / 6 sites` at `scratchpad/seeds/func_0022DBC8.attempt.c` (a variant with one statement moved
scored rc6/5 but was judged structurally wrong, and the round declined to bank it — correct call
under structure-over-count).

Mechanisms it established on this function, all compiled:
- **A goto-built loop suppresses `loop.c` invariant hoisting.** `goto test; wait: _ACTWait(1);
  test: …` has no `NOTE_INSN_LOOP_BEG`, so `lui $3,%hi(D_00275254)` stays *inside* the loop as ROM
  has it. Every `while` / `&&` spelling hoists it to the preheader, costing a callee-saved register
  (frame 80 vs 64) and turning the exit `bne` into `bnel`. `volatile` on the array does not suppress
  it.
- The object must be spelled `D_00275254[0]`, not `D_00275250[1]` — the latter emits `lui+addiu+lw`
  where ROM folds `%lo` into the load.
- `st = D_00633FB4 ^ 1; if (st != 0)` reproduces ROM's single `xori $16,$2,1` feeding two `beqz`.
  `st = (D_00633FB4 != 1)` adds an `sltu`; `st = D_00633FB4; if (st != 1)` keeps the flag in `s0` and
  rematerialises `1` (rc32).

Two residual classes, both compiled and pinned: sched2 emits `addu $17,$2,36` before
`sw $0,D_00633FB4` where ROM has them reversed (three source orders tried; two identical, so not LUID
order), and dbr steals the join's `xori` into the `bne` delay slot where ROM fills it from the
fall-through with the `lui`. The round's hypothesis — passed on as a hypothesis, not a verdict — is
that these are one block-layout problem, since both key off what sits immediately after that branch.

| # | edit | base | outcome |
|---|---|---|---|
| 1 | relaunch opus on the single remaining function, residual handed over as a map with the round's own hypothesis labelled as such | `src/st17a.c` at `36b2a88b` with this function `INCLUDE_ASM`, tree green | pending |

### Operational rule learned the hard way: NEVER push while a worker round is live

I tried to push right after launching F12 and the pre-push hook refused:

```
pre-push: SHA-1 GATE FAILED on refs/heads/main — refusing push.
```

Nothing is wrong with the commits — each was made against a green tree and passed its own pre-commit
gate. The cause is that **the pre-push hook rebuilds the WORKING TREE, not the committed tree**, and
the live F12 worker had an in-flight non-matching body in `src/st17a.c` at that moment
(`git diff --stat` showed +78/-1). The hook was correctly reporting that the working tree does not
round-trip; it just was not measuring what I meant to push.

Its diagnostic text guesses `--no-verify` and suggests rebasing away a bad commit. **Do not act on
that suggestion here** — it would discard good commits to fix a phantom. The fix is to wait for the
round to finish and push once the tree is green again.

Rule for the rest of the chain: **push only between rounds, with `git status` clean apart from
`scratchpad/`.** Commits are safe at any time (pre-commit runs while the tree is green because I
harvest before relaunching); pushes are not.

### F10 result — `src/st05d.c` cleared, 9 for 9, and TWO errors of mine it exposed

**Verification (mine):** `rm build/src/st05d.o`, full `.venv/bin/ninja` → `verify_elf: OK
(fbf50c75…)`; `grep -c INCLUDE_ASM src/st05d.c` → **0**.

Eight 17-instruction door-wait actors, one shape with two varying constants:

```c
void func_0021F5B0(volatile int a0) {
    while (scpDoorTypeUpUp(0x402) == 0) { _ACTWait(1); }
    func_0017B258(0xB8);
}
```

Constants: `F5B0`=0x402/0xB8, `F5F8`=0x403/0xB9, `F640`=0x454/0xBA, `F688`=0x455/0xBB,
`F6D0`=0x456/0xBE, `F718`=0x457/0xBF, `F760`=0x406/0xBC, `F7A8`=0x407/0xBD.

The parameter is **unread** in all eight, yet ROM still homes `$4` to `0x0($29)` with `vars=16`;
`volatile int a0` alone reproduces that, confirmed against the already-matched `actSt05dDoor2` in
the same TU. The extra `nop` before the loop label is gcc's `.p2align 3` loop-head alignment, not a
source artifact.

`func_0021F828` (130 insns) is eleven sequential `if (func_0017B230(id) == 0) A(); else B();`
guards. Two durable reads: the `addiu $4,<anim>` in the `bnez` delay slot is the **shared** first
argument of the calls in *both* arms, not a then-branch value — reading it as branch-local yields a
wrong argument; and `match_diff` reported `rc0 / diff_sites 0` while still emitting a
`delay-slot-occupant` tag with `raw_count 53`, which is advisory noise from epilogue `ld $31`
duplication gcc generates itself. Ninja is the gate.

**ERROR 1 — my instruction counts were inflated by one.** I was counting `/* … */` lines including
the alignment `nop` that sits *after* `endlabel`. These are 17-instruction functions (0x44), not 18.
Every per-function size I have quoted in this ledger for a function with trailing padding is +1.
Counter corrected to stop at `endlabel`; list rebuilt as `scratchpad/targets_v2.txt`.

**ERROR 2, the more damaging one — my target list was silently excluding parked functions.** Four of
these nine (`func_0021F5B0`, `F5F8`, `F640`, `F688`) were on `config/sweep_parked.txt` from an
earlier sweep, so my filter dropped them and my own brief said "four at 18" when there were eight at
17. **All four matched rc0 on the first try.** Parked is not hard — it records that one earlier
single-pass attempt did not land, under a different method. Filter removed: the rebuilt list carries
1895 stubs with parked ones included and merely flagged, of which **56 were previously excluded, 25
of them at ≤30 instructions**. Those 25 are now back in the queue.

---

## F11 — the `src/st17a` family (26 stubs, ~20–132 insns)

Chosen for yield: it is the largest cluster of small stubs left (8 at ≤30) and it is the *same*
actor/stage layer as `src/access.c` and `src/st05d.c`, so the two cleared TUs' idioms transfer
directly. The brief hands over all of them — entry template, wait-loop, assignment-in-condition,
`if`/`else` polarity, the shared-argument-in-delay-slot read, the callee-signature-from-ROM rule,
and the advisory-tag noise — explicitly as models to confirm or refute per function, plus both of my
errors above so the round does not inherit my counts.

| # | edit | base | outcome |
|---|---|---|---|
| 1 | launch opus worker scoped to the TU family | `src/st17a.c` clean at HEAD, tree green at `fbf50c75…` | pending |

### F9 result — `src/access.c` cleared, 19 for 19

**Verification (mine, not the self-report):** `rm build/src/access.o`, full `.venv/bin/ninja` →
`verify_elf: OK (fbf50c75…)`. `grep -c INCLUDE_ASM src/access.c` → **0**. That combination is the
proof: a green byte-identical ELF with zero stubs left in the TU means every function in it matches
from real C. Crutch grep clean. `readelf -sW build/src/access.o` → 30 FUNC symbols, so no inline
helper leaked one.

Four families, all first-try:
1. **Actor-entry template** (18): the `func_0023B170` shape with new immediates. Critically, the
   round **omitted** `int x = a0;` wherever ROM shows only the `sw $4` home and no second `lw` —
   i.e. it used the idiom as a model to confirm per function rather than as a rule.
2. **`actSt25aQueenTalkChk` warp** (20, 38): `long long buf[2]` filled field-by-field from a
   `D_0061Cxxx` pair; template already in `src/st17b.c:16` / `src/st13b.c:123`. `func_0023A9F0`
   extends it with a second 16-byte local held in `$16` because its address is used twice.
3. **`actInitialize` → BoxBar handoff** (26–34): call result lands in `$16`, then a `D_004D4xxx[1]`
   next-actor store, the `unkC4` hookup and `BoxBarSoundOn`.
4. **`scpPlayMotDirSmz` torch trio** (44): the `0x15C` load is reloaded because the intervening
   store aliases it — no `volatile` needed.

**Two callee signatures derived from ROM rather than asserted:**
- **`scpPlayMotDirSmz` takes SIX float args and NO integer args**, in consecutive single FPRs
  `$f12`–`$f17` — verified from the callee's own body
  (`asm/nonmatchings/src/script/scpPlayMotDirSmz.s:6-16`, no `$4`–`$7` use). The `$4` still live at
  the call site is **stale from the preceding `jal`**, not an argument. This confirms the ABI
  allocates integer and FP argument registers independently — the same reason
  `scpSleepEnemyOne(int,int,float)` puts its third argument in `$f12`.
- **`actSwordEffXL` is really `(int, int, int*, int)`** at five call sites, though the matched
  definition at `src/st25a.c:142` declares one parameter and codegens identically because the extra
  parameters are unused. Anyone matching `actE3GateChk` (`src/e3.c:245`) needs the 4-arg form — that
  function is byte-for-byte `func_0023A9F0` minus `scpActivateAllWithKind` and with `$5=0x64`
  instead of `0xB`, so it should fall out of `scratchpad/seeds/func_0023A9F0.c`.

**Loop shape:** `func_0023AD68` needed a call's result as a later argument inside the same `while`
condition. What matched is assignment-in-condition —
`while ((v0 = scpSubAdpcmPlay(0x13)) == 0 || scpSleepEnemyOne(a0, v0, 350.0f) == 0) { _ACTWait(1); }`
— not a `for(;;)`/`break` rotation.

**Supervisor cleanup after harvest:** the round left 8 exact-duplicate `extern` declarations in the
file (legal, but untidy). Stripped them and re-verified byte-identical. Added "declare each extern
once per TU" to the next family brief. Left alone: eleven per-function `KSub_*` typedefs that are
all `{ char pad[0xC4]; int *unkC4; }` — the round kept them per-function to match the existing
committed style in this TU, and collapsing them touches already-matched code, so that is a judgment
call better made when the struct is actually understood.

**Pushed** `c307de40..6c0c0e47`. Repo progress `3006/5447` functions (was 2980 at chain start).

---

## F10 — the `src/st05d` family (9 stubs)

Chosen by the standing smallest-first rule with the same structural tie-break used before: the
smallest remaining non-deferred stubs are a group of 18-instruction functions across several TUs,
and `src/st05d.c` is the one where four of them sit together in a single TU with matched siblings
already above them, so it clears fastest.

| # | edit | base | outcome |
|---|---|---|---|
| 1 | launch opus worker scoped to the TU family; F9's four idioms handed over as models to confirm-or-refute per function, with the explicit note that `int x = a0;` must be omitted where ROM shows no second `lw` | `src/st05d.c` clean at HEAD, tree green at `fbf50c75…` | pending |

### F8 result — `func_0023B170`, and the `src/access` actor-thread template

Verified by me: `rm build/src/access.o`, full `.venv/bin/ninja` → `verify_elf: OK (fbf50c75…)`;
oracle `status match / rc 0 / diff_sites 0`.

```c
void func_0023B170(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    scpSetCageVelocityFriction(0xCAA, 0, 0x1E3, 0);
}
```

An actor-thread entry: register the thread, yield a frame, set cage velocity/friction for cage
`0xCAA` against target `0x1E3`. Callee signature from `src/e3.c:278` / `src/script.c:45` matches
ROM's `$4=0xCAA, $5=0, $6=0x1E3, $7=0`.

**My launch lead was right about the shape and wrong about the mechanism.** I read the stack home
plus discarded load as "an addressable or `volatile` parameter". It is specifically:
`volatile int a0` homes `$4` to `0x0($29)` and reloads on **every** read, and the dead
`int x = a0;` initializer is the *second* volatile read. So the `sw` plus two loads from `0x0($29)`
— one into a register never read again, one into `$4` — is one object (the param's home) read twice,
not an address-taken local.

**Crutch call, and why it passes.** `int x = a0;` emits a real `lw` from a volatile object, so it is
not the zero-code dead-store class. Decisive evidence is that the identical two-line preamble is
*already committed and matched* in two sibling TUs by the same programmer — I re-read both rather
than taking the citation on trust: `src/st13b.c:31` (`actSt13bFloorChk`) and `src/st03t.c:110`
(`actSt03tSwitchRChk`). It is the dev's house idiom, not a construct invented to steer codegen.

**Durable signature for the corpus:** in `src/access.c` and its sibling actor TUs, a prologue of
`sw $4,0($sp)` followed by *two* loads from `0x0($29)` — one into a register never read again, one
into `$4` for the first call — is this idiom. Check it before reaching for a static-chain /
nested-function reading: the dead load landing in `$2` is coincidental register selection, and
`actInitialize` does not consume `$2` on entry.

---

## F9 — the `src/access` template family (scope decision)

**Deliberate scope change, recorded so it is visible.** `func_0023B1B8` turned out to be
byte-for-byte `func_0023B170` with two immediates changed (`0xCAA`→`0xCA9`, `0x1E3`→`0x1E4`).
Spending a whole round per two-constant clone is waste, so this round is scoped to the **19
remaining stubs in `src/access.c`** (18–48 insns), worked smallest-first, one at a time, each gated
by a full ninja before moving on.

This does not break the one-live-worker-per-TU rule — it is still exactly one worker on one TU. It
does relax the skill's one-function-per-worker default, which is a supervisor decision and is logged
here rather than made silently. Instructions to the worker: land one, verify, then next; a function
that does not fit the template is reported as what it actually is, not forced; anything that resists
keeps its `INCLUDE_ASM` stub so the tree never goes red. The worker was also told the instruction
counts in its table are mine and are exactly the kind of number that has been wrong in this chain.

| # | edit | base | outcome |
|---|---|---|---|
| 1 | launch opus worker scoped to the TU family, template handed over as a model to confirm-or-refute per function | `src/access.c` clean at HEAD, tree green at `fbf50c75…` | pending |
| 1a | supervisor message: typo correction, the brief's BANKING line said `.venj/bin/ninja` | same | sent mid-round |

### F7 result — `func_001186C8`, and a durable discriminator

Verified by me: `rm build/src/MicroCode.o`, full `.venv/bin/ninja` → `verify_elf: OK (fbf50c75…)`;
oracle `status match / rc 0 / diff_sites 0`.

The round answered the two-sided question with evidence rather than defaulting: **this is a C
function with an inline-asm body, NOT a whole-function `__asm__` block.**

**The delay slot is the discriminator, and it generalises.** `func_002439B0`
(`src/cod/vendor_2418A0.c`) is the same 16-instruction MMI transpose written as whole-function asm,
and it ends `jr $31` with `sq $11,0x30($4)` hand-filled into the slot — 17 insns. Ours ends `sq`,
`jr $31`, `nop` — 18 insns with the slot spent. gas will not hoist an `#APP` instruction into the
slot, so **a C wrapper always pays the author's explicit trailing `nop` there, while hand-written asm
fills it with real work.** Where two ROM functions share an identical instruction *body* and differ
only in whether the last store sits before or inside the delay slot, they came from two different
source forms. `include/r5900.h`'s `QCOPY16` vs `QCOPY16_NO_NOP` pair encodes the same fact from the
other direction.

The round verified the epilogue model against the matched sibling `mc_TransMicroCode` *before*
writing anything — its emitted `.s` shows the same bare `j $31` with no compiler nop, and its ROM
size confirms the trailing `nop` is the slot occupant rather than an extra instruction. That
predicted 16 asm + `nop` + `j $31` = 0x48, exactly ROM's size, and the prediction held on the first
compile. ee-gcc 2.9 has no MMI intrinsics and does not vectorize, so `pextlw`/`pcpyud` are
unreachable from scalar C — the MMI exception applies to the *body*, and the wrapper is genuine C.

**Supervisor edit after the harvest:** the round wrote the trailing nop as a bare
`__asm__ __volatile__("nop")`. The rest of this TU uses `VU0_NOP()` from `include/vu0.h`, whose
expansion is character-for-character identical. Swapped it for the house spelling and re-verified
rc0 + ninja green. Byte-neutral, readability only.

Follow-ons flagged by the round, same TU and same idiom: `func_00118710` (28 insns),
`func_00118780` (38), `func_00118940` (52), `func_00118818` (74).

---

## F8 — `func_0023B170` (`src/access`, 18 insns)

ROM (read this session, 0x44): stores the incoming `$4` to `0x0($29)`, loads it back twice — once
into `$2` whose value is never used, once into `$4` — then calls `actInitialize(a0)`, `_ACTWait(1)`,
and `scpSetCageVelocityFriction(0xCAA, 0, 0x1E3, 0)`. No prior work exists on it.

Sent with one explicitly-refutable lead: a parameter with a stack home plus a read whose result is
discarded is the shape an addressable or `volatile` parameter produces — and an addressable-param
home is legitimate under the crutch ban, not a crutch. Flagged as a reading of two instructions, not
a diagnosis.

| # | edit | base | outcome |
|---|---|---|---|
| 1 | launch opus convergence worker, frozen brief, no target named; param-home lead attached as refutable | `INCLUDE_ASM` stub, tree green at `fbf50c75…` | pending |

### F6 result — `func_0010EC08`, and a correction to my own launch brief

Verified by me: `rm build/src/DisplayP2O.o`, full `.venv/bin/ninja` → `verify_elf: OK (fbf50c75…)`;
oracle `status match / rc 0 / diff_sites 0` (raw 4 is the in-TU `jal func_0010EB60` false-negative);
crutch-free.

```c
extern short func_0010EB60(float c);

short func_0010EC08(float s, float c)
{
    if (s < 0.0f) {
        return -func_0010EB60(c);
    }
    return func_0010EB60(c);
}
```

**My launch brief said the signature was "already pinned" as `int func_0010EC08(float, float)` by
three parked files. ROM says `short`, and the round corrected it.** Those parked files are not
compiled, so nothing was broken — but "pinned by three declarations" was my phrasing and it was
wrong. A declaration in a parked file is a prior worker's guess, not an artifact.

Recovered model: `func_0010EB60` is an **acos** — clamps its float arg to `[-1,+1]` with two
`bc1tl`+`mov.s` clamps, records the sign, scales by 4096.0f, `cvt.w.s`, indexes the *short* table
`D_00670E50` with `sll $2,$2,1`, `lhu` + `addiu 0x4000`, and sign-extends on both exits — so **it
returns `short`**. `func_0010EC08(s, c)` is the atan2 sign fixup around it: `acos(c)` gives 0..π and
the sign of the sine component `s` picks the half-plane. The `mov.s $f12,$f13` in both delay slots
is just "forward the second float arg", **not** the cross-jump artifact my brief suggested.

Two mechanism reads, both predicted and both held:
- **Two `jal`s ⇒ two separate call expressions.** The single-call form
  (`r = f(c); if (s<0) r = -r; return r;`) emits one `jal`. Writing the call inside each arm
  reproduces the duplicated `jal`+`mov.s`; gcc cannot cross-jump them because the negate sits
  between the call and the epilogue in one arm.
- **`sll/sra 16` in one arm only ⇒ `short` return type AND `short` callee.** With the callee
  declared `short`, gcc trusts `$2` is already sign-extended on the fall-through arm, while `-x`
  promotes to `int` and the `short` return forces the re-extension — exactly the lone
  `negu`/`sll`/`sra` triple. An `int` callee would have given a symmetric or absent extension.

The `bc1f` sense came free from the plain `if (cond) { … } return …;` form — the standard
then-arm-inline / else-arm-out-of-line layout (`feedback_body_out_of_line_branch_direction`).

---

## F7 — `func_001186C8` (`src/MicroCode`, 18 insns)

ROM (read this session, 0x48): four `lq` from `0x0/0x10/0x20/0x30($5)`, an MMI block
(`pextlw`/`pextuw` then `pcpyld`/`pcpyud`) on `$8..$15`, four `sq` to `0x0/0x10/0x20/0x30($4)`, bare
`jr`. A 4x4 matrix transpose. No prior work exists on it.

Sent with one explicitly two-sided question rather than a target: `CLAUDE.md` names **MMI** as one of
the three documented whole-function-`__asm__` exceptions, and
`tough_nuts/delayslot_unfilled/HANDOFF_vendor_2418A0.md` records `func_002439B0` — also 18 insns,
also an MMI 4x4 transpose — as MATCHED that way. So hand asm may be the right answer, but the round
has to establish which and say what it measured, not default to it.

| # | edit | base | outcome |
|---|---|---|---|
| 1 | launch opus convergence worker, frozen brief, no target named; MMI-exception question posed two-sidedly | `INCLUDE_ASM` stub, tree green at `fbf50c75…` | pending |

**Model policy for the rest of the chain: opus only** (user instruction, 2026-08-16). The one fable
round in this chain (F1 round 2) regressed on both sites and size and mis-stated its own instruction
count; that is a single data point and not the reason for the policy — the user set it directly.

**Pushed** `e7c6e38e..c307de40` to `origin/main` (14 commits). The pre-push hook re-ran the SHA-1
gate and `check_no_rom` (724 files scanned) before allowing it.

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
| 1 | launch opus convergence worker, frozen brief, no target named; in-TU `jal` false-negative noted in the measurement traps | `INCLUDE_ASM` stub, tree green at `fbf50c75…` | **MATCHED, rc0 on the first compile.** Committed `8b518218`. |
| 1a | **supervisor verification (mine):** `rm build/src/spider.o` then full `.venv/bin/ninja` | worker's landed TU | `verify_elf: OK (fbf50c75…)`; oracle `status match / rc 0 / diff_sites 0`; crutch-free. |

```c
void func_001EACE8(void *a0)
{
    char *p = *(char **)(*(char **)((char *)a0 + 0x15C) + 0x800);

    *(int *)(p + 0x3C) = 1;
    func_001AE460(a0);
    return debug_assertMessage(D_006335E0, *(int *)((char *)a0 + 8));
}
```

`a0` is the spider actor; `a0+0x15C` points at the owning manager and `+0x800` off that is a
substruct whose `+0x3C` int is raised to 1 before the hand-off — the same double-deref idiom already
matched in the sibling `func_001EAE70` at `src/spider.c:19`. `func_001AE460` is one-arg (signature
from `src/generator.c:28` and `src/ropeFix.c:62`), which ROM confirms by passing `$4` through
untouched. The trailing `j debug_assertMessage` is the void-TCO idiom — `return f(...);` from a void
function with an empty-parameter-list extern, exactly as in the matched `dl_OpenDma`
(`src/DisplayList.c:152`); that return form is what produces the `j` epilogue instead of a `jal`.
The `addiu $5,$0,1` hoist and the store landing in the `jal` delay slot fall out of natural
statement order — no shape pressure was needed.

---

## F5 — `reallocseki` (`src/Basic`, 17 insns)

ROM (read this session, 0x44): saves the gp-rel word `D_00633780` into `s0`, sets it to 1, calls
`func_0013A0F8(D_00632024, size, &D_0061A8A8, 0x17E)` — a debug allocator wrapper with a
`__FILE__`-style string and line 382 — then restores `D_00633780` from `s0`. `freeseki` in the same
TU is also still a stub.

Prior work: `decomp/port_ledger.md:403` — an aug6 port reverted at "insn 5: expected `lui a2,0x0`
built `addiu a3,zero,382`", i.e. the line-number immediate landed where ROM has the `%hi` half of
the string address.

| # | edit | base | outcome |
|---|---|---|---|
| 1 | launch opus convergence worker, frozen brief, no target named, prior-port datum attached as a pointer | `INCLUDE_ASM` stub, tree green at `fbf50c75…` | **MATCHED, rc0 on the first compile.** Committed `337953bb`. |
| 1a | **supervisor verification (mine):** `rm build/src/Basic.o` then full `.venv/bin/ninja` | worker's landed TU | `verify_elf: OK (fbf50c75…)`; oracle `status match / rc 0 / diff_sites 0`; crutch-free — `save` is genuinely read back and both stores are to a real global. |

```c
int reallocseki(int size)
{
    unsigned int save = D_00633780;
    int r;

    D_00633780 = 1;
    r = func_0013A0F8(D_00632024, size, D_0061A8A8, 0x17E);
    D_00633780 = save;
    return r;
}
```

**The model came from the sibling, not the target.** `D_00633780` is the malloc *partition selector*
(`malloc_GetPartition` writes it at `src/Basic.c:80`, `mallocseki` reads it at `:85`). `freeseki`
dispatches on it, and its `== 1` arm is `func_0013A0F8(D_00632024, size, FILE, 0x17E)`.
`reallocseki` is exactly that arm wrapped in a save / set-to-1 / restore of the selector — which is
why both functions carry `__LINE__ == 0x17E`. The dev almost certainly wrote `freeseki(size)` with
`freeseki` marked gnu89 `inline`, and gcc const-propagated the just-stored `D_00633780 == 1` through
the inlined dispatch down to the single arm; writing the collapsed form directly is byte-identical,
so that question never had to be settled.

Codegen facts that made it fall out with no tuning: `D_00633780` / `D_00632024` are `-G8` small data
→ `%gp_rel` with no `lui`, while `D_0061A8A8` as an incomplete `const char[]` is far → the
`lui`/`addiu` pair. The prior port's "insn 5" failure was a scheduling shuffle of that same pair,
not a structural obstacle. Assigning the call result to a local before the restore store keeps the
callee's `$v0` in place with no move, and the `addiu v0,zero,1` / `sw v0` in the `jal` delay slot is
the scheduler hoisting the `= 1` store, automatic from this ordering.

---

## Chain hold state — 2026-08-16

**Tree:** clean apart from `scratchpad/`. `.venv/bin/ninja` → `verify_elf: OK
(fbf50c75cd5911273511c4f9af90503ff8423582)`. Repo progress `2983/5447` functions after F2–F5
(re-read `docs/progress.json` rather than trusting this figure).

**Score so far:** 4 matched (`fzShowV`, `func_001AE420`, `func_001EACE8`, `reallocseki`), each rc0
on the first compile. 1 rotated out unmatched (`func_00244958`) with both frontiers and a full pass
model recorded — not parked, no floor claimed.

**Observed pattern, offered as an observation and not a rule:** every round that recovered the data
model and the callee signatures *before* writing C landed rc0 immediately. The one function that
resisted is the one where the semantics were obvious from the start and the whole problem is which
gcc pass folds a constant address — data-model work cannot help there, which is why it took four
rounds.

**Next targets, in the order the chain should take them:**
1. `src/DisplayP2O func_0010EC08` (18) — strict smallest-first, the standing policy. **Prepared, not
   yet launched** (usage limit hit before the worker could start). Evidence gathered this session,
   so the next round starts from it rather than re-deriving:
   - **Signature is already known:** `extern int func_0010EC08(float a, float b);` is declared
     identically in three parked files — `tough_nuts/func_001B8720/func_001B8720.1.c:428`,
     `tough_nuts/func_001B94B0/func_001B94B0.c:240`, `tough_nuts/func_001B9638/func_001B9638.c:214`.
   - **ROM (0x44, read this session):** `mtc1 $0,$f0` / `c.lt.s $f12,$f0` / `bc1f .L0010EC38`, and
     *both* arms then do `jal func_0010EB60` with `mov.s $f12,$f13` in the delay slot — i.e. both
     call the same callee with the second float argument. The `a < 0` arm additionally does
     `negu $2,$2` then `sll $2,$2,16` / `sra $2,$2,16`, i.e. negate and sign-extend to `short`,
     before `b .L0010EC40`. The two `jal`+`mov.s` pairs being identical across the arms is a
     cross-jump/tail-duplication shape, and the `sll/sra 16` pair is the `(short)` cast idiom —
     both are leads for the next worker to confirm or refute, not a diagnosis.
   - `func_0010EB60` is itself still an `INCLUDE_ASM` stub in the same TU, so expect the in-TU `jal`
     false-negative in `quick_diff` (see F3's note); `match_diff` normalises it and ninja is the gate.
2. `src/MicroCode func_001186C8` (18), `src/access func_0023B170` (18), `src/access func_0023B1B8`
   (18), then the rest of `scratchpad/targets_annotated.txt` in order.
3. **`freeseki` (`src/Basic`, 56 insns) — FLAGGED HIGH-READINESS, out of size order.** Its full shape
   was derived as a by-product of F5 and is recorded here: a 3-way dispatch on `D_00633780` —
   `-1` → assert via `debug_assertMessage(D_0061A890)` + `func_001AD768(FILE, 0x174)` +
   `func_00263FF0(FILE, 0x174, &D_00633788)`, falling through to re-load the selector; `0` →
   `D_00633784 += size + 0x30` then heap `D_00632014` at line `0x17B`; `1` → heap `D_00632024` at
   line `0x17E`; anything else → return 0. Result funnelled through one variable (`$18`) with the
   `-1`-after-assert case bypassing it via a `b` to the epilogue. Worth taking early despite its
   size, since the model is already written down.

**Standing ordering decision, restated:** `func_002453D0` (`src/cod/vendor_2453C0`, 16) stays
deferred within its tie group as another `src/cod/vendor_*` MMIO poll loop — same class as the
unmatched F1 — and `func_00244958` re-enters the queue whenever the chain wants another attempt at
that family. Neither is a skip; both are recorded here.

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
