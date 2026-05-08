extern void func_00254CF8(int a0);
extern int D_00552498[];
extern int D_00552AB8[];

void func_00252438(void)
{
    int v;
    func_00254CF8(1);
    v = D_00552498[0];
    D_00552AB8[0] = v;
    D_00552AB8[0x4 / 4] = v + 0x1800;
    D_00552AB8[0x140 / 4] = v + 0x1B00;
    D_00552AB8[0x144 / 4] = v + 0x3300;
    D_00552AB8[0x280 / 4] = 0;
}
