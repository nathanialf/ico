extern void func_00105F00(int a, int b);

void func_001C22F0(int *self, int a1, int a2)
{
    int *p;
    int *q;
    p = (int *)((int *)self[0x15C / 4])[0x800 / 4];
    q = (int *)p[0x20 / 4];
    func_00105F00(q[0] + 0x20, a1);
    func_00105F00((int)((char *)p + 0x10), a2);
}
