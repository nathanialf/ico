extern int func_00203AA0(int a0);
extern int func_0017B230(int a0);
extern void func_00205B30(int a0, int a1);

void func_00223E50(int x)
{
    volatile int local = x;
    for (;;) {
        if (func_0017B230(0xEA) != 0) break;
        func_00203AA0(1);
    }
    func_00205B30(3, 1);
}
