# gsb_Reduction (seki/src/GsBase) — RESUMED rc13 -> rc6 (2026-06-11)

15-insn GS display-list writer. **CFG + regalloc fully recovered.** Residual
is TWO coupled reorg/sched ties (see below). Was parked rc13; this session
cracked rc13->11->8->7 (param-reuse + volatile-tail-order), then the permuter
found rc7->rc6.

## rc7 -> rc6 (permuter, output-425-1, 2nd stall)
Make the FIRST data store volatile too: `*(volatile ull*)p = a0` (not just the
0x47 store). This groups the base `lui v1 / addiu v1` together (in rc7 the
`li a1,0x47` split them). Current best.c / seed = this rc6 form.
NOTE the permuter's rc4/rc5 outputs are DEGENERATE (dead-conditional: store
0x30000 unconditionally / a0=0x50000 unconditional) — the "improve by deleting
real code" trap; rc6 (425-1) is the lowest LEGIT output. Re-stalled 30 from rc6
(another ~26 distinct forms, none < rc6); permuter re-fired from the rc6 seed.
Residual rc6 diffs = branch region (bnez-collapse vs beqz+b+base-hi-delay
diamond) + missing store-back-1 (still DSE'd). Same two coupled ties as rc7.

## Behaviour (from asm)
```
value = a0 ? 0x50000 : 0x30000     # branch INTO $4 (dead arg reg), single luis
*cur = value                        # sd $4
cur += 1 (8 bytes); commit cur      # sw $2  (store-back 1)
*cur = 0x47                         # sd $5
cur += 1; commit cur                # sw $4  (store-back 2, in jr delay)
```
`cur` = ptr field at D_004C3850+0x10 (32-bit ptr -> store-back is `sw`).
Data writes are 8-byte `sd`. Two committed advances of cur.

## Best seed (rc7) — current best.c
```c
typedef struct { unsigned char pad[0x10]; unsigned long long *cur; } GsBaseRed;
extern GsBaseRed D_004C3850;
void gsb_Reduction(int a0) {
    unsigned long long *p;
    if (a0) { a0 = 0x50000; } else { a0 = 0x30000; }   // param-reuse -> value in $4
    p = D_004C3850.cur;
    *p = a0;
    p++;
    D_004C3850.cur = p;
    *(volatile unsigned long long *)p = 0x47;            // volatile pins tail order
    D_004C3850.cur = p + 1;
}
```
NOTE: rc7 has PERFECT regalloc (value=$4, base=$3/v1, cur=$2/v0, 0x47=$5/a1)
but is MISSING store-back-1 (gcc DSEs it; only 1 sw emitted). A true match
needs BOTH store-backs -> the structurally-complete seed is combo C/B (rc8,
sb1 volatile). Permuter should seed from the rc8 (sb1-present) form.

## Cracks this session (the wins)
- **param-reuse `a0 = const` in both arms** (rc13->11): puts value in $4 (dead
  arg reg) AND defeats movn-ifcvt (movn would clobber the condition reg a0).
  Gave the PERFECT register allocation. Old note "value-in-reg always -> movn"
  was true ONLY without param-reuse.
- **`*(volatile ull*)p = 0x47`** (rc11->8): the non-volatile 0x47 store was being
  hoisted DOWN past the store-backs. Making it volatile PINS source order -> the
  whole tail body now matches ROM exactly.
- **plain store-backs** (rc8->7): with volatile 0x47 as a barrier, plain
  store-backs let reorg fill the jr delay with store-back-2 — BUT gcc then DSEs
  store-back-1. rc7 = jr-delay-filled but sb1 gone.

## The rc7 residual = TWO coupled ties (permuter-class)

### Tie 1: branch DIAMOND vs value-in-$4 (mutually exclusive by hand)
- param-reuse (`a0=const`): value stays in $4 (perfect regalloc) BUT reorg
  COLLAPSES the if/else to a 2-insn `bnez`+delay (no `b`, no base-hi in beqz
  delay). ROM has the diamond: `beqz [delay: lui %hi(D)]; b [delay: lui then];
  else; merge`.
- memory-dest (`*p=const` in arms): PREVENTS collapse -> DIAMOND + base-%hi
  pre-branch — but value -> v0 (not $4) and cur loads in beqz delay (early). rc13.
- hybrid (`a0=const; *p=a0` in arms): gcc drops the dead a0-assign -> value to v0.
  rc14.
- ANY &D reference before the branch (cached `d=&D`, cur-before-branch, early
  const) -> full `la` pre-branch + value out of $4. rc12-18.
- => value-in-$4 (needs single post-merge `*p=a0`, which collapses) XOR diamond
  (needs memory-dest, which frees value to v0). ROM has BOTH. Coupled.

### Tie 2: store-back-1 survival vs store-back-2-in-jr-delay
- sb1 needs anti-DSE: only volatile keeps it (plain -> gcc proves *p !alias
  &D.cur, DSEs it; *p++ fuses both; reading cur back fuses via value-numbering).
- but volatile sb2 can NOT enter the jr delay (combo B: nop). plain sb2 -> reorg
  fills delay BUT either reorders before 0x47 (combo C) or sb1 DSE'd (combo D).
- ROM: sb1 kept AND sb2 plain-in-delay. Not hand-reproducible.

## Volatile-combo map (all tried)
- A (sb1 vol, 0x47 plain, sb2 vol): rc11, 0x47 -> jr delay.
- B (all vol): rc8, CORRECT order, sb2 not in delay (nop).
- C (sb1 vol, 0x47 vol, sb2 plain): rc8, sb2 reordered before 0x47, nop delay.
- D / fully-plain: rc7, sb1 DSE'd, sb2 in delay. **best count**
- G (sb1 vol, 0x47 plain, sb2 plain): rc11.

## Resume levers to try fresh (next session)
- Tie 1 is the func_0024E510 / func_001FB768-class dead-arg-reg + diamond tie:
  permuter found `if((new_var2=new_var)>=7)` for a sibling — look for a
  condition-embedded assignment forcing value-in-$4 WITHOUT a post-merge single
  store. SEED permuter from combo C (rc8, sb1 present = structurally complete).
- Tie 2: a may-alias trick making the 0x47 store provably-alias &D.cur to block
  sb1 DSE while keeping stores plain (sd-vs-sw size mismatch blocks the naive
  same-type cast).

## Permuter
Fire at the genuine stall=30 gate, seeded from the combo-C rc8 form.
