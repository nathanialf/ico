# Building

The long form of the README's quickstart: what the host needs, what each step
does, how a tree carries several targets, and how the hooks and the dashboard
use the build.

## Host

A 64-bit Linux host. The period compilers are 32-bit i386 binaries, and
`tools/period_env.sh` builds a 32-bit preload library with `gcc -m32`, so the
host needs 32-bit libraries and multilib gcc. On Debian or Ubuntu:

```sh
sudo dpkg --add-architecture i386
sudo apt-get update
sudo apt-get install git curl xz-utils make patch gcc gcc-multilib \
    python3 python3-venv libc6:i386 libstdc++6:i386 zlib1g:i386 \
    binutils-mips-linux-gnu
```

`binutils-mips-linux-gnu` provides `mips-linux-gnu-objcopy`, which writes the
ROM views (`tools/extract_elf.py`, `tools/compile_c.sh`, the ninja `rom`
rule). Other distributions need the equivalent packages. The first run needs
network access to fetch the tools listed below.

You also need your own image of each disc you build. A target accepts exactly
one revision of its disc:

- `pal`: the PAL disc, SCES-50760, as a plain ISO.
- `jpn`: the Japanese disc, SCPS-11003, as the raw `.bin` a dump writes and
  its `.cue`. `tools/extract_elf.py` reads the raw 2352-byte sectors itself
  (the `.cue` gives the mode, MODE2/2352 on this disc), so no extra package is
  needed. The revision is `VER = 1.02` in the disc's `SYSTEM.CNF`.
- `kor`: the Korean disc, SCPS-56001, as the plain 2048-byte-sector ISO a
  DVD dump writes (no `.cue`). The revision is `VER = 1.00`.
- `ntsc`: the USA disc, SLUS-20218, as the raw `.bin` a dump writes and its
  `.cue` (MODE2/2352, read as the Japanese one is). The revision is
  `VER = 1.00`.

| target | file | SHA-1 (`config/sha1sums.<slug>.txt`) |
| --- | --- | --- |
| pal | `baserom/pal/baseelf.elf`, the disc's `SCES_507.60` | `da3644c54c26fe760f3b6a591a5fc2eab396ed2b` |
| pal | `baserom/pal/baseelf.rom`, its `objcopy -O binary --gap-fill=0x00` view | `a401d1e5a20b1659189a8b1026a8eb35811dc9ca` |
| jpn | `baserom/jpn/baseelf.elf`, the disc's `SCPS_110.03` | `580da1dcc4c239a1608a10300e7e220fe5d35525` |
| jpn | `baserom/jpn/baseelf.rom`, its `objcopy -O binary --gap-fill=0x00` view | `58ef44cfeeacd060ffb2acfbf42d8a21bbffd318` |
| kor | `baserom/kor/baseelf.elf`, the disc's `SCPS_560.01` | `f9b00596d133c698df20c8ffe4ca2d7107e236bb` |
| kor | `baserom/kor/baseelf.rom`, its `objcopy -O binary --gap-fill=0x00` view | `f438c8f841a84837231d79cab0c761bfb211259b` |
| ntsc | `baserom/ntsc/baseelf.elf`, the disc's `SCUS_971.13` | `a4d8fc1948fb2da2395f3863a94a3b93de55de14` |
| ntsc | `baserom/ntsc/baseelf.rom`, its `objcopy -O binary --gap-fill=0x00` view | `fbf50c75cd5911273511c4f9af90503ff8423582` |

## One command

```sh
mkdir -p baserom
cp "/path/to/Ico (Europe).iso" baserom/Ico_PAL.iso
cp "/path/to/Ico (Japan).bin" baserom/Ico_JPN.bin
cp "/path/to/Ico (Japan).cue" baserom/Ico_JPN.cue
cp "/path/to/Ico (Korea).iso" baserom/Ico_KOR.iso
cp "/path/to/Ico (USA).bin" baserom/Ico_USA.bin
cp "/path/to/Ico (USA).cue" baserom/Ico_USA.cue
VERSION=pal ./build.sh
VERSION=jpn ./build.sh
VERSION=kor ./build.sh
VERSION=ntsc ./build.sh
tools/build.sh gate-all
```

`./build.sh` builds one target, the one `VERSION` names (without it, the
first configured one, `pal`); `tools/build.sh gate-all` builds and gates every
configured target in turn and is what the hooks run. Each needs only its own
disc.

