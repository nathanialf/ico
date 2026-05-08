extern int D_00631AF0;
extern int D_00633D40;
extern void func_0019FFA8(int a0, int a1, int a2, int a3);

int func_0017E4A0(int a0, int a1, int a2, int a3)
{
    int ret = 0;
    a1 = a1 & 0xFF;
    a2 = a2 & 0xFF;
    a3 = a3 & 0xFF;
    if (D_00631AF0 == 0) {
        if (D_00633D40 == 0) {
            func_0019FFA8(a0, a1, a2, a3);
            D_00633D40 = 1;
            ret = 1;
        }
    }
    return ret;
}
