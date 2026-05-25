extern int func_0013A0F8(int a0, int a1, const char *fmt, int line);
extern void func_0013A250(int a0, int a1, int a2);
extern int func_0013A6C0(int *self, int *out, int a2);
extern void func_001A6E28();
extern int D_00632000;
extern const char D_005578D0[];
extern const char D_00557980[];

int func_0013D948(int *self)
{
    int local;
    if (self[0x48 / 4] == 0)
    {
        int m;
        self[0x48 / 4] = 1;
        m = func_0013A0F8(D_00632000, 0x50, D_005578D0, 0x1FA);
        self[0x4C / 4] = m;
        func_0013A250(m, m + 0x30, 8);
    }
    func_0013A6C0((int *) self[0x4C / 4], &local, 1);
    func_001A6E28(D_00557980);
    return local;
}
