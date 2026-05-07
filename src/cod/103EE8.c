extern int func_00202208(int a0);
extern void func_00203AA0(int a0);

void func_00203EE8(volatile unsigned int a0)
{
    if (!a0) {
    }
    {
        register unsigned int v __asm__("$4");
        __asm__ volatile("lw %0, %1" : "=r"(v) : "m"(a0));
        __asm__ volatile("nop");
        func_00202208(v);
    }
    func_00203AA0(1);
}
