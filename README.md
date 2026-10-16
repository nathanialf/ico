# ico

A source tree for the PlayStation 2 game **ICO** (Sony Computer Entertainment,
2001) that rebuilds the boot ELF of the USA retail disc, SLUS-20218
(`SCUS_971.13`, `VER = 1.00`), with the toolchain the game was built with.
Every byte the console loads is identical to the disc's (the ROM image SHA-1
matches), and so is the ELF file itself (its SHA-1 matches the disc's). The
tree was seeded from `main`, the PAL build's finished tree; the USA build is
an earlier link of the same program (its build stamp reads `Aug 20 2001`,
PAL's `Jan 17 2002`), and this branch carries the functions and tables in
which the two differ.

<!-- progress:begin -->
| Target | Sections identical to the base |
| --- | --- |
| [USA retail (SLUS-20218)](https://nathanialf.github.io/ico/#us) | ![.text progress](https://img.shields.io/badge/text-100.00%20%25%20%2874.44%20%25%20source%20%2B%2025.56%20%25%20disc%29-brightgreen.svg) ![.vutext progress](https://img.shields.io/badge/vutext-100.00%20%25-brightgreen.svg) ![.data progress](https://img.shields.io/badge/data-100.00%20%25%20%2869.12%20%25%20source%20%2B%2030.88%20%25%20disc%29-brightgreen.svg) ![.rodata progress](https://img.shields.io/badge/rodata-100.00%20%25%20%288.67%20%25%20source%20%2B%2091.33%20%25%20disc%29-brightgreen.svg) ![.lit4 progress](https://img.shields.io/badge/lit4-100.00%20%25%20%2859.49%20%25%20source%20%2B%2040.51%20%25%20disc%29-brightgreen.svg) ![.sdata progress](https://img.shields.io/badge/sdata-100.00%20%25%20%2894.01%20%25%20source%20%2B%205.99%20%25%20disc%29-brightgreen.svg) ![.sbss progress](https://img.shields.io/badge/sbss-100.00%20%25-brightgreen.svg) ![.bss progress](https://img.shields.io/badge/bss-100.00%20%25-brightgreen.svg) |
<!-- progress:end -->

**[Progress dashboard](https://nathanialf.github.io/ico/#us)**: every
section, directory, translation unit and function of the build compared with
the base ELF.

> [!IMPORTANT]
> This project is not affiliated with Sony Interactive Entertainment or Team
> Ico. *ICO* is a trademark of its owners. No disc data is in this repository;
> you supply your own disc image. Read [`docs/LEGAL.md`](docs/LEGAL.md).

## Status

2606 of the build's 5447 functions are still campaign stubs: the C for them
does not yet give the USA bytes, so the build writes each one from the
user's own `baserom/us/baseelf.elf` at its place in its translation unit
(`config/stubs.us.txt`, `tools/gen_stub_s.py`; nothing of them is
committed). The gate passes with them in place, so every badge above reads
100 %, and the badges split each figure into the share built from the tracked
sources and the share from the disc: the stubs and the data tables. The
`.text` source share is the matched code; the rest of it is the stubs. When
the list is empty the mechanism is idle and the branch is finished in
`main`'s shape.

## Quickstart

```sh
git clone -b ntsc https://github.com/nathanialf/ico.git
cd ico
mkdir -p baserom
cp "/path/to/Ico (USA).bin" baserom/Ico_USA.bin
cp "/path/to/Ico (USA).cue" baserom/Ico_USA.cue
./build.sh
```

`./build.sh` runs `tools/setup.sh` when the Python environment or the
toolchain under `tools/cc/` is missing, extracts `baserom/us/baseelf.elf`
from the disc image when it is missing (`tools/extract_elf.sh`, which first
cooks the raw `.bin` into `baserom/Ico_USA.iso` beside it, once), then runs
`tools/build.sh setup` (or `verify` when `build.ninja` already exists),
`ninja` and `tools/check_elf.py --gate`, and exits non-zero if any step
fails. The host needs a 64-bit Linux with 32-bit libraries, a host gcc,
`mips-linux-gnu-objcopy` and network access for the first run;
[`docs/BUILDING.md`](docs/BUILDING.md) lists the packages and describes each
step.

The build checks the SHA-1s from `config/sha1sums.txt`: the extracted ELF
before it starts, and the rebuilt ROM image and the rebuilt ELF at the end.

| file | SHA-1 |
| --- | --- |
| `baserom/us/baseelf.elf` (the disc's `SCUS_971.13`) | `a4d8fc1948fb2da2395f3863a94a3b93de55de14` |
| `baserom/us/baseelf.rom` and `build/ico.rom` (`objcopy -O binary`) | `fbf50c75cd5911273511c4f9af90503ff8423582` |

The gate (`tools/check_elf.py --gate`) also compares every allocated section
of `build/ico.elf` with the base ELF by address and checks that `.sbss` and
`.bss` cover the base's ranges, and that the whole-file SHA-1 of
`build/ico.elf` is the base ELF's (`--require-elf-sha`): the section headers,
the symbol-name strings ld keeps and the `.DVP` overlay names and tables all
match. The overlay names hash the file and line the DVP assembler was reading
and are the same as PAL's: each microprogram's `.dsm` for the first, then the
text cpp read from standard input (an empty name) and, in normal_c and
normal_l, the shared include `vusrc/scissorcommcut.h`, whose name is derived
(the hash fixes it among the names of its form). The overlay contents are not
code: each section is one byte repeated over the program's size, a byte the
DVP assembler never set, so the five constant-address overlays
(`.DVP.overlay..0x0.*`, one per program) carry whatever the assembler's heap
held. On the USA disc that byte is 0x6E (on PAL's it is zero), and the
seven continuation overlays (`..unknvma.*`) are zero.
`tools/binutils-dvp-overlay-fill.patch` makes dvp-as write the byte
explicitly (`--overlay-fill=N` for the five, 0 for the rest), taken from the
`overlay-fill=110` token on each `.dsm` line of `config/link_order.us.txt`,
so the build does not depend on the host's heap. `tools/check_elf.py
--full-diff` prints the whole-file comparison.

## Progress badges

There is one badge per section of the base ELF, in link order.
`tools/check_elf.py --progress` (`tools/build.sh progress`) rewrites them,
[`docs/PROGRESS.md`](docs/PROGRESS.md) and the dashboard's
`docs/progress.json` from the built ELF and its link map.

A badge reads `100 %` when the whole section equals the base. Where part of a
section comes from the user's ELF, the badge splits the figure: `source` is
the share placed by objects compiled or assembled from the tracked sources
under `ico2/` and `sce/`, and `disc` is the share of the data-only members the
build generates from the user's own ELF (next section) and of the campaign
stubs (Status, above). `.sbss` and `.bss` hold no file bytes, so their figure
is the share of the range that an object defines and the link places at the
base's addresses.

## Data tables

The game links 71 data-only runs of its own archive, `ico2000.a`: the 70
members with data sections and no code that the PAL disc's MAIN.MAP lists
(stage layouts, model paths, motion and sound definitions, way points) and
one run it does not list (`config/data_members.us.txt`). PAL's other two
unlisted runs, the hint table and the subtitle file names, are not in this
build, and no code here reads either. The USA disc ships no map, so each
run's place in this ELF was found from the code that reads it, and each
member keeps PAL's name by member order; the file's header gives the method,
and each row says how its content compares with PAL's (most of the USA
build's tables hold fewer rows, and eight record types have another
layout). They are the
game's content, and nothing of that content is committed. The build
generates them from the user's own `baserom/us/baseelf.elf` into
`build/data/`. Each member becomes `build/data/<member>.c`, an initialized
array of its record type compiled with the game's flags
(`tools/gen_data_c.py`); `config/data_schema.us.txt` holds only the record
type, its header, the element count, MAIN.MAP's symbol names and which
fields are masks. A count derived from a table is a fact about it, not
content: the staff roll's line count is written by the generator as
`sizeof` over the table. [`docs/LEGAL.md`](docs/LEGAL.md) has the
reasoning.

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
                            the USA link has no libscf member, so
                            sce/libscf/ keeps only its header
config/                     link_order.us.txt (every object in link order),
                            link.us.ld (the linker script),
                            data_members.us.txt (the data-only members),
                            data_schema.us.txt (the record type, count and
                            names of each member built as C),
                            stubs.us.txt (the campaign stubs), sha1sums.txt
tools/                      setup, extraction, build and gate scripts, the
                            same on every target branch, listed in
                            tools/README.md
docs/                       documentation, indexed by docs/README.md
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
| GNU ld 2.10 with `tools/binutils-2.10-ee.patch` and `tools/binutils-2.10-dvp-ld.patch` | links `build/ico.elf` | `ftp.gnu.org` `binutils-2.10.tar.gz` (sha256 pinned in `tools/setup.sh`) | GPL-2.0-or-later |
| dvp-as with `tools/binutils-dvp-overlay-fill.patch` | assembles the VU1 microprograms | ps2dev `binutils-gdb`, branch `dvp-v2.45.1`, commit `3eb45ea3` | GPL-3.0-or-later |

The assembler follows the archive, as the disc's link did: the PAL disc's
MAIN.MAP takes libc, libm and libgcc from the compiler's install and every
other library from Sony's SDK install, whose objects carry the later assembler's delay-slot
filling (`tools/compile_c.sh`). The game compiles with `-g -G 8
-fno-common`, Sony's libraries with `-G 0` and no `-g`, newlib and libgcc
also with `-fno-builtin`. The first ld patch backports the R5900 machine type and the
DVP overlay sections from ps2dev's `binutils-2.14-PS2.patch`; the second
places each VU overlay at address 0, the rule of the Cygnus linker shipped
with the GPL ee-gcc 2.9-991111 sources. The licence notices are the tools'
own (`--version` for the assemblers and ld; the source trees for the rest).
The host's `mips-linux-gnu-objcopy` writes `build/ico.rom`.

## Branches

| branch | target | |
| --- | --- | --- |
| `main` | PAL retail, SCES-50760, `SCES_507.60` | the finished PAL tree this branch was seeded from, with its own README |
| `jpn` | Japanese retail, SCPS-11003, `SCPS_110.03` | the same game on the Japanese disc, with its own README |
| `ntsc` | USA retail, SLUS-20218, `SCUS_971.13` | this document |
| `aug6` | the August 6, 2001 prototype | an earlier build of the game, with its own README |

The branches are separate trees and are never merged into each other. The
four share one build layer, file for file: `tools/`, `build.sh`, `.github/`
and `docs/index.html` (`tools/check_shared_layer.sh` checks it); a change to
it lands on `main` first.

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
