extern void func_00100560(int x);
extern void func_00100540(int x);

void func_0023FDA0(int *self, int a1)
{
    func_00100560(self[0x40 / 4]);
    self[0x14 / 4] = self[0x14 / 4] + a1;
    *(long long *)((char *)self + 0x48) = (long long)a1 + *(long long *)((char *)self + 0x48);
    func_00100540(self[0x40 / 4]);
}
