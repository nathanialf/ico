# Legal notes

This is a community decompilation effort. It is not affiliated with, endorsed
by, or sponsored by Sony Interactive Entertainment Inc. (formerly Sony
Computer Entertainment Inc.), Sony Group, Team Ico, or any of their
affiliates. *ICO*, *PlayStation 2*, and *Team Ico* are trademarks of their
respective owners.

## What is in this repository

- Original C source code we have written from scratch as part of the
  decompilation effort.
- Build scripts and tooling we have written.
- Documentation we have written.
- Configuration files (linker scripts, splat YAML, symbol *names* we
  invented) that describe how a user-supplied disc image is split and
  rebuilt.

## What is NOT in this repository, and must never be added

- The ICO disc image (`.bin`/`.iso`/`.cue`/etc.), in whole or in any
  portion, in any encoding.
- The extracted EE-side ELF (`SCUS-97113`) or any portion of it.
- Audio (VAG/ADPCM), image (TM2/PNG-from-disc), texture, model, text, or
  other assets extracted from the disc.
- Symbol tables, MAP/symbol files, or other identifier *tables* — and any
  debug-string, asset, or code blob — copied verbatim or in bulk out of the
  original binary, the disc, or any leaked development material. (Using an
  *individual* fact — a name, an offset, a `__FILE__` path — as a reference is
  governed below, under "Identifiers as references"; copying a *table* of them
  into the repo is what this bullet forbids.)
- Any code believed to have been derived from leaked source code.

The `.gitignore` and `tools/check_no_rom.sh` script make it harder to commit
such material accidentally, but they are not a substitute for contributor
diligence. If you suspect a file in this repo violates these rules, open an
issue tagged `legal` immediately — maintainers will treat it as urgent.

## Public reverse-engineering writeups (allowed as references)

Published, public reverse-engineering material **may** be consulted as
*reference* for naming intuition and structural understanding:

- Conference talks and recorded lectures (GDC, RetroDevs, etc.)
- Blog posts, articles, and personal websites
- Public Ghidra projects with explicit non-leaked provenance
- Academic papers on the PS2 EE / R5900 architecture

The rule: **treat them like academic papers**. Read, internalize, then
re-derive from the disassembly. Never paste their code, comments, or
symbol names verbatim into this repo.

## Identifiers as references — facts vs. expression

Facts observable by reverse-engineering a copy you legally own — function and
symbol *names*, struct field offsets and sizes, array strides, `__FILE__`
source-path strings embedded in `.rodata` — are not copyrightable expression.
They **may** be used as *references* to inform original code, on the same terms
as the public RE writeups above: read, internalize, re-derive; never commit the
source artifact, and never paste a *table* of identifiers in bulk. This is
already how the project recovers original file names (the `__FILE__` census →
`decomp/source_tree.md`) and types data structures
(`tools/dump_struct_accesses.py`).

- **Allowed (reference):** reading the legally-owned binary/disc, or a
  clean-provenance public decomp, and re-deriving names/shapes into your own
  clean code. A name you re-derive this way is your own naming choice, not a
  committed copy of a symbol table.
- **Forbidden (reproduction):** committing the disc image, the extracted ELF,
  asset bytes, or a symbol / MAP / debug *table* — in whole or in bulk — into
  this repository; and any use of leaked source, leaked SDKs, or
  prototype/debug builds (see *Forbidden inputs* below). A clean *retail* disc
  you own is never in this forbidden category; a leaked prototype or debug
  build is, regardless of what it contains.

This line keeps the project clean **by construction**: the repository still
distributes only original source and zero copyrighted tables/assets, while the
reverse-engineering that produces that source may consult the facts in the
product you legally own.

## Forbidden inputs

The following may **never** be used as inputs to this project, even
indirectly:

- Leaked SDKs (Sony Pro-DG, internal Sony tools, debug PS2 firmware).
- Leaked source code from any party.
- Pirated debug builds, prototype builds, or developer review copies of
  ICO or related Team Ico titles.
- Paid asset extractors that bundle game data.

If you have ever read any of the above, disclose it on your first PR so
maintainers can evaluate IP-cleanliness on a per-contribution basis.

## Vendoring (open-source PS2 SDK headers)

Vendoring of open-source PS2 SDK material — specifically the
[`ps2dev`](https://github.com/ps2dev) family of repositories (ps2sdk,
ps2toolchain, ps2-packer) — is permitted because those projects are
themselves community clean-room work, openly licensed. When vendoring:

- Place under `lib/<name>/`.
- Record provenance in `lib/<name>/PROVENANCE.md` (upstream URL, commit
  SHA, license, date pulled).
- Do not modify upstream files in-tree — fork upstream if changes are
  needed.

## What you need to do to build

You must legally own a copy of *ICO* for the PlayStation 2 and supply the
disc image yourself. The build verifies an ELF SHA-1 hash against your
extracted file before proceeding; if you do not provide a valid file, the
build will refuse to run. The supported revisions and their SHA-1
fingerprints are listed in `docs/BUILDING.md`. ELF cryptographic hashes
are not themselves copyrighted — they are fingerprints used to confirm an
exact match — but the disc image and the ELF themselves remain the
property of their rightsholders.

This project does not provide instructions on how to obtain a disc image.
The only legitimate source is a personal dump of a disc you own, performed
in compliance with the law of your jurisdiction.

## Why decompilation projects can exist

Decompilation projects of this kind have an established history (e.g.
Super Mario 64, Ocarina of Time, Majora's Mask, Paper Mario, Sly Cooper,
Jak and Daxter, Kingdom Hearts, and many more). They produce *original
source code* as a clean reverse-engineering exercise, distribute *no
copyrighted assets*, and require the user to bring their own image. We
follow the same model and the same care.

If you are a rightsholder representative and have a concern, please open
a GitHub issue; the maintainers will respond promptly.
