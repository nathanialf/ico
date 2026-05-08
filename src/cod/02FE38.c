void func_0012FE38(int *a0, int a1, int a2)
{
    long long *slot = (long long *)((char *)a0 + 0x78);
    *slot = (*slot & ~(long long)0xE0) | (a1 << 5) | (a2 << 6);
}
