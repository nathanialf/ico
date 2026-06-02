extern void func_0010D838(int a0, int a1);
extern void func_0010DDB8(int a0, int a1, int a2);

void func_00102978(int a0, int a1)
{
    func_0010D838(a0, a1 + 0x60);
    func_0010DDB8(a0, a0, *(int *)(a1 + 0x10));
}
