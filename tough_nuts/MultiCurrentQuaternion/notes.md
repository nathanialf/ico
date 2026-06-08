# MultiCurrentQuaternion (sugipon/src/quaternion) — parked

Asm source: asm/aug6/nonmatchings/sugipon/src/quaternion/MultiCurrentQuaternion.s
TU: sugipon/src/quaternion.c

## Parked 2026-06-08 (deferred from retail-port; NOT a 30-stall floor)

Retail-port candidate that did not match by direct port. VU0 quaternion math; real regalloc/sched diff vs retail body.

## Seed

`tough_nuts/MultiCurrentQuaternion/MultiCurrentQuaternion.c` — retail body rebound to aug6 symbols (does NOT match
as-is). Use as a structural reference for real matching.
