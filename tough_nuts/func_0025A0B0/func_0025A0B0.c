/* func_0025A0B0 — parked near-miss (rc16). Apply replacing the INCLUDE_ASM line.
 * func_00254FF8 / func_00255580 are still-INCLUDE_ASM siblings; no D_ externs.
 * Residual rc16 = dense load scheduling: ROM interleaves the s0[]-field loads
 * with the bit-pack ops in a specific order this flat form doesn't reproduce. */
int func_0025A0B0(unsigned char *a0) {
    unsigned char *s0 = a0;
    unsigned int t2, a1, t0, t1, v0, a2, v1, a3, a0m;
    func_00254FF8();
    t2 = *(unsigned int *)(s0 + 12);
    a0m = 0xFF0000;
    t0 = 0xFF0000;
    a1 = s0[0];
    t1 = t2 >> 8;
    v0 = *(unsigned int *)(s0 + 4);
    t0 |= 0xFFFF;
    a2 = *(unsigned int *)(s0 + 0x10);
    a1 <<= 24;
    v1 = *(unsigned int *)(s0 + 0x14);
    v0 &= a0m;
    a3 = *(unsigned int *)(s0 + 8);
    a0m = a2 & 0xFF0000;
    a1 |= v0;
    v1 &= 0xFF00;
    a0m >>= 16;
    a1 |= v1;
    a3 &= t0;
    t1 &= 0xFFFF;
    t2 <<= 24;
    a2 <<= 16;
    a1 |= a0m;
    a2 |= t1;
    a3 = t2 | a3;
    func_00255580(0x3E, a1, a2, a3);
    return 0;
}
