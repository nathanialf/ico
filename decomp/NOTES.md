# Decomp notes — PS2 EE / R5900 / ICO

Catalog of compiler / assembler / splat / linker quirks that have bitten
matching work. **Read this before starting a new match.** Most "near-miss"
diffs are an instance of one of the patterns below.

Empty at init. Seed entries below are placeholders for the categories we
expect to fill.

## Compiler fingerprint (resolved)

**The matching compiler is `ee-gcc 2.9-991111-01`** (Sony fork of GCC
2.9 dated 1999-11-11). Same build the PAL ICO-decomp project uses;
fetched by `tools/setup.sh` from `decompme/compilers`. The bundled
`ee-as 2.10-ee-001003-1` from the older `ee-gcc 2.96` tarball is kept
alongside and used for assembly only — it picks the right `daddu`
expansion for `move` macros and the right 32-bit `lui+addiu+addu`
expansion for `la $X, sym($Y)`.

How we landed here: ee-gcc 2.96 was the initial guess but produced
encoding-level mismatches (`daddu` vs `or` for register-zero move,
64-bit `la` macro expansion, regalloc preference for `$v1` over `$v0`).
Switching to 2.9-991111 closed every encoding/regalloc gap that
remained after natural-C work and post-processing, yielding a
byte-identical SHA-1 round-trip.

Notes that still apply: most R5900/EE/splat/linker quirks below are
compiler-agnostic. The pre-2.9 sections marked "ee-gcc 2.96" are
historical; some 2.96-specific workarounds (e.g. the inline-asm
`DEFINE_TAILCALL_LWA1` family in the now-deleted `include/ico/codegen.h`)
were unnecessary under 2.9 and have been removed. The rest of the
file's quirks remain valid.

## R5900-specific gotchas (to be cataloged)

- MMI (Multimedia Instructions) — 128-bit ops the EE adds on top of
  MIPS III. `m2c` support varies; Ghidra handles them.
- VU0 macro mode — coprocessor instructions interleaved with EE asm.
  Splat / m2c may not annotate these correctly.
- Branch-delay scheduling differences between wcc, CW, and ee-gcc.

## Splat / spimdisasm gotchas (resolved at init)

Three quirks bit the seed round-trip; all are fixed by `tools/postprocess_ld.py`
(linker-script patch) and `tools/postprocess_asm.py` (asm patch), wired
into `tools/build.sh split`. Don't disable them. If a future splat upgrade emits
the script in a different shape, the post-process will warn rather than
silently re-introduce a diff.

1. **`.cod_bss` start address.** Splat's `. = ALIGN(., 16)` *inside*
   the `(NOLOAD)` section body doesn't propagate to the section's load
   address. The original linker placed `.sbss` at 0x633C00 (0x100-aligned),
   but splat's output put `cod_SBSS_START` at 0x633BD0. Fix:
   `postprocess_ld.py` injects a top-level `. = ALIGN(., 0x100);`
   immediately *before* `.cod_bss (NOLOAD) :`. Per-subsegment
   `align: 0x100` keys in the yaml are silently ignored by splat 0.40.0.

2. **Trailing `.sdata` ALIGN.** Splat emits `. = ALIGN(., 16)` after
   the `.sdata` content, before `cod_SDATA_END = .;`. The original ELF's
   LOAD ends at exactly the last byte of `.sdata` (0x633BC6 — not
   16-byte aligned), so splat's pad makes `build/ico.rom` 10 bytes
   longer than baserom's. Fix: `postprocess_ld.py` strips that one
   ALIGN. The other inter-section ALIGNs (between `.text`/`.data`/etc.)
   are kept — they reflect real section alignment requirements.

3. **`.sdata` tail symbol truncation.** `.sdata` size is 0x22C6 (not
   4-byte aligned). Splat 0.40.0 rounds the last data symbol down to a
   `.word`, dropping the trailing 2 bytes ("E\0", which complete the
   asciz "FALSE\0" at 0x633BC0). Fix: `postprocess_asm.py` patches the
   .sdata.s tail to add `.byte 0x45, 0x00`. Symbol size hints in
   `config/symbol_addrs.us.txt` are silently ignored for this case.

After all three patches, `tools/build.sh setup && ninja` produces
`build/ico.rom` byte-identical to `baserom/baseelf.rom` (SHA-1
`fbf50c75cd5911273511c4f9af90503ff8423582`).

## Per-function .s vs segment .s — gp_rel form mismatch

Splat 0.40.0 emits gp-relative loads/stores in two different forms:

- **Segment .s** (e.g. `asm/cod/000000.s`): explicit
  `lw $v0, %gp_rel(D_FOO)($gp)`. Assembles cleanly under `.set noat`.
- **Per-function .s** (e.g. `asm/matchings/cod/005258/func_X.s`): bare
  `lw $2, (D_FOO) /* gp_rel: (D_FOO) */`. Under `.set noat`, gas tries
  to expand this into a `lui $at, %hi; lw $2, %lo($at)` macro and
  errors out ("macro used $at after .set noat"). Even if it didn't,
  the encoded bytes wouldn't match the original gp_rel instruction.

Fix: `tools/postprocess_asm.py` rewrites the bare-paren form to the
explicit `%gp_rel(SYM)($gp)` form across `asm/matchings/`. Idempotent.
This produces the correct gp_rel encoding and lets the per-function
target round-trip via `tools/quick_diff.sh`.

## Non-sdata externs need unsized array (or oversized) declarations

With `-G 8` set in CFLAGS/ASFLAGS (required for sdata gp_rel codegen),
`extern int FOO;` makes ee-gcc emit `.extern FOO, 4`. The assembler
then sees size 4 ≤ 8 and assumes FOO is in `.sdata` — generating
gp_rel loads/stores. If the symbol is **outside** the sdata range
(0x631900–0x633BC6 for ICO), the resulting gp_rel offset is wrong.

For non-sdata symbols, declare them as:

- **`extern int FOO[];`** — unsized array. ee-gcc omits the `.extern`
  size hint, so gas falls back to absolute (lui+addiu) addressing.
- Or oversized: `extern int FOO[3];` (12 bytes > -G 8 threshold).

The unsized-array form is preferred — matches the actual decomp
intent (these symbols are usually arrays or struct blocks anyway)
and doesn't require knowing the size up front.

## C codegen for $gp-relative loads — `-G 8` everywhere

