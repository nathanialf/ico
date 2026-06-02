extern int func_00122C48(int a0);
extern int func_001EF998(int a0);
extern int func_0020BBF0(int a0);
extern void func_00203B78(void *fn, int a1);

void func_0020D770(int a0)
{
    volatile int local = a0;
    func_00122C48(1);
    func_001EF998(0);
    func_00203B78((void *)func_0020BBF0, 0x15);
}
