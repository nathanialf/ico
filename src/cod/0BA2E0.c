extern void func_00104508(int p, int *self);
extern void func_00102850(int p, int *self);
extern void func_001CFA20(int x);

void func_001BA2E0(int *self)
{
    int *p = (int *)((int *)self[0x15C / 4])[0x800 / 4];
    func_00104508((int)((char *)p + 0x1E0), self);
    func_00102850((int)((char *)p + 0x1D0), self);
    func_001CFA20(p[0x19C / 4]);
}
