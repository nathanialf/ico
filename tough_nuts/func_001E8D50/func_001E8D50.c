extern char D_007097F0[];

void func_001E8D50(int idx)
{
    char *base = &D_007097F0[idx * 0x18];
    *(int *)(base + 0x4) = 0;
}
