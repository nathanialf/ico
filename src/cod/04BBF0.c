extern int D_00631990;
extern int func_001AE830(int *buf);
extern void func_0019CBB8(int a0, int a1, int a2, int *buf);

void func_0014BBF0(int a0)
{
    int buf[4];
    int v0 = func_001AE830(buf);
    func_0019CBB8(a0, D_00631990, v0, buf);
}
