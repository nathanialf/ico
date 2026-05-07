extern void func_0023B518(void);
extern void func_00203B78(void (*a0)(void), int a1);

void func_0023B4F0(int a0)
{
    int local = a0;
    func_00203B78(func_0023B518, 0x15);
    __asm__ __volatile__("" : : "r"(&local));
}
