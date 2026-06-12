/* func_0023FB60 — improved seed, rc2 (was rc12 in old bulk-campaign seed).
 * Apply into common/src/PObj.c replacing the INCLUDE_ASM line.
 * Residual rc2: a single scheduler micro-tie — gcc schedules the branch
 * condition `sll a3,a3,0x10` ONE slot early (before `dsll v0,a2,4` = hi=da2<<4);
 * ROM defers the branch-condition `sll` to be adjacent to `beqz` (hi computed
 * first). Everything else is byte-identical. */
void func_0023FB60(void *a0, short a1, short a2, short a3) {
    unsigned long long v = *(unsigned long long *)((char *)a0 + 0x30);
    int h = (v >> 48) & 0x7FF;
    int w = (v >> 16) & 0x7FF;
    long long da2 = (long long)a2 - ((unsigned long long)(h + 1) >> 1);
    long long da1 = (long long)a1 - ((unsigned long long)(w + 1) >> 1);
    long long hi = da2 << 4;
    long long lo = da1 << 4;
    if (a3) {
        hi = (hi + 8) << 32;
    } else {
        hi = da2 << 36;
    }
    *(long long *)((char *)a0 + 0x20) = lo | hi;
}
