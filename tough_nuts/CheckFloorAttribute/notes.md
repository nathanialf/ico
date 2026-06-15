# CheckFloorAttribute (sugipon/src/motionManager2) — RESUME

Best: **rc3** (seed `CheckFloorAttribute.c`). Permuter (2026-06-15) improved rc4→rc3
via the **multiplier-as-variable** lever: `int mul = 8; sp = (float*)((src + idx*mul)
+ 0x10);` — holding the `8` in a variable fixes the address-op ordering (the `addu
src` lands right). The 3 remaining diffs are ALL the dead guard2 (missing `beq $3`,
a nop in its place, the `addu` that belongs in its delay).

PREVIOUS best rc4 (goto-ret0-last + do-while, literal `*8`).

## What it is (recovered)
```c
int CheckFloorAttribute(float *dst, void *a1) {
    unsigned char *src = a1;
    if ((signed char)src[1] != 0) return 0;       // bnez -> ret0
    int count = src[3];                            // lbu count
    if (count == 0) return 0;                      // guard1 beqz -> ret0
    float *sp = (float*)(src + src[2]*8 + 0x10);   // lbu*8 +0x10 +src
    // ROM redundant ENTRY guard (DEAD - count!=0 already proven):
    if (count == 0) return 1;                      // guard2 beqz -> ret1, addu in delay
    do { *dst++ = *sp++; } while (--count);        // bnez loop
    return 1;
}
```
ROM layout: loop, **ret1 (L0010A0EC)**, then **ret0 (L0010A0F4)** LAST.

## THE residual (rc4, the blocker)
ROM emits **TWO** `beqz $3` count guards:
- A0B8 `beqz $3 -> ret0` (guard1, `if(count==0)return 0`)
- A0C8 `beqz $3 -> ret1` (guard2 = loop-inversion ENTRY guard, **provably dead**:
  after guard1 didn't branch, $3!=0, so A0C8 never branches), with `addu $2,$5,$2`
  (sp=src+off) in its delay slot.

gcc 2.9 **unconditionally DCEs the dead guard2** in every clean-C shape (it proves
count!=0 from guard1). The 4 diffs = missing-beq + missing-addu-in-delay (the dead
guard) + a consequent extra nop + addu-placed-early.

## Exhaustively confirmed (31-hyp stall, 2026-06-15)
ALL fold to rc4 (guard2 removed) or worse — none retains the dead guard:
- nested-if while (rc4), goto-ret0-last + do-while (rc4, BEST: correct ret layout)
- linear `if(count==0)return0; while` (rc8: guard1->bnel, ret0 inline early)
- explicit `if(count==0)return1` + do-while (rc8: guard2 DCE'd)
- static-inline helper holding loop+entry-guard (rc8: inlined+DCE'd)
- separate ret1/ret0 bottom labels + explicit guard2 goto (rc4: DCE'd)
- for-loop, while-test-first, two-var-count (n=count), ptr-end loop, idx-loop
- offset forms: int-var(rc5), shift `<<3`, paren, `&((float*)(src+0x10))[i*2]`
- count types: int/uint/short(rc25)/uchar; body schedules; src char* vs uchar*

The offset/loop bytes are ALREADY byte-correct; ONLY the dead inversion-guard is
missing. **rc4 is the clean-C floor.**

## Why permuter-class (= func_001FB768 pattern) — DEFINITIVELY PROVEN
Retaining the provably-dead inversion guard needs count's value-range to be UNKNOWN
at the while-entry. DECISIVE TEST: `volatile int *kp=&count; while(*kp!=0)` DOES
retain guard2 (`count-beq=2`, both beqz present) — proving the mechanism — but it
spills count to the stack and reloads it (`sw`/`lw`) every iteration; ROM keeps
count in `$3` register throughout (no spill, no reload). So range-breaking via
memory is correct-but-non-matching.

Every REGISTER-ONLY clean-C shape lets gcc prove count!=0 (from guard1) and DCE the
dead guard. Hand levers exhaustively tried & ALL give `beq-guards=1` (guard2 gone),
verified by direct cc1 -S inspection (2026-06-15):
- loop structures: do-while, while, for(;count;), for(;;){if(!c)break}, while(1)
  {if(!c)break}, goto-test, goto-loop, ptr-end
- guard placements: nested-if, linear, goto-ret0-last, explicit if(c==0)return1,
  separate ret1/ret0 labels, `||` compound guard1
- BB boundaries: `do{}while(0)` around offset / loop / count-load / guard1 (4×)
- inline helper: while-body AND explicit-early-return body (inliner re-DCEs it)
- assign-in-condition (func_001FB768 hand lever): `if((count=src[3])==0)`,
  `while((n=count)!=0)`, `for(count=src[3];...)`, `if((count=count)==0)`
- offset orders, count types, body schedules

The register-keeping retention is exactly the permuter's `new_var` assigned-in-
condition (func_001FB768 rc7->0 kept values in regs via a copy gcc's range pass
couldn't see through). Hand C cannot manufacture an optimizer-opaque register value
here (count|0, +0, *1, copies, two-reads, assign-in-cond all fold). LEVER = permuter.

## Permuter run 1 result (2026-06-15)
~460 iters, base score 260 (=rc4). Best harvest = output-260-1 → **true rc3** (scores
were tied-260 but anti-correlated with real_count, per the playbook). Adopted as seed.
The permuter's `new_var=8` only touched the MULTIPLIER, not the guard — so guard2 is
STILL the residual. A future run should seed THIS rc3 and target the count guard
(it needs a register-keeping `new_var` copy of count in the guard, func_001FB768-style).

## On resume after permuter
If permuter found a `new_var`/assigned-in-condition form that retains guard2,
re-apply it cleanly by hand. Seed permuter with THIS rc4 (correct ret layout +
byte-correct offset/loop; only needs guard2 retention).

Differ note: this TU's asm-differ misaligns on delay-slot fills; confirm with
`ninja` (build/.../motionManager2.o), not the match_loop scratch .o.
