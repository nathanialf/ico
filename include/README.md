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
The five VU1 microprogram sources sit at the `ico2/` root for the mirror image
of that reason: MAIN.MAP pulls their objects in from `ico2000.a`, which proves
the archive, but the listing records no source rows for them, so no programmer
directory is recoverable.

## What is left in this directory

| file | holds | used by |
|---|---|---|
| `common.h` | nothing of its own; pulls in `include_asm.h` | every game and SDK TU |
| `include_asm.h` | `INCLUDE_ASM`, `INCLUDE_RODATA`, `INCLUDE_ASM_NOP_PAD`, `ASM_LIT4_SLOT`, `ASM_RODATA_LABEL` | 894 / 0 / 0 / 353 / 0 sites plus `tools/emit_run_defs.py` and `tools/format_layout.py` |
| `labels.inc` | `glabel` and friends, period-assembler spelling | every splat `.s` |
| `macro.inc` | the same macros, modern-gas spelling | `tools/assemble_vu0.py` |

All four exist only because functions are still assembled: `include_asm.h` is
the stub vehicle, `common.h` is how every TU reaches it, and the two `.inc`
files are what the `.s` files assemble against. `labels.inc` and `macro.inc`
are hand edited and locked by a note in `config/ico.pal.yaml`; they are not
duplicates of each other but two assembler dialects, and `tools/quick_diff.sh`
explains which is which.

## The 2026-09-15 migration: five scaffolding headers moved out

`r5900.h`, `vu0.h`, `ico/types.h`, `syscall.h` and `math_private.h` are gone.
Each held code the developers must have had somewhere, so each moved to the
most likely home the evidence supports, and every one of the 365 TUs in the
tree compiles to a byte-identical object across the move (`.text` bytes,
relocation list, `nm -n` order, data sections and section list all unchanged).

The rule applied, in order:

1. rows the listing attributes to a header go to that header, at that line;
2. else a construct several TUs of one programmer's tree share goes to the
   attested header that tree includes;
3. else a construct TUs across programmers share goes to
   `ico2/common/include/typedef.h`, the only attested header every ico2 TU's
   `-I` order reaches;
4. else it goes into the one TU that uses it.

`sce/` is outside that rule: its uses stand for Sony-internal headers this
tree cannot name, because `MAIN.MAP` attests archives and their members and
never a header. Each SDK member that needs a definition now carries its own.

| what moved | to | by which rule |
|---|---|---|
| `GObj`, `Sub15C`, `Obj7F0`, `GeoNode`, `GeoSub`, `GOBJ_SUB` | `ico2/common/include/typedef.h` | 3 (37 TUs over six programmer directories) |
| `SYNC`, `DI`, `EI`, `QCOPY16`, the `VU0_*` set | `ico2/common/include/typedef.h` | 3 (seki, sugipon and ito TUs) |
| `QCOPY64_PARALLEL` | `ico2/seki/src/Matrix.c` | 4 |
| `QCOPY64_SERIAL`, `MAP_A0_TO_SPR`, `LQ16_FROM`, `SQ16_TO` | `ico2/sugipon/src/matrixDrive.c` | 4 |
| `SYNC`, `EI`, `MFC0_STATUS`, `COP0_STATUS_EIE` | `sce/libkernl/intr.c`, `sce/libkernl/diei.c`, `sce/libmc/libmc.c`, `sce/libgraph/graph014.c` | per member |
| the `VU0_*` set | `sce/libvu0/libvu0.c` | per member |
| `SYSCALL_WRAPPER`, `SYSCALL_INLINE` | `sce/libkernl/intr.c`, `klib.c`, `thread.c` | per member |
| the fdlibm two-word float idiom | the six `sce/libm` members that use it | per member |

The placements into `typedef.h` are by include pattern, not by listing rows,
and say so at their definitions. No listing row can name the home of a struct
declaration or of a macro: a declaration emits no instructions, and a macro
expansion is attributed to the line that invokes it. What the listing does
rule out is a home in the SDK tree, since it attributes zero rows to
`/usr/local/sce/ee/include`.

Line 74 of `typedef.h` is still reserved and still empty. The listing puts
`avoid_obstacle2`'s inlined float absolute value there, and that host is still
`INCLUDE_ASM`; nothing above that line may be reflowed.

The macro names are ours throughout. None of them is a disc fact, and none was
renamed to an SDK spelling.

Six definitions were removed in the 2026-09-14 trim because nothing in the
tree, the tools or the docs referenced them: `JTEXT` (`common.h`), `SYNC_P`,
`QCOPY16_NO_NOP` and `QCOPY64_PARALLEL_NO_NOP` (`r5900.h`), and
`INCLUDE_ASM_NOAT` and `INCLUDE_ASM_FS` (`include_asm.h`). Any of the six
comes back out of git history if a TU ever needs it.

The original tree certainly had more headers than eleven. A header that only
declares things leaves no instructions behind, so neither `MAIN.MAP` nor
`SRCFILE.TXT` can name it: the listing sees a header only where code from it
was inlined into a function, and `charFileName.h` is only visible because a
developer typed its path into a message. Those headers are unrecoverable from
the maps, and inventing paths for them would assert a partition nothing has
checked. Declarations therefore stay where the matching work put them, in the
TU that needs them.

## Crutch macros

`REG`, `ANCHOR`, `MEM_BARRIER`, `KEEP_LIVE` and `MATERIALIZE` are gone: no
definition anywhere under `include/` and no use anywhere under `ico2/` or
`sce/`. `SWEEP` is not a macro at all, it survives as eight `/*SWEEP-END...*/`
comment markers in five TUs, which the crutch pass should clear.
