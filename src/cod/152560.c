extern void func_00264DF8(int *buf, int a1, int a2);
extern void func_00252590(int *buf);

void func_00252560(int a0, int a1)
{
    int buf[64];
    func_00264DF8(buf, a0, a1);
    func_00252590(buf);
}
