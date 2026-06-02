extern void func_00105F00(int a0, int a1);
extern void func_00168538(int a0);
extern float D_00630948;

void func_00106DA8(int a0, int a1)
{
    func_00105F00(a0, a1);
    func_00105F00(a0 + 0x10, a0);
    *(float *)(a0 + 0x14) = *(float *)(a0 + 0x14) + D_00630948;
    func_00168538(a0);
}
