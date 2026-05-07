extern char D_007097F0[];

void func_001E8E80(int idx, int a1)
{
    int *p;
    char *base;
    if (idx < 0) {
        return;
    }
    base = &D_007097F0[idx * 0x18];
    ;
    *((int *)(((char *)(*((int **)((&D_007097F0[idx * 0x18]) + 0x14)))) + 0x34)) = a1;
}