The original ICO ELF accesses sdata symbols via single-instruction
gp_rel form (`lw $v0, %gp_rel(SYM)($gp)`). To make ee-gcc + mips-as
emit the same:

- **CFLAGS** must include `-G 8` (small-data threshold). With `-G 0`
  the compiler emits `lui+lw` (4 instructions for load+store of an
  extern int). With `-G 8`, it emits the assembler-macro form
  `lw $2, SYM`.
- **ASFLAGS** must also include `-G 8`. The macro form `lw $2, SYM`
  is expanded by gas at assembly time — with `-G 0` gas treats SYM
  as "not in small data" and emits lui+lw. With `-G 8` gas checks
  the `.extern SYM, size` size; if size ≤ 8, it emits the gp_rel form.

Both flags are required — they must agree. ee-gcc emits `.extern SYM,
4` for any C `extern int`, which lands in the gp_rel bucket at -G ≥ 4.

## .text section alignment — objcopy after assembly

`mips-linux-gnu-as` defaults `.text` section alignment to **2**4
(16-byte)** regardless of the actual `.align` directives in the
source (which max out at `.align 3` = 8-byte for splat output).

When the linker concatenates multiple .text inputs into the merged
`.cod` output section, that 16-byte alignment forces 8 bytes of
padding at every input-section boundary whose offset is 8-aligned
but not 16-aligned (e.g., 0x5258). The original ELF was built from
a single TU so it never hit this — our split per-subsegment build
hits it at every C/asm boundary.

Fix: after each `as` invocation, `mips-linux-gnu-objcopy
--set-section-alignment .text=8 $@` lowers the section alignment to
match the actual content. Must run on **every** .o (asm and src) —
otherwise the boundary after the lowered .o still pads the next .o
up to its 16-byte requirement.

## Per-file CFLAGS overrides — `config/extra_cflags.txt`

A handful of functions need compiler flags that would break the global
SHA-1 if applied across all of `src/`. Examples seen so far:

- `func_001F4C00` matches with `-fno-schedule-insns2`, but a global
  flip breaks the hot-path scheduling in many other functions and the
  rebuild SHA-1 diverges by a few bytes.
- The 4-insn / 0x10 leaf bucket (e.g. `func_0010B2C0`, `func_00159230`,
  `func_001F6C88`) is mostly tail-call wrappers that need the inverse
  of the global `-fno-optimize-sibling-calls`.

Mechanism: `config/extra_cflags.txt` maps file-offset → extra flags.
`tools/extra_cflags.sh <src/cod/X.c>` extracts the file_off from the
basename, looks it up, and prints the flags (empty if no override).
The Makefile `src/.o` rule and `tools/quick_diff.sh` both splice the
output into the CC command line, so the two pipelines stay in sync.

To add an entry:

1. Add `<FILE_OFF_HEX>  <flags...>` to `config/extra_cflags.txt`
   (one entry per line, `#` for comments).
2. `tools/build.sh clean && ninja` — confirm the global SHA-1 still passes (the
   override is per-file, but verify nothing leaked).
3. `tools/quick_diff.sh cod/<FILE_OFF>` — confirm the target now
   matches with the override applied.

Remove an entry the moment the underlying need disappears (e.g. the
matching compiler is identified and the flag becomes default).

## Make CC override

`CC` is a Make built-in variable defaulting to `cc` (the host gcc).
`CC ?= ee-gcc` does NOT override it because `?=` is a no-op when the
variable is already defined. Use `override CC := ee-gcc` to force the
EE compiler in the Makefile.

ee-gcc 2.96 also needs `-B $EEGCC_LIB` to locate its bundled `cc1`,
and `-S` to skip its own ancient `as` (which doesn't grok modern flags
like `-G`). Re-assemble the .s with `mips-linux-gnu-as`.

## Compiler regalloc nudges

ee-gcc 2.96 sometimes reuses an argument register (`$a1`/`$a2`) as the
destination for an arithmetic op when the natural C expression "looks
through" to a load. Original code typically uses `$v1` as the scratch.

Workaround: rewrite the expression so the intermediate value is bound
to a local first, then operated on sequentially. Example:

```c
// Reuses $a1 as result -- doesn't match
return *(short *)((char *)&table[idx] + 0x3C);

// Forces $v1 scratch -- matches
char *base = *(char **)(self + 0x2C);
base += idx * 4;
return *(short *)(base + 0x3C);
```

Both compile to the same instructions, just with different register
allocation. Splitting into sequential statements pins the temp to
`$v1`.

## Combined sdata-set + return-value — pin `$v0` with register asm

Original 3-instruction shape for `D_X = 1; return 1;`:

```
addiu $v0, $zero, 0x1
jr    $ra
sw/sb $v0, %gp_rel(D_X)($gp)
```

ee-gcc 2.96 -O2 splits the constant across two registers (`$v1` for
the store, `$v0` for the return), producing a 4-instruction sequence.
Permuting around this never converges because the natural C surface
always re-derives the split.

**Fix:** pin the temp to `$v0` with a register-asm declaration so the
compiler is forced to reuse one register for both store and return:

```c
extern int D_X;
int func_X(void) {
    register int v __asm__("$2") = 1;
    D_X = v;
    return v;
}
```

(`$2` is `$v0` on R5900.) Works for `sw`, `sb`, `gp_rel` and offset
forms (e.g. `self[N] = v;` for struct-field stores). Cracked all 10
siblings of `func_0013B858` this way.

## Splat delay-slot mis-identification

spimdisasm 1.40.3 (used by splat 0.40.0) sometimes splits a `jr $ra`
delay slot off as a separate "function" when the delay-slot
instruction looks like a plausible function entry (uses an argument
register `$a0`-`$a3` as input, etc.).

Example: `func_00190430` ends with `jr $ra; sw $a1, 0x0($v1)`. spim
declares two functions:

- `func_00190430` (size 0xC): the 3 instructions ending at `jr`.
- `func_0019043C` (size 0x4): the orphan `sw $a1, 0x0($v1)`.

Symptom: claiming `func_00190430` as `c` and writing the natural C
produces a 4-instruction (16-byte) `.text`. The asm subseg covering
0x9043C still emits the orphan `sw`, and the linker concatenates them
— pushing the next real function 4 bytes too high.

