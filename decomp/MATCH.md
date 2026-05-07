# Matching prompt — ico (PS2)

Reuse this verbatim (paste it as the first message of a fresh Claude Code
session) to launch a matching work session on this repo.

---

Continue the **ICO** clean-room decomp at `/primary/dev/ico`. Working
directive: match as many ELF functions as possible, plug away at the
percentage. Same clean-room rules as before — no disc data, no extracted
assets, no leaked-source-derived code, no AI co-author trailer on
commits.

## Do not stop matching

**Run until the Claude usage cap stops you, or until the user explicitly
tells you to stop. Do not stop early, ever.** The only acceptable end-of-
stream is the cap or a direct user instruction. This rule is the most
important rule in this document — every other rule below exists to
support it.

### Cron-driven /loop is NOT a heartbeat to wait on

If this prompt is firing from `/loop 30m decomp/MATCH.md unsupervised`
(or similar), the 30-minute cadence is a **failsafe re-entry mechanism**
in case the agent itself ever winds down — not a per-iteration work
cap. Each fire of the loop should burn many minutes of agent work
(many batches, many candidates, retries, parking attempts) before it
naturally terminates at the usage cap or a user prompt.

**Specific banned patterns** (these are session bugs, regardless of
how they're phrased):

- "Matched N functions this iteration. 1.X% .text. Continuing to
  wait for next cron fire." — DO NOT print this. There is no waiting.
  The next fire is the safety net, not your bedtime.
- A trailing `grep '\.text' docs/PROGRESS.md | head -1` followed by a
  one-line outro. The percentage check is not an end-of-turn ritual.
- "Build green, committed func_X. Ready for next fire." — same
  pattern, just spelled differently. Keep matching.
- One batch of matches, then idle output and tool-quiescence. If you
  finished a batch and aren't sure what to do next, the answer is
  always: re-scan `docs/candidates.md`, pick more candidates, batch
  more claims, run `make setup && make`. There is no "wait" state.

### Things that are not reasons to stop

- Hitting a "natural seam" — current cluster cleared, deferred list
  felt thin, nothing obvious in `tools/find_siblings.py` (when it
  exists) or in `asm/cod/000000.s`.
- "N matches landed this iteration, that's a good place to pause."
  There is no good place to pause that isn't the cap or a user prompt.
- Round-trip went red and you can't immediately see why. Diagnose with
  `tools/first_diff.py`, revert if needed, keep going.
- The current target plateaued. Park it under `tough_nuts/` (see
  "Tough-nut parking" below — **park, do not revert+delete**) and
  pick another.
- A cron-driven loop just fired and you completed one batch. The fire
  is not a permission slip to stop; it's a permission slip to keep
  going if the agent had drifted off task.

When the obvious seam runs out, broaden the search using the full
toolkit: rescan `asm/cod/000000.s` for more leaves, retry an older
deferred entry under newly acquired leverage, launch
`lib/decomp-permuter` on a near-miss, or pick a medium-size unmatched
function and start it. Reporting "I stopped because the obvious seam
ran out" or "I stopped because momentum felt right" is a session bug,
not a finish line.

**Do not emit "iteration results" / "final state" / "session summary"
text.** No bullet lists recapping matches and tough-nuts at the end of
a chunk of work, no "build green at SHA X" sign-off, no totals. That
summary text functions as a self-imposed stopping point. The only
acceptable end-of-stream is the cap or a user prompt; the work itself
(commits, `decomp/NOTES.md` edits, parked tough-nuts) is the record.
Brief mid-stream status notes ("matched func_X", "parking func_Y",
"moving on to subseg Z") are fine — but the moment a listed/numbered
recap shows up, the session has bugged out. Just keep matching.

**Read first** (in this order):

1. `CLAUDE.md` — IP rules, toolchain, build commands, conventions.
2. `decomp/NOTES.md` — every PS2 EE / compiler / splat / linker quirk
   catalogued so far. Most "near-miss" diffs are an instance of a
   pattern in here.
3. `docs/MATCHING_NOTES.md` — per-function tough-nuts and deferred
   targets.
4. `docs/LEGAL.md` — clean-room boundary, what's allowed as a reference,
   what's forbidden as an input.

## Toolkit

Run `--help` on each tool before first use; expect the inventory to grow
over time.

**Fast inner-loop diff (use these BEFORE `make split && make`):**

- `tools/quick_diff.sh <func_name>` — compile one .c (from `src/` or
  `tough_nuts/`) and side-by-side diff against the target asm in
  `asm/matchings/<func>/`. Skips splat and full-ELF linking — runs
  in ~100 ms vs ~30–60 s for `make setup && make`. This is the
  iteration loop for tough nuts.
- `tools/first_diff.py` — when SHA-1 fails, prints the first diverging
  instruction with the function name and call targets resolved through
  the mapfile. Run after a failed `make`.

**Splitting and linker plumbing:**

- `config/ico.us.yaml` — splat configuration. Convert `[0xADDR, asm]` to
  `[0xADDR, c, name]` to claim a subsegment for matching.
- `make setup` — runs splat + post-processing. Re-run after every yaml
  edit.

**Analysis:**

- Ghidra (`tools/ghidra/`) — interactive RE on `baserom/baseelf.elf`.
- `m2c` (`lib/m2c/`) — asm → C scaffold. R5900 MMI/VU may be
  unsupported; fall back to manual decompilation.
- `lib/asm-differ/` — function-level diffing while editing.
- `lib/decomp-permuter/` — randomized rewrites for near-miss matches.

## When a function won't match — the investigation loop

Before parking ANY function, work through these steps in order. Most
mismatches that look "compiler-blocked" yield to step 2 or step 4.

### Step 1: Identify the EXACT instruction-level diff

Run `tools/quick_diff.sh <name>`. Name the specific instructions and
registers that differ — never say "regalloc differs" without naming
them. If quick_diff shows only `daddu | or` for register-zero moves,
that's a known assembler false positive — run `make` to confirm SHA-1
before assuming a real mismatch (see "quick_diff vs full build").

### Step 2: Read the ee-gcc backend source

The ee-gcc 2.9-991111 source is downloadable as
`ee-gcc-2.0.zip` from `github.com/GirianSeed/ee-gcc/releases`
(release tag `src-2.9-ee-991111-01`, matches our `tools/cc/ee-gcc2.9-991111`
binary). Extract and `grep -n <mnemonic>` in
`src/gcc/config/mips/mips.c` and `mips.md` to find the emit site
and its gating conditions. Most "the compiler can't emit X" claims
are wrong — the compiler can, you just need C that satisfies the
gate (target flags, RTX modes, signedness, register class).

Example gates already documented:

  - `lwu`: `unsignedp && TARGET_64BIT` in mips.c (~L1865). Trigger
    by holding the loaded value in a 64-bit-typed expression:
    `long x = *(unsigned int *)p; return ((int)x) & 1;`
  - `j $31` end-of-function: emitted from mips.md `return` template
    `"%*j\\t$31"` outside `.set noreorder` — see step 4.

### Step 3: Construct C that satisfies the gate

Idioms that have worked:

  - **Type chains** to control sign/size: `long`, `unsigned long`,
    `(int)(unsigned int)x`, casts on cast results.
  - **Register pins** for regalloc: `register T *v0 __asm__("$2") = ...;`
    forces gcc to assign that variable to `$v0`. Combine with
    inline-asm operand binding `"+r"(var)` to thread state.
  - **Type the function pointer**: `extern void f(void *fn, ...);`
    + `f((void *)func_X, ...)` produces a `lui+addiu` pair for the
    function pointer.
  - **Type the global**: `extern char D_X[];` produces lui+lo;
    `extern int D_X;` produces gp_rel for in-sdata-range globals.

### Step 4: Promote to a handwritten-asm leaf (`hasm`) via a header macro

When the function is *structurally* a handwritten leaf — a syscall
wrapper, a VU0/COP2 macro shim, an instruction sequence that has no
C-language semantics (e.g. `syscall` itself) — express it as a
**header-defined macro** that expands to the asm body, and keep the
`.c` source as a one-line macro invocation. The yaml entry stays `c`
so the function counts toward `.text` matched-%, but the asm lives in
a header that other peer leaves can reuse.

This is the **preferred escape hatch over Step 5 (postprocess)**.
Reach for a postprocess only when *gcc CAN emit the correct shape but
gas reorders it*, or when *the original codegen depends on
inter-function layout gcc can't know about*. If the body is genuinely
not expressible in C (e.g. needs `syscall`, `vrnext`, `qmfc2`, or a
specific delay-slot fill), promote to `hasm`-via-header instead.

Existing examples:

  - `include/syscall.h` — `SYSCALL_WRAPPER(name, num)` macro emitting
    `addiu $3, $0, NUM; syscall 0`.  Used by all 150 leaf wrappers in
    `src/cod/0001*.c..0009*.c`.  Inspired by ps2sdk's
    `ee/kernel/src/kernel.S` `SYSCALL_SPECIAL` macro.
  - `include/include_asm.h` — generic `INCLUDE_ASM(FOLDER, NAME)` macro
    that `.include`s a handwritten `.s` file at assembly time.  Mirrors
    sotn-decomp's `include/include_asm.h`.

When adding a new pattern:

  1. Define the macro in `include/<topic>.h` (e.g. `include/vu0.h` for
     a COP2 macro family).  Give it a descriptive name in the form
     `<TOPIC>_<SHAPE>(name, args...)`.
  2. Write the asm body inside `__asm__ __volatile__("<one-instr>" ...)`
     blocks — one instruction per `__asm__` block (project rule).
  3. The `.c` source becomes `#include "<topic>.h"` plus one macro call
     per leaf.  No raw `__asm__` in `.c` files.
  4. Cross-reference ps2sdk (`ee/kernel/src/kernel.S`, `ee/vu0/src/`)
     for shape and naming inspiration (clean-room re-derive — never
     paste).

If the macro abstraction would be a one-off (only one function uses
this shape), prefer Step 3 (raw inline asm in the single .c file with
register pins) over a single-use header.

### Step 5: Postprocess the .s file (and check adjacent functions)

**Last resort.** Only reach for postprocessing when gcc CAN emit the
right instructions but gas reorders or expands them differently, OR
when the original codegen relies on inter-function layout that gcc
doesn't know about (shared-epilogue / fall-through stubs). If the
issue is "this isn't expressible in C," go back to Step 4 instead —
header-macro hasm is preferred over a new postprocess pass.

When **adding** a new postprocess, first ask: can the same effect be
expressed as a header-macro hasm pattern (Step 4)? If yes, do that
instead. Postprocesses are accepted only when the transformation
depends on cross-function layout (shared epilogue stubs, jr-ra
delay-slot fall-through to next function) or on assembler-level
quirks (gas-reorder pulling spills into delay slots) that would
require contorting C to defeat.

When **revisiting** an existing postprocess: if the function(s) it
covers are structurally handwritten leaves (single-purpose, narrow
opcode set, repeated shape across siblings), migrate to a
header-macro hasm in `include/<topic>.h`. Postprocess passes that
guard inter-function layout (`shared_sp_restore`, `shared_jr_restore`,
`no_trailing_nop`) typically can't migrate; passes that compensate
for a single-function gas-reorder quirk (`la_sd_interleave`) usually
can.

**Always check what's adjacent to your function in the linker.**
The original Pro-DG / CodeWarrior emitted "shared epilogue stubs":
1- to 4-instruction functions whose body is JUST the missing
prologue/epilogue piece, reachable by fall-through from the preceding
function. If your function ends 4–8 bytes too long, look at the
function immediately AFTER it in `config/ico.us.yaml` (and its
`asm/cod/<NEXTOFF>.s`). If you see a tiny 4-byte function like
`addiu sp, +N; endlabel` or 8-byte `jr ra; addiu sp, +N; endlabel`,
your function is supposed to fall into it — strip the corresponding
suffix from your function's `.s`.

Existing postprocess passes (each driven by a per-file allowlist).
**hasm-migration column** flags whether the pattern is a candidate for
Step 4 (header-macro hasm) instead — re-evaluate during refactor:

  - `config/swap_addu_operands.txt` → sed: addu rs/rt swap.
    *hasm-migration:* not really — single-instruction encoding tweak.
  - `config/coalesce_v1_v0.txt` → sed: drop redundant `move v0,v1`.
    *hasm-migration:* unlikely — register-allocation tweak per-function.
  - `config/swap_sw_pair.txt` → `tools/postprocess_sw_pair.py`.
    *hasm-migration:* unlikely — paired-store ordering inside C body.
  - `config/no_trailing_nop.txt` → `tools/postprocess_no_trailing_nop.py`:
    wraps the final `$L<N>: j $31` in `.set noreorder`/`.set reorder`
    so gas doesn't auto-fill the delay slot with a nop. Use when the
    original codegen leaves the jr ra delay slot empty (next function's
    first instruction acts as the implicit delay slot).
    *hasm-migration:* no — depends on inter-function layout.
  - `config/shared_sp_restore.txt` → `tools/postprocess_shared_sp_restore.py --sp-only`:
    strips the `addu sp, +N` from the delay slot of `j $31`. Use
    when the next adjacent function is a 4-byte `addiu sp, +N` stub.
    *hasm-migration:* no — depends on inter-function layout.
  - `config/shared_jr_restore.txt` → `tools/postprocess_shared_sp_restore.py --jr-and-sp`:
    strips both the `j $31` and the `addu sp` from the gcc-emitted
    epilogue. Use when the next adjacent function is an 8-byte
    `jr ra; addiu sp, +N` stub.
    *hasm-migration:* no — depends on inter-function layout.
  - `config/la_sd_interleave.txt` → `tools/postprocess_la_sd_interleave.py`:
    interleaves `sd $31, OFF($sp)` between the `lui` and `addiu` halves
    of an la-macro emission. Used by 5-arg-via-`$t0` wrappers
    (`func_0024DA50`, `func_0024DA20`).
    *hasm-migration:* attempted; not viable — the wrappers carry
    gcc-generated prologue/epilogue and call-arg setup around the la
    macro, which a header-macro can't reproduce without a `naked`
    attribute (ee-gcc 2.9 doesn't support `naked`). Postprocess is
    the right tool here.

To add a new postprocess:

  1. Write `tools/postprocess_<name>.py` that takes a `.s` path and
     edits in place. Make it idempotent.
  2. Add a per-file allowlist in `config/<name>.txt`.
  3. Add a Makefile clause modeled on the existing ones.
  4. Document the precondition (when it's safe to apply, what
     adjacent functions or call patterns are required).

### Step 6: Park or `.skip` only after steps 1–5 are exhausted

In the parked notes, name the SPECIFIC compiler/assembler limitation
that blocks the match. "Regalloc differs" is not a documented reason
unless you also name (a) the instruction, (b) the registers expected
vs. emitted, (c) what mips.c rule allocates them, (d) why no C
formulation hits a different rule, and (e) why a header-macro hasm
promotion isn't appropriate (e.g., the body is too function-specific
to share, or the issue is scheduling not C-expressibility).

## Picking the next target

**Default: read `docs/candidates.md`.** It's auto-regenerated at the end
of every `make setup` from a cached parse of `asm/cod/*.s`, sorted by
hard-pattern penalty / instruction count / size, with parked functions
already excluded. Eight pre-baked shape buckets cover the common shapes
I keep targeting (4-insn 0x10 leaf, 5-insn 0x14 store-and-forward, 8-insn
0x20 1-jal wrapper, etc.). `grep -E '^\| `func_'` and pick promising rows.

Only fall back to `tools/find_leaves.py` for ad-hoc shape filters that
aren't in the pre-baked buckets. The tool is a per-file pickle-cached
walker (so subsequent calls are fast), but the candidates file is
faster still and persistent.

## Per-function loop

1. Pick a `[0xADDR, asm]` line in `config/ico.us.yaml`. Prefer small,
   leaf-ish ranges. Look at the `.s` file to gauge complexity.
2. Change the line to `[0xADDR, c, name]` (and split the surrounding
   asm subsegment so the new `c` line has explicit asm neighbours).
   Re-run `make setup`. Splat emits the per-function baseline at
   `asm/matchings/name/<func>.s` (gitignored — regenerable from the
   ELF) and expects `src/name.c`.
3. Write the C. Iterate fast with `tools/quick_diff.sh name` until the
   diff is empty or trivially close.
4. Run `make` for the full byte-identical SHA-1 check. If it fails,
   run `tools/first_diff.py` and address the first divergence.
5. If stuck near-match: try `lib/decomp-permuter/` (timeout 300 s for a
   first attempt). If still stuck, park.
6. Once it matches, run `make progress`, run `./tools/check_no_rom.sh`,
   commit. No AI co-author trailer.

## Tough-nut parking

When a function plateaus (permuter exhausted, no obvious structural fix):

**Use `tools/park.sh <vram> "<reason>"`.** It does steps 1-3 below in one
go: moves the best-attempt `src/cod/<file_off>.c` into
`tough_nuts/<func>/<file_off>.c`, writes a `notes.md` with the reason
and a disassembly excerpt for permuter context, and reverts the yaml
line back to `asm`.

After parking, run `make setup && make` to confirm the asm fallback
round-trips, then commit. The auto-permuter (`tools/auto_permute*.sh`)
picks up the new `tough_nuts/` seed on its next pass.

### NEVER revert+delete a near-miss .c file

This is a hard rule, not a guideline. **If you wrote a .c file, ran
`make`, and the SHA-1 mismatch is small (1-3 instructions, scheduling
or regalloc differences, a single relocation flavor mismatch), park
the file via `tools/park.sh`.** Do not:

- `git checkout -- config/ico.us.yaml` to revert the claim and then
  `rm src/cod/<file_off>.c` because "it's not matching." The .c file
  is a **permuter seed** — even a 1-instruction-off attempt is much
  more valuable to the auto-permuter than a blank slate. Throwing it
  away undoes work the next session has to redo.
- "Just revert this one, I'll come back to it later" — you won't,
  and the C body is gone. Park it now.
- Squash a near-miss into the same yaml-revert commit that drops a
  bad batch — separate parking commits keep `tough_nuts/` reviewable.

The only time it's correct to revert+delete instead of park is when
the .c file was structurally wrong from the start (called the wrong
function, used the wrong type, etc.) and is not a useful seed. If the
diff was within ~3 instructions, it's a useful seed. Park it.

### Manual steps (what `park.sh` does)

1. Revert the yaml line to `[0xADDR, asm]`. Run `make setup` to confirm
   the tree is clean.
2. Move the best-attempt `src/name.c` to `tough_nuts/<func>/<func>.c`.
3. Write `tough_nuts/<func>/notes.md` with: failure mode, permuter
   plateau score, structural hints from the asm, what's been tried.
4. Commit the parking-doc only — no broken `src/` left behind.

## Leverage building

When a tough nut cracks, the *recipe* is often higher leverage than the
function itself. Codify recurring patterns in `decomp/NOTES.md`. If a
trick generalizes across ≥2 functions, lift it into saved memory so
future sessions inherit it.

## Wrap-up (only when stopping for cap or user prompt)

When the cap is imminent or the user has told you to stop:

- Keep the working tree clean — revert any half-finished `src/` files
  rather than committing broken state.
- ELF SHA-1 must match at session end (`make` exits 0). If it doesn't,
  revert the last edit until it does.
- `git status` empty before the last commit lands.
- Do **not** emit an "iteration results" or "session summary" — the
  commit log is the record. See "Do not stop matching" above.

## If running unattended

(This section is the seam from which a future `decomp/HEADLESS.md` will
be split off. Skip if running interactively.)

- No `/loop`, no `ScheduleWakeup`, no user Q&A.
- Per-iteration commit cadence: one commit per matched function or per
  parked tough-nut.
- Stop condition: <15 min of usage budget left, or three consecutive
  iterations with no matches and no progress on tough nuts.
- Append a one-line entry to `decomp/RUN_LOG.md` (gitignored) per
  outcome: ISO-8601-Z timestamp, target, matched / deferred, commit
  SHA, one-liner.
