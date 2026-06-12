/* func_002699D0 — parked near-miss (rc9). Apply replacing the INCLUDE_ASM line.
 * func_0026B058 is defined later in the same TU (int-returning).
 *
 * Structure + §5.11 canon (`long long rl; rl = r; a0[0x50] = (int)rl`) are
 * byte-correct. Residual rc9 = a regalloc swap that cascades: ROM moves the
 * func_0026B058 result into the freed $a0 param reg ($4) for `r` and keeps $v0
 * for `f` (the a0[0xC] flag, loaded in the bne delay slot); the build keeps r in
 * $v0 and f in $v1, and swaps the sw-0x50 / ori-0x1000 order. Open: force `r` to
 * reuse $a0 (a0 is saved to $s0 at entry, so $4 is free) — cf.
 * [[feedback_param_reuse_dead_arg_reg]]. */
int func_002699D0(char *a0, int a1, int a2) {
    int r;
    unsigned short f;
    long long rl;
    r = func_0026B058((int *)*(int *)(a0 + 0x54), *(short *)(a0 + 0xE), a1, a2);
    f = *(unsigned short *)(a0 + 0xC);
    if (r == -1) {
        f &= 0xEFFF;
    } else {
        rl = r;
        *(int *)(a0 + 0x50) = (int)rl;
        f |= 0x1000;
    }
    *(short *)(a0 + 0xC) = f;
    return r;
}
