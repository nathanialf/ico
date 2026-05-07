extern void func_00100950(int a0, int *a1);

void func_00101C30(int a0)
{
    int local = a0;
    func_00100950(-9, &local);
    __asm__ __volatile__("" : : "r"(&local));
}
