/* _sprintf_r — parked near-miss (INCOMPLETE). Varargs command builder.
 * The `Rect261120` struct is NOT yet reconstructed — recover its field offsets
 * from the asm (r.idx@0, r.type@?, r.val, r.max/max2 = 0x7FFFFFFF, r.p) before
 * this will compile. func_00262D00 is a still-INCLUDE_ASM sibling. */
void _sprintf_r(int a0, int a1, int a2, int a3,
                   int a4, int a5, int a6, int a7) {
    Rect261120 r;
    long long sargs[5] __attribute__((aligned(8)));
    r.idx = a0;
    sargs[0] = a3;
    sargs[1] = a4;
    sargs[2] = a5;
    sargs[3] = a6;
    sargs[4] = a7;
    r.type = 0x208;
    r.val = a1;
    r.max2 = 0x7FFFFFFF;
    r.p = (void *)a1;
    r.max = 0x7FFFFFFF;
    func_00262D00(&r, (void *)a2, sargs, (void *)a3);
    *(char *)r.p = 0;
}
