extern void func_001F0260(int a0, int a1);

void func_001F0550(int a0)
{
    int p = *(int *)(*(int *)(a0 + 0x15C) + 0x800);
    func_001F0260(*(int *)(p + 0x20), p + 0x10);
}
