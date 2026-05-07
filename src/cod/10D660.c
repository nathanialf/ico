extern void func_0017B258(int a0);
extern void func_0020D690(void);
extern void func_00203B78(void (*a0)(void), int a1);

void func_0020D660(int a0)
{
    int local = a0;
    func_0017B258(0x13F);
    func_00203B78(func_0020D690, 0x15);
    __asm__ __volatile__("" : : "r"(&local));
}
