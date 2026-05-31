# func_001E85D8 (particleEffect) — near-miss rc4, dead-arg-reuse stride/base swap

WORKING C (rc4, ONLY a 1-reg swap on stride-const vs table-base):
  extern char D_007097F0[]; extern void func_001E73A8(int *p);
  struct E24_pe { char pad[0x14]; int *f14; };   // stride 0x18
  void func_001E85D8(int a0, float f) {
      int *p;
      if (a0 < 0) return;
      p = ((struct E24_pe *)D_007097F0)[a0].f14;   // folds +0x14 into the lw
      p[0x38/4] = 1;
      *(float *)((char *)p + 0x3C) = f;
      func_001E73A8(p);     // 1-arg keeps f12 for the void tail-call (j)
  }
Everything EXACT except: expected reuses the dead index arg-reg a0 for the stride const 24
(`addiu a0,zero,24` in bltz delay; base->v1), built puts stride->v1, base->a0 (+ commutative addu swap).
Tried: arr-first decl -> WORSE (hoists base above bltz). Same dead-arg-reuse tie-break as 165B50/B2F0/A0A8.
NEXT: force stride const to reuse a0 / base to v1; or permuter.

## 2026-05-31 (unsupervised) — rc4 pure-coloring floor re-confirmed
5 clean forms (struct-array, explicit-mult, prod-first, prod-first-inline,
idx*24-paren) all rc4-5. Same EMISSION ORDER as ROM (addiu stride; lui base;
mult; addu) — ONLY the a0/v1 coloring is swapped: ROM stride-const→a0 (reuse dead
idx arg) + base→v1; gcc stride→v1 + base→a0. Pure allocator coloring tie-break,
no branch-structure lever (unlike [[dup_store_into_branches]] which cracked the
related 165B50). Seed = clean struct-array (no retired ADDU_RS/KEEP_LIVE pins).
Offline auto_permute / pin candidate. Same dead-arg-reuse class as 165B50/B2F0/A0A8.
