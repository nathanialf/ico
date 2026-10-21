# Building

The long form of the README's quickstart: what the host needs, what each step
does, and how the hooks and the dashboard use the build.

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

You also need your own image of the Official U.S. PlayStation Magazine demo
disc 49, SCUS-97158, a DVD, as a plain 2048-byte-sector ISO. pycdlib reads
its ISO9660 filesystem directly (`tools/extract_elf.py`), so no extra package
is needed. The build accepts exactly one ELF, the ICO demo's
`CUS97113/SCPS_000.00`:

| file | SHA-1 (`config/sha1sums.jun26.txt`) |
| --- | --- |
| `baserom/jun26/baseelf.elf`, the disc's `CUS97113/SCPS_000.00` | `95c3d438185c3b75303b68719cfd48c84f2f8bfa` |
| `baserom/jun26/baseelf.rom`, its `objcopy -O binary --gap-fill=0x00` view | `e5d6dd3c156ed5489a4d2e7bbf4707cd58d0dccc` |

## One command

```sh
mkdir -p baserom
cp "/path/to/demo disc 49.iso" baserom/Ico_JUN26.iso
./build.sh
```

A hard link or a symbolic link in place of the copy works as well; the build
only reads the image.

`./build.sh` runs the steps below that are not already done, in order, and
stops with a non-zero exit at the first failure. A second `./build.sh` on
the built tree rebuilds nothing (`ninja: no work to do.`) and prints the
gate again. The sections
below describe each step; each can also be run on its own. The scripts are
the same on every target branch and take the target, and with it every
`config/*.jun26.*`, `baserom/jun26/` and `build/jun26/` path below, from
`tools/ico_version.py` (`VERSION=<slug>`, else the first
`config/link_order.<slug>.txt` that exists: `config/link_order.jun26.txt` on
this branch, its only target).

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
overlays, one per program, are zero on the PAL disc and 0x6E on the JPN, USA,
Aug-6-2001 and Jun-26-2001 discs; the seven continuation overlays are zero on
all five.
Assembling with `MALLOC_PERTURB_=145` (glibc then fills new memory with 0x6E)
reproduces the second pattern in all twelve. The patch writes the byte
explicitly: `--overlay-fill=N` (0 to 255, default 0) for an overlay whose VU
address is a constant, 0 for the others. `tools/gen_ninja.py` passes the
option only when a `.dsm` line of the link order carries an `overlay-fill=N`
token. The five `.dsm` lines of `config/link_order.jun26.txt` carry
`overlay-fill=110`, so this branch needs the patched dvp-as: an unpatched
one leaves the byte to the host's heap and fails the whole-file SHA-1 unless
the heap happens to hold 0x6E (PAL's link order carries no token).

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

`./build.sh` runs it when `baserom/jun26/baseelf.elf` is missing, and says so
plainly when `baserom/Ico_JUN26.iso` is missing too. The image is already a
2048-byte-sector ISO, so there is nothing to cook. The script reads its
ISO9660 filesystem with pycdlib (`tools/extract_elf.py`). The disc's
`SYSTEM.CNF` boots the magazine's menu (`SCUS_971.58`), not ICO, so the boot
file is the path the target's `DISCS` row names as `boot`
(`tools/ico_version.py`: `CUS97113/SCPS_000.00`); the script extracts it and
writes `baserom/jun26/baseelf.elf` and its `objcopy -O binary` view
`baserom/jun26/baseelf.rom`. It checks both SHA-1s against
`config/sha1sums.jun26.txt` and stops on a mismatch. It also copies the
disc's `SYSTEM.CNF` into `baserom/jun26/`; the demo's directory ships no map
or listing (`docs/LEGAL.md`). Everything under `baserom/` is gitignored.

## 3. `tools/build.sh setup`

`./build.sh` runs it when `build.ninja` is missing, and otherwise runs
`tools/build.sh verify`, which only checks the two SHA-1s; `build.ninja`
rewrites itself when `tools/gen_ninja.py` or one of its inputs changes.

`setup` deletes `build/jun26/`, verifies the SHA-1s of the base ELF and ROM
(`tools/verify_elf.py`), and writes `build.ninja` with `tools/gen_ninja.py`
from these inputs:

- `config/link_order.jun26.txt`: every object of the link in the demo
  link's order, one source per line, with the data-only members as `data:`
  lines. The disc has no map, so the order is PAL's carried over by the
  function census, with the data-only members at the August 6, 2001
  prototype's places, and each line that departs from it says why.
  `tools/gen_ninja.py` runs `tools/check_targets.py` first and fails if a
  tracked source under `ico2/` or `sce/` is missing from it.
- `config/link.jun26.ld`: the hand-written linker script, which places each
  section at the base ELF's addresses and defines the symbols the link needs.
- `config/data_members.jun26.txt`: the data-only members (member, section,
  address range in this ELF, the PAL disc's MAIN.MAP names at their
  offsets).
- `config/data_schema.jun26.txt`: the data-only members written as C (member,
  section, element type, the game header that defines it, element count,
  MAIN.MAP's names).
- `config/stubs.jun26.txt`: the campaign stubs, while it has rows (section 4).

`tools/build.sh` also has `verify` (the SHA-1s only), `regen` (rewrite
`build.ninja`; needed after adding a source), `clean` (delete `build/jun26/`),
`distclean` (delete `build/` and `build.ninja`), `progress` (below) and
`gate-all` and `progress-all`, which do the same for every configured
target, here the one.

## 4. `ninja`

`.venv/bin/ninja`, or any ninja on the PATH. `build.ninja` does the following
(`tools/gen_ninja.py`):

- compiles every C source of the link order with `tools/compile_c.sh`, from
  the source's own directory (`ico2/<programmer>`, `sce/<archive>`), so
  `__FILE__` and the include paths are spelled as the original build spelled
  them: ee-gcc 2.9-991111 with the flags of the source's origin (the game
  `-g -G 8 -fno-common`; Sony's archives `-G 0`; libc, libm and libgcc
  `-G 0 -fno-builtin`) and `-DVERSION_JUN26`, then the assembler of its
  archive. Both run through
  `tools/period_env.sh`, which preloads `tools/period_obstack.c` to restore
  the obstack chunk size of the machine that built the game; ee-as's R5900
  short-loop padding depends on it;
- assembles each hand-written `.s` (`sce/crt0.s`, `sce/libkernl/klib.s`,
  `sce/libkernl/tlbtrap.s` and the R5900 string functions under
  `sce/libc/machine/r5900/`) with its archive's assembler and `-G`;
- assembles the five VU1 microprograms: the period cpp reads each program's
  text, `ico2/vusrc/<stem>.vsm`, from standard input in `ico2/` with
  `-Ivusrc` (it includes `vusrc/vu1_common.h` and, in normal_c and normal_l,
  `vusrc/scissorcommcut.h`) and writes `build/jun26/ico2/vusrc/<stem>.i`;
  dvp-as, run from `ico2/` with `-I` naming `build/jun26/ico2`, assembles
  `vusrc/<stem>.dsm`, the DMA tags around `.include "vusrc/<stem>.i"`. The overlay section names
  dvp-as writes hash the name of the file it is reading and the line: the
  `.dsm` path for the first overlay of each program, the empty name cpp gives
  standard input and the include's path for the others;
- writes the data-only members from the base ELF into `build/jun26/data/`. Each
  of the 71, all listed in `config/data_schema.jun26.txt`, is written as C by
  `tools/gen_data_c.py`: an initialized array of its record type per section,
  with every pointer named after the symbol at its address, floats as the
  shortest decimal that reads back to the same bits and names as string
  literals; a member's own string pool (staffroll_dat's) is written as the
  literals its pointers name, and the compiler lays it out; a count the
  schema marks `count-of=` (staffroll_dat's line count) is written as
  `sizeof` over the table, not read from the ELF. The addresses
  come from a first link, `build/jun26/ico.layout.elf`, in which a zero stand-in of
  the member's size takes its place. The C compiles with the game's flags
  like any `ico2/` source, each section of the object is checked against the
  member's ROM range with its relocations applied, and a label a source
  spells inside the member (`D_<VMA>`) is bound to the member's symbol plus
  its offset by `build/jun26/data/<member>.alias.ld`;
- writes the stubs, when `config/stubs.jun26.txt` has rows (with none, this
  step does nothing). While this target is rebuilt from the tree seeded
  from `main`, a function whose C does not yet give the demo's bytes is listed
  there with its address range and its translation unit, and the C
  carries `INCLUDE_ASM(stem);` where the function stands in the file (the
  stem is the function's name, or the row's `file=<stem>` when two statics
  in two TUs share a name; a function defined in a `.c.inc` the TU includes
  has its line there, named by the row's `in=<file.c.inc>`, and the TU's
  object depends on that file). `tools/gen_stub_s.py` writes
  `build/jun26/stubs/<stem>.s` from the user's own base ELF, one `.word` per
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
  `gen_stub_s.py` writes them to `build/jun26/stubs/<stem>.lit.s`, and the file
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
  macro's header too, `build/jun26/stubs/include_asm.h`, which
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
  `build/jun26/ico.layout.elf`), relocated fields masked, and with `--order` each
  TU's function order with the target's, naming a stub placed before
  functions the target emits earlier;
