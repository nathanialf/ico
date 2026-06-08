# ChaseCamera — fresh, rc12 loop register-coloring/layout

VRAM 0x00184E68. `sum=0; i=0; if(a1>0){f38=a0[0x38];f3C=a0[0x3C]; do{sum+=f3C-f38;
i++;}while(i<a1);} return sum;` (= a1*(f3C-f38) via a loop).
Residual rc12: register coloring differs. ROM: f38->a3, f3C->a0(reused ptr arg),
i->t0, sum->a2; subu/loop body INSIDE .L80. gcc: fields->v0/v1, i->a3, and the
differ shows the body "peeled" before the loop (likely a coloring-driven layout
misalign, not a real peel). ~28 forms (decl order, for/while/do, char-off,
char*/q-ptr, diff-hoist, induction/cmp variants) all rc12. Register-alloc-order +
loop-layout — permuter target. Want f38 in a3 + f3C reusing a0.
## Fire 10: fresh; rc12 loop register-coloring (i->t0 vs a3, fields->a3/a0 vs v0/v1); ~30 forms + 90s permuter (best new_var-0 form still rc12) no rc0. (b)
## Fire 12: BREAKTHROUGH rc12->rc6 via two-step `sum = sum + f3C - f38` (left-to-right, f3C-first decl) — fixes field coloring to a0/a3. Residual rc6 = sum/i/temp regalloc (ROM diff->v1-temp,sum->a2,i->t0 vs built sum->v1,i->a2). 100s permuter from rc6 seed no rc0. Seed updated to rc6 form. (b)
