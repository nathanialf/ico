# func_0013A820 (pad) — near-miss rc3, arg-setup scratch-copy

WORKING C (hw-reg bit, gp globals, scheduling all EXACT — store in jal delay, dsrl 13):
  int func_0013A820(int a0) {
      if (a0 == 2) {
          int *p = (int *)D_00632108;
          unsigned long bit = (*(volatile unsigned long long *)0x12001000 >> 13) & 1;  // keep 64-bit -> dsrl (not dsll/dsra32)
          D_00631950 = bit ^ 1;
          func_00100F18(p[0x30/4], p);
      }
      return 0;
  }
ONLY diff: p (=D_00632108) goes to a2 + `daddu a1,a2` copy + `lw a0,48(a2)`; expected loads p->a1
directly and `lw a0,48(a1)` (no copy). p is BOTH the 2nd arg (a1) and the base for arg1 (a0=p->0x30);
gcc distributes via scratch a2, dev keeps it in a1.
Tried: inline deref, named p, x-first (worse), int* __asm__ alias — all keep the a2->a1 copy.
Levers that WORKED: 64-bit `unsigned long bit` (avoids dsll/dsra32 canon, COOKBOOK bit-test);
  named p (got store into jal delay). NEXT: force the 2nd-arg pointer into a1 directly (no scratch).
