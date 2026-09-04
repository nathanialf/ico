/* __muldi3 — PARKED near-miss rc15. Low-64-bits of a 64x64 multiply,
 * i.e. inlined __muldi3 using EE dual multiply pipes (mult + mult1 + multu).
 * `return a0 * a1;` (long long) CALLS __muldi3 (jal) instead of inlining → rc23.
 * Explicit schoolbook decomposition below = rc15 (right ops, wrong reg/sched). */
long long __muldi3(long long a0, long long a1) {
    int al = (int)a0, ah = (int)(a0 >> 32);
    int bl = (int)a1, bh = (int)(a1 >> 32);
    unsigned long long lolo = (unsigned long long)(unsigned int)al * (unsigned int)bl;
    int cross = al * bh + ah * bl;
    return (long long)((lolo & 0xFFFFFFFF) |
        ((unsigned long long)((unsigned int)(lolo >> 32) + cross) << 32));
}
