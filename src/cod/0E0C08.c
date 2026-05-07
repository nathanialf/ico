extern void func_00105F00(int a0, int a1);

void func_001E0C08(int a0, int a1)
{
    func_00105F00(a0, a1 + 0xA0);
    *(int *)(a0 + 0xC) = 0;
}
