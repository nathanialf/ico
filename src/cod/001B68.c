extern void func_00100950(int a0, int *a1);

void func_00101B68(int a0, int a1, int a2)
{
    int local[3];
    local[1] = a1;
    local[2] = a2 & 0xFFFF;
    local[0] = a0;
    func_00100950(-5, local);
}
