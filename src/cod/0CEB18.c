extern void func_001E4798(int *self, int a, int b, int c, int d, int e);
extern void func_001D4B40(int *p, int x);

int func_001CEB18(int *self)
{
    func_001E4798(self, 0x71C, 0x839, -1, -1, 0x39A);
    func_001D4B40(self, 0);
    self[0x16C/4] = 0;
    return 0;
}
