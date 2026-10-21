# ico

A source tree for the PlayStation 2 game **ICO** (Sony Computer Entertainment,
2001) that rebuilds the boot ELF of the June 26, 2001 demo, with the toolchain
the game was built with. The demo is one of the games on the Official U.S.
PlayStation Magazine demo disc 49 (SCUS-97158, a DVD); its boot ELF is
`CUS97113/SCPS_000.00`, which the disc's menu starts (the disc's own
`SYSTEM.CNF` boots the menu, `SCUS_971.58`), and its build stamp reads
`Jun 26 2001` `20:01:21`. Every byte the console loads is identical to the
disc's (the ROM image SHA-1 matches), and so is the ELF file itself (its SHA-1
matches the disc's). The tree was seeded from `main`, the PAL build's finished
tree, through the function census against PAL and against the August 6, 2001
prototype (`aug6`); this branch carries the functions, records and tables in
which the demo differs; [`docs/README.md`](docs/README.md) lists those
differences.

<!-- progress:begin -->
| Target | Sections identical to the base |
| --- | --- |
| [Jun-26-2001 demo (SCUS-97158)](https://nathanialf.github.io/ico/#jun26) | ![.text progress](https://img.shields.io/badge/text-100.00%20%25%20%2897.55%20%25%20source%20%2B%202.45%20%25%20disc%29-brightgreen.svg) ![.vutext progress](https://img.shields.io/badge/vutext-100.00%20%25-brightgreen.svg) ![.data progress](https://img.shields.io/badge/data-100.00%20%25%20%2868.37%20%25%20source%20%2B%2031.63%20%25%20disc%29-brightgreen.svg) ![.rodata progress](https://img.shields.io/badge/rodata-100.00%20%25%20%289.12%20%25%20source%20%2B%2090.88%20%25%20disc%29-brightgreen.svg) ![.lit4 progress](https://img.shields.io/badge/lit4-100.00%20%25%20%2895.69%20%25%20source%20%2B%204.31%20%25%20disc%29-brightgreen.svg) ![.sdata progress](https://img.shields.io/badge/sdata-100.00%20%25%20%2898.59%20%25%20source%20%2B%201.41%20%25%20disc%29-brightgreen.svg) ![.sbss progress](https://img.shields.io/badge/sbss-100.00%20%25-brightgreen.svg) ![.bss progress](https://img.shields.io/badge/bss-100.00%20%25-brightgreen.svg) |
<!-- progress:end -->

**[Progress dashboard](https://nathanialf.github.io/ico/#jun26)**: every
section, directory, translation unit and function of the build compared with
the base ELF.

> [!IMPORTANT]
> This project is not affiliated with Sony Interactive Entertainment or Team
> Ico. *ICO* is a trademark of its owners. No disc data is in this repository;
> you supply your own disc image. Read [`docs/LEGAL.md`](docs/LEGAL.md).

## Status

3098 of the Jun-26-2001 demo build's 5175 functions are still campaign stubs:
the C for them does not yet give the demo's bytes, so the build writes each one
from the user's own `baserom/jun26/baseelf.elf` at its place in its
translation unit (`config/stubs.jun26.txt`, `tools/gen_stub_s.py`; nothing of
them is committed). The gate passes with them in place, so every badge above
reads 100 %, and the badges split each figure into the share built from the
tracked sources and the share from the disc: the stubs and the data tables.
The `.text` source share is the matched code; the rest of it is the stubs.
When the list is empty the mechanism is idle and the branch is finished in
`main`'s shape.

## Quickstart

```sh
git clone -b jun26 https://github.com/nathanialf/ico.git
cd ico
mkdir -p baserom
cp "/path/to/demo disc 49.iso" baserom/Ico_JUN26.iso
./build.sh
```

`./build.sh` runs `tools/setup.sh` when the Python environment or the
toolchain under `tools/cc/` is missing, extracts `baserom/jun26/baseelf.elf`
from the disc image when it is missing (`tools/extract_elf.sh`; the image is a
plain 2048-byte-sector ISO of the DVD, read directly), then runs
`tools/build.sh setup` (or `verify` when `build.ninja` already exists),
`ninja` and `tools/check_elf.py --gate`, and exits non-zero if any step
fails. The host needs a 64-bit Linux with 32-bit libraries, a host gcc,
`mips-linux-gnu-objcopy` and network access for the first run;
[`docs/BUILDING.md`](docs/BUILDING.md) lists the packages and describes each
step.

The build checks the SHA-1s from `config/sha1sums.jun26.txt`: the extracted
ELF before it starts, and the rebuilt ROM image and the rebuilt ELF at the end.

| file | SHA-1 |
| --- | --- |
| `baserom/jun26/baseelf.elf` (the disc's `CUS97113/SCPS_000.00`) | `95c3d438185c3b75303b68719cfd48c84f2f8bfa` |
| `baserom/jun26/baseelf.rom` and `build/jun26/ico.rom` (`objcopy -O binary`) | `e5d6dd3c156ed5489a4d2e7bbf4707cd58d0dccc` |

The gate (`tools/check_elf.py --gate`) also compares every allocated section
of `build/jun26/ico.elf` with the base ELF by address and checks that `.sbss`
and `.bss` cover the base's ranges, and that the whole-file SHA-1 of
`build/jun26/ico.elf` is the base ELF's (`--require-elf-sha`): the section
headers, the symbol-name strings ld keeps and the `.DVP` overlay names and
tables all match. The overlay names hash the file and line the DVP assembler
was reading: each microprogram's `.dsm` for the first, then the text cpp read
from standard input (an empty name) and, in normal_c and normal_l, the shared
include `vusrc/scissorcommcut.h`, whose name is derived (the hash fixes it
among the names of its form). Four of the demo's programs differ from the
later builds' (cluster, mesh, normal_c and normal_l), and so do the lines
their continuation overlays are named after: mesh 327, normal_c 244 and
`scissorcommcut.h` 325, normal_l 243 and `scissorcommcut.h` 131 and 456. The
overlay contents are not code: each section is one byte repeated over the
program's size, a byte the DVP assembler never set, so the five
constant-address overlays (`.DVP.overlay..0x0.*`, one per program) carry
whatever the assembler's heap held. On the demo disc that byte is 0x6E (on
PAL's it is zero), and the seven continuation overlays (`..unknvma.*`) are
zero. `tools/binutils-dvp-overlay-fill.patch` makes dvp-as write the byte
explicitly (`--overlay-fill=N` for the five, 0 for the rest), taken from the
`overlay-fill=110` token on each `.dsm` line of `config/link_order.jun26.txt`,
so the build does not depend on the host's heap. `tools/check_elf.py
--full-diff` prints the whole-file comparison.

## Progress badges

There is one badge per section of the base ELF, in link order.
`tools/check_elf.py --progress` (`tools/build.sh progress`) rewrites them,
[`docs/jun26/PROGRESS.md`](docs/jun26/PROGRESS.md) and the dashboard's
`docs/jun26/progress.json` from the built ELF and its link map.

A badge reads `100 %` when the whole section equals the base. Where part of a
section comes from the user's ELF, the badge splits the figure: `source` is
the share placed by objects compiled or assembled from the tracked sources
under `ico2/` and `sce/`, and `disc` is the share of the data-only members the
build generates from the user's own ELF (next section) and of the campaign
stubs `config/stubs.jun26.txt` still lists (Status, above). `.sbss` and `.bss`
hold no file bytes, so their figure is the share of the range that an
object defines and the link places at the base's addresses.

## Data tables

The game links 120 data-only runs of its own archive, `ico2000.a`
(`config/data_members.jun26.txt`): the 70 members with data sections and no
code that the PAL disc's MAIN.MAP lists (stage layouts, model paths, motion
and sound definitions, way points), mcdata.o's own .data, the save
icon's icon.sys record, which PAL reads from the disc instead, and the 49
enemy-set tables of the stage models in EnemyInit.o, which PAL keeps only
for its first model. PAL's three unlisted runs, the hint table,
the motion sync pairs and the subtitle file names, are not in this build, as
in the August 6, 2001 prototype, and no code here reads any of them. The demo
disc ships no map, so each run's place in this ELF was found from the code
that reads it, the members follow the prototype's member order, and each
member keeps PAL's name by member order; the file's header gives the method.
Many of the demo's tables hold another number of rows, and several record
types have another layout (`docs/README.md`). They are the game's content,
and nothing of that content is committed. The build generates them from the
user's own `baserom/jun26/baseelf.elf` into `build/jun26/data/`. Each member
becomes `build/jun26/data/<member>.c`, an initialized array of its record
type compiled with the game's flags (`tools/gen_data_c.py`);
`config/data_schema.jun26.txt` holds only the record type, its header, the
element count, MAIN.MAP's symbol names and which fields are masks. A count
derived from a table is a fact about it, not content: the staff roll's line
count is written by the generator as `sizeof` over the table.
[`docs/LEGAL.md`](docs/LEGAL.md) has the reasoning.

## Layout

```
ico2/<programmer>/<kind>/   the game, at the paths the PAL disc's listing
                            records: common, fumi, ito, omori, script, seki,
                            sugipon, each with src/ and include/, and fumi's
                            ios/, isys/ and sound/, ito's mpeg/
ico2/vusrc/                 the five VU1 microprograms (cluster, mesh,
                            normal_c, normal_l, particle): each a .dsm (the
                            DMA tags) around its .vsm (the program, through
                            cpp), and two shared includes
sce/<archive>/              Sony's runtime libraries (libkernl, libgraph,
                            libdma, libpad, libmc, libcdvd, libmpeg, libipu,
                            libpkt, libsndn2, libvu0) and the compiler's
                            newlib libc and libm and libgcc, plus crt0.s;
                            the demo's link has no libscf member
config/                     link_order.jun26.txt (every object in link
                            order), link.jun26.ld (the linker script),
                            data_members.jun26.txt (the data-only members),
                            data_schema.jun26.txt (the record type, count
                            and names of each member built as C),
                            stubs.jun26.txt (the campaign stubs, while any
                            remain), sha1sums.jun26.txt
tools/                      setup, extraction, build and gate scripts, the
                            same on every target branch, listed in
                            tools/README.md
docs/                       documentation, indexed by docs/README.md;
                            docs/jun26/ holds the generated progress files
baserom/  build/            local only and gitignored: the user's disc image
                            and extracted ELF, and the build output
```

Each game file compiles from inside its programmer's directory with relative
`-I../<other>/include` entries, because ee-gcc writes the path it is given
into `__FILE__` strings the ROM contains (`tools/compile_c.sh`).
[`docs/HEADERS.md`](docs/HEADERS.md) says which headers the PAL disc attests
and where the other declarations live, and
[`docs/PROGRAMMERS.md`](docs/PROGRAMMERS.md) who wrote which subsystem.

## Toolchain

`tools/setup.sh` fetches or builds every tool into `tools/cc/`; nothing comes
from a Sony SDK.

| tool | role | source | licence |
| --- | --- | --- | --- |
| ee-gcc 2.9-991111-01 | compiles every C file | `decompme/compilers` release `ee-gcc2.9-991111-01.tar.xz` | GNU GPL (GCC) |
| ee-as 2.9-991111 (bundled with that compiler) | assembles the game, libc, libm and libgcc | same archive | GNU GPL (binutils) |
| SCE ee-as 2.10-ee-001003-1 (bundled with ee-gcc 2.96) | assembles the SDK archives under `sce/` | `decompme/compilers` release `ee-gcc2.96.tar.xz`; only its assembler runs | GNU GPL (binutils) |
| GNU ld 2.10 with `tools/binutils-2.10-ee.patch` and `tools/binutils-2.10-dvp-ld.patch` | links `build/jun26/ico.elf` | `ftp.gnu.org` `binutils-2.10.tar.gz` (sha256 pinned in `tools/setup.sh`) | GPL-2.0-or-later |
| dvp-as with `tools/binutils-dvp-overlay-fill.patch` | assembles the VU1 microprograms | ps2dev `binutils-gdb`, branch `dvp-v2.45.1`, commit `3eb45ea3` | GPL-3.0-or-later |

The assembler follows the archive, as the disc's link did: the PAL disc's
MAIN.MAP takes libc, libm and libgcc from the compiler's install and every
other library from Sony's SDK install, whose objects carry the later
assembler's delay-slot filling (`tools/compile_c.sh`). The game compiles with
`-g -G 8 -fno-common`, Sony's libraries with `-G 0` and no `-g`, newlib and
libgcc also with `-fno-builtin`. The first ld patch backports the R5900
machine type and the DVP overlay sections from ps2dev's
`binutils-2.14-PS2.patch`; the second places each VU overlay at address 0,
the rule of the Cygnus linker shipped with the GPL ee-gcc 2.9-991111 sources.
The licence notices are the tools' own (`--version` for the assemblers and
ld; the source trees for the rest). The host's `mips-linux-gnu-objcopy`
writes `build/jun26/ico.rom`.

## Branches

| branch | targets | |
| --- | --- | --- |
| `main` | `pal` (PAL retail, SCES-50760, `SCES_507.60`) and `jpn` (Japanese retail, SCPS-11003, `SCPS_110.03`) | the shared tree this branch was seeded from, with its own README; finished targets join there |
| `ntsc` | `us` (USA retail, SLUS-20218, `SCUS_971.13`) | a single-target tree with its own README, until it joins `main` |
| `aug6` | `aug6` (the August 6, 2001 prototype) | a single-target tree with its own README, until it joins `main` |
| `jun26` | `jun26` (the June 26, 2001 demo, SCUS-97158, `CUS97113/SCPS_000.00`) | this document: a single-target tree, until it joins `main` |
| `pal` | `pal` | the single-target PAL tree, frozen |
| `jpn` | `jpn` | the single-target Japanese tree, frozen |

`ntsc`, `aug6` and `jun26` are separate trees that are never merged into each
other or into `main`. Every branch carries one build layer, file for file:
`tools/`, `build.sh`, `.github/` and `docs/index.html`
(`tools/check_shared_layer.sh` checks it against `main`); a change to it lands
on `main` first. A finished target joins `main` by the recipe in `main`'s
`docs/BUILDING.md` ("Targets and version blocks").

## PC port

[ico-pc](https://github.com/nathanialf/ico-pc) is a fork of `main` that is
being turned into a native PC port; it builds on the PAL tree, not on this
one. See [`docs/PORT.md`](docs/PORT.md).

## Legal and licence

The code in this repository is MIT licensed ([`LICENSE`](LICENSE)). The
licence covers the code written for this project and grants no rights in the
game, its data or anything else owned by Sony Interactive Entertainment or
Team Ico. [`docs/LEGAL.md`](docs/LEGAL.md) says what may and may not be in the
repository and which references were used.
