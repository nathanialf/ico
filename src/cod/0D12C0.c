extern void func_00144240(int a0);

void func_001D12C0(int a0, int a1)
{
    register int p __asm__("$2");
    p = *(int *)(a0 + 0x15C);
    p += a1 * 4;
    func_00144240(*(int *)(p + 0x61C));
}
