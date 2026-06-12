/* func_002490C0 — parked near-miss (rc12, improved from old bulk seed rc14).
 * Apply into common/src/PObj.c replacing the INCLUDE_ASM line.
 * Needs (declared before the func):
 *   extern int D_0054ABD0[]; extern char D_006289D8[];
 *   extern int D_0054ABF0[]; extern char D_0054BD90[];
 *
 * a0==0 branch is a single loop with two back-edges to `body` (the ROM outer
 * back-edge from func_00242B68 re-enters at the unconditional func_002484D0 call,
 * NOT the inner-while test) — the goto-CFG below captures that (a do/while form
 * gave rc14). Residual rc12 = LICM PLACEMENT + loop block layout: ROM hoists the
 * loop-invariant %hi of D_0054ABF0($s1) and D_0054BD90($s0) into the loop
 * preheader at .L002490EC (AFTER the func_001019E0 call) and uses `b` (beq
 * zero,zero) to enter the inner-while at its test (body-first layout). gcc instead
 * sinks `lui $s1` ahead of the call's `addiu a0` delay slot and lays the loop out
 * test-first (no `b`). Registers/structure otherwise correct. Open: force the
 * %hi hoist to stay in the preheader + body-first loop rotation. */
extern int D_0054ABD0[];
extern char D_006289D8[];
extern int D_0054ABF0[];
extern char D_0054BD90[];

int func_002490C0(int a0) {
    if (a0 == 0) {
        if (D_0054ABD0[0] > 0) {
            func_001019E0(D_006289D8);
        }
        goto test;
    body:
        func_002484D0(0x3C);
    test:
        if (D_0054ABF0[0] != 0) goto body;
        if (func_00242B68(D_0054BD90) != 0) goto body;
        return 0;
    }
    if (D_0054ABF0[0] != 0) {
        return 1;
    }
    if (func_00242B68(D_0054BD90)) {
        return 1;
    }
    return 0;
}
