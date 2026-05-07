extern void func_00105F00(int a0);
extern int func_0010D830(int a0, int a1);

void func_001E6D68(int a0, int a1, int a2)
{
    func_00105F00(a0);
    return func_0010D830(a0 + 0x10, a2);
}