- links with ld 2.10 and `config/link.jun26.ld`, once to `build/jun26/ico.syms.elf`
  (symbols kept, with the map `build/jun26/ico.jun26.map`) and once stripped to
  `build/jun26/ico.elf`, as the base is;
- writes `build/jun26/ico.rom` with `objcopy -O binary`;
- runs `tools/check_elf.py --gate`: every allocated section of
  `build/jun26/ico.elf` must hold the base ELF's bytes at the base's addresses,
  `.sbss` and `.bss` must be allocated over the base's ranges, and
  `build/jun26/ico.rom` and `build/jun26/ico.elf` must have the recorded SHA-1s
  (`--require-elf-sha`). A second, informational table compares `.reginfo`,
  the `.DVP.*` sections, `e_flags`, `e_entry` and the program and section
  headers. The build fails when a gated check fails.

`./build.sh` prints the gate table once more after ninja. ninja does not
track header or `.c.inc` dependencies (the VU includes under `ico2/vusrc/`
are listed on the cpp step): after editing one, run
`tools/build.sh clean` before `ninja`.

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
rewrites the README's badge block, the table in `docs/jun26/PROGRESS.md` and
`docs/jun26/progress.json` from the built ELF, its link map and the function
symbols of `build/jun26/ico.syms.elf`. A byte counts for its section when the map
row that places it belongs to an object built from `ico2/` or `sce/` and the
byte equals the base's; bytes from `build/jun26/data/` and any campaign stub's
bytes are counted separately, as from the disc. The count is by object, so
`staffroll_dat`'s count word
(4 bytes of `.sdata`) counts as from the disc although the generator
computes it from the table's element count.