`./build.sh` runs the steps below that are not already done, in order, and
stops with a non-zero exit at the first failure. On a four-core host with
the toolchain already installed and `baserom/<slug>/` already extracted,
`rm -rf build build.ninja && tools/build.sh setup && .venv/bin/ninja` took
22 s and 39 s in two runs for `pal` and
`tools/build.sh clean && tools/build.sh setup && .venv/bin/ninja` took 51 s
and 47 s in two runs for `jpn`, 31 s and 30 s for `kor` and 40 s and 41 s for
`ntsc`; each ended with
`check_elf: gate PASS`. A
fresh clone of the public repository, with the toolchain downloads of
section 1, took 92 s for `pal` on the same host. A second `./build.sh` on the
built tree rebuilds nothing (`ninja: no work to do.`) and prints the gate
again. The sections below describe each step; each can also be run on its
own. The scripts take the target, and with it every `config/*.<slug>.*`,
`baserom/<slug>/` and `build/<slug>/` path below, from `tools/ico_version.py`
(`VERSION=<slug>`, else the first `config/link_order.<slug>.txt` that exists).
`build.ninja` at the repository root is the manifest of one target at a time;
its first line names the slug, and `tools/build.sh` writes it again when the
target changes. `build/<slug>/` is per target, so building `pal` and then
`jpn` and back keeps each one's objects and ninja state.

## 1. Host setup: `tools/setup.sh`

`./build.sh` runs it when the venv, ninja or any of the four tools under
`tools/cc/` is missing. It is idempotent: a second run finds each tool and
skips it.

1. Creates `.venv/` and installs `tools/requirements.txt`: pyelftools (ELF
   reading), pycdlib (the ISO reader), ninja and clang-format.
2. Fetches **ee-gcc 2.9-991111-01** into `tools/cc/ee-gcc2.9-991111/` from
   the `decompme/compilers` releases. Its bundled `as` (ee-as 2.9-991111)
   assembles the game, libc, libm and libgcc. It also fetches **ee-gcc 2.96**
   into `tools/cc/ee-gcc2.96/` for its bundled SCE assembler
   (2.10-ee-001003-1), which assembles Sony's SDK archives; that compiler is
   never run. The script warns when a compiler is present but does not run
   (missing 32-bit libraries).
3. Checks for `mips-linux-gnu-objcopy`.
4. Builds the linker and the VU assembler from public GPL source (next
   section). On a four-core host the dvp-as source fetch takes about 20 s,
   the dvp-as build about 30 s and ld 2.10 about 17 s (`tools/setup.sh`
   comments).
5. Installs the git hooks (`tools/install_hooks.sh`, below).

`SKIP_TOOLCHAIN=1` skips steps 2 to 4.

### The linker and the DVP assembler

| tool | source | licence | built as |
| --- | --- | --- | --- |
| `tools/cc/binutils-2.10-ee/bin/ld` | GNU binutils 2.10, `https://ftp.gnu.org/gnu/binutils/binutils-2.10.tar.gz` (sha256 pinned in `tools/setup.sh`), with `tools/binutils-2.10-ee.patch` and `tools/binutils-2.10-dvp-ld.patch` | GPL-2.0-or-later | `--target=mipsel-elf`, `make all-ld` |
| `tools/cc/dvp-as/bin/dvp-as` | ps2dev `binutils-gdb`, branch `dvp-v2.45.1`, commit `3eb45ea37f0efd498d1de3cf9562de07197aefa8` (`https://github.com/ps2dev/binutils-gdb`), with `tools/binutils-dvp-overlay-fill.patch` | GPL-3.0-or-later | `--target=dvp`, `make all-gas` |

