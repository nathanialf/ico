extern int func_00240EA0(int a, int b, int c, int d, int e, int f, int g);
extern void func_001C3760(void);
extern int D_006332A4;

int func_001C36E0(void) {
    int v = func_00240EA0(0, 0, 0, 0, (int)&func_001C3760, 0, 0);
    D_006332A4 = v;
    return v;
}