The dashboard is `docs/index.html`, which reads each target's
`progress.json`. On a push that changes `docs/index.html`,
`docs/jun26/progress.json`, `docs/jun26/PROGRESS.md`,
the workflow or its script, `.github/workflows/pages.yml` runs
`.github/scripts/build_pages_site.sh`, which assembles one site and deploys
it to GitHub Pages. The page is `main`'s `docs/index.html` (read from
`origin/main` on the other branches); this branch supplies only
`docs/jun26/progress.json` and `docs/jun26/PROGRESS.md`, the dashboard's
`jun26` tab ("Demo").

## Hooks

`tools/install_hooks.sh` (run by `tools/setup.sh`) installs two git hooks.

- **pre-commit**: `tools/check_no_rom.sh` (refuses disc images, executables,
  extracted assets and large binaries), `tools/check_dev_native.py` (refuses
  constructs that only steer the compiler, with the ROM-proven exceptions in
  `tools/dev_native_allow.txt`), `tools/check_targets.py`, and
  `tools/format.sh --check` on the staged C. When a staged path is under
  `ico2/`, `sce/`, `config/`, `tools/` or `baserom/`, it then runs
  `tools/build.sh gate-all` (every configured target from scratch, here
  `jun26`; a missing `baserom/jun26/` fails the commit) and
  `tools/build.sh progress-all`, and adds the refreshed README block and
  `docs/jun26/` progress files to the commit. `check_dev_native.py` checks an
  asm block against the PAL disc's listing, `baserom/pal/SRCFILE.TXT`; on a
  checkout without it, the blocks it would check are reported as
  unverified instead, so the unverified count is higher there.
- **pre-push**: for each pushed branch other than `main`,
  `tools/check_shared_layer.sh` fetches `origin/main` and refuses the push
  when the branch's `tools/`, `build.sh`, `.github/` or `docs/index.html`
  differs from main's, naming the files; those are the same on every target
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

Any PS2 emulator can run `build/jun26/ico.elf` as a sanity check, with
`baserom/Ico_JUN26.iso` as the disc for the game's data files. Started this
way the demo is not started by the disc's menu, so the hand-back to the menu
(`demoDisc.c`) has no arguments to return.
