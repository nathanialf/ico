# func_001C0870 (switch) — near-miss rc4, v0/v1 deref-temp swap

WORKING C (structure EXACT — beql + store-in-delay + jal + store-after, s0/s1 callee-saved):
  void func_001C0870(char *self_, int a1) {
      GObj *self = (GObj *)self_;
      Sub15C *sub = self->p_15C;
      Obj800 *p = sub->p_800;
      if (p->f_4 != a1) { func_001BC0A8(); }
      p->f_4 = a1;
  }
ONLY diff: v0/v1 swap. Expected sub(self->0x15C)->v0, p->f_4->v1; built sub->v1, p->f_4->v0.
Tried: inline deref, named sub/p, reversed cmp (a1!=p[1]), typed structs — all same swap.
Recurring v0/v1 deref-temp-vs-compared-value tie-break (same family as 165B50/E85D8/A0A8).
NEXT: force the compared value into v1 / the deref temp into v0; or permuter.

## 2026-05-31 (unsupervised) — DUP-STORE drops rc4->rc3
Duplicating the `p[1]=a1` store into both if/else arms (`if(p[1]!=a1){call();p[1]=a1;}
else{p[1]=a1;}`) removes one diff (rc4->rc3). Residual rc3 = the compared value
p[1] colors to v0 (gcc reuses v0 freed after the ->0x800 deref) vs ROM's v1, which
cascades into the beql operand + the delay-slot store using the reused v0 instead
of s1. 3 dup-store combos (named-cur, sub-ptr, eq-first) all rc3. Pure v0/v1
deref-temp coloring floor (family of 165B50/E85D8). Seed = dup-store rc3 for permuter.

## 2026-05-31 (unsupervised, exhaustive) — rc3 floor; permuter ZERO improvement
40+ hand forms (incl dup-store rc4->rc3) + a 15-min permuter run (dup-store seed,
68k iterations) found ZERO improvement over base score 15 — a strict local minimum
for the permuter's mutation operators. Residual rc3 = v0/v1 deref-temp coloring:
compared p[1] reuses the freed v0; ROM uses v1. Required the retired REG("$3") pin.
Genuine clean-C floor under no-pin/no-inline-asm constraints. Seed = clean dup-store
rc3 for the long offline auto_permute. See [[permuter_at_30stall_cracks_floors]].
