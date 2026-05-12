/* src/cod/0652F8.c — func_001652F8 */

extern char D_002A4C48[];

int func_001652F8(int *a0)
{
    unsigned int *p = (unsigned int *)(D_002A4C48 + a0[2] * 0x4C);
    unsigned int field = p[0x48 / 4];
    unsigned int v0 = (field >> 18) & 1;
    if (v0 != 0) goto zero;
    v0 = (field >> 21) & 1;
    v0 = v0 ^ 1;
    if (v0 == 0) goto one;
zero:
    return 0;
one:
    return 1;
}
