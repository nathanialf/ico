extern void func_00193848(int a0);
extern void func_00193830(int a0);

void func_00231A98(volatile unsigned int a0)
{
    func_00193848(a0);
    {
        register unsigned int v __asm__("$4");
        __asm__ volatile("lw %0, %1" : "=r"(v) : "m"(a0));
        __asm__ volatile("nop");
        func_00193830(v);
    }
}
