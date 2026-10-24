# Legal notes

What this repository may contain, what it must never contain, and which
references its source was written from.

This is a community decompilation project. It is not affiliated with,
endorsed by, or sponsored by Sony Interactive Entertainment Inc. (formerly
Sony Computer Entertainment Inc.), Sony Group, Team Ico, or any of their
affiliates. *ICO*, *PlayStation 2* and *Team Ico* are trademarks of their
respective owners.

## What is in this repository

- C and assembly source written for this project, which the period toolchain
  compiles into the game's boot ELF.
- Build scripts and tooling written for this project, and two patches to GNU
  binutils 2.10 (GPL, like the code they patch).
- Documentation written for this project.
- Configuration that describes how the user's own disc image is checked and
  how the rebuilt ELF is linked: the link order, the linker script, the
  data-table index, the data-table schema (record types and counts, no
  values) and the SHA-1s of the expected files, each per target
  (`config/*.<slug>.*`, `config/sha1sums.<slug>.txt`).
- The `VERSION_<SLUG>` blocks in which a target's build differs from PAL's,
  under the same rules as every other source.
- `config/ico.pal.yaml`, `config/symbol_addrs.pal.txt` and
  `config/symbol_addrs.pal.data.txt`, kept as a record of the old split
  layout; nothing in the build reads them. The two symbol lists hold the
  names this tree defines and the addresses the link places them at, the
  same facts `nm` prints over `build/pal/ico.elf`; they are a record of the
  rebuilt ELF, not a copy of a disc file.

## What is not in this repository, and must never be added

- The ICO disc image (`.bin`, `.iso`, `.cue` or any other form), in whole or
  in part.
- The boot ELF of any revision (`SCES_507.60`, `SCPS_110.03`,
  `SCUS_971.13`, the prototypes), or any part of it.
- Audio, images, textures, models, text or other assets from the disc.
- The game's data tables (next section).
- Symbol tables, map files or other identifier tables, and any debug string,
  asset or code blob, copied verbatim or in bulk out of the binary, the disc
  or any leaked development material. Using an individual fact (a name, an
  offset, a `__FILE__` path) as a reference is covered under "Identifiers as
  references" below; this item forbids copying a table of them into the
  repository.
- Any code believed to derive from leaked source.

`.gitignore` and `tools/check_no_rom.sh` (run by the pre-commit hook) make it
harder to commit such material by accident. They do not replace care. If you
suspect a file in this repository breaks these rules, open an issue tagged
`legal`.

## The data tables are generated at build time

Each disc's link includes 70 members of the game's archive `ico2000.a` that
have data sections and no code (MAIN.MAP of the PAL disc; the Japanese,
Korean, prototype and demo links have the same set, the USA link all but the
hint table and the subtitle file names), plus three data runs MAIN.MAP does
not list (none of which the prototype's or the demo's link has);
`config/data_members.<slug>.txt` lists them all for each target except
`enemy-def` (72 runs, 70 for `ntsc`, 69 for `aug6`; 119 for `jun26`, which
also generates `mcdata.o`'s save icon record and `EnemyInit.o`'s 49 enemy-set
tables, data the other links hold inside objects with code). They
are the game's content: stage object layouts, model and motion file tables,
sound definitions, way points, the staff roll. There is no program in them to
re-derive, and their values are never committed, as C, as assembly or in any
other form, with the one exception below.

One exception: `enemyKind`. The member `enemy-def`, the table `enemyKind`
that `enemy.c` reads, is committed as C source in
`ico2/sugipon/src/enemyKind.c`, by the owner's decision of 2026-10-24. The
PC port offers the USA build's enemy tuning as a play variant on every disc,
which needs the USA table without the USA disc. The table holds only numbers,
one row per enemy kind: the model and particle ids, the life, the scale, the
dodge range and the attribute bits. It holds no names, text or layouts. It
is the only exception; no other member follows it, and every other member is
still generated at build time as described below.

The build reads them from the user's own `baserom/<slug>/baseelf.elf` and
writes them under `build/<slug>/data/`, which is gitignored. Each member is
written as `build/<slug>/data/<member>.c`, an initialized array of its record
type from `config/data_schema.<slug>.txt` that compiles with the game's flags
(`tools/gen_data_c.py`). The committed schema and the record types in the
owners' headers hold only types, element counts and symbol names. The
configuration files hold member names, address ranges, record types and the
names MAIN.MAP gives the symbols, and nothing of the tables' content.

The line drawn is between content and facts about its shape. The names,
tables and strings are content and are never committed. A count or size
derived from a table is an ordinary fact about it, as its element count is:
the staff roll's line count, `staffRollNameDataNum`, is the table's element
count less its two null entries, recorded in the schema and written by the
generator as `sizeof` over the table, not read from the disc.

