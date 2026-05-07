extern void func_0013DDF8(int a0);
extern int func_0013E0C0(int a0, int a1, int a2);

void func_0013E1D8(int a0, int a1, int a2)
{
    int new_var;
    int s1 = a1 & 0xFF;
    func_0013DDF8(a0);
    new_var = s1;
    return func_0013E0C0(a0, new_var, a2);
}