The first patch backports, from ps2dev's `binutils-2.14-PS2.patch`
(`github.com/ps2dev/ps2toolchain` commit `aa984e7`), the R5900 machine (so
the inputs' `e_flags` mach bits 0x00920000 survive the link) and the DVP
overlay section types (`.DVP.ovlytab` with its `sh_link`, `.DVP.ovlystrtab`,
`.DVP.overlay.*`). The second is the linker side of the overlays: dvp-as
fills `.DVP.ovlytab` itself with relocations, and the Cygnus linker in the GPL
ee-gcc 2.9-991111 combined tree (`ld/emultempl/elf32.em` `place_orphan`,
published as `github.com/polybiusproxy/parappa2_gcc` commit `620426a`) gives
every `.DVP.overlay.*` orphan its own output section at address 0, as the
retail ELF has them. Target `mipsel-elf` writes `elf32-littlemips`, the output
format MAIN.MAP names.

The dvp-as patch sets the one thing in an overlay section that is not code.
dvp-as sizes each `.DVP.overlay.*` section as one byte repeated over the
program's length and never writes that byte (`create_vuoverlay_section` in
`gas/config/tc-dvp.c` drops the pointer `frag_var` returns), so the section
carries whatever the assembler's heap held. The five constant-address
overlays, one per program, are zero on the PAL and Korean discs and 0x6E on
the JPN, USA and Aug-6-2001 discs; the seven continuation overlays are zero on
all five.
Assembling with `MALLOC_PERTURB_=145` (glibc then fills new memory with 0x6E)
reproduces the second pattern in all twelve. The patch writes the byte
explicitly: `--overlay-fill=N` (0 to 255, default 0) for an overlay whose VU
address is a constant, 0 for the others. `tools/gen_ninja.py` passes the
option only when a `.dsm` line of the link order carries an `overlay-fill=N`
token; PAL's and the Korean one carry none, so their command lines also work
with an unpatched dvp-as. The five `.dsm` lines of `config/link_order.jpn.txt`
and of `config/link_order.ntsc.txt` carry `overlay-fill=110` (0x6E), so the
Japanese and USA builds need the patched dvp-as.
With the patch the build no longer depends on the host's heap; without it a
host with `MALLOC_PERTURB_` set fails PAL's whole-file SHA-1.

Neither build needs bison, flex or makeinfo. The 2.10 tarball ships its
generated parsers, but its configure stops when it finds no lex or yacc, so
the script answers that probe with cache variables and make never regenerates
the shipped files. The dvp target's gas has no generated parser, and
`MAKEINFO=true` skips the manuals. The 2.10 tree's `config.sub` and
`config.guess` predate x86_64 hosts; the dvp clone's copies replace them. The
2.10 sources need `gcc -std=gnu89 -fcommon`. Each tool has a stamp keyed on
its commit and patch hash, or on the tarball and patch hashes, and is rebuilt
when that changes.

## 2. The base ELF: `tools/extract_elf.sh`

