# ico

A source tree for the PlayStation 2 game **ICO** (Sony Computer Entertainment,
2001) that rebuilds the boot ELF of four retail discs, the PAL one,
SCES-50760 (`SCES_507.60`), the Japanese one, SCPS-11003 (`SCPS_110.03`;
`SYSTEM.CNF` reads `VER = 1.02`, `VMODE = NTSC`), the Korean one,
SCPS-56001 (`SCPS_560.01`; `VER = 1.00`, `VMODE = NTSC`), and the USA one,
SLUS-20218 (`SCUS_971.13`; `VER = 1.00`, `VMODE = NTSC`), of the August 6,
2001 prototype disc (`SCUS_971.13`; `VER = 1.00`, `VMODE = NTSC`), and of
the June 26, 2001 demo on the Official U.S. PlayStation Magazine demo disc 49
(SCUS-97158; the demo's own ELF `CUS97113/SCPS_000.00`, which the disc's
menu starts; `VER = 1.00`, `VMODE = NTSC`), with the toolchain the game was
built with. `VERSION=pal`, `VERSION=jpn`, `VERSION=kor`, `VERSION=ntsc`,
`VERSION=aug6` or `VERSION=jun26` picks the target. For each,
every byte the console loads is identical to the disc's (the ROM image SHA-1
matches), and so is the ELF file itself (its SHA-1 matches the disc's).

The demo, the prototype and the USA, Japanese and Korean builds are earlier
links of the same program as the PAL one: the demo's ELF carries the stamp
`Jun 26 2001`, the others' debug menus' `DISC VER.` lines read `Aug  7
2001`, `Aug 20 2001`, `Nov  2 2001` and `Jan  9 2002` (`debug.c`), PAL's
`Jan 17 2002`, and the Korean text is the Japanese one with 24 files
changed. One tree (`ico2/`, `sce/`) builds all six: its base text is the
PAL revision, and where another build differs the same file holds its lines
inline in `VERSION_JPN`, `VERSION_KOR`, `VERSION_NTSC`, `VERSION_AUG6` and
`VERSION_JUN26` blocks;
[`docs/TARGETS.md`](docs/TARGETS.md) lists those differences and
[`docs/BUILDING.md`](docs/BUILDING.md) explains the blocks.

<!-- progress:begin -->
| Target | Sections identical to the base |
| --- | --- |
| [PAL retail (SCES-50760)](https://nathanialf.github.io/ico/#pal) | ![.text progress](https://img.shields.io/badge/text-100.00%20%25-brightgreen.svg) ![.vutext progress](https://img.shields.io/badge/vutext-100.00%20%25-brightgreen.svg) ![.data progress](https://img.shields.io/badge/data-100.00%20%25%20%2872.54%20%25%20source%20%2B%2027.46%20%25%20disc%29-brightgreen.svg) ![.rodata progress](https://img.shields.io/badge/rodata-100.00%20%25%20%289.62%20%25%20source%20%2B%2090.38%20%25%20disc%29-brightgreen.svg) ![.lit4 progress](https://img.shields.io/badge/lit4-100.00%20%25-brightgreen.svg) ![.sdata progress](https://img.shields.io/badge/sdata-100.00%20%25%20%2899.91%20%25%20source%20%2B%200.09%20%25%20disc%29-brightgreen.svg) ![.sbss progress](https://img.shields.io/badge/sbss-100.00%20%25-brightgreen.svg) ![.bss progress](https://img.shields.io/badge/bss-100.00%20%25-brightgreen.svg) |
| [Japanese retail (SCPS-11003)](https://nathanialf.github.io/ico/#jpn) | ![.text progress](https://img.shields.io/badge/text-100.00%20%25-brightgreen.svg) ![.vutext progress](https://img.shields.io/badge/vutext-100.00%20%25-brightgreen.svg) ![.data progress](https://img.shields.io/badge/data-100.00%20%25%20%2872.82%20%25%20source%20%2B%2027.18%20%25%20disc%29-brightgreen.svg) ![.rodata progress](https://img.shields.io/badge/rodata-100.00%20%25%20%289.63%20%25%20source%20%2B%2090.37%20%25%20disc%29-brightgreen.svg) ![.lit4 progress](https://img.shields.io/badge/lit4-100.00%20%25-brightgreen.svg) ![.sdata progress](https://img.shields.io/badge/sdata-100.00%20%25%20%2899.91%20%25%20source%20%2B%200.09%20%25%20disc%29-brightgreen.svg) ![.sbss progress](https://img.shields.io/badge/sbss-100.00%20%25-brightgreen.svg) ![.bss progress](https://img.shields.io/badge/bss-100.00%20%25-brightgreen.svg) |
| [Korean retail (SCPS-56001)](https://nathanialf.github.io/ico/#kor) | ![.text progress](https://img.shields.io/badge/text-100.00%20%25-brightgreen.svg) ![.vutext progress](https://img.shields.io/badge/vutext-100.00%20%25-brightgreen.svg) ![.data progress](https://img.shields.io/badge/data-100.00%20%25%20%2872.84%20%25%20source%20%2B%2027.16%20%25%20disc%29-brightgreen.svg) ![.rodata progress](https://img.shields.io/badge/rodata-100.00%20%25%20%289.63%20%25%20source%20%2B%2090.37%20%25%20disc%29-brightgreen.svg) ![.lit4 progress](https://img.shields.io/badge/lit4-100.00%20%25-brightgreen.svg) ![.sdata progress](https://img.shields.io/badge/sdata-100.00%20%25%20%2899.91%20%25%20source%20%2B%200.09%20%25%20disc%29-brightgreen.svg) ![.sbss progress](https://img.shields.io/badge/sbss-100.00%20%25-brightgreen.svg) ![.bss progress](https://img.shields.io/badge/bss-100.00%20%25-brightgreen.svg) |
| [USA retail (SLUS-20218)](https://nathanialf.github.io/ico/#ntsc) | ![.text progress](https://img.shields.io/badge/text-100.00%20%25-brightgreen.svg) ![.vutext progress](https://img.shields.io/badge/vutext-100.00%20%25-brightgreen.svg) ![.data progress](https://img.shields.io/badge/data-100.00%20%25%20%2869.12%20%25%20source%20%2B%2030.88%20%25%20disc%29-brightgreen.svg) ![.rodata progress](https://img.shields.io/badge/rodata-100.00%20%25%20%289.65%20%25%20source%20%2B%2090.35%20%25%20disc%29-brightgreen.svg) ![.lit4 progress](https://img.shields.io/badge/lit4-100.00%20%25-brightgreen.svg) ![.sdata progress](https://img.shields.io/badge/sdata-100.00%20%25%20%2899.82%20%25%20source%20%2B%200.18%20%25%20disc%29-brightgreen.svg) ![.sbss progress](https://img.shields.io/badge/sbss-100.00%20%25-brightgreen.svg) ![.bss progress](https://img.shields.io/badge/bss-100.00%20%25-brightgreen.svg) |
| [Aug-6-2001 prototype](https://nathanialf.github.io/ico/#aug6) | ![.text progress](https://img.shields.io/badge/text-100.00%20%25-brightgreen.svg) ![.vutext progress](https://img.shields.io/badge/vutext-100.00%20%25-brightgreen.svg) ![.data progress](https://img.shields.io/badge/data-100.00%20%25%20%2869.24%20%25%20source%20%2B%2030.76%20%25%20disc%29-brightgreen.svg) ![.rodata progress](https://img.shields.io/badge/rodata-100.00%20%25%20%289.66%20%25%20source%20%2B%2090.34%20%25%20disc%29-brightgreen.svg) ![.lit4 progress](https://img.shields.io/badge/lit4-100.00%20%25-brightgreen.svg) ![.sdata progress](https://img.shields.io/badge/sdata-100.00%20%25%20%2899.82%20%25%20source%20%2B%200.18%20%25%20disc%29-brightgreen.svg) ![.sbss progress](https://img.shields.io/badge/sbss-100.00%20%25-brightgreen.svg) ![.bss progress](https://img.shields.io/badge/bss-100.00%20%25-brightgreen.svg) |
| [Jun-26-2001 demo (SCUS-97158)](https://nathanialf.github.io/ico/#jun26) | ![.text progress](https://img.shields.io/badge/text-100.00%20%25-brightgreen.svg) ![.vutext progress](https://img.shields.io/badge/vutext-100.00%20%25-brightgreen.svg) ![.data progress](https://img.shields.io/badge/data-100.00%20%25%20%2868.37%20%25%20source%20%2B%2031.63%20%25%20disc%29-brightgreen.svg) ![.rodata progress](https://img.shields.io/badge/rodata-100.00%20%25%20%289.30%20%25%20source%20%2B%2090.70%20%25%20disc%29-brightgreen.svg) ![.lit4 progress](https://img.shields.io/badge/lit4-100.00%20%25-brightgreen.svg) ![.sdata progress](https://img.shields.io/badge/sdata-100.00%20%25%20%2899.91%20%25%20source%20%2B%200.09%20%25%20disc%29-brightgreen.svg) ![.sbss progress](https://img.shields.io/badge/sbss-100.00%20%25-brightgreen.svg) ![.bss progress](https://img.shields.io/badge/bss-100.00%20%25-brightgreen.svg) |
<!-- progress:end -->

**[Progress dashboard](https://nathanialf.github.io/ico/#pal)**: every
section, directory, translation unit and function of each build compared with
its base ELF. Each target's numbers on the site come from its own branch
(`pal`, `jpn`, `kor`, `ntsc`, `aug6`, `jun26`); the `docs/<slug>/` files here
are `main`'s build record.

> [!IMPORTANT]
> This project is not affiliated with Sony Interactive Entertainment or Team
> Ico. *ICO* is a trademark of its owners. No disc data is in this repository;
> you supply your own disc images. Read [`docs/LEGAL.md`](docs/LEGAL.md).

## Quickstart

```sh
git clone https://github.com/nathanialf/ico.git
cd ico
mkdir -p baserom
# PAL
cp "/path/to/Ico (Europe).iso" baserom/Ico_PAL.iso
VERSION=pal ./build.sh
# Japanese
cp "/path/to/Ico (Japan).bin" baserom/Ico_JPN.bin
cp "/path/to/Ico (Japan).cue" baserom/Ico_JPN.cue
VERSION=jpn ./build.sh
# Korean
cp "/path/to/Ico (Korea).iso" baserom/Ico_KOR.iso
VERSION=kor ./build.sh
# USA
cp "/path/to/Ico (USA).bin" baserom/Ico_USA.bin
cp "/path/to/Ico (USA).cue" baserom/Ico_USA.cue
VERSION=ntsc ./build.sh
# the August 6, 2001 prototype
cp "/path/to/Ico (prototype).bin" baserom/Ico_AUG6.bin
cp "/path/to/Ico (prototype).cue" baserom/Ico_AUG6.cue
VERSION=aug6 ./build.sh
# the June 26, 2001 demo (Official U.S. PlayStation Magazine demo disc 49)
cp "/path/to/demo disc 49.iso" baserom/Ico_JUN26.iso
VERSION=jun26 ./build.sh
```

Each target needs only its own disc. Without `VERSION` the target is the first
configured one, `pal`. `tools/build.sh gate-all` builds and gates every
configured target and fails at once, naming the missing file, if one of them
has no `baserom/<slug>/baseelf.elf`.

`./build.sh` runs `tools/setup.sh` when the Python environment or the
toolchain under `tools/cc/` is missing, extracts `baserom/<slug>/baseelf.elf`
from the disc image when it is missing (`tools/extract_elf.sh`; for the
Japanese, USA and prototype discs it first cooks the raw `.bin` into
`baserom/Ico_JPN.iso`, `baserom/Ico_USA.iso` or `baserom/Ico_AUG6.iso` beside
it, once; the PAL, Korean and demo images are plain ISOs, read directly; the
demo disc's `SYSTEM.CNF` boots the magazine's menu, and the build reads the
demo's own ELF, `CUS97113/SCPS_000.00`), then
runs `tools/build.sh setup` (or `verify` when `build.ninja` already exists),
`ninja` and `tools/check_elf.py --gate`, and exits non-zero if any step
fails. The host needs a 64-bit Linux with 32-bit libraries, a host
gcc, `mips-linux-gnu-objcopy` and network access for the first run;
[`docs/BUILDING.md`](docs/BUILDING.md) lists the packages and describes each
step.

The build checks the SHA-1s from `config/sha1sums.<slug>.txt`: the extracted
ELF before it starts, and the rebuilt ROM image and the rebuilt ELF at the
end.

| target | file | SHA-1 |
| --- | --- | --- |
| pal | `baserom/pal/baseelf.elf` (the disc's `SCES_507.60`) | `da3644c54c26fe760f3b6a591a5fc2eab396ed2b` |
| pal | `baserom/pal/baseelf.rom` and `build/pal/ico.rom` (`objcopy -O binary`) | `a401d1e5a20b1659189a8b1026a8eb35811dc9ca` |
| jpn | `baserom/jpn/baseelf.elf` (the disc's `SCPS_110.03`) | `580da1dcc4c239a1608a10300e7e220fe5d35525` |
| jpn | `baserom/jpn/baseelf.rom` and `build/jpn/ico.rom` (`objcopy -O binary`) | `58ef44cfeeacd060ffb2acfbf42d8a21bbffd318` |
| kor | `baserom/kor/baseelf.elf` (the disc's `SCPS_560.01`) | `f9b00596d133c698df20c8ffe4ca2d7107e236bb` |
| kor | `baserom/kor/baseelf.rom` and `build/kor/ico.rom` (`objcopy -O binary`) | `f438c8f841a84837231d79cab0c761bfb211259b` |
| ntsc | `baserom/ntsc/baseelf.elf` (the disc's `SCUS_971.13`) | `a4d8fc1948fb2da2395f3863a94a3b93de55de14` |
| ntsc | `baserom/ntsc/baseelf.rom` and `build/ntsc/ico.rom` (`objcopy -O binary`) | `fbf50c75cd5911273511c4f9af90503ff8423582` |
| aug6 | `baserom/aug6/baseelf.elf` (the prototype disc's `SCUS_971.13`) | `5d169c281756a8bde712704fa0cb9eb984693cd6` |
| aug6 | `baserom/aug6/baseelf.rom` and `build/aug6/ico.rom` (`objcopy -O binary`) | `2b4d7de41966ff38d061b4c985de45fc212e2fb2` |
| jun26 | `baserom/jun26/baseelf.elf` (the demo disc's `CUS97113/SCPS_000.00`) | `95c3d438185c3b75303b68719cfd48c84f2f8bfa` |
| jun26 | `baserom/jun26/baseelf.rom` and `build/jun26/ico.rom` (`objcopy -O binary`) | `e5d6dd3c156ed5489a4d2e7bbf4707cd58d0dccc` |

The gate (`tools/check_elf.py --gate`) also compares every allocated section
of `build/<slug>/ico.elf` with the base ELF by address and checks that `.sbss`
and `.bss` cover the base's ranges, and that the whole-file SHA-1 of
`build/<slug>/ico.elf` is the base ELF's (`--require-elf-sha`): the section
headers, the symbol-name strings ld keeps and the `.DVP` overlay names and
tables all match. The overlay names hash the file and line the DVP assembler
was reading: each microprogram's `.dsm` for the first, then the text cpp read
from standard input (an empty name) and, in normal_c and normal_l, the shared
include `vusrc/scissorcommcut.h`, whose name is derived (the hash fixes it
among the names of its form). The line in each name is the `.vsm` line where
the overlay's first instruction stands, taken from cpp's line markers, so
where the demo schedules a program otherwise than the later builds (mesh,
normal_c, normal_l) a `#line LN(...) ""` before that instruction gives each
target its own line. The overlay contents are not code: each section
is one byte repeated over the program's size, a byte the DVP assembler never
set, so the five constant-address overlays (`.DVP.overlay..0x0.*`, one per
program) carry whatever the assembler's heap held. On PAL's build machine that
and the Korean one it was zero; the JPN, USA, Aug-6-2001 and Jun-26-2001
discs carry 0x6E there, and every disc
leaves the seven continuation overlays (`..unknvma.*`) zero.
`tools/binutils-dvp-overlay-fill.patch` makes dvp-as write the byte
explicitly (`--overlay-fill=N` for the five, 0 for the rest), taken from an
`overlay-fill=N` token on the `.dsm` lines of the target's link order (none on
pal's or kor's, `overlay-fill=110` on each of jpn's, ntsc's, aug6's and jun26's), so the build no longer depends on
the host's heap: with the unpatched assembler, a host that sets
`MALLOC_PERTURB_` (145 gives 0x6E) fails PAL's whole-file SHA-1.
`tools/check_elf.py --full-diff` prints the whole-file comparison.

## Progress badges

There is one badge per section of the base ELF, in link order.
`tools/check_elf.py --progress` (`tools/build.sh progress`) rewrites them,
`docs/<slug>/PROGRESS.md` ([pal](docs/pal/PROGRESS.md),
[jpn](docs/jpn/PROGRESS.md), [kor](docs/kor/PROGRESS.md), [ntsc](docs/ntsc/PROGRESS.md), [aug6](docs/aug6/PROGRESS.md), [jun26](docs/jun26/PROGRESS.md)) and the dashboard's `docs/<slug>/progress.json`
from the built ELF and its link map; `tools/build.sh progress-all` does it
for every configured target.

A badge reads `100 %` when the whole section equals the base. Where part of a
section comes from the data tables (next section), the badge splits the
figure: `source` is the share placed by objects compiled or assembled from
the tracked sources under `ico2/` and `sce/`, and `disc` is the share of the
data-only members the build generates from the user's own ELF. `.sbss` and `.bss` hold no file
bytes, so their figure is the share of the range that an object defines and
the link places at the base's addresses.

## Data tables

Each disc's link includes 70 members of the game's own archive,
`ico2000.a`, with data sections and no code that the PAL disc's MAIN.MAP lists
(stage layouts, model paths, motion and sound definitions, way points) and
three runs it does not list; the build generates 72 of those data-only runs
for each disc (`config/data_members.<slug>.txt`), because `enemy-def` is
committed source (below).
The Japanese, Korean and USA discs ship no map, the prototype disc's map
is PAL's and the demo's directory ships none, so each run's place in an ELF
was found from
the code that reads it, and each member keeps PAL's name by member order (the
USA build generates 70 runs: PAL's hint table and subtitle file names are not
in its link; the August prototype's 69, the 70 members less `enemy-def` and
none of the three unmapped runs; the demo's 119, the 70 members, `mcdata.o`'s
save icon record and `EnemyInit.o`'s 49 enemy-set tables, less `enemy-def`).
They
are the game's content, and nothing of that content is committed, with one
exception: the enemy kind table `enemyKind` is committed as
`ico2/sugipon/src/enemyKind.c` (the paragraph "One exception: `enemyKind`" in
[`docs/LEGAL.md`](docs/LEGAL.md)). The build
generates them from the user's own `baserom/<slug>/baseelf.elf` into
`build/<slug>/data/`. Each member becomes `build/<slug>/data/<member>.c`, an
initialized array of its record type compiled with the game's flags
(`tools/gen_data_c.py`); `config/data_schema.<slug>.txt` holds only the record
type, its header, the element count, MAIN.MAP's symbol names and which
fields are masks. A count derived from a table is a fact about it, not
content: the staff roll's line count is written by the generator as
`sizeof` over the table. [`docs/LEGAL.md`](docs/LEGAL.md) has the
reasoning.

## Layout

```
ico2/<programmer>/<kind>/   the game, the PAL revision, at the paths the PAL
                            disc's listing records: common, fumi, ito, omori,
                            script, seki, sugipon, each with src/ and
                            include/, and fumi's ios/, isys/ and sound/,
                            ito's mpeg/
ico2/vusrc/                 the five VU1 microprograms (cluster, mesh,
                            normal_c, normal_l, particle): each a .dsm (the
                            DMA tags) around its .vsm (the program, through
                            cpp, the demo's lines in version blocks), and
                            two shared includes
sce/<archive>/              Sony's runtime libraries (libkernl, libgraph,
                            libdma, libpad, libmc, libcdvd, libmpeg, libipu,
                            libpkt, libscf, libsndn2, libvu0) and the
                            compiler's newlib libc and libm and libgcc, plus
                            crt0.s
config/                     per target <slug>: link_order.<slug>.txt (every
                            object in link order), link.<slug>.ld (the linker
                            script), data_members.<slug>.txt (the data-only
                            members), data_schema.<slug>.txt (the record
                            type, count and names of each member built as C),
                            sha1sums.<slug>.txt; ico.pal.yaml and
                            symbol_addrs.pal*.txt are kept as a record and
                            nothing reads them
tools/                      setup, extraction, build and gate scripts, the
                            same on every branch, listed in tools/README.md
docs/                       documentation, indexed by docs/README.md;
                            docs/<slug>/ holds each target's progress files
baserom/<slug>/  build/<slug>/
                            local only and gitignored: the user's disc image
                            and extracted ELF, and the build output
```

Each game file compiles from inside its programmer's directory with relative
`-I../<other>/include` entries, because ee-gcc writes the path it is given
into `__FILE__` strings the ROM contains (`tools/compile_c.sh`).
[`docs/HEADERS.md`](docs/HEADERS.md) says which headers the disc attests
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
| GNU ld 2.10 with `tools/binutils-2.10-ee.patch` and `tools/binutils-2.10-dvp-ld.patch` | links `build/<slug>/ico.elf` | `ftp.gnu.org` `binutils-2.10.tar.gz` (sha256 pinned in `tools/setup.sh`) | GPL-2.0-or-later |
| dvp-as with `tools/binutils-dvp-overlay-fill.patch` | assembles the VU1 microprograms | ps2dev `binutils-gdb`, branch `dvp-v2.45.1`, commit `3eb45ea3` | GPL-3.0-or-later |

The assembler follows the archive, as the disc's link did: MAIN.MAP takes
libc, libm and libgcc from the compiler's install and every other library
from Sony's SDK install, whose objects carry the later assembler's delay-slot
filling (`tools/compile_c.sh`). The game compiles with `-g -G 8
-fno-common`, Sony's libraries with `-G 0` and no `-g`, newlib and libgcc
also with `-fno-builtin`. The first ld patch backports the R5900 machine type and the
DVP overlay sections from ps2dev's `binutils-2.14-PS2.patch`; the second
places each VU overlay at address 0, the rule of the Cygnus linker shipped
with the GPL ee-gcc 2.9-991111 sources. The licence notices are the tools'
own (`--version` for the assemblers and ld; the source trees for the rest).
The host's `mips-linux-gnu-objcopy` writes `build/<slug>/ico.rom`.

## Targets and branches

A target is a slug: `pal`, `jpn`, `kor`, `ntsc` (USA retail), `aug6` (the
August 6, 2001 prototype) or `jun26` (the June 26, 2001 demo).
A tree builds the targets that have a `config/link_order.<slug>.txt`; the
target is chosen by `VERSION=<slug>`. Each target has its own
`config/*.<slug>.*`, `config/sha1sums.<slug>.txt`, `baserom/<slug>/`,
`build/<slug>/` and `docs/<slug>/`; its source differences are the
`VERSION_<SLUG>` blocks of the shared files.

| branch | targets | |
| --- | --- | --- |
| `main` | `pal` (PAL retail, SCES-50760, `SCES_507.60`), `jpn` (Japanese retail, SCPS-11003, `SCPS_110.03`), `kor` (Korean retail, SCPS-56001, `SCPS_560.01`), `ntsc` (USA retail, SLUS-20218, `SCUS_971.13`), `aug6` (the August 6, 2001 prototype, `SCUS_971.13`) and `jun26` (the June 26, 2001 demo, SCUS-97158, `CUS97113/SCPS_000.00`) | this document; all six gate here |
| `pal` | `pal` | the single-target PAL tree as it was at `738b77d1f`, frozen, but for hotfixes and main's shared layer; current release `pal-v1.0.4` (`0a09a8965`) |
| `jpn` | `jpn` | the single-target Japanese tree as it was at `4506374a6`, frozen, but for hotfixes and main's shared layer; current release `jpn-v1.0.2` (`36d432ae4`) |
| `kor` | `kor` | the single-target Korean tree as it was at `b65c0fcf4` (`kor-v1.0.0`), frozen, but for hotfixes and main's shared layer; current release `kor-v1.0.1` (`97b640aa0`) |
| `ntsc` | `ntsc` | the single-target USA tree as it was at `8c99cc75a` (`ntsc-v1.0.0`), frozen, but for hotfixes and main's shared layer; current release `ntsc-v1.0.1` (`67c876a25`) |
| `aug6` | `aug6` | the single-target prototype tree as it was at `c8e730628` (`aug6-v1.0.0`), frozen, but for hotfixes and main's shared layer; current release `aug6-v1.0.1` (`ba93991ed`) |
| `jun26` | `jun26` | the single-target demo tree as it was at `230819536` (`jun26-v1.0.0`), frozen, but for hotfixes and main's shared layer; current release `jun26-v1.0.1` (`654630aa7`) |

`pal`, `jpn`, `kor`, `ntsc`, `aug6` and `jun26` are history: new work lands
on `main`, and a fix to one of their targets is ported to its branch as a
hotfix release. No branch is merged into `main` (nor `main` into one); each
carries the shared build layer, file for file (`tools/`, `build.sh`,
`.github/` and `docs/index.html`, which `tools/check_shared_layer.sh` checks
against `main`). A further target would join by the recipe in
[`docs/BUILDING.md`](docs/BUILDING.md).

## PC port

[ico-pc](https://github.com/nathanialf/ico-pc) is a fork of this repository
that is being turned into a native PC port. This tree remains the
byte-matched reference. Reconstruction bugs the port finds are fixed here
first, under this repository's rules, and then merged into the port. See
[`docs/PORT.md`](docs/PORT.md).

## Legal and licence

The code in this repository is MIT licensed ([`LICENSE`](LICENSE)). The
licence covers the code written for this project and grants no rights in the
game, its data or anything else owned by Sony Interactive Entertainment or
Team Ico. [`docs/LEGAL.md`](docs/LEGAL.md) says what may and may not be in the
repository and which references were used.
