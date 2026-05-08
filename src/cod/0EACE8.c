extern int D_006335E0[];
extern void func_001AE460(int *self);
extern void func_001A6E28(int *a0, int a1);

void func_001EACE8(int *self) {
    int *p = (int *)((int *)self[0x15C/4])[0x800/4];
    p[0x3C/4] = 1;
    func_001AE460(self);
    func_001A6E28(D_006335E0, self[0x8/4]);
}
