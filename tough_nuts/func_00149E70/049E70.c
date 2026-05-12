extern int D_00631AE4;

int func_00149E70(int *self)
{
    int *p;
    if (self == 0) return 0;
    if (self != (int *)D_00631AE4) return 0;
    p = (int *)self[0x59];
    if (p == 0) return 0;
    return (int)((*(long long *)((char *)p + 0x20) << 8) >> 32) & 1;
}
