extern void func_00243C78(int a, int b, float f);
extern void func_00243DC8(int a, int b, float f);
extern void func_00243D20(int a, int b, float f);

void func_00243E70(int a0, int a1, float *fa)
{
    func_00243C78(a0, a1, fa[2]);
    func_00243DC8(a0, a0, fa[1]);
    func_00243D20(a0, a0, fa[0]);
}
