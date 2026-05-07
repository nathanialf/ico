extern int D_00633038;
extern void func_001B7218(int a0, int a1);

int func_001B5158(void)
{
    func_001B7218(0x8C, D_00633038);
    func_001B7218(0x8D, D_00633038 ^ 1);
    return -1;
}
