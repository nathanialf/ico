/* func_0025CD78 — isNaN(float): (0x7F800000 - (bits & 0x7FFFFFFF)) >> 31.
 * STRUCTURE RECOVERED. Residual: pure a0<->v1 regalloc swap (rc7, 1 root cause).
 * The ROM puts mfc1 -> $3(v1), copies to v0, mask in a0, inf in v1(reuse).
 * This compound-accumulator form gives the identical data flow but mfc1 -> $4(a0)
 * with mask/inf swapped accordingly. ~24 distinct 32-bit source forms tried; int
 * read always allocates bits to a0 once any computation follows (only `return u.i`
 * and a 64-bit `long` read reach v1, the latter dragging in dsubu/dsll 64-bit ops).
 * NEXT: this is the permuter's wheelhouse (v0/v1/a0 swap) — fire the Step-4 shot on
 * resume; or find the source form that seeds mfc1 into v1 with 32-bit arithmetic. */
int func_0025CD78(float x) {
    union { float f; int i; } u;
    int r;
    u.f = x;
    r = u.i;
    r &= 0x7FFFFFFF;
    r = 0x7F800000 - r;
    return (unsigned)r >> 31;
}
