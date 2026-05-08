extern void func_00168AE0(int a, int b, int c, int d, int t0);
extern void func_001182F0(int a, int b);

void func_00107DD8(int a0, int *a1, int *info)
{
    int *p = (int *)info[0];
    int v = ((int *)p[0x15C / 4])[0xC / 4];
    func_00168AE0(a0, (int)a1, info[2], v + (info[1] << 6), (int)p);
    a1[0x4 / 4] = 0;
    func_001182F0((int)a1, (int)a1);
}