For now: avoid claiming functions whose per-function `.s` ends at `jr`
*without* the delay slot; check
`asm/matchings/<name>/<func>.s` size against the function's actual
end before claiming. Functions where spim correctly captured the
delay slot (e.g. `func_0010A2E0` with `nonmatching ..., 0x10`) match
fine.

Long-term fix: hand-edit splat output to merge orphan delay slots, or
upstream a spim heuristic patch.

## Linker quirks

## Linker quirks

- **RWX LOAD segment warning** is harmless on PS2 (matches snap's N64
  behavior). Suppress with `--no-warn-mismatch` in `LDFLAGS` (already
  set in the Makefile).
- **Auto-generated absolute-symbol stubs** in `config/undefined_syms_auto.us.txt`
  declare `D_<HEX>` symbols at literal addresses for any spimdisasm-
  detected `lui+addiu` pair pointing outside the ELF range. They are
  never executed — they exist only to satisfy the linker. Don't delete
  them; regenerate via `tools/build.sh setup`.
- **`tools/build.sh distclean` nukes `config/ico.us.ld`**, which is
  generated by splat. Run `tools/build.sh setup` after distclean before
  `ninja`, otherwise the build fails because the linker script is
  missing.

## Header-macro library for inline-asm matching tricks

`src/cod/*.c` files are kept free of raw `__asm__` blocks.  Each
matching trick that *was* an inline-asm body now lives behind a
header-defined macro:

- `include/syscall.h` — `SYSCALL_WRAPPER(name, num)` for the 150
  EE-syscall leaves at file offsets `0x0001XX..0x0009XX`.  Modeled on
  ps2sdk's `ee/kernel/src/kernel.S` `SYSCALL_SPECIAL` macro.
- `include/r5900.h` — `SYNC()` (memory barrier) and
  `QCOPY16(scratch)` / `QCOPY16_NO_NOP(scratch)` (single-quadword
  copy via lq/sq).
- `include/matching.h` — workarounds for ee-gcc 2.9 codegen edge cases:
    - `VOLATILE_RELOAD_CALL(addr, target)` — volatile reload + nop
      barrier + 1-arg call (defeats gas-reorder pulling the lw into
      the jal delay slot).
    - `DEAD_DADDU_V0_SP(pinned_a0)` — injects a dead `daddu $v0,
      $sp, $0` between two calls (used by `func_0010D7F8` family).
    - `FABSF_BIT_TWIDDLE(x)` — fabsf via 0x7FFFFFFF mask without the
      union-access regalloc artifact.
    - `DEFEAT_TCO()` / `KEEP_LIVE(x)` / `KEEP_LIVE_MEM(x)` — opaque
      no-instruction barriers that prevent gcc tail-call optimization
      and/or hold a stack-resident value live.
    - `NOREORDER_BARRIER()` — open-then-close `.set noreorder` block.

When you find a new pattern that needs a one-off inline-asm
formulation, **prefer adding a macro to one of these headers** over
inserting raw `__asm__` in the .c file.  See `decomp/MATCH.md` Step 4
for the doctrine.

## VU0 wrappers — handwritten asm (`hasm`) leaves, not C with inline asm

Pure VU0/COP2 wrapper functions (no C body, just an `__asm__` block of
VU0 instructions) are claimed in the yaml as `hasm`, not `c`.  Splat
emits them to `src/cod/<off>.s` directly from the base ELF, and the
`progress.py` matched-bytes counter treats `hasm` the same as `c` (see
`MATCHABLE_TYPES`).  This avoids carrying the multi-line inline-asm
formulations the original 2.96-era seeds had.

The few VU0 wrappers that DO need to live as `.c` (because they call
out to gcc-emitted prologue/epilogue around the asm body) use single-
instruction `__asm__` blocks via a header macro — see the next
section.

## VU0 inline asm — `$ACC`, `$Q`, `$R`, `.set noreorder`

VU0 macro instructions in inline `__asm__` need EE-specific syntax that
mips-linux-gnu-as 2.x accepts:

- **Special VU0 registers** carry a `$` prefix in inline asm even though
  splat's per-function .s files emit them bare (`ACC`, `Q`, `R`). Use
  `$ACC`, `$Q`, `$R` in C inline asm or the assembler reports `invalid
  operands`. (Splat's segment-level .s is what `make` consumes; that
  one already uses `$ACC`. The matchings/ files are reference-only.)
- **mfc1 → qmtc2.ni** has a load-delay slot. With default `.set
  reorder` the assembler inserts a `nop` between them. Original ICO
  code does NOT have the nop, so wrap that pair with `.set noreorder`
  / `.set reorder`. Keep the wrap *minimal* — wrap the mfc1/qmtc2 pair
  only. If you put `.set noreorder` over the whole asm block, the
  trailing `sqc2`/`sd` won't be reordered into the gcc-emitted `j $31`
  delay slot, leaving an extra `nop` at end-of-function.
- **Pattern that matches "store in jr delay slot":** drop the trailing
  `nop` from your inline asm and let the gcc-emitted `j $31` reorder
  the previous instruction into its delay slot. With the inline asm in
  reorder mode, gas does the right thing.

Example (vec scale with float arg, jr-delay-slot store):

```c
void f(void *dst, void *src, float k) {
    __asm__ __volatile__(
        "lqc2 $vf4, 0($a1)\n\t"
        ".set noreorder\n\t"            // wrap only the mfc1/qmtc2 pair
        "mfc1 $t0, $f12\n\t"
        "qmtc2.ni $t0, $vf5\n\t"
        ".set reorder\n\t"
        "vmulx.xyzw $vf6, $vf4, $vf5x\n\t"
        "sqc2 $vf6, 0($a0)"             // no trailing nop — let gas reorder
        : : : "memory"
    );
}
```

## Force store ordering with an `__asm__` memory barrier

ee-gcc 2.96's scheduler likes to reorder back-to-back stores by offset
to coalesce them, which can flip the C source order:

```c
*(int *)(p + 0x9C) = 0;   // emits as 9C, 98, A0
*(int *)(p + 0x98) = 0;
*(int *)(p + 0xA0) = 0;
```

To pin the order to source order *and* still let the third store fall
into a `jr` delay slot, mark the first two as `volatile` and insert an
`__asm__` memory barrier between the second and third:

