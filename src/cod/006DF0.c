extern void func_00105F00(int a0, int a1);
extern void func_00168558(int a0);
extern float D_0063094C;

void func_00106DF0(int a0, int a1)
{
    func_00105F00(a0, a1);
    func_00105F00(a0 + 0x10, a0);
    *(float *)(a0 + 0x14) = *(float *)(a0 + 0x14) + D_0063094C;
    func_00168558(a0);
}
