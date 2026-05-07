extern void func_00243AE8(int *buf, int a, int b);
extern void func_00243950(int *buf, int *buf2);

void func_00194398(int a, int b)
{
    int buf[4];
    func_00243AE8(buf, a, b);
    func_00243950(buf, buf);
}
