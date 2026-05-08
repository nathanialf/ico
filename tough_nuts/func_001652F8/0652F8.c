extern char D_002A4C48[];

int func_001652F8(int *self)
{
    int idx = self[0x8/4];
    int v = *(int *)(&D_002A4C48[idx * 0x4C] + 0x48);
    if (((unsigned)v >> 18) & 1) return 0;
    return (((unsigned)v >> 21) & 1) ^ 1;
}
