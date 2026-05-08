extern int func_00240EA0(int a, int b, int c, int d, int e, int f, int g);
extern void func_001F2370(void);
extern int D_00633748;

int func_001F22A0(void) {
    int v = func_00240EA0(0, 0, 0, 0, (int)&func_001F2370, 0, 0);
    D_00633748 = v;
    return v;
}
