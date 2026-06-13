# staffRollMain (common/src/staffroll) — parked rc2 after 30-stall (no frame, tail-call j)

## State: rc2, crutch:false. Single diff = a 2-store sched2 PERMUTATION.
ROM tail: `B45C(swc1 f0), [C1C8,C1DC,C1CC,C1D8 zeros], j func_00260568, B460(swc1 f0 in delay)`.
gcc clusters the two `swc1 $f0` stores (B45C, B460 — both = reloaded D_0062C1C4 = 0.0)
and fills the j delay with a zero-store instead of B460.

## Root: VALUE-driven clustering. f0 is loaded once (lwc1 D_0062C1C4; the sw $0 store
to C1C4 can't forward to the float load → reload). Both stores share f0; gcc's scheduler
groups same-register uses, putting them adjacent. ROM keeps f0 live across the 4 zero
int-stores and emits B460 last (delay).

## Exhausted (30 distinct hand hypotheses, all rc2 or worse):
store reorderings (B460 anywhere → still clusters); §8.25 hoist (B460 2nd-to-last);
volatile (B460 only / both floats / whole tail — tail-volatile gets the order RIGHT but
mis-places B45C early since volatile pins it right after the f0 load, pushing the early
stores after it → rc10); RAW dep B460=B45C (gcc forwards f0, still clusters); float[2]
array; struct {flag,x,y}; chained zeros; long-long zeros (rc5, wrong width); int-return
tail (rc8); swapped params; local temp z; widen source gap; up-count (reverses but same);
temp call-arg ptr; int-store C1C4 (rc10); sequential/ROM zero orders (both rc2, zeros
schedule freely). The cluster is INVARIANT to source shape — proven not a source-shape fix.

## Verdict: permuter-domain "tail-call j delay" emission residue (cookbook §8 list).
The tail-volatile experiment PROVES the target order is achievable — the permuter should
find a register-occupying mutation that breaks the f0 cluster without mis-placing B45C.
RESUME: apply seed, `match_loop.py reset staffRollMain --reason "..."`, then permuter or
a fresh non-source idiom (e.g. occupy f0 between the stores with a benign float op IF one
exists in ROM — none currently; or a second value in a different f-reg).
