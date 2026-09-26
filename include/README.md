# `include/` is build infrastructure, not part of the mirrored source tree

The game tree under `ico2/` mirrors the paths the PAL disc's own listing
records, one directory per programmer. The eleven headers the disc's evidence
places live there. The table names the rung that places each one: only the
retail ELF's own bytes are direct facts, while the listing and the map come
from other links correlated to it.

| header | home | evidence rung |
|---|---|---|
| `sugiCommon.h` | `ico2/sugipon/include/` | SRCFILE.TXT rows |
| `typedef.h` | `ico2/common/include/` | SRCFILE.TXT rows |
| `b50climb.h`, `b100climb.h`, `b200climb.h` | `ico2/omori/include/` | SRCFILE.TXT rows |
| `g50climb.h`, `g100climb.h`, `g200climb.h` | `ico2/omori/include/` | SRCFILE.TXT rows |
| `itou_common.h`, `mv_defs.h` | `ico2/ito/include/` | SRCFILE.TXT rows |
| `charFileName.h` | `ico2/common/include/` | ROM bytes, a string the ELF bakes |

Ten of the eleven come from `baserom/pal/SRCFILE.TXT`, which attributes
instructions to them. The eleventh has no rows at all. `charFileName.h` is
named by the message at `D_00619370` (.rodata, VMA `0x00619370`, rom offset
`0x519370`), which spells `commmon/include/charFileName.h` with the
developers' typo and asks the reader to raise `MAX_CHARS`. That path is typed
by hand into the message, not a `__FILE__` expansion, so it fixes the
header's name and directory but not the `-I` spelling gcc saw. The three
sites in `ico2/common/src/charFileManager.c` that print it all compare
against 1637, so that bound is the one thing the header can be given.

Nothing is placed under `ico2/` or `sce/` without naming the rung that places
it: ROM bytes, then listing rows, then map rows, then neighbours and include
pattern, then public SDK naming. The five VU1 microprogram sources sit at the
`ico2/` root for the converse reason: MAIN.MAP pulls their objects in from
`ico2000.a`, which proves the archive, but the listing records no source rows
for them, so no programmer directory is recoverable.

## What is left in this directory

| file | holds | used by |
|---|---|---|
| `common.h` | nothing of its own; pulls in `include_asm.h` | every game and SDK TU |
| `include_asm.h` | `INCLUDE_ASM`, a still-asm function's stub | every TU that still has one |
| `labels.inc` | `glabel` and friends, period-assembler spelling | every splat `.s`, `tools/assemble_vu0.py`, `tools/quick_diff.sh` |

All three exist only because functions are still assembled. `include_asm.h`
is the stub vehicle, `common.h` is how every TU reaches it, and `labels.inc`
is what the `.s` files assemble against. `labels.inc` is hand edited and
locked by a note in `config/ico.pal.yaml`, since splat's default regen would
revert it. It is the only dialect left: its modern-gas twin `macro.inc` was
deleted on 2026-09-15, when the data blobs and the VU1 microprograms moved
onto the period assembler with every other object. A blob `.s` sets
`__blob = 1` after including it, which keeps the file's one section instead
of filing each `dlabel` object into its own `.rodata.<sym>`.

## The 2026-09-15 migration: five scaffolding headers moved out

`r5900.h`, `vu0.h`, `ico/types.h`, `syscall.h` and `math_private.h` are gone.
Each held code the developers must have had somewhere, so each moved to the
most likely home the evidence supports. Every one of the 365 TUs in the tree
compiles to a byte-identical object across the move (`.text` bytes,
relocation list, `nm -n` order, data sections and section list all
unchanged).

The rule applied, in order:

1. rows the listing attributes to a header go to that header, at that line;
2. else a construct several TUs of one programmer's tree share goes to the
   attested header that tree includes;
3. else a construct TUs across programmers share goes to
   `ico2/common/include/typedef.h`, the only attested header every ico2 TU's
   `-I` order reaches;
4. else it goes into the one TU that uses it.

`sce/` is outside that rule. Its uses stand for Sony-internal headers this
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

The placements into `typedef.h` rest on include pattern, not listing rows,
and say so at their definitions. No listing row can name the home of a struct
declaration or of a macro: a declaration emits no instructions, and a macro
expansion is attributed to the line that invokes it. The listing does rule
out a home in the SDK tree, since it attributes zero rows to
`/usr/local/sce/ee/include`.

Line 74 of `typedef.h` holds the float absolute value helper the listing
attributes there; `avoid_obstacle2` matched with it in chain 1 pass 130.
Nothing above that line may be reflowed.

The macro names are ours throughout. None of them is a disc fact, and none
was renamed to an SDK spelling.

The 2026-09-14 trim removed six definitions that nothing in the tree, the
tools or the docs referenced: `JTEXT` (`common.h`), `SYNC_P`,
`QCOPY16_NO_NOP` and `QCOPY64_PARALLEL_NO_NOP` (`r5900.h`), and
`INCLUDE_ASM_NOAT` and `INCLUDE_ASM_FS` (`include_asm.h`). Any of the six can
come back from git history if a TU needs it.

The original tree certainly had more than eleven headers. A header that only
declares things leaves no instructions behind, so neither `MAIN.MAP` nor
`SRCFILE.TXT` can name it. The listing sees a header only where code from it
was inlined into a function, and `charFileName.h` is visible only because a
developer typed its path into a message. Those headers cannot be recovered
from the maps, and inventing paths for them would assert a partition nothing
has checked. Declarations therefore stay where the matching work put them, in
the TU that needs them.

## Crutch macros

`REG`, `ANCHOR`, `MEM_BARRIER`, `KEEP_LIVE` and `MATERIALIZE` are gone: no
definition anywhere under `include/` and no use anywhere under `ico2/` or
`sce/`. `SWEEP` is not a macro at all. It survives as eight
`/*SWEEP-END...*/` comment markers in five TUs, which the crutch pass should
clear.

On 2026-09-15 the three data-side macros nothing used were removed from
`include_asm.h`: `INCLUDE_RODATA`, `ASM_RODATA_LABEL` and
`INCLUDE_ASM_NOP_PAD`. Data a landing needs is carved as a yaml row and
defined in the TU's C. The one case that keeps a macro is a pool word whose
owner is still asm: the slot line.
