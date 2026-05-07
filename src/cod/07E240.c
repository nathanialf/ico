extern int func_001E29E8(int a0, int a1, int a2);

void func_0017E240(int a0, int a1)
{
    int s0 = *(int *)(a0 + 0x164);
    *(int *)(s0 + 0x120) = func_001E29E8(a0, a1, s0 + 0x610);
}
