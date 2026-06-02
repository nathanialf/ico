extern void func_00149FF0(int x);
extern void func_0014A2C8(int x);
extern void func_00104240(int *self, int *buf);
extern void func_0013FF88(int self, int a, int b);
extern long long D_0055A1B0[];

void func_0017E4F0(int *self)
{
    long long buf[2];
    func_00149FF0((int)self);
    func_0014A2C8((int)self);
    buf[0] = D_0055A1B0[0];
    buf[1] = D_0055A1B0[1];
    func_00104240(self, (int *)buf);
    func_0013FF88((int)self, 0x27, (int)self);
}
