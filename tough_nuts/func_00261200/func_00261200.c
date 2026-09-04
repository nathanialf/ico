/* sscanf — parked near-miss (rc7, de-crutched). Apply replacing the
 * INCLUDE_ASM line. D_0054D504 already declared in TU; strlen /
 * func_002611F8 / __svfscanf are still-INCLUDE_ASM siblings. Varargs.
 *
 * The old bulk seed pinned `register int s0 __asm__("$16")` (a crutch the diff
 * rejects). Clean `int s0 = a1;` lives in $16 naturally but rc7 = a prologue
 * scheduling tie: ROM emits `daddu s0,a1` 3rd (right after `li v1,4`, before the
 * stores/`sd ra`), gcc sinks it past the `sw v0,16(sp)` / `sd ra`. a1 must be
 * saved to a callee-saved reg before the strlen call (a1=$5 is clobbered);
 * the WHEN is the open question. Open: force the a1->s0 copy early w/o the pin. */
extern int D_0054D504[];
extern int strlen(int);
extern void func_002611F8();
extern void __svfscanf();

void sscanf(int a0, int a1, ...) {
    int buf[22];
    int r;
    int s0 = a1;
    *(short *)((char *)buf + 0xC) = 4;
    buf[0] = a0;
    buf[4] = a0;
    r = strlen(a0);
    buf[1] = r;
    buf[5] = r;
    buf[8] = (int)&func_002611F8;
    buf[21] = D_0054D504[0];
    buf[12] = 0;
    buf[17] = 0;
    __svfscanf(buf, s0, (char *)__builtin_next_arg(a1) - 6*8);
}
