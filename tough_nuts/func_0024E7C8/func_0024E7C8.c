extern void func_00251088(int a0);
extern int D_0054C758[];
extern int D_0054CD78[];

void func_0024E7C8(void) {
    int base;
    func_00251088(1);
    base = D_0054C758[0];
    D_0054CD78[1] = base + 0x1800;
    D_0054CD78[0] = base;
    D_0054CD78[0x50] = base + 0x1B00;
    D_0054CD78[0x51] = base + 0x3300;
    D_0054CD78[0xA0] = 0;
}
