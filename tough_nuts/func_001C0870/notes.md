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