## Public reverse-engineering material (allowed as references)

Published reverse-engineering material may be consulted as a reference for
naming and structure: conference talks, blog posts and articles, public
Ghidra projects with clear non-leaked provenance, and academic papers on the
PS2 EE / R5900. Treat them like academic papers: read, understand, then
re-derive from the disassembly. Never paste their code, comments or symbol
names into this repository.

Public source code under an open licence is used the same way. Sony's
libraries in `sce/` were written from the shipped instructions; their header
names follow the SDK's public naming, and each declaration is the signature
of the member under `sce/` that defines it; the kernel calls in `eekernel.h`
follow the public ps2sdk `kernel.h` (each header's opening comment says
which). The newlib and libgcc members follow newlib's and GCC's published
source, whose licences permit it.

## Identifiers as references: facts, not expression

Facts observable in a copy you legally own (function and symbol names, struct
field offsets and sizes, array strides, `__FILE__` paths in `.rodata`) are
not copyrightable expression. They may inform original code: read,
understand, re-derive. Never commit the source artifact, and never paste a
table of identifiers in bulk.

- **Allowed:** reading the legally owned binary or disc, or a public decomp of
  clean provenance, and re-deriving names and shapes into your own code.
- **Forbidden:** committing the disc image, the extracted ELF, asset bytes, or
  a symbol, map or debug table in whole or in bulk; and any use of leaked
  source, leaked SDKs, or leaked prototype or debug builds (below). A retail
  disc you own is never in that category.

## Forbidden inputs

These may never be used as inputs to this project, even indirectly:

- Leaked SDKs (Sony Pro-DG, internal Sony tools, debug PS2 firmware).
- Leaked source code from any party, including any of ICO or other Team Ico
  titles, however obtained.
- Paid asset extractors that bundle game data.

If you have ever read any of the above, say so on your first pull request so
your contributions can be reviewed for provenance.

## Retail PAL disc symbol maps (`pal`)

The PAL retail disc (`SCES-50760`, boot ELF `SCES_507.60`, `SYSTEM.CNF`
`VER = 1.00`) ships three build artifacts next to the boot ELF, which the USA
disc does not:

- `MAIN.MAP`: a GNU ld linker map (member load order and symbol table).
- `SRCFILE.TXT`: an `objdump -dl` listing of a slightly earlier link of the
  same program (`20020116MasterVer1.00EU`): every instruction with its
  function label and the source path and line number it came from. It
  contains no source statements.
- `TRFILE.TXT` / `TRTABLE.BIN`: an address-to-function/file/line table.
  `TRFILE.TXT` has one text line per address (111515 lines);
  `TRTABLE.BIN` is a binary index of 111515 eight-byte entries, each an
  address from `TRFILE.TXT` and a 32-bit offset.

These are officially distributed retail media that every buyer received.
Symbol names, file boundaries and file paths read out of them are used as
references in the source tree, the same way as any other fact in the disc.
The listing's line data was used to recover names, file boundaries and the
order of functions in each file. It is not a licence to reconstruct source
statements, and it contains none. `tools/extract_elf.sh` copies `MAIN.MAP`,
`SRCFILE.TXT`, `TRFILE.TXT` and `SYSTEM.CNF` into gitignored `baserom/pal/`;
it does not copy `TRTABLE.BIN`, which nothing in the build reads. None of
them is ever committed or bulk-copied. Because the listing comes from a
different link than the shipped ELF, names were attached to shipped
functions by instruction-stream correlation, never by copying an address.

## Japanese retail disc (`jpn`)

The Japanese retail disc (`SCPS-11003`, boot ELF `SCPS_110.03`, `SYSTEM.CNF`
`VER = 1.02`) ships no linker map, listing or address table next to its boot
ELF. Its names come from the PAL disc's listing above, by instruction-stream
correlation (`tools/correlate_elf.py`): each function of the Japanese ELF is
paired with a PAL function whose instructions, relocated fields masked, are
the same, and takes that function's name. Where the census paired two
functions only by their position inside a run of unpaired ones (the ordinal
tier), the pairing was checked by rebuilding the function from the PAL
function's source. One name was corrected while the functions were rebuilt:
the ending's save step keeps the name `actEndLogoChk` that the August 6, 2001
prototype's `TRFILE.TXT` gives it (below), and the step before it, which
PAL's map calls `actEndLogoChk`, carries a derived name. A function no PAL
function claims also carries a derived name. The data-only members take
PAL's names by member order. No address is copied from either PAL file:
every address in `config/*.jpn.*` was found in the user's own
ELF.

