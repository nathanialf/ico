/* func_00269950 — parked near-miss (rc2). Apply replacing the INCLUDE_ASM line.
 * func_0026B058 / func_0026AE80 are defined later in the same TU (int-returning).
 *
 * Residual rc2 = §5.11 return canonicalization: ROM sign-extends the int return
 * of func_0026AE80 to 64-bit (`dsll32 v0,0`/`dsra32 v0,0`) across the saved-reg
 * epilogue; the build trusts the callee's int result and omits it. int-temp form
 * `int r = func_0026AE80(...); return r;` does not add it. Permuter-class per
 * [[feedback_s511_low32_canon_permuter_recipe]] — left for a permuter pass. */
int func_00269950(void *a0, int a1, int a2) {
    unsigned short flag = *(unsigned short *)((char *)a0 + 0xC);
    if (flag & 0x100) {
        func_0026B058((int *)*(int *)((char *)a0 + 0x54), *(short *)((char *)a0 + 0xE), 0, 2);
    }
    flag = *(unsigned short *)((char *)a0 + 0xC) & 0xEFFF;
    *(unsigned short *)((char *)a0 + 0xC) = flag;
    return func_0026AE80((int *)*(int *)((char *)a0 + 0x54), *(short *)((char *)a0 + 0xE), a1, a2);
}
