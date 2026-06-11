# func_00137E00 (fumi/ios/mcdata) — parked rc2 (b), twin of func_00137DB8 (writes 9)

BREAKTHROUGH for the mcdata family: a do{}while(0) around the store-value setup
CRACKS the -2 coalescing (rc3 -> rc2). Seed:
```c
int func_00137E00(void *a0) {
    McHdr *h, *hp; int v;
    h = (McHdr *)a0;
    do { v = 9; hp = h; } while (0);   // BB-split -> -2 reused in a3
    hp->w[1] = v;
    h->ll &= -2;
    return iosMsgSend(D_0027D308, a0, 0, -2);
}
```
The permuter found this (output-60-1, legit; output-10-1 was the UB form, rejected).
rc2 residual: the `a1 = a0` copy (iosMsgSend 2nd arg) position — ROM schedules it
BEFORE the `ld` (h->ll); gcc schedules it AFTER. ~25 hand forms (h/hp arg, decl
order, do-while placements, *(ll*)h, arg-var) all rc2; permuter found only rc2.
A1-position is a scheduling tiebreak (the new floor).

APPLY TO TWINS func_00137DB8 / func_00137ED8 / func_00137F20 / _iosMcIconWriteIconsys:
the do-while(0) form gets them rc3 -> rc2 too (on resume, re-attack from this seed).
