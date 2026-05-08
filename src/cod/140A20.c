extern void func_00100560(int x);
extern void func_00100540(int x);

int func_00240A20(int *self)
{
    int ret;
    func_00100560(self[0x40 / 4]);
    ret = (self[0x10 / 4] << 11) + self[0x14 / 4];
    func_00100540(self[0x40 / 4]);
    return ret;
}
