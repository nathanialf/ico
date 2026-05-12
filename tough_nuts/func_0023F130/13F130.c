int *func_0023F130(int *a0, int a1, long long a2)
{
    long long u;
    int *ret;
    u = a2 & 0xFFFFFFFFLL;
    a0[2] = a1;
    a0[3] = 0;
    a0[0] = (int)u;
    a0[1] = (int)(a2 >> 32);
    ret = a0 + 4;
    return ret;
}
