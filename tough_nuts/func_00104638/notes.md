# func_00104638 (geometryManager) — near-miss, 3-iter FP clamp loop, f0/f1 reg-swap

WORKING C (max hoisted, loop structure mostly correct):
  int func_00104638(float *a0, int *a1) {
      int ret = 0; int i;
      float max = D_00630904;                 // HOIST: local var forces lwc1 f2 before loop
      for (i = 2; i >= 0; i--) {              // count-down bgez
          float v = *a0;
          if (v < max) { *a0 = max; ret = 1; *a1 = 0; }
          else if (D_00630908 < v) { *a0 = D_00630908; ret = 1; *a1 = 0; }
          a1++; a0++;
      }
      return ret;
  }
Matched: max hoist (f2 before loop), counter, the clamp stores, a1/a0 advance, ret=1, sw 0(a1).
DIFF: FP reg-swap — expected *a0->f0, min->f1; built *a0->f1, min->f0 (c.lt.s operands swapped).
Plus built loads min in the bc1f delay (speculative) vs expected in the else branch.
WORKED levers: `float max = D_X;` local HOISTS the loop-invariant (despite fp-licm caveat — ROM has it).
Tried: inline *a0, named v — f0/f1 swap persists. Recurring reg-swap family (cousin of v0/v1, dead-arg-reuse);
clean lever elusive (retired §2.6 FP pin would fix). NEXT: permuter, or force *a0 into f0.
