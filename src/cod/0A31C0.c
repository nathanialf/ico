extern int D_00632A0C;
extern int func_00100230(int a, int b, int c);
extern void func_00100250(int a, int b);
extern void func_001AA688(void);
extern void func_00100B40(int a);

void func_001A31C0(void)
{
    if (D_00632A0C != -1) {
        func_00100250(1, D_00632A0C);
    }
    D_00632A0C = func_00100230(1, (int)func_001AA688, -1);
    func_00100B40(1);
}
