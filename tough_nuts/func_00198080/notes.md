# func_00198080 (ito/src/queen) — rc2 near-miss

Queen cloth-animation dispatcher. Verified structure (cross-checked against
the matched sibling `func_00197EE0`, which builds the 0x7F0 object: `0xC`=flag,
`0x10`/`0x14`=DispCloth4D handles):

```c
func_0010F068();
func_0010F048((int)self);
cloth = sub->0x7F0;
x = sub->0x834;                 // pre-load (delay slot), shares sub -> v1
if (cloth->0xC != 0)
    GetClothAnimation(cloth->0x10, x+0x40, x);   // conditional
x = sub->0x834;                 // reload-after-if (CSE'd away in not-taken path)
GetClothAnimation(cloth->0x14, x+0x40, x);       // unconditional tail (sibcall)
```

## Progression (genuinely-distinct hypotheses only)
- 16: first naive (raw casts, x after call) — gcc frame16/no-s0.
- reload-INSIDE-if (rc6): sub=v1 pre-branch BUT post-call reload reg = v0 (ROM v1)
  AND if-block daddu/lw-a0 order wrong.
- x-fresh-in-if (rc5): if-block daddu order RIGHT, but sub coalesces to a1
  everywhere (ROM v1). sub=v1 requires the anon-CSE pre-load; daddu-order
  requires fresh-load latency — **mutually exclusive in clean C**.
- **reload-AFTER-if + pre-load x (rc2): BREAKTHROUGH.** sub=v1 everywhere, reload
  reg = v1 (correct). The not-taken path CSEs the post-if reload onto the
  delay-slot x; the taken path reloads. This is the seed above.

## Sole residual (rc2): if-block sched2 tiebreak
ROM if-block: `lw a0,0x10(s0); daddu a2,a1; jal; [addiu a1,a1,0x40 delay]`
Built:        `daddu a2,a1; lw a0,0x10(s0); jal; [addiu a1,a1,0x40 delay]`
Just the lw-a0 / daddu-a2 order swapped (a 2-line diff). The function's OWN tail
call (block 4) schedules load-first correctly with the identical arg pattern; the
ROM if-block also has the identical tight `addiu-in-jal-delay` structure yet emits
load-first. So it is a pure sched2 priority/LUID tiebreak, not forced by the WAR
chain (daddu->addiu).

## Levers that all FOLD to the same RTL (do NOT re-count as distinct):
arg0-temp, handle/base temps, ptr-to-array deref, do-while(0) single+double,
comma-in-condition, precompute-arg1, int*-index, int-typed +0x15C slot, self-as-int.
do-while(newvar) needs a runtime-0 that doesn't exist cleanly here.

## Next: permuter
This is a textbook permuter case (cf. func_001FB768: permuter found
`if ((new_var2 = new_var) >= 7)`, a non-coalescing copy hand pins couldn't make).
Seed the permuter with THIS rc2 source.