```c
*(volatile int *)(p + 0x9C) = 0;
*(volatile int *)(p + 0x98) = 0;
__asm__ __volatile__("" : : "r"(p) : "memory");
*(int *)(p + 0xA0) = 0;          // free to land in jr delay slot
```

Pure `volatile` on all three pins the order but blocks delay-slot fill.
Pure non-volatile lets the scheduler reorder. The barrier is the
combination that matches.

## Tooling shortcuts

Two helpers that replace the throwaway shell pipelines I kept retyping:

- **`tools/find_leaves.py`** — walks `asm/cod/*.s` and prints functions
  matching size/insn-count/jal-count/shape filters. Use it to hunt for
  candidate match patterns. Examples:
  - `tools/find_leaves.py --no-vu --jal 0 --insns 4 --size 0x10` —
    leaf functions, 4 instructions, 0x10 bytes.
  - `tools/find_leaves.py --has-vu --insns '4..6' --size '0xC..0x18'`
    — VU0 functions in a size range.
  - `--shape 'lw,sw,jr,sw'` filters by mnemonic sequence (first token
    only, dotted VU like `vmul.xyz` preserved). Use `*` for any.
  - `--contains 'gp_rel\(D_'` regex on the body.
  - `--exclude-parked` skips functions registered under
    `tough_nuts/<func>/` (known unmatchable with the current toolchain
    — la-macro 64-bit, daddu/or, no-TCO, ret-1+sdata-set regalloc, etc.).
    Each `tough_nuts/<func>/` subdirectory is one parked function with a
    seed `<func>.c` and a `notes.md`. Use `--exclude-parked` on routine
    queries so the same dead-end functions stop coming back. Example:
    `tools/find_leaves.py --no-vu --jal 0 --insns 4 --size 0x10 --exclude-parked`.
    To park a new function, create `tough_nuts/<func_NAME>/` with a seed
    `.c` + `notes.md` describing the failure mode (see
    `tough_nuts/README.md`). The `--parked-file FILE` flag adds extra
    one-off names from a flat file on top of the `tough_nuts/` set.
    Filtering happens after the asm cache is loaded, so adding a
    tough_nuts entry does not require `--rebuild-cache`.
- **`tools/claim.py`** — flips a yaml subsegment to `c`, writes the
  source, inserts an asm filler at `addr+size` if needed. Single mode:
  `tools/claim.py single --vram 0x118460 --size 0x10 --comment '...' --body-file src.c`.
  Batch mode: `tools/claim.py batch --manifest claims.toml`. TOML schema
  is `[[claim]]` with `vram`, `size`, `comment`, `body` (literal C).

After running `claim.py`, run `make setup && make` (the script tells
you). Do NOT pre-create the `.c` then run claim — claim refuses to
clobber existing entries marked `c`.

- **`tools/auto_permute.sh`** — parallel decomp-permuter pool driving
  every function with a `tough_nuts/<func>/` directory. (The legacy
  `tools/auto_permute_parked.sh` is now a one-line forwarding shim.)
  Wires up:
  - `tools/permute_run.sh <func_name>` — per-function driver. Resolves
    the seed (auto-discovers under `tough_nuts/<func>/*.c` or
    `src/cod/<file_off>.c`), slices the asm out of
    `asm/matchings/cod/<file_off>/<func>.s` or the segment-level
    `asm/cod/<seg>.s`, builds the permuter run dir under
    `lib/decomp-permuter/runs/<func>/` with `compile.sh` (ee-gcc 2.96
    + `mips-linux-gnu-as`, same flags as `tools/quick_diff.sh`), then
    execs `permuter.py`.
  - `tools/gen_permuter_settings.py` — regenerates `permuter_settings.toml`
    at the repo root (compiler_type = gcc, ee-gcc path baked from the
    `EEGCC` env or the default `tools/cc/ee-gcc2.96/bin/gcc`).
  - `tools/auto_permute.sh` — the orchestrator. Runs up to
    `PARALLEL` permuter processes concurrently (default 4), each at
    `-j 1` so total CPU ≈ `PARALLEL`. Promotes the best-scoring
    candidate from each run back into the seed file between passes,
    so progress survives across restarts. On match, prints
    `MATCH: <func>` and moves on without auto-promoting into
    `src/`/yaml — operator review only. Skips functions whose yaml
    entry is already `c`-typed. Activity log lands at
    `lib/decomp-permuter/auto_permute.log`; per-function permuter logs
    at `lib/decomp-permuter/runs/<func>/permuter.log`.

  Env vars: `PARALLEL=N` (default 4), `STOP_AT_SCORE=N` (default 0 =
  match-only; use `STOP_AT_SCORE=50` to stop on hand-attackable
  near-misses), `ITERATIONS=N` (default 0 = infinite),
  `SKIP_MATCHED=0` to retry already-promoted functions,
  `TOUGH_NUTS_DIR=path` to use a different registry root.

  One-time setup (the permuter needs `toml`; `pynacl` and `Levenshtein`
  are optional):
  ```sh
  .venv/bin/pip install pynacl toml Levenshtein
  tools/gen_permuter_settings.py    # writes permuter_settings.toml
  ```

  Run it:
  ```sh
  tools/auto_permute.sh                          # all of tough_nuts/*/
  PARALLEL=8 STOP_AT_SCORE=50 tools/auto_permute.sh
  tools/auto_permute.sh func_00105278            # single function
  ```

  The orchestrator never calls `make`; it only mutates seed files
  under `tough_nuts/` (and writes intermediates under the gitignored
  `lib/decomp-permuter/runs/`). Once it prints `MATCH: <func>`, the
  matching candidate sits at `lib/decomp-permuter/runs/<func>/output-0-*/source.c`
  for the operator to review and promote into `src/cod/<file_off>.c`
  via `tools/claim.py` (or the equivalent yaml flip + `make setup`).

## Stale `asm/cod/<seg>.s` files

When you flip a yaml entry from `asm` to `c`, splat removes the old
`asm/cod/<seg>.s`, but **the previous splat run's `.s` files for the
*surrounding* segments may still contain the function** (because splat
emits one `.s` per asm subsegment, covering the full range up to the
next subsegment, and re-emits with new boundaries each setup). Symptom:

