# func_00254930 — PARKED near-miss rc8 (not permuter-run)

VRAM 0x00254930, common/src/PObj.c. Struct update + clamp + tail-call.
Struct (int* a0, cf. sibling func_002547A8): a0[0](ll)=0, a0[2]=base, a0[3]=cur,
a0[4]=0, a0[6](ll)=accumulator, a0[9]=limit, a0[0xA]=wrap.

## Shape (rc8 seed) — see func_00254930.c
v=(long long)(a1<<3)+a0[6]; sum=a0[2]+(int)((v<<29)>>32); a0[0]=0; a0[4]=0;
a0[6]=v; a0[3]=sum; if((unsigned)sum>=(unsigned)a0[9]) a0[3]=sum-a0[0xA];
tail-call func_00254800(a0,0) (void → sibcall j).
KEY FIXES already in: `(long long)(a1<<3)` not `(long long)a1<<3` → **sll** not
dsll (rc18→rc8); a0 stays in $7 across to the tail call.

## Residual rc8 (regalloc + scheduling)
- delta=(int)((v<<29)>>32) and limit=a0[9] land in SWAPPED regs: ROM delta=$4,
  limit=$3(v1); gcc delta=$3(v1), limit=$4. (a0 ptr is in $7/a3.)
- the `a0[6]=v` (sd v0,24) store: ROM schedules it LATE (after the sltu), gcc
  early. ~9 forms tried (delta temp, store reorders[C89!], sum-after-stores,
  signed/swapped cmp) — all rc8 or worse.

## RESUME
1-reg-pair delta/limit swap + 1 store-position. Likely one root (the v-store
timing pins the free-reg order). Try forcing the v-store after the compare, or a
ptr-to-array deref to flip delta/limit ($3/$4). NOTE: ee-gcc 2.9 is C89 — all
decls MUST be at the top of the block.
