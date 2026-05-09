extern void func_00264128(int x, int y);
extern void func_001A6E28(char *p, int y);
extern char D_006168F8[];

void func_001AE1B8(int *self, int a1, int a2)
{
    if (a1 != 0) {
        func_00264128(a1, self[0] + self[0x4 / 4]);
    }
    self[0x4 / 4] = self[0x4 / 4] + a2;
    func_001A6E28(D_006168F8, self[0x4 / 4]);
}