Of the user's Japanese disc the build reads `SYSTEM.CNF`, to find the boot
file, and `SCPS_110.03`: it checks the ELF's SHA-1 and generates the 73
data-only members from it (above). Every function, the five VU1
microprograms and Sony's libraries are compiled or assembled from the
tracked sources; nothing of the code is read from the disc.
`tools/extract_elf.sh` copies `SYSTEM.CNF` into gitignored `baserom/jpn/`.

The Japanese string literals in the sources (the EUC-JP files
`.gitattributes` lists) are the program's own text, the messages and names
the compiled code prints or passes, written as the code that uses them. They
are facts the program needs to be rebuilt, as in the shared tree, not assets of
the disc.

## Korean retail disc (`kor`)

The Korean retail disc (`SCPS-56001`, boot ELF `SCPS_560.01`, `SYSTEM.CNF`
`VER = 1.00`) ships no linker map, listing or address table next to its boot
ELF either. Its names are the Japanese build's, carried to the Korean ELF by
the same instruction-stream correlation against the Japanese build: of the
5727 functions the census pairs, 5679 have bodies equal to the Japanese
ones, and every function of the tree compiles to the Korean bytes at the
address the link gives it. No name or address comes from any Korean file
other than the user's own ELF: every address in `config/*.kor.*` was found
in it.

Of the user's Korean disc the build reads `SYSTEM.CNF`, to find the boot
file, and `SCPS_560.01`: it checks the ELF's SHA-1 and generates the 73
data-only members from it (above). Every function, the five VU1
microprograms and Sony's libraries are compiled or assembled from the
tracked sources; nothing of the code is read from the disc.
`tools/extract_elf.sh` copies `SYSTEM.CNF` into gitignored `baserom/kor/`.
The disc's other files (its data archive `DFDATAS/DATA.DF`, the IOP modules
and `IOPRP224.IMG`) are never read by the build and never committed.

## USA retail disc (`ntsc`)

The USA retail disc (`SLUS-20218`, boot ELF `SCUS_971.13`, `SYSTEM.CNF`
`VER = 1.00`) ships no linker map, listing or address table next to its boot
ELF either. Its names come from the PAL disc's listing above, by
instruction-stream correlation (`tools/correlate_elf.py`): each function of
the USA ELF is paired with a PAL function whose instructions, relocated
fields masked, are the same, and takes that function's name. Where the
census paired two functions only by their position inside a run of unpaired
ones, and where a USA function no PAL function claimed was tied by other
evidence to a PAL function the census left without a twin (a body equal
with immediates and jump targets masked, PAL's size and order, call sites,
data tables, callees or body alignment), the pairing was checked by
rebuilding the function from the PAL function's source with the USA build's
changes until the gate passed; every function of the tree compiles to the
USA bytes at the address the link gives it. Functions a data member points
at were named by that member's key or by the record they address. A
function with no PAL counterpart carries a derived name. The data-only
members take PAL's names by member order. No address is copied from either
PAL file: every address in `config/*.ntsc.*` was found in the user's own
ELF.

Of the user's USA disc the build reads `SYSTEM.CNF`, to find the boot file,
and `SCUS_971.13`: it checks the ELF's SHA-1 and generates the 71 data-only
members from it (above). Every function, the five VU1 microprograms and
Sony's libraries are compiled or assembled from the tracked sources; nothing
of the code is read from the disc. `tools/extract_elf.sh` first cooks the
raw `.bin` into `baserom/Ico_USA.iso`, then copies `SYSTEM.CNF` into
gitignored `baserom/ntsc/`.

Where the USA build lays out a record differently from PAL's (eight of the
data tables' record types among them), the layout was derived from the code
that reads it in both builds (the field offsets each twin function's loads
and stores use), not from any other source.

## Prototype disc (`aug6`)

The `aug6` target builds the August 6, 2001 ICO prototype (`SCUS_971.13`,
`SYSTEM.CNF` `VER = 1.00`; the branch `aug6`, frozen at `c8e730628`, is the
single-target tree it was joined from). That prototype disc ships three
build artifacts next to its boot ELF and no `SRCFILE.TXT`:

- `MAIN.MAP`: the same file as the PAL disc's (582413 bytes), so it
  describes a third link, neither the prototype's nor the PAL ELF's.
- `TRFILE.TXT`: an address-to-function/file/line table whose addresses are
  offset from the prototype ELF's by a shift that is constant within a
  region but not across the whole file.
- `TRTABLE.BIN`: the binary index of `TRFILE.TXT`, one eight-byte entry
  per line (103258), as on the PAL disc.

The names of functions that exist only in the prototype come from
`TRFILE.TXT`, one fact at a time: a function's name, file or line is read
from its entry once the shift for that region has placed the entry at the
function's address. The project uses this factual metadata (names,
addresses, file boundaries, `__FILE__` paths) on the same terms as the retail
maps above. This rests on common decompilation practice for symbol information present in a
distributed compiled binary: the Ocarina of Time decomp builds the
symbol-bearing GameCube debug ROM, the Paper Mario TTYD decomp seeds names
from a demo-disc symbol map. A review prototype that circulated through
collectors is closer to a grey area than retail media; using its metadata is
a deliberate choice of this project, not settled community consensus. Leaked
source and leaked SDKs stay forbidden on every branch.

