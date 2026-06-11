# GetEnemyHitNodeFlag (sugipon/src/enemy) — rc7 near-miss (2026-06-11)

Counts zero-flag nodes. Data model CONFIRMED from sibling `InitDemoMotionGeo` /
`HotInitDemoMotionGeo` in the same TU: `p=self->0x15C; q=p->0x7F0;
base=q->0x14` (int array); a node is "hit" when `base[i] == 0`. count = p->0x88.

## Behaviour
```
result = 0
if (count <= 0) return 0          # blez count, result=0 in delay
for (i over count): if (base[i]==0) result++   # movz, countdown pointer-walk
return result
```

## Best seed (rc7) = the dev idiom (current best.c)
```c
int GetEnemyHitNodeFlag(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    int count = *(int *)((char *)p + 0x88);
    int result = 0;
    if (count > 0) {
        int *q = *(int **)((char *)p + 0x7F0);
        int *base = *(int **)((char *)q + 0x14);
        int i;
        for (i = 0; i < count; i++) if (base[i] == 0) result++;
    }
    return result;
}
```

## The rc7 residual = PURE 2-temp register swap (permuter-class)
Everything matches EXCEPT result and the loop counter are swapped:
- ROM: accumulator=`a1`($5), counter=`a2`($6), arr=`a0`($4)  (sequential a0/a1/a2)
- built: accumulator=`a2`, counter=`a1`  (a1/a2 swapped)
gcc gives the **bnez-operand (the countdown counter) the lower reg a1**; ROM
gives the **accumulator a1**. The counter has one extra loop-ref (the bnez read)
so gcc colors it first → a1. Source-shape-invariant.

## Tried (~11, all rc7 or worse) — same class as gsb_Reduction's residual
decl-order (result-first / i-first / both-outside), i-before-arr, count-as-counter
(rc11), pointer-to-array on arr, explicit-n temp, while(--i), *arr++, index-up for
both inline and dev-idiom (rc15 when arr hoisted past guard) — ALL keep the swap.

## Resume levers to try fresh
- Grind to stall=30 then permuter (this is exactly the gsb_Reduction-class
  2-temp coloring tiebreak the permuter cracked there via a structural mutation).
- Look for a form that gives the ACCUMULATOR an extra reference (so it colors
  before the counter) WITHOUT adding an instruction — or reduces the counter's
  ref weight. Seed the permuter from this rc7 dev-idiom form.
