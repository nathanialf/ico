/* func_00257380 — parked near-miss (rc8). Apply replacing the INCLUDE_ASM line.
 * func_00255060 is a still-INCLUDE_ASM sibling; no D_ externs needed.
 *
 * Residual rc8 = a single base/value register swap that cascades through all 3
 * stores. ROM puts `base` (= p[8] + (idx<<4), recomputed per store) in $a0 (the
 * freed param reg) and the first store's value v2[1] in $a1; built reverses them
 * (base->$a1, v2[1]->$a0). Source order of v2 vs base, and inlining the v2 deref,
 * do NOT move it (gcc deterministically reuses $a0 for the value, not the base).
 * Open: force `base` to reuse the freed $a0 (param a0 is saved to $s0 at entry,
 * so $a0 is free) — none of the obvious decl/order reshapes flip the tie. */
void func_00257380(int *a0) {
    int *p;
    unsigned short idx;
    char *base;
    char *v2;
    if (*(a0 + 0) & 2) {
        p = (int *)func_00255060();
        idx = *(unsigned short *)((char *)a0 + 0x4E);
        v2 = (char *)(*(int *)((char *)p + 0x10));
        base = (char *)(*(int *)((char *)p + 8)) + (idx << 4);
        *(base + 0x12) = *(unsigned char *)(v2 + 1);
        idx = *(unsigned short *)((char *)a0 + 0x4E);
        base = (char *)(*(int *)((char *)p + 8)) + (idx << 4);
        *(base + 0x1A) = 0x40;
        idx = *(unsigned short *)((char *)a0 + 0x4E);
        base = (char *)(*(int *)((char *)p + 8)) + (idx << 4);
        *(base + 0x1B) = 0x40;
    }
    *(a0 + 1) += 2;
}
