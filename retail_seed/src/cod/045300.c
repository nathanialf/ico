extern int func_001E6CA0(int a0, int a1, int a2);

void func_00145300(int *a0)
{
    int *v0 = (int *)a0[0x164 / 4];
    int *v1 = (int *)v0[0x670 / 4];
    int a1 = v1[0x1B8 / 4];
    if (a1 == 0) {
        return;
    }
    return func_001E6CA0(0x1B1, a1, 1);
}
