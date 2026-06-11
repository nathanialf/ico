# gsb_Reduction (seki/src/GsBase) — parked at rc13 (stall=30 + permuter)

15-insn GS display-list writer. **CFG fully recovered**; residual is pure
regalloc/scheduling/addressing-folding within the correct control flow.

## Behaviour (from asm)
```
p = D_004C3850.cur                      # ptr field at +0x10
*p = (a0 ? 0x50000 : 0x30000)           # 8-byte (sd) store
cur = p+1 (store-back)
*(p+1) = 0x47
cur = p+2 (store-back)
```
Two 8-byte writes to the current GIF/packet pointer, each followed by advancing
and storing the pointer back to `D_004C3850+0x10`. `0x47` is likely a GS reg addr.

## Best seed (rc13)
```c
typedef struct { unsigned char pad[0x10]; unsigned long long *cur; } GsBaseRed;
extern GsBaseRed D_004C3850;
void gsb_Reduction(int a0) {
    unsigned long long *p = D_004C3850.cur;
    if (a0) { *p = 0x50000; } else { *p = 0x30000; }
    p++;
    *(unsigned long long *volatile *)&D_004C3850.cur = p;     // volatile WRITE keeps both store-backs
    *p = 0x47;
    *(unsigned long long *volatile *)&D_004C3850.cur = p + 1;
}
```

## What's solved
- **`sd` 8-byte stores**: `unsigned long long` (the TU's 64-bit idiom).
- **Two store-backs**: gcc dead-store-eliminates the first `cur=p`. Casting only
  the store-back WRITES to `volatile` (`*(ull *volatile *)&cur = p`) keeps both,
  while leaving the `cur` READ non-volatile so it stays schedulable.
- **The branch (not movn)**: value-in-reg (`v = a0?C1:C2`, or any if/else writing
  a register) ALWAYS gets ifcvt'd to `movn` by ee-gcc 2.9. Storing the constant
  THROUGH the pointer in each arm (`if(a0) *p=C1; else *p=C2;`) is the ONLY form
  that keeps the `beqz/b/lui` diamond — gcc can't cmove a memory destination, then
  store-sinks to one `sd` after the merge. Confirmed: ~6 value-in-reg variants
  (ternary, if/else int, if/else ull, goto-diamond, single-sided) all → movn.
- **`p+1` final advance** (vs `*p++`): lets gcc compute cur+16 before the last
  store, filling the jr delay (rc16→rc14).
- **Direct `D_004C3850.cur`** (vs cached `GsBaseRed *d`): rc14→rc13.

## The rc13 residual (one cascade)
ROM: value selected via branch INTO A REGISTER ($4, reusing the dead arg reg a0),
THEN `cur` loaded (lw) AFTER the branch, base `&D` kept in $3 with `0x10`
displacement (split `lui %hi` in the beq delay slot, `addiu %lo` after). Built:
memory-dest forces `cur` (lw) BEFORE/IN the branch delay (the arms need `p`), and
folds `+16` into `%hi/%lo(D+16)` (recomputed). **Root**: ROM's arms set a value
register; ours store. That requires value-in-reg-via-branch, which ee-gcc cmoves —
so cur can't be deferred past the branch by any clean source. Register numbers
(value $2 vs ROM $4, cur $5 vs $2, base $6 vs $3) also differ — the same dead-arg-
reg-reuse tiebreak as func_0024E510.

## Hypotheses tried (~30, all rc13–19) — stall=30
if/else memory-dest, ternary, goto-diamond, single-sided, cached-`d`, char*-base,
slot-ptr, array-view, p++/p+1/p[1]/++p/p2-temp store-backs, volatile field / write-
only / buffer-ptr, value as literal/5<<16/UL/named-const, unsigned/bool/==0 cond,
long long vs ull, (void)a0. WORSE: full-volatile-field → single `bne` (rc14);
volatile buffer ptr → rc15; goto/double-adv → rc19; value-in-reg → movn (rc13–14).

## Permuter
`permute_run.sh gsb_Reduction <seed> -- --stop-on-zero -j 4` fired at the 30-stall.

## Resume levers to try fresh
- Defeat the ifcvt cmove for value-in-reg (would unlock cur-after-branch + base+disp
  + dead-arg-reg reuse in one shot). Look for an arm shape ifcvt won't unify.
- Force the compare-constant value into $4 (dead arg reg) — func_0024E510-class tie.
- Make gcc keep `&D` base in one reg with split `%hi`(delay)/`%lo`(after-branch).
