extern void func_00203AA0(int a0);

void func_00175CB0(int a0)
{
    volatile int local = a0;
    int v0 = local;
    int v1 = *(int *)(v0 + 0x164);
    *(int *)(v1 + 0x33C) = 0;
    func_00203AA0(0);
}
