extern char D_006F8EE0[];

void func_001AA608(int a0, int a1, int a2)
{
    int *p = (int *)(D_006F8EE0 + a1 * 8 + a0 * 0xD0);
    *p = *p + a2;
}
