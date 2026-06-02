extern void func_00243AE8(int *buf);
extern void func_00243978(int a0, int *buf);

void func_001947D0(int a0)
{
    int buf[4];
    func_00243AE8(buf);
    buf[1] = 0;
    func_00243978(a0, buf);
}
