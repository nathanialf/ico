extern int D_00631A00;
extern int D_00274ED4[];
extern int D_00633E9C;
extern int D_0063305C;
extern void func_001A0010(int x);
extern void func_0013B858(void);
extern void func_0013ED40(int x, int y);
extern void func_0017B288(int x);

int func_001B4F58(int a0)
{
    if (a0 != 0) {
        int v;
        func_001A0010(0);
        v = D_00631A00;
        D_00274ED4[0] = 1;
        D_00633E9C = v;
        func_0013B858();
        func_0013ED40(0, 0);
        func_0017B288(0x161);
        if (D_0063305C == 0) {
            D_0063305C = 1;
        }
    }
    return -1;
}
