# func_0013B878 (ios/pad.c)

**Status:** 1-instruction near-miss — permuter candidate.

The C body is functionally complete and produces a byte-identical match
**except** the prologue emission order of two independent instructions:

```
expected:                 built:
sd  s1,16(sp)             sd  s1,16(sp)
daddu a1,zero,zero        sd  s0,0(sp)
sd  s0,0(sp)              daddu a1,zero,zero
```

`daddu a1,zero,zero` is func_002641D8's 2nd arg (`0`); gcc schedules it
*after* the `sd s0` callee-save instead of *between* the two saves.

Tried (no effect): `-fno-schedule-insns`, `-fno-schedule-insns2`,
`-fno-delayed-branch`, `-fno-peephole`, `do/while(0)` wrap of the call,
pinning `a1` to `$5` + `KEEP_LIVE` (made it worse — loaded a1 from gp).
The `$3` (v1) pin + `KEEP_LIVE` on the D_002811C0 base, and splitting the
`+0x1B8` off the symbol address (eager materialize), are both load-bearing
and correct.

This is a pure instruction-emission-order swap — exactly what the permuter
closes. Seed above is the best human attempt.
