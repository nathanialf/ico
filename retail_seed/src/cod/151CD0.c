int func_00251CD0(int *a0, int idx, int a2, int a3)
{
    char *arr;
    char *p1;
    int rv;
    arr = (char *)a0[0x40 / 4];
    idx = idx << 3;
    p1 = arr + 0xC;
    arr += idx;
    p1 += idx;
    *(volatile int *)(arr + 0x10) = a3;
    rv = *(volatile int *)p1;
    *(volatile int *)p1 = a2;
    return rv;
}
