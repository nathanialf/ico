# `include/` is build infrastructure, not part of the mirrored source tree

The game tree under `ico2/` mirrors the paths the PAL disc's own listing
records, one directory per programmer, and the ten headers the listing
attributes live there (or, for newlib's `math_private.h`, under `sce/`):

| header | home |
|---|---|
| `sugiCommon.h` | `ico2/sugipon/include/` |
| `typedef.h` | `ico2/common/include/` |
| `b50climb.h`, `b100climb.h`, `b200climb.h` | `ico2/omori/include/` |
| `g50climb.h`, `g100climb.h`, `g200climb.h` | `ico2/omori/include/` |
| `itou_common.h`, `mv_defs.h` | `ico2/ito/include/` |
| `math_private.h` | `sce/libm/common/` (newlib's own location) |

Everything still in this directory was written by this project and has no
counterpart in the disc's maps: `common.h`, `r5900.h`, `vu0.h`,
`include_asm.h`, `syscall.h`, `macro.inc`, `labels.inc` and `ico/`.

The original tree certainly had more headers than ten. A header that only
declares things leaves no instructions behind, so neither `MAIN.MAP` nor
`SRCFILE.TXT` can name it: the listing sees a header only where code from it
was inlined into a function. Those headers are unrecoverable from the maps,
and inventing paths for them would assert a partition nothing has checked.
Declarations therefore stay where the matching work put them, in the TU that
needs them or in the headers here.
