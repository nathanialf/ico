extern char D_002A4C48[];

int func_001652D0(int *a0)
{
    int *p = (int *)(D_002A4C48 + a0[2] * 0x4C);
    return ((unsigned int)p[0x48 / 4] >> 18) & 1;
}
