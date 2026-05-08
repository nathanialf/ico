extern void func_0013A5B8(char *p, int *self, int zero, int neg2);
extern char D_00280F88[];

void func_001381D0(int *self)
{
    self[0x4 / 4] = 0xC;
    *(long long *)self = *(long long *)self & -2LL;
    func_0013A5B8(D_00280F88, self, 0, -2);
}
