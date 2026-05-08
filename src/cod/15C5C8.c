extern int func_002591F0(int x, int y, int z, int w);

void func_0025C5C8(void)
{
    int i;
    for (i = 0; i < 2; i++) {
        func_002591F0(0xB, i, 0xFFFFFF, 0);
        func_002591F0(0x28, i, 0, 0);
    }
    func_002591F0(0x1F, 0, 0, 0);
}