`./build.sh` runs it when `baserom/<slug>/baseelf.elf` is missing, and says so
plainly when the target's disc image is missing too (`VERSION=jpn
tools/extract_elf.sh` runs it by hand; the image names are in the table
below, `DISCS` in `tools/ico_version.py`). The script reads the disc's
ISO9660 filesystem with pycdlib (`tools/extract_elf.py`), extracts the boot
file named by `SYSTEM.CNF`'s `BOOT2` line, and writes
`baserom/<slug>/baseelf.elf` and its `objcopy -O binary` view
`baserom/<slug>/baseelf.rom`. It checks both SHA-1s against
`config/sha1sums.<slug>.txt` and stops on a mismatch (given a target with no
such file it records them and creates it). Everything under `baserom/` is
gitignored.

| target | image under `baserom/` | boot file | also copied into `baserom/<slug>/` |
| --- | --- | --- | --- |
| pal | `Ico_PAL.iso` | `SCES_507.60` | `MAIN.MAP`, `SRCFILE.TXT`, `TRFILE.TXT`, `SYSTEM.CNF` (reference material, `docs/LEGAL.md`) |
| jpn | `Ico_JPN.bin` and `Ico_JPN.cue` | `SCPS_110.03` | `SYSTEM.CNF` (the Japanese disc ships no map or listing) |
| kor | `Ico_KOR.iso` | `SCPS_560.01` | `SYSTEM.CNF` (the Korean disc ships no map or listing) |
| ntsc | `Ico_USA.bin` and `Ico_USA.cue` | `SCUS_971.13` | `SYSTEM.CNF` (the USA disc ships no map or listing) |

For a raw image the script first cooks it: it reads the mode from the `.cue`,
keeps the 2048 bytes of user data of each 2352-byte sector, and writes the
result once to `baserom/Ico_JPN.iso` or `baserom/Ico_USA.iso` beside the
`.bin`, a cache that later runs read directly.

## 3. `tools/build.sh setup`

`./build.sh` runs it when `build.ninja` is missing, and otherwise runs
`tools/build.sh verify`, which only checks the two SHA-1s; `build.ninja`
rewrites itself when `tools/gen_ninja.py` or one of its inputs changes.

`setup` deletes `build/<slug>/`, verifies the SHA-1s of the base ELF and ROM
(`tools/verify_elf.py`) and writes `build.ninja` with `tools/gen_ninja.py`
from these inputs:

- `config/link_order.<slug>.txt`: every object of the link in the retail
  link's order, one source per line, with the data-only members as `data:`
  lines. The Japanese, Korean and USA discs have no map, so `jpn`'s, `kor`'s
  and `ntsc`'s orders are PAL's carried over by the function census, and each
  line that departs from it says why. `tools/gen_ninja.py` runs `tools/check_targets.py` first (below)
  and fails if a source is missing from every configured target's order.
- `config/link.<slug>.ld`: the hand-written linker script, which places each
  section at the base ELF's addresses and defines the symbols the link needs.
- `config/data_members.<slug>.txt`: the data-only members (member, section,
  address range, the PAL disc's MAIN.MAP names at their offsets).
- `config/data_schema.<slug>.txt`: the data-only members written as C (member,
  section, element type, the game header that defines it, element count,
  MAIN.MAP's names).

`tools/build.sh` also has `verify` (the SHA-1s only), `regen` (rewrite
`build.ninja`; needed after adding a source), `clean` (delete
`build/<slug>/`), `distclean` (delete `build/` and `build.ninja`), `progress`
(below) and, for every configured target, `gate-all` (each target's base files
are required first, and the command fails naming any that is missing; then
`setup` and `ninja` for each in turn) and `progress-all`.

## 4. `ninja`

`.venv/bin/ninja`, or any ninja on the PATH. `build.ninja` does the following
(`tools/gen_ninja.py`):

- compiles every C source of the link order with `tools/compile_c.sh`, from
  the source's own directory (`ico2/<programmer>`, `sce/<archive>`), so
  `__FILE__` and the include paths are spelled as the original build spelled
  them: ee-gcc 2.9-991111 with the flags of the source's origin (the game
  `-g -G 8 -fno-common`; Sony's archives `-G 0`; libc, libm and libgcc
  `-G 0 -fno-builtin`) and the target's `-DVERSION_<SLUG>` and `LN` (below),
  then the assembler of its archive. Both run through
  `tools/period_env.sh`, which preloads `tools/period_obstack.c` to restore
  the obstack chunk size of the machine that built the game; ee-as's R5900
  short-loop padding depends on it;
- assembles each hand-written `.s` (`sce/crt0.s`, `sce/libkernl/klib.s`,
  `sce/libkernl/tlbtrap.s` and the R5900 string functions under
  `sce/libc/machine/r5900/`) with its archive's assembler and `-G`;
- assembles the five VU1 microprograms: the period cpp reads each program's
  text, `ico2/vusrc/<stem>.vsm`, from standard input in `ico2/` with
  `-Ivusrc` (it includes `vusrc/vu1_common.h` and, in normal_c and normal_l,
  `vusrc/scissorcommcut.h`) and writes `build/<slug>/ico2/vusrc/<stem>.i`; dvp-as,
  run from `ico2/` with `-I` naming `build/<slug>/ico2`, assembles `vusrc/<stem>.dsm`, the
  DMA tags around `.include "vusrc/<stem>.i"`. The overlay section names
  dvp-as writes hash the name of the file it is reading and the line: the
  `.dsm` path for the first overlay of each program, the empty name cpp gives
  standard input and the include's path for the others;
- writes the data-only members from the base ELF into `build/<slug>/data/`. Each
  of the 73, all listed in `config/data_schema.<slug>.txt`, is written as C by
  `tools/gen_data_c.py`: an initialized array of its record type per section,
  with every pointer named after the symbol at its address, floats as the
  shortest decimal that reads back to the same bits and names as string
  literals; a member's own string pool (staffroll_dat's) is written as the
  literals its pointers name, and the compiler lays it out; a count the
  schema marks `count-of=` (staffroll_dat's line count) is written as
  `sizeof` over the table, not read from the ELF. The addresses
  come from a first link, `build/<slug>/ico.layout.elf`, in which a zero stand-in of
  the member's size takes its place. The C compiles with the game's flags
  like any `ico2/` source, each section of the object is checked against the
  member's ROM range with its relocations applied, and a label a source
  spells inside the member (`D_<VMA>`) is bound to the member's symbol plus
  its offset by `build/<slug>/data/<member>.alias.ld`;
- writes the stubs, when `config/stubs.<slug>.txt` has rows (on `main` none has
  rows, and this step does nothing). While another target is rebuilt from
  this tree, a function whose C does not yet give that target's bytes is
  listed there with its address range and its translation unit, and the C
  carries `INCLUDE_ASM(stem);` where the function stands in the file (the
  stem is the function's name, or the row's `file=<stem>` when two statics
  in two TUs share a name; a function defined in a `.c.inc` the TU includes
  has its line there, named by the row's `in=<file.c.inc>`, and the TU's
  object depends on that file). `tools/gen_stub_s.py` writes
  `build/<slug>/stubs/<stem>.s` from the user's own base ELF, one `.word` per
  instruction with no relocations, and the assembler reads it at that point
  of the compiler's output, so the stub sits between the functions around it
  and the gate passes at every commit. The constants the function brought
  into the TU's data sections (gcc's string literals, constants and jump
  tables, the assembler's `li.s` pool in .lit4 and `li.d` pool in .rodata,
  a static inside the function) are not in the stub's words; a `lit4`,
  `rdlit` or `sdlit` row gives a range of .lit4, .rodata or .sdata they
  occupy, and the stub file writes them after the function, so the TU's
  later constants keep their places. Without those rows the code moves
  too: every address of a constant in an instruction (a `%hi`/`%lo` pair,
  a `$gp` offset) is a relocated field, so a constant that moves changes
  the words of every function that loads it, and the gate's .text row
  cannot pass before the data sections do. A stubbed inline function is
  split in two: gcc writes its strings and other constants where the
  function is defined, among its neighbours', and its code after the whole
  file, so its `rdlit` and `sdlit` rows for those carry `def`,
  `gen_stub_s.py` writes them to `build/<slug>/stubs/<stem>.lit.s`, and the file
  reads them with `INCLUDE_ASM_LIT(stem);` in the definition's place, while
  the code, the .lit4 floats, the `li.d` doubles and the jump tables (the
  assembler interns .lit4 in load order, and a jump table is referenced
  from the code) follow `INCLUDE_ASM(stem);` at the end of the file.
  `--literals` derives those rows, and `--carve` runs it while the function is still C: the TU compiled on this
  tree names, by its relocations, the constants each function references
  and which function owns each one in the order gcc reads the file (the
  first user of a string, an inline function reading where it is defined;
  a constant the C still emits with the listed functions removed, such as
  the string of an inline function left in C, is the C's), the
  row's words in the target ELF give their addresses (`$gp` offsets and
  `%hi`/`%lo` pairs), and the two lists must pair one to one; what cannot be
  placed by a row is printed as HAND and a pair that differs as DISAGREE,
  for the hand. It writes the
  macro's header too, `build/<slug>/stubs/include_asm.h`, which
  `tools/compile_c.sh` searches last: the tree tracks no copy, so a TU that
  includes it compiles only while stubs exist. `--carve NAME` and
  `--restore NAME` (`--carve-all`, `--restore-all`) replace a definition
  with its `INCLUDE_ASM` line and put it back from `main`, on the file's
  bytes; an inline function's line goes to the end of the file, since gcc
  2.9 emits inline functions after everything else (for one defined in a
  `.c.inc`, the end of the including TU, and the row is marked `inline`),
  and an inline function called after its definition is refused, while one
  whose later uses only take its address, or whose later callers never
  reach the object, keeps its declaration in place. A function carved
  without its literal rows gets its `INCLUDE_ASM_LIT` line from a later
  `--literals` that adds a `def` row, and a row with no definition to put
  back (no C, a nested function) is reported ABSENT with the target side
  alone. The line shifts every
  later line of the TU; a TU that uses `__LINE__` below it keeps its
  numbering with a `#line` directive after the `INCLUDE_ASM` line, written by
  hand (a row's `lines=N` records the span of the body it stands for), and
  the gate decides. Nothing of it is tracked. `--check` names a stub out of
  place; `tools/check_dev_native.py` refuses an `INCLUDE_ASM` or
  `INCLUDE_ASM_LIT` the list does not carry and a listed stem whose file
  lacks it; the progress figures
  count a stub's bytes as from the disc and its function as a stub, not as
  matched. `tools/match_check.py TU FUNC` (or `--all`) compiles one TU into a
  scratch object and compares each function with the target's words at its
  range, relocated fields masked, so a function's state is known before the
  link; `tools/object_check.py` compares each object's `.text` with the
  target at the object's address in the link (or, when the link fails, in
  `build/<slug>/ico.layout.elf`), relocated fields masked, and with `--order` each
  TU's function order with the target's, naming a stub placed before
  functions the target emits earlier;
