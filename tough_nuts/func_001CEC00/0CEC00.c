extern char D_0061D560[];

int func_001CEC00(void *a0)
{
    void *p = *(void **)((char *)a0 + 0x15C);
    void *q = *(void **)((char *)p + 0x800);
    int idx = *(int *)((char *)q + 0x8);
    return *(int *)(D_0061D560 + idx * 0x14 + 0x10) & 3;
}
