extern void func_00203AA0(int a0);

void func_0015E7C0(volatile unsigned int a0)
{
    int *v1 = *(int **)((char *)a0 + 0x164);
    *(unsigned int *)((char *)v1 + 0x34) = 0xFFFFFFFFu;
    func_00203AA0(0);
}
