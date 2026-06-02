extern int func_001C0870(int a0, int a1);

void func_0015F6C0(volatile unsigned int a0)
{
    int *v1 = *(int **)((char *)a0 + 0x164);
    func_001C0870(*(int *)((char *)v1 + 0x5EC), 0);
}
