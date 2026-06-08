# SetRootBaseQuaternion (sugipon/src/geometryManager) — parked

Asm source: asm/aug6/nonmatchings/sugipon/src/geometryManager/SetRootBaseQuaternion.s
TU: sugipon/src/geometryManager.c

## Parked 2026-06-08 (deferred from retail-port; NOT a 30-stall floor)

Retail-port candidate that did not match by direct port. genuinely 2-arg (reads $5) but matched sibling SetRootQuaternion calls it with 1 arg; needs sibling rework to pass 2nd arg matching ROM.

## Seed

`tough_nuts/SetRootBaseQuaternion/SetRootBaseQuaternion.c` — retail body rebound to aug6 symbols (does NOT match
as-is). Use as a structural reference for real matching.
