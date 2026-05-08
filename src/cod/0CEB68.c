extern void func_001E4798(int self, int a1, int a2, int a3, int t0, int t1);
extern void func_001D4B40(int self, int a1);

void func_001CEB68(int *self)
{
    func_001E4798((int)self, 0x71C, 0x839, -1, -1, 0x39A);
    func_001D4B40((int)self, 0);
    self[0x16C / 4] = 0;
}
