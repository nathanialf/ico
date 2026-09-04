# _clipW (fumi/src/fuzio)

best real_count = 4, stall 8/30 at park-to-resume (iter 140 in match_loop state).

## Purpose / data model
Walks `D_006A4B40[]` index table (length `D_0062C01C`); for each entry derefs
`D_0062C020->unk18[idx]` to a `short *p` run terminated by a negative short.
For each non-negative entry: `e = ctx->unk10 + (*p)*0x50` (0x50-stride FzEntry),
reads `val = *(int*)(e+0x48)`; if top nibble clear and the 0xF0000 field != 0x10000,
calls `__ClipFloor(arg0, e, 0, 1)`; on success writes e/arg1/arg2 into arg0+0x88/0x80/0x84
and sets ret=1. Inner `do..while(*(volatile short*)p >= 0)`.

## Residual (rc4)
block 4: ROM emits `lw a1,0(gp)` where our shape emits `lhu v1,0(s1)` — a
gp-rel global reload vs a short reload, plus a value/ctx reload coloring/sched tie.
Looks like a reload-placement + s1/s2/s3 coloring tie around the value (`*p`) load
filling the bgez delay vs the ctx (`unk10`) reload at the top of block 4.

## Levers tried (from match_loop state, ~9 distinct + permuter once earlier history)
- inline value `*p*0x50` + volatile do-while; plain bgez, value re-read inline
- reorder e operands (value first) inline + volatile to fill bgez delay
- outer do-while + N>0 guard + ++i in condition; carried volatile inner
- carried+volatile + writeback via computed base w (extra pseudo) to flip s2/s3
- fresh `int idx=(unsigned short)*p` temp at body top
- drop volatile -> plain signed `*p>=0` (lh); if(N>0){do..while(i<N)} outer
- volatile on the VALUE load `(int)*(volatile short*)p`; plain test
- explicit carry short v read once; body uses (int)v; loop-rotation
- volatile-read D_0062C020 pointer into local c at body top

## To try next
- gp-rel: the ROM `lw a1,0(gp)` suggests a near-gp global is reloaded as the
  ClipFloor arg1 (arg1 passed through). Try keeping arg1 live differently / route
  through a gp-rel-typed alias so the reload colors into a1 from gp.
- decl-order of `e`/`val` to change which of value/ctx fills the bgez delay slot.
- typed FzEntry array `ents[*p]` instead of `unk10 + *p*0x50` to fix base coloring.
