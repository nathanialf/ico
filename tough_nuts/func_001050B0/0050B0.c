extern int D_00631B40;
extern char D_0065FA40[];
extern float D_002759A0[];
extern void func_002438E8(void *a0, void *a1);

void func_001050B0(float f1, float f2, float f3)
{
    void *p = &D_0065FA40[D_00631B40 * 64];
    D_002759A0[0] = f1;
    D_002759A0[5] = f2;
    D_002759A0[10] = f3;
    func_002438E8(p, p);
}
