# ico

<!-- progress:begin -->
![.text progress](https://img.shields.io/badge/text-90.78%20%25-green.svg)
![.vutext progress](https://img.shields.io/badge/vutext-100.00%20%25-brightgreen.svg)
![.data progress](https://img.shields.io/badge/data-2.56%20%25-orange.svg)
![.rodata progress](https://img.shields.io/badge/rodata-5.20%20%25-orange.svg)
![.lit4 progress](https://img.shields.io/badge/lit4-100.00%20%25-brightgreen.svg)
![.sdata progress](https://img.shields.io/badge/sdata-2.61%20%25-orange.svg)
![.sbss progress](https://img.shields.io/badge/sbss-82.56%20%25-green.svg)
![.bss progress](https://img.shields.io/badge/bss-73.99%20%25-yellowgreen.svg)
<!-- progress:end -->

**[Live progress dashboard](https://nathanialf.github.io/ico/#pal)**: decomp status per directory, TU and function for this branch's target (PAL retail, SCES-50760), updated on every push. The dashboard covers all three targets; switch with the picker at the top.

A decompilation of the PlayStation 2 game **ICO** (2001, Sony Computer
Entertainment / Team Ico).

This branch targets the **shipped PAL retail build** (disc SCES-50760, boot
ELF `SCES_507.60`). Each target has its own branch:

| branch | target | slug | splat config |
| --- | --- | --- | --- |
| `main` | PAL retail, SCES-50760 (`SCES_507.60`) | `pal` | `config/ico.pal.yaml` |
| `ntsc` | USA retail, SLUS-20218 (`SCUS_971.13`) | `us` | `config/ico.us.yaml` |
| `aug6` | Aug-6-2001 US Preview prototype | `aug6` | `config/ico.aug6.yaml` |

The three branches share the toolchain, the conventions and most of the
recovered source. The tools detect a working tree's target from its
`config/ico.<slug>.yaml` (`tools/ico_version.py`). The PAL tree was seeded by
porting every matched body from `ntsc` and `aug6` whose bytes survive here
Both passes are done; the port drivers and their ledgers are retired, and each
carve row in `config/ico.pal.yaml` carries its own reasoning.

The goal is original source code that, compiled with the original build chain
(ee-gcc 2.9-991111-01 + its period ee-as 2.9-991111), reproduces a
byte-for-byte identical EE-side ELF. No disc data or extracted assets ship
with this repository. You must legally supply your own disc image to build.

> [!IMPORTANT]
> This project is unaffiliated with Sony Interactive Entertainment, Team Ico,
> or any of their affiliates. *ICO* is a trademark of its respective owners.
> Read [`docs/LEGAL.md`](docs/LEGAL.md) before contributing.

## Status

`tools/build.sh setup && ninja` verifies `build/ico.rom` against
`baserom/pal/baseelf.rom` (`a401d1e5a20b1659189a8b1026a8eb35811dc9ca`). The
boot ELF `baserom/pal/baseelf.elf` is
`da3644c54c26fe760f3b6a591a5fc2eab396ed2b`. The round trip is byte-identical
on every commit; the pre-commit and pre-push hooks run the gate.

`tools/progress.py` regenerates the badges (`tools/build.sh progress` runs it
together with the dashboard). There is one badge per section of the reference
ELF, in link order: `.text`, `.vutext`, `.data`, `.rodata`, `.lit4`, `.sdata`,
`.sbss`, `.bss`. The last two are NOBITS and hold no ROM bytes, so their
figure is **ownership**: how much of the section a compiled TU defines and the
link seats at the ROM's addresses, not bytes reproduced. A section the ELF
sizes at zero (`.vudata` here) gets no badge.

[`docs/PROGRESS.md`](docs/PROGRESS.md) has the per-section breakdown.

## Quickstart

```sh
./tools/setup.sh                    # idempotent: venv, submodules, EE toolchain, ghidra
cp "/path/to/Ico (Europe).iso"  baserom/Ico_PAL.iso
./tools/extract_elf.sh              # baserom/pal/baseelf.{elf,rom} + SHA-1 record
tools/build.sh setup                # SHA-1 verify ELF → splat → emit build.ninja
ninja                               # assemble + link + SHA-1-check rebuilt ELF
```

You supply the disc image yourself. `baserom/` is gitignored and nothing from
the disc is ever committed. On `ntsc` the same commands read
`baserom/Ico_USA.bin` + `.cue` instead.

The build stops unless the SHA-1 of the extracted ELF matches
`config/sha1sums.txt`. `ninja` is the inner-loop builder. `tools/gen_ninja.py`
regenerates `build.ninja` from `config/ico.pal.d` whenever its inputs change,
so flipping a yaml subsegment needs no manual step.

[`docs/BUILDING.md`](docs/BUILDING.md) has the full walkthrough, the
prerequisites and the PCSX2 sanity check.

## Matching workflow

1. Every `.text` TU is a subsegment of `config/ico.pal.yaml`: 223 game TUs
   plus the SCE SDK library code under `sce/`. Boundaries and names come from
   the PAL disc's own linker map and listing via
   `tools/gen_pal_symbol_addrs.py`. SDK code is `sce/<archive>/<member>.c`
   where MAIN.MAP's member spans tile the retail run, and one file per run,
   named for the archive, where they do not. A started TU is
   `ico2/<programmer>/<kind>/<TU>.c` (or under `sce/` for the SDK code) with
   one `INCLUDE_ASM` line per unmatched function. Its splat baseline is
   `asm/nonmatchings/<TU path>/<func>.s`. TUs still marked `asm` in the yaml
   have not been started.
2. Read the function's rows in the disc's `SRCFILE.TXT` listing and its
   census row in `docs/pal_source_tree.md` (local, from
   `tools/gen_pal_source_tree.py`, which gives each file's functions in
   source order, the `#include`-coalesced TUs and the header-resident inline
   helpers). `docs/HEADERS.md` tracks the developer-named headers. The old
   pickups queue and the port ledgers are retired.
3. Iterate with `tools/quick_diff.sh <TU-stem> <func>` (~100 ms / try).
   When the diff is empty, run `ninja` for the full byte-identical SHA-1
   check. `ninja` is authoritative: `quick_diff` can false-pass on in-TU
   relocs and the 4-byte delay-slot nop.
4. Run `./tools/check_no_rom.sh`, commit.

The loop is run by hand. `tools/match_diff.py <TU-stem> <func>` is the
authoritative score. It reloc-normalizes both streams and reports
`real_count`, the number of root divergences. `tools/tu_check.py <TU-stem>`
re-diffs every already-matched function in the TU, so an edit cannot
silently break a sibling.

Matching is **one pass across every TU**, driven from the disc's own maps.
The `SRCFILE.TXT` line map is the source-shape oracle; `MAIN.MAP` and the
census give names and layout. Per function, reason from the line map and the
compiler's own dumps. Land the function when the rebuilt ELF is
byte-identical; `ninja` is the only gate that says so. A pass that ends
before a function lands records its exact state, and the next pass resumes
on it. There are no stall counters, no iteration budgets and no floor
verdicts: the compiler is fixed, so a source shape that produces those bytes
exists. Diff counts pick the next axis; they are not the objective.

Where the residual is whole-function register allocation, reload or coloring
rather than a local tie, drive the whole body toward the ROM's codegen
instead of minimising the diff each step. Accept diff-count regressions while
coloring classes snap into place in groups. The levers are in
[`docs/COOKBOOK.md`](docs/COOKBOOK.md) §13.

Pattern catalogs and quirk references:
[`docs/COOKBOOK.md`](docs/COOKBOOK.md) (>1600-line shape-to-fix lookup),
[`docs/NOTES.md`](docs/NOTES.md) (PS2/EE/compiler/linker quirks),
[`docs/MATCH_VU.md`](docs/MATCH_VU.md) (VU0 macro matching), and
[`docs/PROGRAMMERS.md`](docs/PROGRAMMERS.md) (author-to-subsystem map).

## Layout

Decompiled C follows the **retail build's own source tree**. The release
build collapsed the prototype's per-programmer directories into a flat
layout, which the PAL disc's `SRCFILE.TXT` listing spells out file by file
(`docs/pal_source_tree.md`, local-only). The prototype's per-programmer
attribution survives as metadata (the progress site's grouping);
[`docs/PROGRAMMERS.md`](docs/PROGRAMMERS.md) has the author-to-subsystem
mapping.

```
config/         splat yaml + linker scripts (ico.pal.{yaml,ld,d},
                symbol_addrs.pal.txt), ELF SHA-1
ico2/           the game tree the disc's listing records, one directory per
                programmer (common, fumi, ito, omori, script, seki, sugipon)
                and under each the kinds that programmer shipped: src/, and
                fumi's ios/ isys/ sound/, ito's mpeg/, plus each programmer's
                own include/ (sugiCommon.h, itou_common.h, *climb.h,
                typedef.h, mv_defs.h), see docs/HEADERS.md
sce/            SCE SDK library code, one directory per archive; where
                MAIN.MAP's member spans tile the run it is one file per
                member, otherwise one file per run
                plus the 5 hand-typed VU1 microprogram .S sources at the
                ico2/ root itself: MAIN.MAP pulls their objects in from
                ico2000.a, but the listing records no source rows for them,
                so the programmer directory is unrecorded
include/        the build scaffolding this project wrote: common.h,
                include_asm.h and the two splat .inc files.  The five
                headers that held recovered declarations moved into the
                attested ico2 headers and TUs on 2026-09-15, see
                include/README.md
asm/            splat output (gitignored except asm/nonmatchings/)
assets/         extracted disc data (gitignored)
baserom/        local-only: user's disc + extracted ELF (gitignored)
build/          build artifacts (gitignored)
lib/            submodules (splat, asm-differ)
tools/          build orchestration + matching aids (compile_c.sh,
                quick_diff.sh, match_diff.py, find_carves.py,
                gen_pal_symbol_addrs.py, gen_pal_data_symbols.py,
                gen_pal_source_tree.py, check_dev_native.py ...)
docs/           the project's one documentation directory: README.md indexes
                every file in it: HEADERS.md and PROGRAMMERS.md, the
                dashboard the Pages site serves (index.html + progress.json
                + PROGRESS.md), and the local pattern catalogs (NOTES.md,
                COOKBOOK.md, MATCH_VU.md, gitignored)
```

### File-structure conventions

- **`ico2/<programmer>/<kind>/<TU>.c`**: tracked matched C for one
  translation unit, at the path the listing records for it. Each TU compiles
  from inside its own programmer directory with relative
  `-I../<other>/include` entries, because ee-gcc bakes the spelling it is
  given into `__FILE__`. Typed data definitions sit next to the functions
  that reference them.
- **Typed data** is placed by **per-TU yaml carving**: dot-form
  `.rodata`/`.data`/`.sdata` subsegments, and `.sbss`/`.bss` for the
  uninitialised runs, in `config/ico.pal.yaml`. It is never a generated
  sidecar and never a `section` attribute in the source. Carved constants are
  written into the owning `<TU>.c`, so gcc's emission replaces the asm-side
  blob. `docs/NOTES.md` ("Data carves") has the carve rules and known blockers.
- **A parked near-miss** stays as its `INCLUDE_ASM` line, with the reasoning
  recorded next to the function rather than in a separate directory.

## Build pipeline

```
disc image (Ico_PAL.iso on main; .bin/.cue on ntsc)
   │
   │  tools/extract_elf.sh
   ▼
baserom/pal/baseelf.{elf,rom}  ←──── SHA-1 oracle for every build
   │
   │  tools/build.sh setup    (raw round-trip: NO ld/asm postprocess,
   │    patch_splat.py            NO data→typed-C migration)
   │    assemble_vu0.py → hand-typed VU1 .S → .s
   │    splat → asm/, config/ico.pal.ld
   │    tools/gen_ninja.py → build.ninja
   ▼
ninja
   │
   │  ee-gcc 2.9 (ico2/**/*.c) + period ee-as 2.9-991111 (asm/*.s),
   │    both via tools/compile_c.sh
   │  + always-on asm/ROM-encoding parity in preprocess_old_as.py /
   │    compile_c.sh (move→daddu, break 0,N, FCC + COP1-move hazard nops,
   │    FP-store-before-jr, unaligned-store-before-tail-j, .lit4 placement)
   │  link via config/ico.pal.ld
   ▼
build/ico.elf → objcopy → build/ico.rom
                              │
                              ▼
                    SHA-1 check vs baserom/pal/baseelf.rom
```

## Toolchain

- **Compiler**: ee-gcc 2.9-991111-01, fetched from `decompme/compilers`
  into `tools/cc/ee-gcc2.9-991111/`.
- **Assembler**: two, chosen per archive by the disc's link (see
  `docs/NOTES.md`, "Assembler per archive"): the period ee-as 2.9-991111
  (ee-gcc 2.9's own `as`) for the game and for libc, libm and libgcc, and
  SCE's 2.10-ee assembler for the SDK-install archives, whose shipped
  objects carry its delay-slot fill. Never per TU or per function. A parse
  failure is a hard error to fix in the source. splat's own `.s` and the
  final link use `mips-linux-gnu-as/ld/objcopy`.
- **Linker**: GNU ld via `mips64r5900el-ps2-elf-ld`.
- **Analysis**: Ghidra under `tools/ghidra/`; `splat` (`lib/splat/`) for
  ELF splitting; `asm-differ` for the per-function diff.
- **Emulator**: PCSX2 (optional, for an ELF sanity check).

## License

MIT, see [`LICENSE`](LICENSE). The license covers the original code we wrote.
It grants no rights in disc data or in any IP owned by SIE / Team Ico.

## Reference decomps

Two decomps we cross-reference regularly, read for technique and never
copied from:

- [`parappadev/parappa2`](https://github.com/parappadev/parappa2): Sony
  Japan Studio, PS2 2001, **same `ee-gcc 2.9-991111-01` toolchain as
  ICO**. Useful for compiler idioms and header / macro patterns. Its per-TU
  `slinky` section-linking approach was tried on an ICO branch that no
  longer exists; all three live branches are raw splat round trips.
  `docs/NOTES.md` has specific cross-references.
- [`zeldaret/oot`](https://github.com/zeldaret/oot): Ocarina of Time, N64.
  The decomp workflow this project models its structure on: splat-driven
  yaml, asm-differ, per-function matching loop.