```
multiple definition of `func_XXX'; build/asm/cod/SEG.o: first defined here
```

Fix: delete the stale `asm/cod/<surrounding>.s` and re-run `make setup`.
For larger blast radii, `rm -f asm/cod/*.s build/asm/cod/*.o; make
setup` is the nuclear option (rebuilds everything).

## Defeating tail-call optimization in ee-gcc 2.9

ee-gcc 2.9-991111 has sibling-call optimization hardcoded ON at -O2;
`-fno-optimize-sibling-calls` is rejected. For wrapper functions whose
original ICO codegen uses a full stack frame (`addiu sp, -N; sd ra,
…; jal …; ld ra, …; jr ra; addiu sp, +N`) instead of a tail call
(`j …`), defeat the optimization per-function with an empty inline-asm
barrier *after* the wrapped call:

```c
void func_X(int a0) {
    func_Y(a0);
    __asm__ __volatile__("");  // blocks sibling-call opt
}
```

If the wrapper additionally needs a larger frame than the saved-`ra`
slot would force (e.g. 0x20 vs 0x10), add a dummy local and route a
pointer to it through the barrier so the compiler must allocate stack
for it:

```c
void func_X(void) {
    int local;
    func_Y(arg);
    __asm__ __volatile__("" : : "r"(&local));
}
```

Without the `&local` clobber, the local gets dead-store-eliminated and
the frame collapses again. Used by func_00123C00 (0x20 frame) but not
its sibling func_00241A00 (0x10 frame, no local needed).

## quick_diff vs full build — `move`-macro expansion mismatch

Trust `make` (full build SHA-1) over `tools/quick_diff.sh` for any
function that materializes 0 into a register. The two pipelines use
different assemblers and pick different expansions for `move $rD, $0`:

- **Full build**: ee-as 2.10 (`tools/cc/ee-gcc2.96/bin/as -mcpu=5900
  -G 8`) expands `move $rD, $0` to `daddu $rD, $0, $0` — matches
  original ICO codegen.
- **quick_diff**: mips-linux-gnu-as (`-march=r5900 -mabi=eabi -G 8`)
  expands the same macro to `or $rD, $0, $0` — disassembles as `or`,
  causes a false-negative diff line.

Symptom: quick_diff reports `daddu | or` mismatches on lines that
materialize 0, but `make` round-trips the full ELF SHA-1 cleanly.
**Always confirm with `make` before parking a function** that only
diverges on `move $rD, $0` expansion. The pre-2.9 NOTES "daddu vs or"
section below is now obsolete (resolved by the EE_AS path); the
remaining false negative is purely in the diff harness.

## Migrating data sections from asm to src (per-VMA named sections + SORT_BY_NAME)

Splat outputs every data section (`.sdata` / `.lit4` / `.rodata` /
`.data`) as a single `.section .X, "flags"` blob in `asm/data/cod/`.
With the section as one blob, the linker can't reorder it by symbol
VMA — the bytes are tied to the one .o that splat produces, and that
.o lands in `build/asm/`, so `tools/progress.py` doesn't credit any of
those bytes to the matched-bytes counter (it only walks `build/src/`).

Architecture for getting data sections to count toward progress:

1. `tools/rewrite_data_named_sections.py` rewrites each
   `asm/data/cod/*.s` so every `dlabel D_X` block lives in its own
   per-VMA named section (`.section ".X.0xVMA", "flags"`). `.align N`
   directives between blocks (no-ops in the blanket layout because
   cumulative cursor was already aligned at the symbol's VMA) are
   replaced with absolute-VMA `.skip K` pads — this preserves byte
   layout even for byte-aligned mid-section symbols like `D_006331B3`.
2. `tools/postprocess_ld.py` injects `*(SORT_BY_NAME(.X.0x*))` at the
   top of each data output section in `config/ico.us.ld`. With per-VMA
   names, the sort produces deterministic VMA-order layout regardless
   of which .o file contributes which symbol.
3. `tools/build_data_tu_map.py` votes each data symbol to its owning
   TU by parsing `%hi`/`%lo`/`%gp_rel` references from every text
   function and looking the function's TU up in `decomp/tu_map.json`.
   Symbols with no votes (touched only by untagged functions, or not
   text-referenced) fall back to VMA-proximity assignment from the
   nearest voted neighbor. Output: `decomp/data_tu_map.json`
   (gitignored — symbol-name keyed, ~700 KB).
4. `tools/migrate_data_per_tu.py` reads the TU map and emits one
   `src/<TU>_data.c` sidecar per TU containing the byte content of
   every D_<VMA> dlabel assigned to that TU. Definitions use
   `__attribute__((section(".X.0xVMA")))`; the linker places each
   section at the correct VMA via SORT_BY_NAME. Sidecars are
   gitignored because the byte literals come directly from baserom
   (IP-sensitive); the build round-trips byte-identical because the
   linker sees the same bytes either way.
5. `tools/decode_sdata_lit4_typed.py` (one-shot) is the typed-promotion
   tool for `.sdata` and `.lit4`. It reads the bytes directly out of
   `baserom/baseelf.elf` (keyed off `decomp/data_tu_map.json` for
   the symbol VMA list) and emits typed C — `float D_X = 1.0f`,
   `const char D_X[] = "..."`, single int/short/char — into
   **per-TU tracked `src/<TU>.c` files** (`src/Basic.c`,
   `src/way_tool.c`, `src/ios/cdvd.c`, …), mirroring
   `decomp/data_tu_map.json`'s assignments. The per-TU layout
   is in place from the start; no consolidated `sdata.c`/`lit4.c`.
   Typed-form emission is gated on 8-aligned VMAs (where gcc's
   `.align 3` for arrays is a no-op); non-8-aligned blocks fall
   through to per-VMA single-element chunks identical to
   `_emit_chunked`'s logic, keeping section alignment ≤ 4 so the
   linker doesn't pad around them. The decoder refuses to overwrite
   any `src/<TU>.c` it didn't generate itself (recognized by a
   `decode_sdata_lit4_typed.py` signature in the header comment),
   so hand-crafted TU files like `src/Basic.c` are safe across
   re-runs.
6. `tools/rewrite_data_named_sections.py` is the final step. It
   wraps each remaining asm dlabel block in a per-VMA named
   `.section`, then strips any block whose D_<VMA> symbol is
   defined anywhere under `src/**/*.c` (typed sources OR
   auto-generated sidecars). Pool/data-sidecar files are the
   single source of truth for "which symbols are migrated"; the
   rewriter never re-introduces duplicates.

Chunking strategy (shared between `_emit_chunked` in
`migrate_data_per_tu.py` and the misaligned-VMA fallback in
`decode_sdata_lit4_typed.py`):

* For 8-aligned VMAs (~99% of rodata/data symbols), emit ONE
  `unsigned char[N]` array per block. ee-gcc 2.9 emits `.align 3`
  for arrays — a no-op at an 8-aligned VMA.
* For misaligned VMAs, fall back to per-VMA aligned-largest-first
  chunks (`unsigned int` for 4-aligned 4-byte chunks, then `short`,
  then `char`). Each single-element chunk gets `.align 2` / `.align
  1` / no-align respectively, so the section's alignment requirement
  stays small enough that the linker can place it at any byte VMA.

Big sidecars use `mips-linux-gnu-as` (added to
`config/use_modern_as.txt`) — the bundled ee-as 2.10 takes literal
minutes on inputs that large (cdvd_data.c is ~30 MB of .s after gcc
expansion).

State as of session 2026-05-11:

* `.sdata`: 100% via 72 tracked `src/<TU>.c` files (decoder-promoted
  from baserom; safe to commit because the typed forms — string
  literals, named float constants, single hex word definitions —
  are a developer's clean-room reconstruction, not raw bytes).
* `.lit4`: 100% via the same per-TU `src/<TU>.c` files (every entry
  decodes as `float D_X = <value>f;`).
* `.rodata` / `.data`: 0% tracked; bytes live in gitignored per-TU
  `_data.c` sidecars. Hand-typing follows `decomp/MATCH_DATA.md`,
  with new typed definitions added to the same `src/<TU>.c` that
  already holds the TU's typed sdata/lit4 entries (per-TU layout).

## EUC-JP debug strings in `.rodata` (Japan-Studio convention)

ICO is a Japan Studio title; its rodata contains a substantial body of
**EUC-JP-encoded** Japanese debug strings interleaved with the English
ones. Scanning `baserom/baseelf.elf` shows 196 multi-character EUC-JP
runs spread across 41 TUs (133 distinct symbols). They're standard
developer asserts and printf-style logs:

* `0x005539E0` `"メーンスレッドの起動失敗しました\n"`  (main thread startup failed)
* `0x00553CB8` `"…が壁の中に突入させようとしたのでクリップしました\n"`  (clipped a push-into-wall)
* `0x00555800` `"光源オフでリフレクションを表示.\n"`  (showing reflection with lights off)
* `0x0055A398` `"warpGirl.c:もしDEBUG STAGE SELECTでなくてここを通ったら おかしい！"`
* … plus 129 more across `BgAnimation`, `DObj`, `Texture`, `motionManager`,
  `way_util`, `chain`, etc.

**Why EUC-JP, not Shift-JIS:** the bytes only decode under EUC-JP. ee-gcc
2.9 on the original Sony Pro-DG / Solaris+Linux build hosts used EUC-JP
as the default source encoding, which matches what's in the binary.

**Storage convention:** typed in the tracked main TU file (e.g.
`src/charFileManager.c`) as

```c
/* EUC-JP: "メーンスレッドの起動失敗しました\n" */
__attribute__((section(".rodata.0x005539E0"))) const char D_005539E0[40] =
    "\245\341\241\274\245\363\245\271\245\354\245\303\245\311\244\316"
    "\265\257\306\260\274\272\307\324\244\267\244\336\244\267\244\277\n";
