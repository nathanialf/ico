void func_0017EC50(void *a0, float f)
{
    long * volatile *pp = (long * volatile *)((char *)a0 + 0x164);
    long *p = *pp;
    *(long *)((char *)p + 0x20) = *(long *)((char *)p + 0x20) | 0x100000;
    {
        int **q = (int **)*pp;
        int *r = *(int **)((char *)q + 0x678);
        *(float *)((char *)r + 0x340) = f;
    }
}
