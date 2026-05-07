extern void func_00243AE8(int *buf, int a1, int a2);
extern void func_00243950(int *buf, int *buf2);

void func_00194398(int a0, int a1)
{
    int buf[4];
    func_00243AE8(buf, a0, a1);
    func_00243950(buf, buf);
}
