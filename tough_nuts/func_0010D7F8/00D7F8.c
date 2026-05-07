extern void func_001186C8(int *buf);
extern int func_0010D5C8(int a0, int *buf);

int func_0010D7F8(int a0)
{
    int buf[16];
    func_001186C8(buf);
    return func_0010D5C8(a0, buf);
}
