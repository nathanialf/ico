extern void func_0010D838(int *buf, int x);
extern void func_0010DDB8(int self, int *buf, int y);

void func_0010DDF8(int self, int a1, int a2)
{
    int buf[4];
    func_0010D838(buf, a2);
    func_0010DDB8(self, buf, a1);
}
