int func_00251CD0(int *self, int idx, int a2, int a3)
{
    char *p = (char *)self[0x10];
    char *base = p + idx * 8;
    int *slot = (int *)(base + 0xC);
    int old;
    *(int *)(base + 0x10) = a3;
    old = *slot;
    *slot = a2;
    return old;
}
