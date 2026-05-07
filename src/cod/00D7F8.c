extern void func_001186C8(int *buf);
extern int func_0010D5C8(int a0, int *buf);

int func_0010D7F8(int a0)
{
    int buf[16];
    func_001186C8(buf);
    {
        register int aa __asm__("$4") = a0;
        __asm__ volatile("daddu $2, $29, $0" : : "r"(aa));
        return func_0010D5C8(aa, buf);
    }
}
