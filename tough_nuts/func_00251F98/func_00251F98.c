/* func_00251F98 — parked near-miss (rc2). Apply replacing the INCLUDE_ASM line.
 * No external decls needed (all params).
 *
 * Residual rc2 = an operator-association tie in the a2>0 branch. ROM groups
 *   base = (base + 1) + (((a2-1)<<a1) + a3)
 * i.e. `addiu base,1` early and `addu shift,a3` then `addu base,(shift+a3)`.
 * The flat `base + 1 + ((a2-1)<<a1) + a3` reassociates to (base+a3)+(shift+1)
 * — the +1 and +a3 land on the wrong sub-terms (rc2). EVERY reshape that forces
 * the grouping (explicit parens, a `sh` temp, split statements, operand reorder)
 * regresses to rc23-44 because it drops the `int *ptr=a0` save (ROM keeps the
 * pointer in $t2/daddu t2,a0; the reshapes make gcc reload *a0 directly). Open:
 * force the (base+1)+(shift+a3) grouping WITHOUT perturbing the ptr-save alloc. */
void func_00251F98(int *a0, int a1, int a2, int a3, int a4) {
    int limit, base, delta;
    int *ptr = a0;
    limit = 16 << a1;
    base = *ptr;
    if (a4) base = base >> 1;
    if (a2 > 0) {
        base = base + 1 + ((a2 - 1) << a1) + a3;
        if (base >= limit) base = base - (limit << 1);
    } else if (a2 < 0) {
        base = base - 1;
        delta = (~a2 << a1) + a3;
        base = base - delta;
        if (base < -limit) base = base + (limit << 1);
    }
    *ptr = a4 ? base << 1 : base;
}