- links with ld 2.10 and `config/link.<slug>.ld`, once to `build/<slug>/ico.syms.elf`
  (symbols kept, with the map `build/<slug>/ico.<slug>.map`) and once stripped to
  `build/<slug>/ico.elf`, as the base is;
- writes `build/<slug>/ico.rom` with `objcopy -O binary`;
- runs `tools/check_elf.py --gate`: every allocated section of
  `build/<slug>/ico.elf` must hold the base ELF's bytes at the base's addresses,
  `.sbss` and `.bss` must be allocated over the base's ranges, and
  `build/<slug>/ico.rom` and `build/<slug>/ico.elf` must have the recorded SHA-1s
  (`--require-elf-sha`). A second, informational table compares `.reginfo`,
  the `.DVP.*` sections, `e_flags`, `e_entry` and the program and section
  headers. The build fails when a gated check fails.

`./build.sh` prints the gate table once more after ninja. ninja does not
track header or `.c.inc` dependencies (the VU includes under `ico2/vusrc/`
are listed on the cpp step): after editing one, run
`tools/build.sh clean` before `ninja`.

## Targets and version blocks

One tree builds every configured target. A target is configured when
`config/link_order.<slug>.txt` exists; `VERSION=<slug>` picks which one a
command works on.

**One file per name.** `ico2/` and `sce/` are the source of every target. The
base text is the PAL revision, the one the PAL disc's maps and listing
describe; where another target's build differs, the same file holds that
target's lines inline, so they read side by side. The Japanese and Korean
builds share most of their differences from PAL (the Korean text is the
Japanese one with 24 files changed), so one block serves both:

