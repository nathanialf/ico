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

- (To be cataloged once we run splat against the ICO ELF for the first
  time.)

## Linker quirks

- (To be cataloged.)
