extern int D_00631AE4;
extern int D_00631AE8;
extern void func_0017C9B0(int x);
extern void func_001297A0(int x, int y, int z);
extern void func_00203AA0(int x);
extern int func_0012AA80(int x);
extern void func_0017E330(int x, int y, int z, float a, float b);

void func_0020D238(int unused)
{
    func_0017C9B0(6);
    func_001297A0(0x2F9, 1, 0);
    while (func_0012AA80(0x2F9) == 0) {
        func_00203AA0(1);
    }
    func_00203AA0(1);
    func_0017E330(6, D_00631AE4, D_00631AE8, 1.0f, 8.0f);
}
