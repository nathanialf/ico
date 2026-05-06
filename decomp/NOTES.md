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

## Splat / spimdisasm gotchas

- **Round-trip is *not* byte-identical at the seed** (10-byte size diff,
  0x30-offset shift in early `.text` `lui+addiu` pairs that load BSS-
  region addresses). Cause: splat's `. = ALIGN(., 16)` between `.sdata`
  and `.sbss` aligns to 16, but the original ELF aligns `.sbss` to 0x100
  (visible as `.sdata` ending at `0x00633BC6` and `.sbss` starting at
  `0x00633C00`). Fix: bump `.sbss` subsegment alignment in the yaml or
  override the linker script to `ALIGN(., 0x100)` at the `.sbss` boundary.
  Same likely applies to the `.bss → end` boundary (10-byte tail diff).
  This is the first matching task — do it before any C work; otherwise
  every function that takes a sbss/bss address will diff.

- Splat's auto-generated `linker_script_extra.ld` only contains
  `ENTRY(_start)` for ICO; we already pass it via `-T` in the Makefile.

## Linker quirks

- **RWX LOAD segment warning** is harmless on PS2 (matches snap's N64
  behavior). Suppress with `--no-warn-mismatch` in `LDFLAGS` (already
  set in the Makefile).
- **Auto-generated absolute-symbol stubs** in `config/undefined_syms_auto.us.txt`
  declare `D_<HEX>` symbols at literal addresses for any spimdisasm-
  detected `lui+addiu` pair pointing outside the ELF range. They are
  never executed — they exist only to satisfy the linker. Don't delete
  them; regenerate via `make setup`.

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
