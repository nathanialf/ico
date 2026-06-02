extern void func_0010D530(int *buf);
extern void func_001E8B48(int a, int b, int *buf);

void func_0017DC90(int a0, int a1)
{
    int buf[4];
    func_0010D530(buf);
    func_001E8B48(a1, a0, buf);
}