The functions the prototype shares with the retail builds take their names
from the PAL disc's listing by instruction-stream correlation, as the USA
build's do (above); the data-only members take PAL's names by member order.
No address is copied from either disc's map: every address in
`config/*.aug6.*` was found in the user's own ELF.

Of the user's prototype disc the build reads `SYSTEM.CNF`, to find the boot
file, and `SCUS_971.13`: it checks the ELF's SHA-1 and generates the 70
data-only members from it (above). Every function, the five VU1
microprograms and Sony's libraries are compiled or assembled from the
tracked sources; nothing of the code is read from the disc.
`tools/extract_elf.sh` first cooks the raw `.bin` into
`baserom/Ico_AUG6.iso`, then copies `MAIN.MAP`, `TRFILE.TXT` and
`SYSTEM.CNF` into gitignored `baserom/aug6/` as reference material. Where
the prototype lays out a record differently from PAL's (ten of the data
tables' record types among them, eight of them the USA build's layouts),
the layout was derived from the code that reads it in both builds, not from
any other source.

## Demo disc (`jun26`)

The `jun26` target builds the ICO demo of the Official U.S. PlayStation
Magazine demo disc 49 (SCUS-97158, a DVD; the branch `jun26`, frozen at
`230819536`, is the single-target tree it was joined from). The disc's
`SYSTEM.CNF` (`VER = 1.00`) boots the magazine's menu, `SCUS_971.58`, which
starts the ICO demo from its own directory: the boot ELF is
`CUS97113/SCPS_000.00`, named by the `boot` key of the target's `DISCS` row
(`tools/ico_version.py`). That directory ships no `SYSTEM.CNF`, linker map,
listing or address table, and the ELF has no symbol table. The demo's names
are carried to it by instruction-stream correlation
(`tools/correlate_elf.py`), the function census: each function of the demo
ELF is paired with a function of another build whose instructions,
relocated fields masked, are the same, and takes that function's name. The
census ran against PAL's ELF, named by the PAL disc's map and listing above,
against the August 6, 2001 prototype, named by its `TRFILE.TXT` and
`MAIN.MAP`, and against the USA retail build, whose tree takes its names
from the same maps. A name tied by other evidence (a data table's slot, a
caller, the record it addresses, a function's place among its neighbours)
was checked against the function's body when the function was rebuilt from
source and the gate passed. A function or object with no counterpart in any
of those builds carries a derived name, marked `/* derived name */` in the
source. The 70 archive members take PAL's names by member order; the
enemy-set tables take names derived from PAL's `enemymodel01` set and the
icon.sys record a derived one, each said in the header of
`config/data_members.jun26.txt`. No address is copied from any of those
files: every address in `config/*.jun26.*` was found in the user's own ELF.

Of the user's disc image the build reads the disc's `SYSTEM.CNF` and
`CUS97113/SCPS_000.00`: it checks the ELF's SHA-1 and generates the 120
data-only members from it (above). Every function, the five VU1
microprograms and Sony's libraries are compiled or assembled from the
tracked sources; nothing of the code is read from the disc.
`tools/extract_elf.sh` copies the disc's `SYSTEM.CNF` into gitignored
`baserom/jun26/`; nothing else of the disc (the menu, the other games) is
read. Where the demo build lays out a record differently from PAL's
(several of the data tables' record types among them), the layout was
derived from the code that reads it (the field offsets the demo's loads and
stores use, compared with the twin function's in PAL's or the prototype's
build), not from any other source.

## What you need to build

You must legally own a copy of *ICO* for the PlayStation 2 and supply the
disc image yourself. The build checks the extracted ELF's SHA-1 before it
proceeds and refuses any other file (`config/sha1sums.<slug>.txt`,
`docs/BUILDING.md`). A SHA-1 is a fingerprint, not a copy of the work; the
disc image and the ELF remain the property of their rightsholders.

This project gives no instructions for obtaining a disc image. The only
legitimate source is a personal dump of a disc you own, made in compliance
with the law where you live.

## Why decompilation projects can exist

Projects of this kind have a long history (Super Mario 64, Ocarina of Time,
Majora's Mask, Paper Mario, Sly Cooper, Jak and Daxter, Kingdom Hearts and
many more). They produce original source code by reverse engineering,
distribute no copyrighted assets, and require users to bring their own image.
This project follows the same model.

If you represent a rightsholder and have a concern, please open a GitHub
issue.
