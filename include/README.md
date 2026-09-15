# `include/` is build infrastructure, not part of the mirrored source tree

The game tree under `ico2/` mirrors the paths the PAL disc's own listing
records, one directory per programmer, and the eleven headers the disc
attests live there:

| header | home | what attests it |
|---|---|---|
| `sugiCommon.h` | `ico2/sugipon/include/` | SRCFILE.TXT rows |
| `typedef.h` | `ico2/common/include/` | SRCFILE.TXT rows |
| `b50climb.h`, `b100climb.h`, `b200climb.h` | `ico2/omori/include/` | SRCFILE.TXT rows |
| `g50climb.h`, `g100climb.h`, `g200climb.h` | `ico2/omori/include/` | SRCFILE.TXT rows |
| `itou_common.h`, `mv_defs.h` | `ico2/ito/include/` | SRCFILE.TXT rows |
| `charFileName.h` | `ico2/common/include/` | a string the retail ELF bakes |

Ten of the eleven come from `baserom/pal/SRCFILE.TXT`, which attributes
instructions to them. The eleventh has no rows at all: `charFileName.h` is
named by the message at `D_00619370` (.rodata, VMA `0x00619370`, rom offset
`0x519370`), which spells `commmon/include/charFileName.h` with the
developers' typo and asks the reader to raise `MAX_CHARS`. That path is hand
typed into the message, not a `__FILE__` expansion, so it fixes the header's
name and directory but not the `-I` spelling gcc saw; the three sites in
`ico2/common/src/charFileManager.c` that print it all compare against 1637, so
the bound is the one thing the header can be given.

Nothing is placed under `ico2/` or `sce/` unless the disc's maps attest it.
Two headers stay here for that reason even though both plausibly existed in
the original trees: `math_private.h` (newlib's public tree keeps one under
`libm/common`, but the disc's listing cannot show it, since a header that
emits no instructions leaves no rows; ours is a re-derivation of the public
fdlibm idiom) and `vu0.h` (the game's inline VU0 instructions are attributed
to the TU lines; whether the developers wrapped them in a header of their own
is unknowable, so the wrapper is kept here as scaffolding and is neither
promoted into the tree nor expanded into the TUs).

The five VU1 microprogram sources sit at the `ico2/` root for the mirror
image of that reason: MAIN.MAP pulls their objects in from `ico2000.a`, which
proves the archive, but the listing records no source rows for them, so no
programmer directory is recoverable.

## What is left in this directory

Everything here was written by this project and has no counterpart in the
disc's maps.

| file | holds | used by |
|---|---|---|
| `common.h` | nothing of its own; pulls in `include_asm.h` | every game and SDK TU |
| `include_asm.h` | `INCLUDE_ASM`, `INCLUDE_RODATA`, `INCLUDE_ASM_NOP_PAD`, `ASM_LIT4_SLOT`, `ASM_RODATA_LABEL` | 894 / 0 / 0 / 353 / 0 sites plus `tools/emit_run_defs.py` and `tools/format_layout.py` |
| `r5900.h` | `SYNC`, `EI`, `DI`, `MFC0_STATUS`, `COP0_STATUS_EIE`, `QCOPY16`, `QCOPY64_SERIAL`, `QCOPY64_PARALLEL`, `LQ16_FROM`, `SQ16_TO`, `MAP_A0_TO_SPR` | the EE kernel, libmc, libgraph and mpeg TUs |
| `syscall.h` | `SYSCALL_WRAPPER`, `SYSCALL_INLINE` | 131 and 2 sites under `sce/` |
| `ico/types.h` | `GObj`, `Sub15C`, `Obj7F0`, `GeoNode`, `GeoSub`, `GOBJ_SUB` | 91 / 1 / 1 sites, the last two through the first three |
| `math_private.h` | the fdlibm two-word float idiom | `sce/libm/` |
| `vu0.h` | inline VU0 instruction wrappers | the geometry TUs |
| `labels.inc` | `glabel` and friends, period-assembler spelling | every splat `.s`, `tools/assemble_vu0.py`, `tools/quick_diff.sh` |

`labels.inc` is hand edited and locked by a note in `config/ico.pal.yaml`
(splat's default regen would revert it). It is the only dialect left: the
modern-gas twin `macro.inc` was deleted on 2026-09-15 when the data blobs and
the VU1 microprograms moved onto the period assembler with everything else.
A blob `.s` sets `__blob = 1` after including it, which keeps the file's one
section instead of filing each `dlabel` object into its own `.rodata.<sym>`.

Six definitions were removed in the 2026-09-14 trim because nothing in the
tree, the tools or the docs referenced them: `JTEXT` (`common.h`), `SYNC_P`,
`QCOPY16_NO_NOP` and `QCOPY64_PARALLEL_NO_NOP` (`r5900.h`), and
`INCLUDE_ASM_NOAT` and `INCLUDE_ASM_FS` (`include_asm.h`). The last two are
worth a note: `INCLUDE_ASM_FS`'s own comment claimed `box.c` and `switch.c`
used it through `config/extra_cflags.txt`, and both claims are stale, the
per-function flag machinery is retired and neither file names the macro. Any
of the six comes back out of git history if a TU ever needs it.

No prototypes live here, so none moved into a TU. No typedef moved into
`ico2/common/include/typedef.h` either: the listing attributes exactly one
line of that header to code, a float absolute value inlined twice into
`avoid_obstacle2`, and no typedef at all, so there is no evidence that it
owned any of `ico/types.h`'s shapes.

The original tree certainly had more headers than eleven. A header that only
declares things leaves no instructions behind, so neither `MAIN.MAP` nor
`SRCFILE.TXT` can name it: the listing sees a header only where code from it
was inlined into a function, and `charFileName.h` is only visible because a
developer typed its path into a message. Those headers are unrecoverable from
the maps, and inventing paths for them would assert a partition nothing has
checked. Declarations therefore stay where the matching work put them, in the
TU that needs them or in the headers here.

## Crutch macros

`REG`, `ANCHOR`, `MEM_BARRIER`, `KEEP_LIVE` and `MATERIALIZE` are gone: no
definition anywhere under `include/` and no use anywhere under `ico2/` or
`sce/`. `SWEEP` is not a macro at all, it survives as eight `/*SWEEP-END...*/`
comment markers in five TUs, which the crutch pass should clear.
