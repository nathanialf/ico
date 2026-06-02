extern void func_00264128(int sum, int n);
extern void func_001A6E28(char *p, int y);
extern char D_006168F8[];

void func_001AE1B8(int *self, int n, int a2)
{
    if (n != 0) {
        func_00264128(self[0] + self[1], n);
    }
    self[1] += a2;
    func_001A6E28(D_006168F8, self[1]);
}
