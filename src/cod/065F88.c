extern char D_002A4C48[];

int func_00165F88(int *a0)
{
    int *p = (int *)(D_002A4C48 + a0[2] * 0x4C);
    return (((unsigned int)p[0x48 / 4] >> 21) & 1) ^ 1;
}
