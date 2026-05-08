extern int func_0013A0F8(int a0, int a1, int *a2, int a3);
extern void func_00103120(int v, int *self);
extern int D_00612620[];
extern int D_00632010;

void func_0019EF10(int *self) {
    int v = func_0013A0F8(D_00632010, self[0x88/4] << 6, D_00612620, 0x14C);
    self[0x90/4] = v;
    func_00103120(v, self);
}
