# soundDataAreaGet (fumi/sound/s_init) — RESUME

Lookup over the 16-entry × 0x30 sound-data area `D_006A3070` (bound always
`base + 0x300`). Given `key = *a0`, scan entries, return the entry whose
first int matches, else 0. Confirmed dev data-model from MATCHED siblings in
the same TU: `debug_DispSEInfo` (`char*p; char*end=base+0x300; p+=0x30;
while((int)p<(int)end)`), `soundSeSemiCommonLoadChk` (`for(i=0;i<0x300;
i+=0x30){char*p=base+i;...}` — strength-reduces to the pointer-walk + slt).

## ROM shape (the asm)
Two lockstep pointers: a1 = deref+bound (biv), a2 = returned copy (a2==a1
every iter). end=a3. The return-walker advance is SPLIT across both delay
slots via a v1 temp:
```
a1=base; a3=a1+0x300; a2=a1
L: lw v0,0(a1); beq v0,key,found [v1=a2]        # COPY in beq-delay
   addiu a1,0x30; slt a1<a3; bne L [a2=v1+0x30] # ADD in bnez-delay
   return 0
found: return a2
```

## Best: rc5 (was rc7 parked) — SEED = soundDataAreaGet.c
```c
char *p=D_006A3070, *r=D_006A3070, *end=D_006A3070+0x300;
do { char *next = r + 0x30;            // pre-hoist (fills beq-delay)
     if (*(int*)p==key) goto found;
     p += 0x30; r = next; } while ((int)p < (int)end);
return 0; found: return r;
```
Registers ALL correct now: deref/biv=a1, return=a2, end=a3, shadow split
present. Only 5 bytes differ, ONE coupled root cause = **split direction**:
- ROM: `v1=a2` (COPY, beq-delay) then `a2=v1+0x30` (ADD, bnez-delay);
  base materialized into a1 (the biv) -> `daddu a2,a1`.
- built: `v1=a2+0x30` (ADD, beq-delay) then `a2=v1` (COPY, bnez-delay);
  base materialized into a2 (the accumulator r) -> `daddu a1,a2`.

Net-identical mirror image. The `next=r+0x30` pre-hoist is REQUIRED for the
shadow (and pushes biv to a1), but it forces ADD-first. To get ROM's
COPY-first, gcc would need a surviving copy `v1=r` before the branch — but
gcc copy-propagation ELIMINATES every standalone/double-use copy tried.

## This session's distinct hand hypotheses (all -> rc5 or worse):
- next=r+0x30 + goto-found out-of-line -> **rc5** (the seed; from rc7).
- snapshot cur=r;r=cur+0x30 (+r=p anchored) -> rc10 (cur coalesced, biv->v1).
- return cur (snapshot returned, scoped) -> rc10.
- save=r copy returned + plain r+=0x30 -> rc10 (copy coalesced).
- double-use a=r;b=a+0x30;return a;r=b -> rc5 identical (copy still folded).
- int-typed walkers -> rc5 identical.
- next from p / comma-in-while advance / plain r+=0x30 -> rc10 (no shadow;
  shadow needs next on the RETURNED walker r only).
- dual pre-hoist pn+rn -> rc18 (heavy pipeline).
- r=p tracking -> rc8.
- volatile/plain single-ptr return p, index for-loop return p -> rc12 (bnel
  pipeline; the dev did NOT write the naive single-ptr — needs 2 walkers).

## Verdict: split-direction is a copy-propagation-defeating delay-slot
scheduler tie — permuter-class (cf. func_001FB768 `if((new_var2=new_var)>=7)`,
func_00141048 reorg-tail, COOKBOOK §3.10 walking-ptr search-return).
Parked rc5 by USER DIRECTION (not a 30-stall). On resume: seed is rc5
(registers correct). Either fire the permuter on the rc5 seed (it cracks
exactly this copy-vs-add split tie), or find clean C yielding a SURVIVING
copy `v1=r` before the branch (assign-in-condition double-name forms — keep
hunting one gcc won't fold).
