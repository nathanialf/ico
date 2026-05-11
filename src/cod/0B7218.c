extern char D_002E81F0[];

void func_001B7218(int a0, int a1)
{
    int *p = (int *)(D_002E81F0 + a0 * 0x6C);
    p[0x68 / 4] = (p[0x68 / 4] & ~2) | ((a1 & 1) << 1);
}
