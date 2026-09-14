# `include/` is build infrastructure, not part of the mirrored source tree

The game tree under `ico2/` mirrors the paths the PAL disc's own listing
records, one directory per programmer, and the ten headers the listing
attributes live there:

| header | home |
|---|---|
| `sugiCommon.h` | `ico2/sugipon/include/` |
| `typedef.h` | `ico2/common/include/` |
| `b50climb.h`, `b100climb.h`, `b200climb.h` | `ico2/omori/include/` |
| `g50climb.h`, `g100climb.h`, `g200climb.h` | `ico2/omori/include/` |
| `itou_common.h`, `mv_defs.h` | `ico2/ito/include/` |

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
