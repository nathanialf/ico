extern void func_0014A3A8(int a0);

void func_00176198(int a0)
{
    int local;
    __asm__ __volatile__("sw $4, %0" : "=m"(local));
    __asm__ __volatile__("nop");
    func_0014A3A8(a0);
}
