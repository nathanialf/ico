/* func_0024B010 — parked near-miss (rc11, improved from old bulk seed rc19).
 * Apply into common/src/PObj.c replacing the INCLUDE_ASM line.
 * D_007115C0/D_00711280 already declared in TU (func_0024A538 region);
 * func_0024AA38 is a still-INCLUDE_ASM sibling.
 *
 * Residual rc11 = a register-NUMBER cascade: ROM puts the D_007115C0 %hi temp in
 * $v1 (shared by the `D_007115C0[0]=8` store and the `s0 = base` addiu), built
 * puts it in $a3, shifting dest ($a3->$t0) and the rest by one. Pure regalloc
 * tie; structure/loop are byte-correct. The explicit `dst = (char*)s0 + 0xC`
 * (vs `((char*)s0)[0xC+i]`) dropped 19->11 by precomputing the copy base.
 * Tried (no change): dst before vs after the s0[1]/s0[2] stores; s0[0]=8 vs
 * D_007115C0[0]=8 (identical codegen). Open: bias the %hi temp into $v1. */
int func_0024B010(int a0, int a1, char *a2) {
    int *s0 = D_007115C0;
    int i;
    int val;
    int ret;
    char *dst;
    D_007115C0[0] = 8;
    s0[1] = a0;
    s0[2] = a1;
    dst = (char *)s0 + 0xC;
    for (i = 0; i < 6; i++) {
        dst[i] = a2[i];
    }
    ret = func_00242978(D_00711280, 1, 0, D_007115C0, 0x80, D_007115C0, 0x80, 0, 0);
    if (ret < 0) {
        return 0;
    }
    val = s0[5];
    if (val == 1) {
        func_0024AA38(a0, a1, 2);
        val = s0[5];
    }
    return val;
}
