extern void func_00104508(int *a0, int a1);
extern void func_00178990(int *a0, int a1);

void func_0017A9D8(int a0)
{
    int locals[4];
    func_00104508(locals, a0);
    func_00178990(locals, -1);
    __asm__ __volatile__("" : : "r"(locals));
}
