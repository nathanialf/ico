# Decomp notes — PS2 EE / R5900 / ICO

Catalog of compiler / assembler / splat / linker quirks that have bitten
matching work. **Read this before starting a new match.** Most "near-miss"
diffs are an instance of one of the patterns below.

Empty at init. Seed entries below are placeholders for the categories we
expect to fill.

## Compiler fingerprint (open question)

ICO is a 2001 first-party SCEI title. The matching compiler is most
likely:

- **Sony Pro-DG (wcc)** — Sony's in-house PS2 SDK toolchain pre-2003.
- **Metrowerks CodeWarrior for PS2** — common third-party choice.
- **ee-gcc** — unlikely for a 2001 SCEI first-party but possible.

Investigation notes:

- [ ] Inspect `baserom/baseelf.elf`'s `.comment` section once extracted.
- [ ] Compare prologue/epilogue patterns to known wcc/CW/ee-gcc samples.
- [ ] Check for compiler-specific symbol mangling in any leftover symbols.

Update this section once the compiler is identified; the rest of this
file's quirks are organized by compiler family.

## R5900-specific gotchas (to be cataloged)

- MMI (Multimedia Instructions) — 128-bit ops the EE adds on top of
  MIPS III. `m2c` support varies; Ghidra handles them.
- VU0 macro mode — coprocessor instructions interleaved with EE asm.
  Splat / m2c may not annotate these correctly.
- Branch-delay scheduling differences between wcc, CW, and ee-gcc.

## Splat / spimdisasm gotchas (resolved at init)

Three quirks bit the seed round-trip; all are fixed by `tools/postprocess_ld.py`
(linker-script patch) and `tools/postprocess_asm.py` (asm patch), wired
into `make split`. Don't disable them. If a future splat upgrade emits
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

After all three patches, `make setup && make` produces
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
  them; regenerate via `make setup`.
- **make distclean nukes config/ico.us.ld**, which is generated by
  splat. Run `make setup` after distclean before `make`, otherwise the
  build fails with "No rule to make target 'config/ico.us.ld'".

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

## Compiler identification — provisional

`splat create_config` defaulted to `compiler: EEGCC` for ICO. Quick
inspection shows:

- No `.comment` section in `baseelf.elf` (compiler stripped it).
- `.rodata` contains `sceMcOpen`, `sceMcClose`, etc. — confirms SCE PS2
  SDK use, but doesn't pin the compiler.
- Need to compare prologue/epilogue patterns against ee-gcc-emitted
  reference code once the toolchain is installed.

Treat `EEGCC` as a working hypothesis, not a confirmed fact. If matching
plateaus quickly with weird scheduling diffs, suspect Pro-DG/wcc or
CodeWarrior and revisit.
