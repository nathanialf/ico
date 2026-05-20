extern int D_004C7710[];

void func_00111918(long long a0, long long a1)
{
    long long *p = (long long *)D_004C7710[4];
    *p = a1;
    D_004C7710[4] = (int)(p + 1);
    p[1] = a0;
}
