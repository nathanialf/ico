# nearest_waypoint_by_lineseg (fumi/src/way_util) — parked

Asm source: asm/aug6/nonmatchings/fumi/src/way_util/nearest_waypoint_by_lineseg.s
TU: fumi/src/way_util.c

## Parked 2026-06-08 (deferred from retail-port; NOT a 30-stall floor)

Retail-port candidate that did not match by direct port. float-literal .lit4 pool: ROM uses lwc1 %gp_rel(D_named) where retail body emits a literal; masked-immediate false-twin. Needs named-global ref or .lit4 work.

## Seed

`tough_nuts/nearest_waypoint_by_lineseg/nearest_waypoint_by_lineseg.c` — retail body rebound to aug6 symbols (does NOT match
as-is). Use as a structural reference for real matching.
