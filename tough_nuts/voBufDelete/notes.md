# voBufDelete (ito/mpeg/mv_vobuf) — parked at rc5 (loop-init scheduling only)

## Status
Algorithm fully recovered; matches ROM except a 3-byte scheduling residual in the
frame-clear loop's init block (file offset 0x19BA54-0x19BA60).

## Key dev-intent finding (from voBufGetTag, now matched)
voBufGetTag matched as `void voBufGetTag(volatile int *a0)` — the movie output
ring buffer is VOLATILE (shared with the IPU/interrupt; movie_init in mv_main.c
also takes `volatile int *`). So voBufDelete takes the SAME `volatile int *a0`.

`volatile` is the breakthrough: it ordered the field inits (writeIdx@12,
numFrames@16, readIdx@8) AND fixed the loop register tie (counter->a1, stride->v1,
matching ROM). Combined with a do-while (no initial guard), this took voBufDelete
from rc32 -> rc5. The seed here is the volatile do-while form.

## Remaining residual (rc5 = 2 link-resolved false-negs + 3 real)
The 2 `addiu a2,a2,24` (blk 3/9) are in-TU "p != NULL" %lo false-negs that resolve
in the full link. The 3 REAL bytes: gcc materializes `li v0,5` (numFrames value)
and `lui v1,0xa` (stride hi) one instruction LATER than ROM:
  ROM:   addiu v0,5 ; sw zero,12 ; lui v1 ; sw v0,16 ; sw zero,8
  built: sw zero,12 ; addiu v0,5 ; sw v0,16 ; lui v1 ; sw zero,8
Store ORDER matches (12,16,8); only the two value-materializations are deprioritized
by sched2 (short critical path: li 5 -> sw 16; the loop reloads a0[4] from memory so
the reg chain is broken). Confirmed NOT a hard volatile barrier — the li sits between
two :TI volatile stores and is movable; sched2 just won't hoist it. ~40 hand shapes
+ two permuter runs (volatile seed base score 210) did not crack it. Permuter-class
sched2 tie; re-attack with a structural perturbation that lengthens the 5's chain.

## Companion: data carve (REVERTED, redo when this matches)
The deq_movie_mes assert strings carve `[0x457158, .rodata, ito/mpeg/mv_vobuf]`
(D_00557158 "../ito/include/mv_defs.h" + D_00557178 "p != NULL") REQUIRES the inline
`deq_movie_mes` form so mv_vobuf.o emits the strings via __FILE__ (explicit string
defs don't reproduce the 0x20/0x10 padding). It is coupled to this match: re-apply
the yaml split + `#include "mv_defs.h"` + include_ito.txt entry once the loop matches.
The seed here uses extern strings (standalone, no header) for the permuter.
