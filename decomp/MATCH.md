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
(many batches, many candidates, retries, postprocess additions,
header-macro promotions) before it naturally terminates at the usage
cap or a user prompt.

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
- The current target plateaued. Check the diff-triage cheat-sheet —
  if no cheat-sheet row matches and no sibling shape applies, **park
  it** via `tools/park_tu.py` and move on. The permuter pool picks up
  the seed. See "Tough-nut parking" below.
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
(commits, `decomp/NOTES.md` edits, new postprocesses, header-macro
additions) is the record. Brief mid-stream status notes ("matched
func_X", "iterating on func_Y", "moving on to subseg Z") are fine —
but the moment a listed/numbered
recap shows up, the session has bugged out. Just keep matching.

**Read first** (in this order):

1. `CLAUDE.md` — IP rules, toolchain, build commands, conventions.
2. `decomp/NOTES.md` — every PS2 EE / compiler / splat / linker quirk
   catalogued so far. Most "near-miss" diffs are an instance of a
   pattern in here.
3. `decomp/COOKBOOK.md` — shape-indexed C recipes (asm fingerprint →
   C template + headers). Skim the ToC; when you spot a familiar asm
   shape, jump straight to that section.
4. `docs/MATCHING_NOTES.md` — per-function tough-nuts and deferred
   targets.
5. `docs/LEGAL.md` — clean-room boundary, what's allowed as a reference,
   what's forbidden as an input.

## Recipe-first fast path (use this FIRST on every new function)

**The fast path starts with `auto_match --bucket`, NOT with reading
individual `.s` files.** Hand-classifying one candidate at a time is
the slow path — it burns minutes per function on triage before any C
is written. Bucket-classify a whole TU in one shot, then look at the
table and pick the high-leverage rows.

### Step 0 — Always: bucket-classify before reading any asm

```sh
tools/auto_match.py --bucket asm/nonmatchings/src/<TU>/
```

That prints a one-line-per-candidate table with vram, size, top recipe,
and outcome (`scaffold` / `no-template` / `no-recipe`). Read the table
once; do NOT read individual `.s` files until the table tells you
which functions are worth opening.

What to do based on the outcome column, in priority order:

  - **`scaffold` rows** — the classifier has a template for this shape
    (§1.x wrappers, §2.x regalloc, §7.x mixed FP, etc.). If 3+ rows
    in the same bucket have the same recipe id, batch-claim them
    together with `--apply` (see "Batch claim" below). If only one,
    `--scaffold-only` it and iterate by hand.
  - **`no-template` rows** — recipe matched but its entry is a PARK
    (§1.3, §3.3) or branch-likely-only diff. These need direct Step
    4 / Step 5 work (header-macro hasm or new postprocess); don't
    iterate C on them.
  - **`no-recipe` rows** — natural-C territory. Open the `.s`, write
    naive C, quick_diff. These are the slowest per-function but often
    the most numerous in close-to-done TUs.

### Batch claim (`--apply`) — preferred when ≥2 templated rows

```sh
tools/auto_match.py --apply --bucket asm/nonmatchings/src/<TU>/
```

Writes scaffolds for every templated candidate, claims them in yaml,
runs `tools/build.sh setup` ONCE (nuclear-clean batching), then
quick_diffs each. Diff-table tells you which immediately landed and
which need more iteration. **Refuses if `src/cod/` is dirty** — commit
or stash first.

### Single function (when a bucket isn't right)

```sh
# Just classify, don't scaffold
tools/classify_asm.py asm/nonmatchings/<TU>/func_<addr>.s

# Scaffold to stdout (review before writing)
tools/classify_asm.py --scaffold asm/.../func_X.s

# Scaffold straight to disk
tools/classify_asm.py --scaffold --write src/cod/<file_off>.c asm/.../func_X.s

# Scaffold by recipe id when you've already decided
tools/classify_asm.py --recipe 2.1 --name func_X --write src/cod/<off>.c
```

### Scaffolds are sketches, not drop-ins

The scaffold output is a 10-20 line C **sketch** showing the recipe's
canonical shape with `func_target` / `OFF` / `D_X` placeholders. It is
not standalone code — you fill in the callee names, operand offsets,
and struct types from the `.s` jal targets and operand context. Some
scaffolds (e.g. §2.1) are just the regalloc trick fragment (a single
`register REG("$3")` declaration + `KEEP_LIVE`) — you still write the
surrounding body.

### Coalesced-TU quick_diff invocation

For coalesced TUs (the function lives in `src/<TU>.c` via `INCLUDE_ASM`
rather than its own `.c` file), pass the TU name AND the function name:

```sh
tools/quick_diff.sh <TU>           # only works for single-function .c
tools/quick_diff.sh <TU> func_X    # for multi-function .c (the common case)
```

The script disassembles the whole TU but uses `--disassemble=func_X`
on both sides so the comparison is scoped to just that function. The
remaining "differences" in the diff output that show `jal 0 <other_func>`
on one side and `jal 0 <func_X>` on the other are cosmetic — objdump
names the relocated branch by the nearest preceding symbol in the
.o file, which differs between built (multi-func) and target
(single-func). Verify byte match by running `ninja` once after the
quick_diff stream is otherwise identical.

## Toolkit

Run `--help` on each tool before first use; expect the inventory to grow
over time.

**Recipe lookup & scaffolding (use these BEFORE writing any C):**

- `decomp/COOKBOOK.md` — shape-indexed cookbook. Each recipe carries an
  asm fingerprint, a C template, required header macros, and a back-link
  to the originating `feedback_*.md` memory. Recipes are grouped:
  §1 wrappers, §2 regalloc nudges, §3 branch shape, §4 conditional,
  §5 pointer/gp_rel, §6 unaligned/MMI, §7 float, §8 scheduler
  postprocesses, §9 frame/stack, §12 build gotchas, §13 one-off
  per-function postprocesses. Appendix A inventories every header macro.
- `tools/classify_asm.py <file.s>` — fingerprints a single `.s` and
  prints the top-N matching recipes from the cookbook. Add `--scaffold`
  to also emit a starter C template with the wrapper name substituted
  in. Add `--write src/cod/<off>.c` to commit it to disk. Use
  `--recipe N.M --name func_X` to scaffold by recipe id without
  classifying.
- `tools/auto_match.py` — batch orchestrator. `--dry-run` prints the
  plan for a list of candidates; `--scaffold-only` writes scaffolds to
  a `/tmp/auto_match_*` dir; `--apply` runs the full pipeline (write
  scaffolds, claim into yaml, `make setup`, quick_diff, tabulate). See
  the "Recipe-first fast path" above.

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

Work through these steps in order. **Parking is forbidden** — every
step has a specific tool; use them. Most mismatches that look
"compiler-blocked" yield to step 2 or step 4.

**Tools available at every step** (cross-reference: Toolkit section
above):

- ee-gcc backend source at `github.com/GirianSeed/ee-gcc/releases`
  (matches our 2.9-991111 binary) — `grep -n <mnemonic>` in
  `src/gcc/config/mips/mips.c` and `mips.md` to find emit sites.
- Header-macro library at `include/syscall.h`, `include/r5900.h`,
  `include/matching.h` — extend with new macros when a pattern repeats.
- `tools/quick_diff.sh <name>` — ~100 ms iteration loop.
- `tools/first_diff.py` — failed-`make` post-mortem with function
  names from the mapfile.
- `lib/decomp-permuter/` — randomized C rewrites; useful when a
  near-miss is regalloc/scheduling and you've exhausted Steps 2–4.
  Launch with `lib/decomp-permuter/import.py` then `permuter.py`.
- Postprocess passes (`tools/postprocess_*.py`) — last resort for
  gas-reorder or inter-function-layout issues; see Step 5.

### Step 0: Classify (always first)

Run `tools/classify_asm.py asm/nonmatchings/<TU>/<func>.s` before
anything else. The fingerprint summary (insn count, frame size, jal
count, branch-likely set, MMI/FP/FCC, gp_rel) tells you which cookbook
section to read; the top-N recipe list tells you which C idiom most
likely applies. If a recipe with a template surfaces, read it from
`decomp/COOKBOOK.md` and start from the scaffold — most of Steps 1–6
below become "fill in the TODOs and verify."

Skipping this step means re-deriving recipes that are already
catalogued. Don't.

### Step 1: Identify the EXACT instruction-level diff

Run `tools/quick_diff.sh <name>`. Name the specific instructions and
registers that differ — never say "regalloc differs" without naming
them. If quick_diff shows only `daddu | or` for register-zero moves,
that's a known assembler false positive — run `make` to confirm SHA-1
before assuming a real mismatch (see "quick_diff vs full build").

If the diff narrows to a pattern catalogued in the cookbook, the
recipe tells you what to do directly:
  - §5.3 (gp_rel addiu vs daddiu false positive) → commit, the bytes
    match the original ELF.
  - §3.3 (branch-likely-only diff) → ee-gcc 2.9 now usually picks bnel
    naturally for known-safe-to-annul shapes; if not, restructure the
    delay-slot operation. See §8.6 (retired postprocess).
  - Any §8.x detector firing → check that postprocess's config gate
    and add the function to its allowlist.

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

### Step 4: Promote to a handwritten-asm leaf via a header macro (preferred), or splat-emitted `.s` (fallback)

When the function is *structurally* a handwritten leaf — a syscall
wrapper, a VU0/COP2 macro shim, an instruction sequence that has no
C-language semantics (e.g. `syscall` itself) — express it as a
**header-defined macro** that expands to the asm body, and keep the
`.c` source as a one-line macro invocation. The yaml entry stays `c`
so the function counts toward `.text` matched-%, but the asm lives in
a header that other peer leaves can reuse.

#### Two patterns, in strict priority order

**Priority: Pattern C (header macro + `c` yaml)** — preferred.

  - The asm body lives in `include/<topic>.h` as a macro.
  - `src/cod/<off>.c` does `#include "<topic>.h"` and a one-line macro
    invocation (or, for matching tricks, a sequence of macro calls).
  - yaml: `[0xADDR, c, cod/<off>]`.
  - Examples: `include/syscall.h` (150 syscall wrappers),
    `include/r5900.h` (SYNC, QCOPY16, …), `include/matching.h`
    (DEFEAT_TCO, KEEP_LIVE, VOLATILE_RELOAD_CALL, …),
    `include/vu0.h` (per-instruction VU0/COP2 macros — see below).

**Fallback: Pattern A (`hasm` yaml + splat-emitted `.s` in `src/`)** —
use only when Pattern C is impossible or impractical.

  - Splat regenerates `src/cod/<off>.s` from the base ELF on `make
    setup` (gitignored regeneration; the `.s` file is committed once
    and splat refuses to overwrite — see `lib/splat/.../hasm.py`).
  - yaml: `[0xADDR, hasm, cod/<off>]`.
  - Splat needs `hasm_in_src_path: True` in the yaml header (already
    set).
  - `progress.py` counts `hasm` the same as `c`.
  - Use when: the function has a fixed-shape body that no header-macro
    abstraction usefully covers (e.g., a one-off byte-level pattern
    that won't recur), OR when the macro abstraction would be a 1:1
    file-per-macro that adds no real reuse.

#### When to choose which

  - **Pattern C (default).** The body is one or more recognisable
    instruction families (syscall, COP2 op, sync barrier, dispatch
    wrapper, etc.).  Even if it's a one-off pattern, prefer Pattern C
    when the body can be expressed as a small number of macro calls
    plus C glue — the .c file documents intent better than splat-emitted
    `.s` does.

  - **Pattern A (fallback).** The body is a long opaque sequence of
    instructions that doesn't fit a macro idiom (e.g., a VU0 routine
    with 14+ unique instructions in a specific schedule), OR Pattern C
    requires `__attribute__((naked))` that ee-gcc 2.9 doesn't support.

This is the **preferred escape hatch over Step 5 (postprocess)**.
Reach for a postprocess only when *gcc CAN emit the correct shape but
gas reorders it*, or when *the original codegen depends on
inter-function layout gcc can't know about*. If the body is genuinely
not expressible in C (e.g. needs `syscall`, `vrnext`, `qmfc2`, or a
specific delay-slot fill), promote to a header macro (Pattern C);
postprocesses are still last resort.

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
  - ~~`config/swap_sw_pair.txt` → `tools/postprocess_sw_pair.py`~~
    **retired 2026-05-21** — use `*(volatile T *)&` cast on both stores.
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
  - ~~`config/la_sd_interleave.txt` → `tools/postprocess_la_sd_interleave.py`~~
    **retired 2026-05-21** — use the `LA_SPLIT` macro from
    `include/matching.h`, which emits `lui` and `addiu` in two
    separate `#APP/#NO_APP` blocks with an interior `KEEP_LIVE`. ee-gcc
    2.9 then schedules `sd $ra` in the gap, matching the original.

To add a new postprocess:

  1. Write `tools/postprocess_<name>.py` that takes a `.s` path and
     edits in place. Make it idempotent.
  2. Add a per-file allowlist in `config/<name>.txt`.
  3. Add a Makefile clause modeled on the existing ones.
  4. Document the precondition (when it's safe to apply, what
     adjacent functions or call patterns are required).

### Step 6: Permuter as the next-to-last resort

When Steps 1–5 leave a near-miss (≤3 instructions different, regalloc
or scheduling shape), run `lib/decomp-permuter/`:

  1. `lib/decomp-permuter/import.py src/cod/<name>.c <func_name>` —
     creates a permuter input directory under
     `lib/decomp-permuter/nonmatchings/<func_name>/`.
  2. `lib/decomp-permuter/permuter.py lib/decomp-permuter/nonmatchings/<func_name> --threads N`
     — runs randomized rewrites; emits `output-<i>-<j>/` directories
     with `score.txt` per attempt.
  3. **Score 0 = match.** Promote the seed (copy
     `output-0-0/source.c` to `src/cod/<name>.c`), run `make` to
     confirm SHA-1, commit.
  4. Stop after 60–300 s of permuter runtime if no score-0 emerges
     and the running best is plateaued; investigate the specific
     near-miss shape and feed back into Step 3 (new C idiom) or
     Step 5 (new postprocess).

The auto-permuter (`tools/auto_permute*.sh`) IS the escape hatch for
live work. After 1 quick_diff iteration with no cheat-sheet recipe and
no sibling leverage, park to `tough_nuts/` (`tools/park_tu.py` for
coalesced TUs, `tools/park.sh` for legacy `src/cod/`). The permuter
chews on the seed across passes; score-0 hits land in
`lib/decomp-permuter/runs/<func>/output-0-*/source.c` and get
promoted back into the TU by hand or via promote tooling. Step 4
(header-macro hasm) and Step 5 (new postprocess) are still the right
moves when you can SEE the gap class — but for "permuter-shaped"
shapes (reg shuffle, branch likely, scheduling), park is faster.

### Step 7: Park to the permuter pool (1-iteration rule)

**Park aggressively.** If your first `quick_diff` doesn't byte-match,
check the cheat-sheet (below) and:

1. **If the diff shape matches a cheat-sheet row** — apply that recipe
   directly. Most one-shape diffs (volatile-cast store order, REG
   pins, KEEP_LIVE barriers) land in iteration 2.
2. **If you have a confirmed sibling shape** in the same TU — try
   transferring the trick from the sibling. Sibling-transfer matches
   typically land in 1–2 iterations.
3. **Otherwise, park immediately.** Don't grind. The cheap default is:

   ```sh
   # Coalesced TU (src/<TU>.c):
   tools/park_tu.py func_X src/<TU>.c "<short reason>"
   # Edit the TU to revert the function body to INCLUDE_ASM(...)
   ninja  # confirm SHA-1 round-trips with asm fallback
   git add -A && git commit -m 'Park func_X (<reason>)'

   # Legacy single-function file (src/cod/<file_off>.c):
   tools/park.sh 0x<vram> "<reason>"
   ```

   The parked seed lands in `tough_nuts/func_X/`. `tools/auto_permute.sh`
   picks it up on its next pass and chews until score-0 or
   `STOP_AT_SCORE`. Score-0 hits land in
   `lib/decomp-permuter/runs/func_X/output-0-*/source.c`.

**Why park aggressively:** manual iteration is the slow step. Permuter
explores reg-shuffle / branch-likely / scheduling space at thousands
of attempts per minute — orders of magnitude faster than a human
trying shapes by hand. Burning your attention on iter 3+ of the same
function is the same compute the permuter would have done for free.

**Don't park when you have leverage**: a sibling shape you've already
matched in the TU, a cheat-sheet recipe with a labeled fix, or a
known-class postprocess gap. Those are 1-iteration wins, not
permuter-shaped problems.

## Picking the next target

**`docs/candidates.md` does not currently exist.** The pre-baked
candidate file the old prompt used to point at hasn't been regenerated
since the TU-coalesce work landed. Until it comes back, use the live
discovery commands below. Each runs in well under a second and skips
already-claimed functions thanks to the filter in `tools/auto_match.py`.

### Fastest path to the next match — three live queries

These are ordered by leverage. Try them in order; stop at the first
that yields a tractable candidate.

**A. Close-to-done TU buckets** — partially decompiled TUs with a small
number of remaining `INCLUDE_ASM` lines are the highest-leverage target.
Finishing one of them lets the TU move from "partial coalesce" to "fully
matched" and often surfaces a sibling family the classifier can crack
together.

```sh
# Rank typed TUs by remaining INCLUDE_ASM count (lowest = closest to done)
grep -rcE 'INCLUDE_ASM' src/*.c \
  | awk -F: '$2 > 0 && $2 < 15' \
  | sort -t: -k2 -n \
  | head -10

# Pick one and classify its unmatched funcs in one shot
tools/auto_match.py --bucket asm/nonmatchings/src/<TU>/
```

The bucket output already prints recipe verdicts per candidate; the
high-weight rows (§1.2, §1.7, §2.1, §6.x, §7.x at weight ≥ 0.7) are
the immediate plays.

**B. Sibling families inside a single TU** — within a chosen TU, look
for several `INCLUDE_ASM` lines whose callees share a target. Those
are wrappers around the same helper; classifier rules tend to fire on
all of them.

```sh
# Pull every unmatched func name out of one TU
grep -oE 'INCLUDE_ASM\([^,]+,\s*func_[0-9A-Fa-f]+\)' src/<TU>.c \
  | grep -oE 'func_[0-9A-Fa-f]+'

# Eyeball the .s files for a common jal target → sibling family
for fn in <names>; do
  grep -h '^[ \t]*jal ' asm/nonmatchings/src/<TU>/$fn.s | head -3
done | sort | uniq -c | sort -rn
```

**C. Pure-asm subsegs** — fall back here when the typed TUs offer
nothing tractable. These are `[ADDR, asm, src/cod/<off>]` entries that
have never been claimed; they're noisier (many are big or weird) but
some are small leaves the classifier can recognize.

```sh
# A few random small pure-asm candidates — `shuf` gives variety so
# repeated sessions don't keep landing on the same heads
grep -nE '\[0x[0-9A-F]+, asm, src/cod/' config/ico.us.yaml \
  | shuf | head -10
```

Then `tools/auto_match.py` on the candidates that look small from
their `.s` size.

### Why this order

- (A) is highest-yield because a close-to-done TU has structural
  context (sdata, prototypes, sibling matched funcs) that often makes
  a remaining `INCLUDE_ASM` solvable from the same recipe a peer used.
- (B) is the fast-pass pattern (`feedback_fast_pass_subshape`): ~50%
  first-try match rate when 3-5 funcs share an exact wrapper shape.
  `auto_match.py --apply` is built for exactly this case.
- (C) is broad-search; lower hit-rate per candidate, but unblocks
  matching once the typed TUs hit a wall.

### Don't waste time on

- Brute-forcing all ~880 unmatched funcs through `classify_asm.py`
  one at a time. That iterates the full INCLUDE_ASM set serially and
  takes minutes. The queries above carve out the right ~10-20 to
  inspect.
- Picking from `asm/nonmatchings/` by name without a yaml-or-INCLUDE_ASM
  check first. That tree has stale per-function `.s` artifacts from
  before the TU coalesces — they look unmatched but aren't.
  `auto_match.py`'s filter catches this for free; `classify_asm.py`
  alone does not.

### TU-level / coalesce work

**For TU-level work** (coalescing src/cod/<hex>.c shims into per-TU
files, not individual function matching), read in order:

- `docs/tu_coalesce.md` — TU coalesce queue, ranked by cod-shim count
  descending. Regenerated by `tools/tu_candidates.py`.
- `docs/tu_candidates.md` — close-to-done TUs first (companion ranking).
- `decomp/placement_plan.md` — per-function placement recommendations
  (PROMOTE_TYPED vs INCLUDE_ASM vs NO_ACTION) with confidence/evidence.
  Regenerated by `tools/build_placement_plan.py`.

These are complementary to the live discovery queries above:
queries A/B/C pick one function to match; the TU-level docs above
pick a structural promotion target.

**Skip the giants when coalescing.** `src/way_tool.c` (558 funcs),
`src/PObj.c` (410), `src/commonact.c` (217 — partial already at
`[0x0683A8, c, src/commonact]`, don't expand), and `src/motionManager.c`
(121) are off-limits for whole-TU promotion. Compile-per-attempt cost
scales linearly with TU size and a 558-func TU would dominate the
matching loop. Promote *named slices* only (commonact-style partial),
or skip these and pick a smaller TU. See `decomp/NOTES.md` § "`main`
location and the don't-coalesce-the-giants-yet rule".

## Per-function loop

1. Pick a `[0xADDR, asm]` line in `config/ico.us.yaml`. Prefer small,
   leaf-ish ranges. Look at the `.s` file to gauge complexity.
2. **Classify before claiming.** Run
   `tools/classify_asm.py asm/nonmatchings/<TU>/func_<addr>.s` to see
   the recipe verdict. If the top recipe has a template, scaffold
   directly with `--scaffold --write src/cod/<file_off>.c`. If the
   verdict is `§0.0 natural C` or `no recipes matched`, write naive C
   yourself.
3. Change the yaml line to `[0xADDR, c, name]` (and split the
   surrounding asm subsegment so the new `c` line has explicit asm
   neighbours). Re-run `make setup`. Splat emits the per-function
   baseline at `asm/matchings/name/<func>.s` (gitignored — regenerable
   from the ELF) and expects `src/name.c`. The scaffold from step 2 is
   already at the expected path.
4. Fill the TODO placeholders in the scaffold (callee names from jal
   targets, struct field offsets from the asm). Iterate with
   `tools/quick_diff.sh name` until the diff is empty or trivially close.
5. Run `make` for the full byte-identical SHA-1 check. If it fails,
   run `tools/first_diff.py` and address the first divergence.
6. If stuck near-match: identify the exact codegen decision that
   differs (operand order, regalloc, branch direction, delay-slot
   fill). Try at least 3–5 distinct C reformulations from the cookbook
   §2/§3/§4 (REG pins, MATERIALIZE/KEEP_LIVE barriers, volatile casts,
   goto labels, single-vs-multi return points). If no C formulation
   reaches the target, escalate to Step 4 (header-macro hasm) or Step
   5 (new postprocess) of the investigation loop. **Do not park.**
7. Once it matches, run `./tools/check_no_rom.sh`, commit. No AI
   co-author trailer. (The progress tables are refreshed by
   `tools/self-monitor.sh` on its 10 s tick — don't run `make progress`
   from the matching loop.)

### Batch alternative — `tools/auto_match.py --apply`

For a homogeneous bucket (several candidates sharing the same recipe
shape, e.g. all 2-jal wrappers in a TU), `auto_match --apply` does
steps 2-4 for the whole batch in one pass: scaffolds every candidate,
claims them, runs `make setup` once (nuclear-clean), and reports
matched/diffs per candidate. Then you iterate on the `diffs` rows
individually starting at step 4 of the per-function loop.

## Tough-nut parking — the default after 1 iteration

**Park aggressively.** The old rule was "no parking, grind every
function to match" — that overweighted human iteration. The new rule:
after 1 quick_diff iteration that doesn't byte-match, the *default*
next action is `tools/park_tu.py` (coalesced TU) or `tools/park.sh`
(legacy `src/cod/`). The seed lands in `tough_nuts/func_X/` and the
permuter pool chews on it across passes.

The exceptions — keep iterating directly — are narrow but real:

1. **Cheat-sheet-recipe diffs.** If the diff shape matches a row in
   the diff-triage cheat-sheet below, apply that recipe directly.
   That's an iteration-2 match, not a permuter problem.
2. **Sibling-transfer.** If you matched func_Y in this TU and func_X
   looks identical, port the trick. Usually iter 1–2.
3. **Postprocess work.** If you can see the postprocess gap (gas
   reorders correct gcc emit, missing class-level rewriter), add the
   postprocess instead of parking. See Step 5 of the investigation
   loop.

Everything else — alloca, packed-struct alignment proofs, search
loops with branch-likely heuristics, reg-shuffle near-misses, state
machines, frame-size mismatches — is permuter-shaped. Park it after
iter 1, save your attention for shapes you have leverage on.

**Why this changed:** of 62 score-0 permuter hits in the runs
directory, ~95% land within their first auto_permute pass.
Iterating manually past iter 1 on a non-leverage shape is the same
compute the permuter would have done for free overnight. The
expensive resource is human attention, not CPU.

### Reverting — fine, just save the seed first

Reverting an in-progress C body to `INCLUDE_ASM` is now the natural
park flow. The rule is: **don't delete the seed.** Run `park_tu.py`
or `park.sh` *first* to write the seed into `tough_nuts/<func>/`
before reverting. Only then revert the TU file and confirm ninja
round-trips with the asm fallback.

Structurally-wrong attempts (called the wrong function, wrong arg
types, would never match no matter the codegen) can still be
revert + delete without parking — they'd just spin the permuter at
score>500 forever. Use judgment: 30 lines of type-confused mess at
first quick_diff = revert; anything that compiles cleanly and produces
a near-miss diff = park.

### Diff-triage cheat-sheet (read BEFORE iterating more than twice)

When stuck, run quick_diff once and classify the *shape* of the diff
before trying another C reformulation. The recipe to reach for is
implied by the shape:

| Diff shape | Recipe | Source of fix |
|---|---|---|
| Only branch mnemonic (`beq` vs `beql`, `bne` vs `bnel`) | §8.6 (postprocess retired) — gcc usually picks bnel natively; restructure delay-slot op if not | source-level |
| `daddiu` (expected) vs `addiu` (built) on `%gp_rel` | §5.3 false positive | commit as-is |
| Only one FP reg letter differs (`$f0` vs `$f1`) | §2.6 `REG("$fN")` pin in `{ }` block | feedback_fpr_letter_swap |
| Chain of `lw $rT, OFF($rs)` where expected alternates `$v0`/`$v1`, built uses one reg | §2.7 DUAL pin (`p_v0` + `p_v1`, alternate source) | feedback_dual_pin_alternating |
| `swc1` (or `sw`/`sd`) in jal delay slot vs `addiu`/`lw` in expected delay | §8.22 `__asm__ volatile("" ::: "memory")` between trailing stores and call | feedback_memory_barrier_before_call |
| `lui+addiu` of `D_X` clusters right before `jal`, expected has them earlier | §5.7 `T *p = D_X; KEEP_LIVE(p);` | feedback_eager_rodata_materialize |
| Single missing `daddu $v1, $v0, $0` after a jal | §2.1 `REG("$3")` + `KEEP_LIVE(q)` | feedback_keep_live_v1_pin |
| `ld $31` and `daddu $v0,$0,$0` swapped at epilogue | §8.3 C fix: convert multiple `return 0;` to `goto end; ... end: return 0;` | retired postprocess |
| Operand swap on `addu $X,$Y,$Z` vs `addu $X,$Z,$Y` | §8.11 postprocess `swap_addu_operands` | already wired |
| `nop` between branch and "would-be delay" sw | §8.5 (blez/likely) or §8.21 (beq/bne) postprocess | already wired |
| Trailing `nop` after `j $31` | §8.12 postprocess `no_trailing_nop` | already wired |
| `c.lt.s` / FCC compare without trailing `nop` | §8.15 postprocess `fcc_nop` | already wired |

If the diff doesn't match any row above, **then** iterate. If it does
match, jump straight to that recipe — don't burn time trying naive
reformulations of the C.

Running `tools/quick_diff.sh <TU> <func>` automatically pipes the diff
through `tools/tag_diff.py`, which fires hints matching this table.
Read the hints **before** iterating.

## Leverage building — codify the recipe, not just the match

When a tough nut cracks, the *recipe* is often higher leverage than
the function itself. The cookbook + classifier + memory system only
stays useful if you feed it every time you discover a new shape.

### When you crack a new pattern — DO THIS BEFORE MOVING ON

If the trick you just used isn't already in `decomp/COOKBOOK.md`,
make these additions in the SAME commit (or the immediately-following
one) as the match itself:

1. **Save a feedback memory** — `feedback_<short-slug>.md` in the
   memory dir. Structure: rule → **Why:** → **How to apply:**. Always
   helpful — it captures the *why* even before you know if the trick
   generalizes.
2. **Add a recipe to `decomp/COOKBOOK.md`** if the trick generalizes
   (or is plausibly going to). Pick the right section by what you'd
   grep for in `.s`: §1 wrapper shape, §2 regalloc, §3 branch, §4
   conditional, §5 pointer/gp_rel, §6 unaligned/MMI, §7 float,
   §8 scheduler postprocess, §9 frame/stack, §12 build gotcha,
   §13 one-off per-function postprocess. Each recipe carries:
   - ASM fingerprint (the line you'd grep for)
   - ```c template (the canonical C body — this is what the
     classifier's `--scaffold` mode emits, so make it compilable)
   - Headers (`matching.h` / `regpin.h` / `r5900.h` as needed)
   - One-sentence Why (compiler bias being defeated)
   - Example: `func_X` and a link back to the feedback memory
3. **Add a classifier rule** in `tools/classify_asm.py` if the asm
   fingerprint is detectable from a single-pass scan. Append a `R(...)`
   entry to `RULES` with the predicate list, weight, and the recipe
   id (e.g. `"4.3"` to anchor to §4.3). If the rule needs a multi-line
   pattern (e.g. "bltzl followed by negu"), add a derived signal in
   `_derive_signals()` first.
4. **If a new postprocess was needed**, also add a §8.x or §13 entry
   in the cookbook with: pattern (gcc-emit shape), fix (config file +
   tu/func entry), example function. Cross-reference the script
   filename.

### Threshold — recipe vs memory-only

- **One function cracked**: write the feedback memory, defer the
  cookbook entry. Don't speculate on shape generality from N=1.
- **Two functions cracked with the same trick**: cookbook entry. Two
  occurrences is enough signal that future sessions will hit it.
- **A whole sibling family cracked**: cookbook entry + classifier rule.
  The rule prevents the next session re-discovering it manually.
- **A new postprocess landed**: cookbook §8/§13 entry mandatory. The
  config file allowlist is opaque without it.

### When to extend the classifier, not just the cookbook

The cookbook is human-discoverable (Ctrl-F or skim ToC). The
classifier is automatic — it surfaces the recipe without the human
having to remember to look. Add a classifier rule when:

- The asm fingerprint is concrete (specific mnemonic, operand shape,
  frame/jal/branch pattern) — not "vibes."
- A predicate can be expressed in pure-stdlib Python over the
  `Signals` dict. Multi-line patterns get a `_has_*()` helper in
  `_derive_signals()`.
- The rule's weight makes sense in the existing ranking. Specific
  recipes get 0.7–1.0; "hint" rules (e.g. "FCC compares present,
  might need fcc_nop") get 0.3–0.4.

Don't add a classifier rule when the recipe is "write naive C" or
"park it" — the §0.0 natural-C fallback already covers those.

### Cookbook hygiene

When updating the cookbook:

- Verify the C block compiles (or at least parses cleanly) — the
  scaffolder pulls it verbatim. A broken template silently breaks
  every future scaffold.
- Keep wrapper placeholder names to `func_wrapper` / `wrapper`. Don't
  use `func_X` for the wrapper — the scaffolder leaves `func_X` as a
  TODO for the callee.
- Link to the originating feedback memory at the bottom of the recipe
  (`See: [feedback_X]`). Memory is source of truth; cookbook is the
  index.

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
- Per-iteration commit cadence: one commit per matched function or
  per postprocess/header-macro addition.
- Stop condition: <15 min of usage budget left, or three consecutive
  iterations with no matches and no progress on tough nuts.
- Append a one-line entry to `decomp/RUN_LOG.md` (gitignored) per
  outcome: ISO-8601-Z timestamp, target, matched / deferred, commit
  SHA, one-liner.
