extern char D_004CAEC0[];

int func_00205B50(int idx)
{
    char *base = &D_004CAEC0[idx * 0x34];
    return (*((int *)((&D_004CAEC0[idx * 0x34]) + 0x28))) != 0;
}
