extern int D_00633E70;

void func_001B0518(int a0)
{
    int v1 = D_00633E70;
    *(int *)(a0 + 0xC) |= 1;
    if (a0 == v1) {
        D_00633E70 = 0;
    }
}
