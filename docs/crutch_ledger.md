# Crutch ledger

What was measured when a crutch could not be replaced by a byte-identical
crutch-free source shape, and what was tried. One section per construct.
A site listed here carries a `CRUTCH:` comment in the source naming the class
and the measured delta.

The scan that produced these rows is
`.claude/.decomp_stash/crutch_scan/SCAN_2026-09-14.md`.

## Zero-code frame reservation (an unused local)

Five sites. In each, a local is declared, never read, never written, and its
address is never taken, yet deleting the declaration changes the emitted
object: the frame shrinks and every slot below it moves. The ROM frame is the
evidence that the dev's source had an object there.

Gate used per site: delete the line, run `.venv/bin/ninja`, compare
`build/<path>.o` with the pre-change object byte for byte.

| site | object | measured on deletion |
|---|---|---|
| `ico2/ito/src/stage_orient.c` `MakeStageOrientMatrix` | `VECTOR unused` | vars 240 -> 224; `v` moves from sp+208 to sp+192 and the aggregate temp with it |
| `ico2/common/src/debug.c` `debug_openLog` | `volatile char buf[256]` | frame loses 256 bytes of vars |
| `ico2/fumi/src/fieldCollision.c` `MakeCollisionDependGObjList` | `char buf[0x30]` | frame 0x60 -> 0x30, register saves only |
| `ico2/omori/src/access.c` `GetDataFileName` | `int buf[0x40]` | frame loses 256 bytes of vars |
| `ico2/seki/src/Shadow.c` `shadow_Render` | `float buf[4]` | frame loses its only 16 bytes of vars |

Four of the five sit next to a printf stub or a block the listing shows emitting
no code, so the reading that fits the data is a vestigial debug buffer: the dev
declared it, a debug block used it, and the stub compiled to nothing. That is a
source shape, not a steering trick, but the declaration as it stands in this
repo emits no bytes of its own, so it is marked and recorded rather than
claimed clean.

`stage_orient` is the one where the slot is not next to a debug block. Axes
tried there:

- Delete it. vars drops to 224 and every slot shifts. Rejected.
- Move the vector build into a nested `static inline SetStageOrientPos(VECTOR *,
  float *)` whose own `VECTOR t` initialiser supplies the third 16-byte object.
  This reproduces ROM's frame size exactly (vars 240) but assigns the slots in
  the wrong order: `v` lands at sp+192 and the aggregate temp at sp+208, where
  ROM has an unwritten slot at sp+192, `v` at sp+208 and the temp at sp+224.
  gcc 2.9 lays locals out in declaration order from the low end, so matching
  ROM needs a 16-byte object declared *before* `v`, which is what the unused
  local is. Rejected.
- Writing `v` field by field instead of with an aggregate initialiser removes
  the ld/sd copy pair ROM has, so the initialiser form is confirmed and is not
  the axis. Not a candidate.

Open axis: a 16-byte object declared before `v` that the emitted body genuinely
uses somewhere gcc can drop the uses but not the slot. Nothing in the two
callers suggests one yet.

## Symbol alias kept because the plain name inlines

`ico2/sugipon/src/quaternion.c` `DivQuaternion` called `MultiQuaternion` through
a `__pn` alias. The alias is gone, but the call cannot use the plain name: the
TU's own definition of `MultiQuaternion` carries the repo's coalescing `inline`
marker, so gcc inlines the body where ROM has a `jal`. Measured: dropping the
`inline` marker from the definition instead does not match either (the object
diverges at byte 81, an emission-order change). The call now goes through a cast
of the existing declaration, the remedy CLAUDE.md and `ico2/fumi/src/way_util.c`
already use. The real fix is whatever replaces the `inline` markers when the
TU's inline modelling is settled.

## Register pins and inline asm that are not crutches

Listed so a later audit does not re-open them. Every one feeds a real asm
consumer or is a documented whole-function exception:

- FP and GPR return capture for a VU0 or MMI asm block: `ico2/seki/src/Matrix.c`
  `_GetRandom`, `ico2/sugipon/src/quaternion.c` `RegularizeQuaternion`,
  `ico2/sugipon/src/clothAnimation.c` `tensionMoveNoReduce`,
  `ico2/sugipon/src/geometryManager.c`, `sce/libvu0/libvu0.c` (three),
  `ico2/omori/src/camera-ico2.c`.
- `sce/libm/math/kf_cos.c`: seven pins naming the six coefficient registers and
  the comparison register the hand-placed interleave writes.
- `ico2/fumi/src/way_llf.c` `WayPointList_next`: `$4` pin feeding a whole-function
  `.set noreorder` block through `"+r"`.
- `ico2/sugipon/src/clothAnimation.c` `int sp_buf[4]` in `tensionMoveNoReduce`
  and its sibling: the VU0 block stores through `0x0(sp)`, so the buffer is the
  asm's storage, not a frame filler.
- `__asm__ __volatile__("break")` assert traps, `syscall` wrappers in
  `sce/libkernl/libkernl_100110.c`, and the `__asm__(".section .text"...)`
  whole-function bodies.
- `ico2/sugipon/src/quaternion.c` `GetQuaternionFromMatrix` declares a real gcc
  nested function with a body, not a self-aliased declaration.
