extern void func_00104140(int *buf);
extern void func_002438B8(int a, int *buf, int c);

void func_001C0648(int a0, int a1, int a2)
{
    int buf[16];
    func_00104140(buf);
    func_002438B8(a0, buf, a2);
}