```c
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    thisIsYourStartStage = n < 104 ? n : 103;
#else
    thisIsYourStartStage = n < 106 ? n : 105;
#endif
```

`#if !defined(VERSION_JPN) && !defined(VERSION_KOR)` marks lines only PAL
has. `#ifdef VERSION_JPN` is left where the Korean build has PAL's lines
(`cdvd.c`, `pad.c`) or where only the Japanese build has them (`e3.c`), and
`#ifdef VERSION_KOR` where the Korean build has lines of its own. Where all
three differ, the Korean block sits inside the Japanese one:

```c
        switch (lt_current_property_item()) {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
#ifdef VERSION_KOR
        case 8:
#else
        case 14:
#endif
#else
        case 44:
#endif
```

The USA build's text is PAL's with 189 files changed, so its lines sit in
`#ifdef VERSION_NTSC` blocks against PAL's (`#ifndef VERSION_NTSC` around
lines only it lacks), each covering whole statements or a whole definition.
Where the place already holds a Japanese block, the USA block nests inside
the PAL arm; where the USA build has the Japanese and Korean lines, the
condition names it too:

```c
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(51);
#else
#ifdef VERSION_NTSC
    lt_switch_layout(50);
#else
    lt_switch_layout(54);
#endif
#endif
```

`#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_NTSC)`
holds lines the three later builds share, and `#if !defined(VERSION_JPN) &&
!defined(VERSION_KOR) && !defined(VERSION_NTSC)` lines only PAL has.

The three-way sites nest rather than take `#elif` arms because clang-format
formats each arm count of a nesting level in a pass of its own: with a third
arm at the top level of a file, the third pass takes no arm of a two-arm
block, and a two-arm block that splits a brace (`if (...) {` in each arm)
leaves that pass unbalanced, which shows as blank lines and misplaced `case`
labels in `tools/format.sh`'s output. `tools/check_targets.py` accepts
`#elif defined(...)` arms, and `version_lines` and `tools/format_layout.py`
read them; they suit a file whose other blocks keep their braces whole.

`tools/compile_c.sh` defines `VERSION_<SLUG>` for the target it compiles
(`-DVERSION_PAL`, `-DVERSION_JPN`, `-DVERSION_KOR`, `-DVERSION_NTSC`). A
block covers whole
statements, and where most of a function or declaration differs the block
holds each target's whole definition rather than interleaving them line by
line. A comment that differs only in a value names every target's
(`0x194 bytes (JPN and KOR 0x190)`). The `.dsm` files are not preprocessed
and have no blocks; their header comments name every target's addresses.
Every object is built from its row's path
(`build/jpn/ico2/script/src/st02a.o`), and the link order's rows name the
same files for every target; `sce/libscf/libscf.c` is compiled only for PAL,
whose link order alone lists it.

