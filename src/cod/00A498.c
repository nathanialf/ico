extern void func_00104508(int a0, int a1);

void func_0010A498(int a0, int a1)
{
    func_00104508(a0, a1);
    *(float *)(a0 + 0x4) += *(float *)(*(int *)(a1 + 0x15C) + 0x270);
}
