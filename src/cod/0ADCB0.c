extern int D_00632F74;
extern char D_004B3D10[];
extern char D_004B3B68[];
extern void func_001AE8A0(int a0, int *a1, int a2);

void func_001ADCB0(int self) {
    func_001AE8A0(self, &D_00632F74, 4);
    func_001AE8A0(self, (int *)D_004B3D10, 0x2D80);
    func_001AE8A0(self, (int *)D_004B3B68, 0x1A0);
}