**Line numbers.** The original build passed `__LINE__` to its debug
allocators and asserts, so those lines are part of each build's data, and
they differ between builds. The repository's lines are not the original
files' lines, so such a call spells the number, and `LN(pal, jpn, kor, ntsc)`
picks the target's: `iosMallocDebug(ios_partition_seki, asize,
"src/FileManager.c", LN(349, 331, 331, 312))`. `tools/compile_c.sh` defines
`LN` with `VERSION_<SLUG>`; `ico2/ito/include/mv_defs.h`'s `alloc_zeroed` is
the header case (lines 43 and 44 on PAL, 42 and 43 on JPN, KOR and NTSC).
The Korean build has the Japanese numbers except in `cdvd.c` and `pad.c`,
which have PAL's, and `jimaku.c`'s assertion, 658. The USA build's number
is its own at every site it compiles, and PAL's stands as its argument at a
site in an arm it does not compile. `flag.c`'s `InitFlagGeo` passed
`__LINE__` in the original, so it spells each line too (PAL 87, 95, 102,
132, 145 and 172; the USA build 31, 39, 46, 65 and 77), the macro
`FLAG_ALLOC_NODES` taking the caller's line as its third argument. This is
the convention zeldaret/oot's `include/line_numbers.h` uses for the same
problem.

**The rules.** `tools/check_targets.py` (run by `tools/gen_ninja.py`, so by
every `setup`, and by the pre-commit hook) reads the files git tracks or
would track (untracked, not ignored), so a file not yet staged is checked
too:

1. Every source (`.c`, `.s`, `.S`, `.dsm`) is a row of at least one
   configured target's link order.
2. Every source row of every configured link order is a file.
3. There is no `targets/` directory: a target's differences are inline.
4. A `VERSION_<SLUG>` name appears only in C sources and headers, and only
   for a configured slug.
5. A `VERSION_<SLUG>` name appears only in a version condition of one of the
   forms `#ifdef VERSION_A`, `#ifndef VERSION_A`, `#if defined(VERSION_A) ||
   defined(VERSION_B)`, `#if !defined(VERSION_A) && !defined(VERSION_B)` and
   `#elif defined(VERSION_A)` (also joined by `||`), and a block's `#elif`
   arms follow its `#if` and name no target an earlier arm took.

`tools/gen_data_c.py` reads a record header's version blocks for the target
it writes (`version_lines`), and `tools/format_layout.py` keeps a block's
arms tight (no blank line after the opening line, an `#elif` or `#else`,
none before an `#elif`, `#else` or `#endif`). Each of the three has a
`--self-test` on fixed cases. ninja does not track headers or `.c.inc` files;
adding a source needs `tools/build.sh regen`, and editing a header needs
`tools/build.sh clean`.

**Joining a later target.** `aug6` (branch `aug6`) joins by these steps, as
`kor` and `ntsc` did.

1. Copy the branch's `config/*.<slug>.*` files and its
   `config/sha1sums.<slug>.txt`, with `link.<slug>.ld`'s `INCLUDE` paths under
   `build/<slug>/`, and its `docs/<slug>/` progress files.
2. For each file that differs from `main`'s (`git diff --name-only main
   <branch> -- ico2 sce`, leaving out the ones that differ only in
   encoding), write the target's lines into the shared file as version blocks.
   Find the target's base first: a branch seeded from another target's tree
   (`kor` from `jpn`) adds its name to that target's conditions wherever it
   has that target's lines, and keeps its own lines in `#ifdef
   VERSION_<SLUG>` blocks nested inside them; a branch seeded from PAL's
   tree (`ntsc`) puts its lines in `#ifdef VERSION_<SLUG>` blocks against
   PAL's, nested in the PAL arm where a Japanese block already stands, and
   names itself in a Japanese condition where it has those lines. A hunk
   that differs only in comments keeps `main`'s text. Check each file by resolving
   its blocks for the target and comparing the result with the branch's file
   outside comments.
3. Add the target to `VERSION_DEFS` in `tools/compile_c.sh`, give `LN` its
   argument there (`LN(pal, jpn, kor, ntsc, <slug>)`), and add the target's
   number to every `LN(...)` call: its own where it compiles the line, the
   base target's where it does not. A site that still passes `__LINE__`
   (`flag.c` did) spells every target's number first.
4. Move the branch's `tools/dev_native_allow.txt` rows for sites in the
   files it changed onto the shared files' lines.
5. Run `tools/build.sh gate-all`, then compare each object of every target
   with its build before the join (the joined target's with its branch's)
   outside `.mdebug`. A target's stubs are per slug
   (`config/stubs.<slug>.txt`, `build/<slug>/stubs/`), so a target can gate in
   the combined tree with stubs remaining; joining at 0 stubs is the project's
   practice, not a mechanical limit.
