extern int *D_00631AE4;
extern int func_001F40C8(int a0);

int func_0017E5B0(void)
{
    int *v0 = D_00631AE4;
    int *v1 = (int *)v0[0x164 / 4];
    int a = v1[0x140 / 4];
    if (a == 0) {
        return 0;
    }
    return func_001F40C8(a);
}
