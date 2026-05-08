extern void func_0017DF38(int a0, int a1, int *buf, int a3, float f);
extern void func_00203AA0(int x);
extern int D_00631AE8;
extern long long D_0061C0B0[];

void func_0022ED40(volatile unsigned int a0)
{
    volatile int local;
    long long buf[2];
    buf[0] = D_0061C0B0[0];
    buf[1] = D_0061C0B0[1];
    func_0017DF38(D_00631AE8, 0, (int *)buf, 0, 100.0f);
    func_00203AA0(0);
}
