extern char *D_00717764;
extern char *D_0071776C;

void func_0024BBC0(int a0, int a1, int a2)
{
    char *base;
    if (a0 < 0) {
        base = D_00717764;
    } else {
        base = D_0071776C;
    }
    *(int *)(base + a0 * 8 + 4) = a2;
    *(int *)(base + a0 * 8) = a1;
}