```

* **Octal escapes (`\NNN`)** keep the source file pure ASCII — no
  Japanese characters in the .c content itself, no compiler
  `-finput-charset` flag needed, no editor-mojibake risk.
* The decoded EUC-JP sits in a leading comment as a translator's aid;
  the source-of-truth is the bytes, which `quick_data_diff` verifies
  byte-identical to the ROM.
* This follows the same "typed reconstruction" convention as the
  English ASCII strings in the same files — same shape, just non-ASCII
  bytes expressed via standard C escapes.

**Mechanical promotion:** `tools/promote_jp_rodata.py` scans every
`src/*_data.c` sidecar, detects words whose little-endian bytes decode
as EUC-JP with ≥1 Japanese codepoint, generates the octal-escaped
`const char` form, and appends a block to the tracked main TU file.
The sidecar's duplicate definition is dropped automatically on the
next `tools/migrate_data_per_tu.py` run (it scans existing typed
definitions across `src/**/*.c`).

## VU0 microcode (`.vutext`) — kept as opaque textbin, not typed

`.vutext` is 20,704 bytes (`0x50E0`) of hand-written VU0 microcode at
VMA `0x0026F5E0`. The block:

* Has **no `.rela.vutext` relocations** — the bytes are a pure opaque
  blob to the EE-side linker (the only references *into* it come
  from MIPS .text via DMA tags and VU0 setup code, which already
  resolve correctly via the linker's `.text` section placement).
* Is **not MIPS/EE machine code.** VU0 is a separate coprocessor ISA
  with its own register file and instruction set (`vmadd`, `vsub`,
  `vrnext`, etc.). ee-gcc / mips-linux-gnu-as don't disassemble or
  assemble VU0 instructions, so the bytes cannot round-trip through
  any of our existing typed-decomp paths.

**Policy:** `.vutext` stays as a `textbin` subseg pulled via
`.incbin` from `assets/cod/16F5E0.textbin.bin` (gitignored). It is
*not* a target for typed reconstruction in this project. Treating
hand-written coprocessor microcode as an opaque blob is the
convention used by sm64 / pm64 / similar decomps for the same
reason. If someone wants to reconstruct it as VU mnemonics, the
prerequisite is a VU0 disassembler + a `hasm`-style subseg with
`src/vutext.s` containing the actual `vmadd…` directives — a
multi-week project in its own right.

**`tools/progress.py`** correctly reports `.vutext` at 0% under the
IP-aware filter (the bytes come from `assets/cod/16F5E0.textbin.bin`,
which is gitignored). The percentage stays at 0% until a hand-typed
`src/vutext.s` replaces the textbin subseg.

**A 64-byte size detail to know:** the splat-extracted bin file
(`assets/cod/16F5E0.textbin.bin`) is 20,768 bytes — 64 bytes larger
than the ELF `.vutext` section's `sh_size` (20,704 / `0x50E0`). The
extra 64 trailing bytes are all zero. They cover the file-offset
gap between `.vutext`'s end and `.data`'s start in the original ELF
(`0x1756C0` → `0x175700`). The yaml subseg
`[0x16F5E0, textbin, cod/16F5E0]` extracts from `0x16F5E0` up to the
next subseg at `0x174700`, which is the full 20,768-byte stretch
including the 64-byte alignment pad. This is benign: the linker
re-emits exactly those bytes (all zero) into the final ROM, and the
SHA-1 round-trip matches.

## Patterns parked in `tough_nuts/`

- **`la` macro 64-bit expansion** (`func_00105278` family): ee-gcc 2.96
  with `-G 8 -O2 -mips3` emits `lui+daddiu+daddu` for `&array[index]`
  via the gas `la` macro, where the original used `lui+addiu+addu` (32-
  bit). Symptom: 6-insn array index funcs (`lui; sll; addiu; addu; jr;
  lw`) consistently mismatch. Suspect compiler isn't ee-gcc.
- **`daddu vs or` for register move** (historical, resolved): ee-gcc
  2.96 emits `or $vN, $zero, $zero` to materialize 0; original ICO uses
  `daddu`. Under 2.9-991111 + ee-as 2.10, the EE assembler picks
  `daddu` for the `move` macro and the diff vanishes in the full build.
  quick_diff still shows the divergence — see "quick_diff vs full
  build" above.

## Build-environment fingerprint (informational)

The compiler question is settled at the top of this file (ee-gcc
2.9-991111-01, byte-identical round-trip). The notes below catalog the
*other* signals the baseelf carries — useful for sanity-checking
toolchain assumptions and for naming subsystems later.

**Stripped metadata.** No `.comment`, `.note`, `.mdebug`, `.pdr`, or
`.gptab.*` sections survive in `baseelf.elf`. Any future investigation
that wants compiler/build-flag strings has to fall back to codegen
fingerprinting — there is nothing to read.

**Sony PS2 SDK linker conventions present.** The ELF carries SDK-
specific section names that rule out non-Sony toolchains (CodeWarrior in
particular):

- `.vutext` / `.vudata` / `.vubss` — VU code/data sections from the
  Sony SDK linker scripts. `.vutext` is 20704 bytes; `.vudata` and
  `.vubss` are size 0 but the section table entries persist.
- `.DVP.ovlytab`, `.DVP.ovlystrtab`, and a dozen `.DVP.overlay.*`
  sections — output of `dvp-as` / `dvp-link` (Sony's VU assembler and
  overlay linker). Section-name shape is
  `.DVP.overlay..<vma>.<id>.<idx>.<flags>` with vma = `0x0` or
  `unknvma`. Total ~22 KB across all overlays, all marked X+W.
- `.reginfo` (24 bytes) — standard MIPS but populated by Sony's linker.

**ELF header flags.** `e_flags = 0x20924001`. Decoded:

- bit 0 (`EF_MIPS_NOREORDER`) — set, matches `-mno-reorder`-friendly
  output.
- byte at the MACH position = `0x92` (`EF_MIPS_MACH_5900`) — explicit
  Sony R5900 marker. Standard for PS2 retail ELFs.

**SDK library version tags.** `.data` carries the PsII library banners:

- `PsIIlibcdvd 2240` at `data+0x2DC204`
- `PsIIlibpad  2200` at `data+0x2DDC7C`

These pin the SDK release window. Useful if we ever need to match
against a specific SDK version's library object files.

**SCE assert macro signature.** `.rodata+0xDC548` has
`assertion "%s" failed: file "%s", line %d\n` — the format string from
the Sony PS2 SDK's `SCE_ASSERT` / `assert` macro. Implies asserts were
left in (debug-ish build) and that any `__FILE__` argument was emitted
verbatim.

**Source-path leak via `__FILE__`.** The SCE assert macro emits the
caller's `__FILE__` into the function's rodata. Scanning `.rodata` for
`<dir>/<file>.[ch]` patterns recovered **96 source files across 5
directories** of the original tree: `src/` (83 files), `ios/` (7),
`isys/` (2), `sound/` (2), `include/` (2 confirmed). Full list and
inferred subsystem groupings are in `decomp/source_tree.md`; the
recovered layout is materialized as an empty skeleton with per-
directory README under `decomp/source_tree/` (regenerate via
`tools/build_source_tree.py`). When matching a function whose rodata
contains `assertion "%s" failed`, the embedded path tells you which
original TU it belongs to — that's the mechanical way to start
populating per-file subsegments in `config/ico.us.yaml`.

**SHIFT-JIS debug strings.** Multiple Japanese-encoded format strings
in `.rodata` (the `\xa4\xce`, `\xa4\xac` byte pairs are SHIFT-JIS
hiragana). Confirms SCE Japan source provenance. When emitting these as
`.rodata` contents from C, keep them as raw byte arrays or escape
literals — do not let an editor "helpfully" re-encode to UTF-8.

**What this does *not* tell us.** None of the above pins the compiler
front-end (already pinned by SHA-1 round-trip anyway). It also doesn't
tell us whether the build used `-g` or any debug-symbol flags — those
artifacts (if they ever existed) were stripped along with `.mdebug`.

**Inspection recipe** (read-only, safe to re-run):

```sh
.venv/bin/python -c "
from elftools.elf.elffile import ELFFile
with open('baserom/baseelf.elf','rb') as f:
    elf = ELFFile(f)
    print(f'flags=0x{elf.header.e_flags:08x} entry=0x{elf.header.e_entry:08x}')
    for sec in elf.iter_sections():
        print(f'  {sec.name:<40} {sec[\"sh_type\"]:<14} {sec[\"sh_size\"]:>10}')
