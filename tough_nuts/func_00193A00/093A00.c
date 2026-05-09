extern void func_0013FF88(int *self, int x, int *self2);

int func_00193A00(int *self, short *p)
{
    int *q = (int *)((int *)self[0x15C/4])[0x800/4];
    short v = p[0x30/2];
    q[0x50/4] = v;
    q[0x8/4] = p[0x32/2];
    if (v == 1) {
        q[0x54/4] = 2;
        func_0013FF88(self, 1, self);
    }
    return 1;
}
