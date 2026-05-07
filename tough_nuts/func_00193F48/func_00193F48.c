extern char D_002A4C48[];

void func_00193F48(int a0)
{
    int idx = *(int *)(a0 + 0x8);
    char *base = &D_002A4C48[idx * 0x4C];
    *(short *)(base + 0x42) = 0;
}