"
```


## Per-TU section linking — slinky integration roadmap

When a TU owns sdata symbols AND has functions that reference them,
ee-gcc 2.9 emits `%gp_rel` only when the function's TU sees the
symbol as `extern` (not as a typed def with a section attribute). Our
current pipeline wraps every typed sdata def in
`__attribute__((section(".sdata.0xVMA")))` and uses
`SORT_BY_NAME(.sdata.0x*)` in the linker script for placement. That
forces the def into the same TU as the function on coalesce, breaking
`%gp_rel` and the SHA-1 gate. See `src/DmaPacket.c` REVISIT note for
the canonical case.

**Path forward** is `decompals/slinky` — a YAML-driven linker script
generator already used by parappa2 (same ee-gcc 2.9-991111-01) and
several other PS2 decomps. slinky lists `.o` files in VMA order;
linker concatenates per-input-file. Per-TU plain `.sdata` defs
preserve `%gp_rel`.

`tools/setup.sh` step 7 installs `slinky-cli` via cargo (or skips if
Rust is unavailable). Once installed, the migration is sketched in
the approved Phase 3 plan
(`/primary/home/n/.claude/plans/glittery-dreaming-meerkat.md`):

1. **Section design**. ICO ELF has one merged `.cod` PROGBITS
   section (text + data + rodata + lit4 + sdata) and `.cod_bss`
   (NOLOAD). Most decomps using slinky have separate output sections
   per type — adapting requires either (a) decomposing `.cod` into
   per-section slinky segments and recombining in the output, or
   (b) using `sections_subgroups` to keep one segment with internal
   ordering. (a) is structurally cleanest but risks SHA-1 mismatch
   if section boundaries shift.
2. **slinky.yaml generator**. A new `tools/gen_slinky.py` emits
   `config/ico.us.slinky.yaml` from the splat YAML +
   `decomp/data_tu_boundaries.json`. .text follows splat's order;
   data sections list per-TU `.o` files in VMA order from
   `data_tu_boundaries.json`'s promotable TUs.
3. **Per-TU promotion** (one PR per TU): drop the typed def's
   `__attribute__((section(".X.0xVMA")))`, just `int D_X = 0;`. The
   slinky.yaml gains an entry placing this `.o`'s plain section at
   the right VMA. ee-gcc emits `%gp_rel` for the same-TU function.
4. **Tool retirement**. Once SORT_BY_NAME is no longer carrying
   meaningful weight, `tools/postprocess_ld.py` (the SORT_BY_NAME
   injector + intersection ALIGN bumpers),
   `tools/rewrite_data_named_sections.py`, and
   `tools/migrate_data_per_tu.py` (the `.X.0xVMA` wrapper) shrink or
   retire.

**slinky `\!=` SORT_BY_NAME**. slinky lists files in declared order;
it does not re-sort sections by name. To preserve our current per-VMA
placement, the sidecar files (`<TU>_data.c`) must emit their typed
defs in VMA order (declaration order = link order). Non-promotable TUs
(scattered VMA ranges across multiple non-contiguous TU regions) need
to either be split into per-region `.o`s OR remain on the asm side
with the catch-all SORT_BY_NAME pattern (hybrid is possible if those
catch-all `.o`s are listed in the slinky.yaml at their VMA range).

**Initial scan** (from `decomp/data_tu_boundaries.json`, generated by
`tools/build_data_tu_boundaries.py`): 87 TUs across 309 TU-sections;
236 TU-sections are promotable today (single contiguous run of
TU-owned symbols; no foreign-TU interleaving). `.sdata` is the
smallest section to migrate first (~8.7 KB) and unblocks the most
matching work (gp_rel codegen).

### Phase 3b'/3c status (slinky pipeline stood up)

`tools/gen_slinky.py` + `tools/postprocess_slinky_ld.py` (wired into
`tools/build.sh slinky`) produce `config/ico.us.slinky.yaml` and the
matching `config/ico.us.slinky.ld`. Design choice: **per-section
segments**, parappa2-style — one slinky segment per ICO ELF section
(`text`, `data`, `rodata`, `lit4`, `sdata`, `sbss`, `bss`). Each
segment's `files:` list is sorted by the .o's minimum contributing
VMA in that section. The single-merged-`.cod` option was ruled out:
once C TUs have content in multiple sections with non-correlated
VMAs, a single `files:` list can't preserve cross-section VMA
ordering. The built `.elf` then has separate
`.text/.data/.rodata/.lit4/.sdata/.sbss/.bss` output sections rather
than today's merged `.cod`+`.cod_bss`; SHA-1 is over `.rom`
(`objcopy -O binary`), so loadable bytes are what matter.

**`postprocess_slinky_ld.py` bridges the typed-section gap.** Slinky
emits per-`.o` globs `<.o>(.<sect>*)` in declared order. The
`(.sdata*)` glob matches both `.sdata` and `.sdata.0xVMA`, which
means each TU's `.o` (carrying scattered `.sdata.0x*` sections from
`tools/rewrite_data_named_sections.py`) dumps its sections back-to-
back at the current loc counter — wrong cross-VMA order, ~440 bytes
of layout drift. The post-processor injects
`*(SORT_BY_NAME(.X.0x*))` at the top of each data/rodata/lit4/sdata
block. GNU ld claims each input section at the *first* matching
output reference, so the typed sections are absorbed in name (= VMA)
order first; the per-`.o` globs that follow only see the residual
plain `.X` sections (currently empty per TU). As TUs migrate to
plain sections in Phase 3d, the per-`.o` globs start carrying real
content and the SORT_BY_NAME catch-all shrinks. When the catch-all is
empty, the injector retires (Phase 3e).

**Status: SHA-clean parallel artifact.** Linking with the patched
`slinky.ld` produces an ELF whose `.rom` matches `baseelf.rom`
(`fbf50c75cd5911273511c4f9af90503ff8423582`). `ninja` still uses the
postprocess_ld.py-patched `ico.us.ld` for the default build —
swapping ninja's `-T` to `slinky.ld` is a separate change deferred to
Phase 3d, when the first per-TU promotion lands.

**Per-section status today** (per `tools/gen_slinky.py` output):

| segment | contributing .o files |
|---------|----------------------|
| text    | 2836 (from splat) |
| data    | 60 |
| rodata  | 145 |
| lit4    | 34 |
| sdata   | 87 |
| sbss    | 1 (the asm blanket) |
| bss     | 1 (the asm blanket) |

The slinky.ld correctly resolves `_gp` via `gp_info` on the lit4
segment (offset `0x7FF0` — matches today's
`_gp = cod_LIT4_START + 0x7FF0`), pins `.text` at `0x00100000` and
stacks the alloc sections with `0x100` start alignment
(`.bss` at `0x80`). All structural pieces are in place.

**Reproduce:**

```sh
tools/build.sh setup && .venv/bin/ninja   # canonical SHA-clean build
tools/build.sh slinky                     # regen slinky.{yaml,ld}
# Optional: link with slinky.ld to confirm SHA still matches.
```

