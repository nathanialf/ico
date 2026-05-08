extern void func_0014B768(int a0);
extern void func_0013FF88(int a0, int a1, int a2);

void func_0017B4E0(int *self, int a1)
{
    int *p;
    func_0014B768((int)self);
    p = (int *)((int *)self[0x164 / 4])[0x670 / 4];
    p[0xC0 / 4] = a1;
    func_0013FF88((int)self, 0x2D, (int)self);
}
