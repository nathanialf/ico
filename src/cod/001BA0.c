extern void func_00100950(int a0, int *a1);

void func_00101BA0(int a0, int a1, int a2)
{
    int local[3];
    int new_var;
    new_var = a2 & 0xFFFF;
    local[0] = a0;
    local[1] = a1;
    local[2] = new_var;
    func_00100950(-6, local);
}
