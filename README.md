# ico

A source tree for the PlayStation 2 game **ICO** (Sony Computer Entertainment,
2001) that rebuilds the boot ELF of the PAL retail disc, SCES-50760
(`SCES_507.60`), byte for byte, with the toolchain the game was built with.

<!-- progress:begin -->
![.text progress](https://img.shields.io/badge/text-100.00%20%25-brightgreen.svg)
![.vutext progress](https://img.shields.io/badge/vutext-100.00%20%25-brightgreen.svg)
![.data progress](https://img.shields.io/badge/data-100.00%20%25%20%2872.54%20%25%20C%20%2B%2027.46%20%25%20table%29-brightgreen.svg)
![.rodata progress](https://img.shields.io/badge/rodata-100.00%20%25%20%289.49%20%25%20C%20%2B%2090.51%20%25%20table%29-brightgreen.svg)
![.lit4 progress](https://img.shields.io/badge/lit4-100.00%20%25-brightgreen.svg)
![.sdata progress](https://img.shields.io/badge/sdata-100.00%20%25%20%2899.91%20%25%20C%20%2B%200.09%20%25%20table%29-brightgreen.svg)
![.sbss progress](https://img.shields.io/badge/sbss-100.00%20%25%20%2899.68%20%25%20C%20%2B%200.32%20%25%20table%29-brightgreen.svg)
![.bss progress](https://img.shields.io/badge/bss-100.00%20%25-brightgreen.svg)
<!-- progress:end -->

**[Progress dashboard](https://nathanialf.github.io/ico/#pal)**: every
section, directory, translation unit and function of the build compared with
the base ELF.

> [!IMPORTANT]
> This project is not affiliated with Sony Interactive Entertainment or Team
> Ico. *ICO* is a trademark of its owners. No disc data is in this repository;
> you supply your own disc image. Read [`docs/LEGAL.md`](docs/LEGAL.md).

## Quickstart

```sh
git clone https://github.com/nathanialf/ico.git
cd ico
mkdir -p baserom
cp "/path/to/Ico (Europe).iso" baserom/Ico_PAL.iso
./build.sh
```

`./build.sh` runs `tools/setup.sh` when the toolchain under `tools/cc/` is
missing, extracts `baserom/pal/baseelf.elf` from the disc image when it is
missing (`tools/extract_elf.sh`), then runs `tools/build.sh setup`, `ninja`,
and `tools/check_elf.py --gate`, and exits non-zero if any step fails. The
host needs a 64-bit Linux with 32-bit libraries, a host gcc, a MIPS `objcopy`
and network access for the first run; [`docs/BUILDING.md`](docs/BUILDING.md)
lists the packages and describes each step.

The build checks two SHA-1s from `config/sha1sums.txt`: the extracted ELF
before it starts and the rebuilt ROM image at the end.

| file | SHA-1 |
| --- | --- |
| `baserom/pal/baseelf.elf` (the disc's `SCES_507.60`) | `da3644c54c26fe760f3b6a591a5fc2eab396ed2b` |
| `baserom/pal/baseelf.rom` and `build/ico.rom` (`objcopy -O binary`) | `a401d1e5a20b1659189a8b1026a8eb35811dc9ca` |

The gate (`tools/check_elf.py --gate`) also compares every allocated section
of `build/ico.elf` with the base ELF by address and checks that `.sbss` and
`.bss` cover the base's ranges.

## Progress badges

There is one badge per section of the base ELF, in link order.
`tools/check_elf.py --progress` (`tools/build.sh progress`) rewrites them,
[`docs/PROGRESS.md`](docs/PROGRESS.md) and the dashboard's
`docs/progress.json` from the built ELF and its link map.

A badge reads `100 %` when the whole section equals the base. Where part of a
section comes from the extracted data tables (next section), the badge splits
the figure: `C` is the share placed by objects compiled or assembled from
sources under `ico2/` and `sce/`, and `table` is the share written out of the
user's own ELF at build time. `.sbss` and `.bss` hold no file bytes, so their
figure is the share of the range that an object defines and the link places
at the base's addresses.

## Data tables

The game links 70 members of its own archive, `ico2000.a`, that have data
sections and no code: stage layouts, model paths, motion and sound
definitions, way points (MAIN.MAP; the list is `config/data_members.pal.txt`,
which also carries three data runs MAIN.MAP does not list and one four-byte
`.sbss` word). They are the game's content, not its program, so the tree does
not transcribe them as C. At build time `tools/extract_data.py` writes each
one's bytes from the user's `baserom/pal/baseelf.elf` into `build/data/`, as
assembly the period assembler turns back into the same bytes; nothing it
writes is ever committed. [`docs/LEGAL.md`](docs/LEGAL.md) has the reasoning.

## Layout

```
ico2/<programmer>/<kind>/   the game, at the paths the disc's listing records:
                            common, fumi, ito, omori, script, seki, sugipon,
                            each with src/ and include/, and fumi's ios/,
                            isys/ and sound/, ito's mpeg/
ico2/vusrc/                 the five VU1 microprograms (cluster, mesh,
                            normal_c, normal_l, particle) as dvp-as sources
sce/<archive>/              Sony's runtime libraries (libkernl, libgraph,
                            libdma, libpad, libmc, libcdvd, libmpeg, libipu,
                            libpkt, libscf, libsndn2, libvu0) and the
                            compiler's newlib libc and libm and libgcc, plus
                            crt0.s
config/                     link_order.pal.txt (every object in link order),
                            link.pal.ld (the linker script),
                            data_members.pal.txt (the extracted tables),
                            sha1sums.txt; ico.pal.yaml and symbol_addrs.pal*.txt
                            are kept as a record and nothing reads them
tools/                      setup, extraction, build and gate scripts, listed
                            in tools/README.md
docs/                       documentation, indexed by docs/README.md
baserom/  build/            local only and gitignored: the user's disc image
                            and extracted ELF, and the build output
```

Each game file compiles from inside its programmer's directory with relative
`-I../<other>/include` entries, because ee-gcc writes the path it is given
into `__FILE__` strings the ROM contains (`tools/compile_c.sh`).
[`docs/HEADERS.md`](docs/HEADERS.md) explains which headers the disc attests
and how the others were placed, and
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
| dvp-as | assembles the VU1 microprograms | ps2dev `binutils-gdb`, branch `dvp-v2.45.1`, commit `3eb45ea3` | GPL-3.0-or-later |

The assembler follows the archive, as the disc's link did: MAIN.MAP takes
libc, libm and libgcc from the compiler's install and every other library
from Sony's SDK install, whose objects carry the later assembler's delay-slot
filling (`tools/compile_c.sh`). The game compiles with `-g -G 8`, Sony's
libraries with `-G 0` and no `-g`, newlib and libgcc also with
`-fno-builtin`. The first ld patch backports the R5900 machine type and the
DVP overlay sections from ps2dev's `binutils-2.14-PS2.patch`; the second
places each VU overlay at address 0, the rule of the Cygnus linker shipped
with the GPL ee-gcc 2.9-991111 sources. The licence notices are the tools'
own (`--version` for the assemblers and ld; the source trees for the rest).
A MIPS `objcopy` from the host writes `build/ico.rom`.

## Branches

| branch | target | |
| --- | --- | --- |
| `main` | PAL retail, SCES-50760, `SCES_507.60` | this document |
| `ntsc` | USA retail, SLUS-20218, `SCUS_971.13` | the same game on the USA disc, with its own README |
| `aug6` | the August 6, 2001 prototype | an earlier build of the game, with its own README |

The branches are separate trees and are never merged into each other.

## Legal and licence

The code in this repository is MIT licensed ([`LICENSE`](LICENSE)). The
licence covers the code written for this project and grants no rights in the
game, its data or anything else owned by Sony Interactive Entertainment or
Team Ico. [`docs/LEGAL.md`](docs/LEGAL.md) says what may and may not be in the
repository and which references were used.