6. Commit on `main` (the hook runs every target's gate), then add the slug
   to `FROZEN_SLUGS` in `.github/scripts/build_pages_site.sh` with its
   `FROZEN_BRANCH_<slug>` and `FROZEN_DIR_<slug>`. The branch stays in
   `BRANCHES` and in `.github/workflows/pages.yml`, and its tab in
   `docs/index.html` keeps reading the branch: the site never reads a
   target's numbers from `main`.

## EUC-JP sources

Some game sources carry Japanese text in EUC-JP, and their string literals
are the ROM's bytes. `.gitattributes` lists each of them with
`working-tree-encoding=EUC-JP`: git stores the file as UTF-8 and checks it
out as EUC-JP, which is what the compiler reads. An editor or a pipe that
rewrites one of these files as UTF-8 changes its bytes; change them with an
ASCII patch and `git apply`. Check that the count of high bytes in the file
is unchanged after any edit.

## Progress and the dashboard

`tools/build.sh progress` runs `tools/check_elf.py --progress`, which
rewrites the README's badge block, the table in `docs/<slug>/PROGRESS.md` and
`docs/<slug>/progress.json` from the built ELF, its link map and the function
symbols of `build/<slug>/ico.syms.elf`; `tools/build.sh progress-all` does
every configured target, and the README's badge block gets one row per
`docs/<slug>/progress.json`. A byte counts for its section when the map
row that places it belongs to an object built from `ico2/` or `sce/` and the
byte equals the base's; bytes from `build/<slug>/data/` are counted separately as
extracted tables. The count is by object, so `staffroll_dat`'s count word
(4 bytes of `.sdata`) counts as from the disc although the generator
computes it from the table's element count.

The dashboard is `docs/index.html`, which reads each target's `progress.json`.
On a push that changes `docs/index.html`, a `docs/<slug>/progress.json` or
`docs/<slug>/PROGRESS.md`, the workflow or its script, `.github/workflows/pages.yml` runs
`.github/scripts/build_pages_site.sh`, which assembles one site and deploys
it to GitHub Pages. A push to any of `main`, `pal`, `jpn`, `kor`, `ntsc`,
`aug6` and `jun26` deploys, and every deploy assembles the whole site. The
page is `main`'s `docs/index.html` (read from `origin/main` on the other
branches). Every target's `progress.json` and `PROGRESS.md` come from that
target's own branch: `pal`, `jpn`, `kor` and `ntsc` (frozen) supply
`docs/pal/`, `docs/jpn/`, `docs/kor/` and `docs/ntsc/`, `aug6` supplies
`docs/aug6/` and `jun26` supplies `docs/jun26/`. `main`'s `docs/<slug>/` stay
as the combined build's progress record and are never published. Each tab's
repo and `PROGRESS.md` links point at its branch.

## Hooks

`tools/install_hooks.sh` (run by `tools/setup.sh`) installs two git hooks.

- **pre-commit**: `tools/check_no_rom.sh` (refuses disc images, executables,
  extracted assets and large binaries), `tools/check_dev_native.py` (refuses
  constructs that only steer the compiler, with the ROM-proven exceptions in
  `tools/dev_native_allow.txt`), `tools/check_targets.py`, and
  `tools/format.sh --check` on the staged C. When a
  staged path is under `ico2/`, `sce/`, `config/`, `tools/` or
  `baserom/`, it then runs `tools/build.sh gate-all` (every configured target
  from scratch; a missing `baserom/<slug>/` of any of them fails the commit)
  and `tools/build.sh progress-all`, and adds the refreshed README block and
  `docs/*/` progress files to the commit.
- **pre-push**: for each pushed branch other than `main`,
  `tools/check_shared_layer.sh` fetches `origin/main` and refuses the push
  when the branch's `tools/`, `build.sh`, `.github/` or `docs/index.html`
  differs from main's, naming the files; those are the same on every
  branch, and a change to them lands on `main` first. The comparison leaves
  out `tools/dev_native_allow.txt` (a pathspec exclude): it holds sites in the
  branch's own sources, so each branch keeps its own. Then, for each pushed
  ref whose commits touch the build, it requires the working tree to be at
  that ref's tip with no uncommitted changes under `ico2/`, `sce/`,
  `config/` or `tools/`, and runs `tools/build.sh gate-all` on it.

`tools/format.sh` formats the tracked C with the tracked `.clang-format` and
then `tools/format_layout.py`'s top-level blank-line layout. The game
compiles with `-g`, where a moved line break can change the code, so run the
gate after formatting.

## Running the rebuilt ELF (optional)

Any PS2 emulator can run `build/<slug>/ico.elf` as a sanity check, with
`baserom/Ico_PAL.iso` (or, for `jpn`, the cooked `baserom/Ico_JPN.iso`, or the
`.bin` and `.cue`; for `kor`, `baserom/Ico_KOR.iso`) as the disc for the game's data files.
