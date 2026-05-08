extern void func_00264128(int a, int b);

void func_001AE8A0(int *self, int a1, int a2)
{
    if (a1 != 0) {
        func_00264128(a1, self[0] + self[0x4 / 4]);
    }
    self[0x4 / 4] = self[0x4 / 4] + a2;
}
