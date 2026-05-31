# func_001D9C58 (motionManager) — near-miss rc5, v0/v1 swap on global ptr

WORKING C (everything EXACT except 1 register; idiom from matched sibling func_001DC938):
  void func_001D9C58(void) {
      int v = func_00105278();
      func_00118678(v);
      { float *p = (float *)D_00633F3C;
        func_00105308(p[0], p[1] + p[0x1D0/4] + 10.0f, p[2]); }  // 10.0f -> lui 0x4120;mtc1 (immediate)
      func_0010DF70((char *)D_00633F3C + 0x30);
      func_001D9890();   // void tail call (j)
  }
Matched: both calls, the daddu a0,v0 (func_00118678 arg = func_00105278 ret), FP add order
(p[1]+p[1D0]+10.0), the SECOND fresh D_00633F3C load for func_0010DF70, the void tail-call j.
ONLY diff: the global pointer p (D_00633F3C) lands in v1 (built) vs v0 (expected) -> cascades to 5
lwc1 lines. Recurring v0/v1 deref/global tie-break.
ROOT: the matched sibling func_001DC938 gets p->v0 because it has an EXTRA LEADING call (func_00104F20)
before func_00105278; this func has func_00105278 as the FIRST call, so the allocation differs.
Tried: register p, plain p, nested vs separate-v call. NEXT: force p into v0 after the calls; or permuter.
