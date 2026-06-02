extern int D_00631990;
extern int D_006325B0;
extern char D_0028A520[];
extern int func_001AE1B8(int a0, int *a1, int a2);

void func_0017B1A8(int a0)
{
    D_006325B0 = D_00631990;
    func_001AE1B8(a0, &D_006325B0, 4);
    return func_001AE1B8(a0, (int *)D_0028A520, 0x2E);
}
