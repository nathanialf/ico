extern char D_007097F0[];

void func_001E8E80(int idx, int a1)
{
    int *p;
    char *base;
    if (idx < 0) {
        return;
    }
    base = &D_007097F0[idx * 0x18];
    p = *(int **)(base + 0x14);
    *(int *)((char *)p + 0x34) = a1;
}
