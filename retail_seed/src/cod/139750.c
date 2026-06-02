extern int func_0017B230(int x);
extern void func_001297A0(int x, int y, int z);
extern void func_00205B30(int x, int y);

void func_00239750(void)
{
    if (func_0017B230(0x2C) != 0) {
        func_001297A0(0x91, 0, 0);
        func_00205B30(0x21, 1);
    } else {
        func_001297A0(0x90, 0, 0);
        func_00205B30(0x21, 0);
    }
    if (func_0017B230(0x2D) != 0) {
        func_001297A0(0x93, 0, 0);
        func_00205B30(0x22, 1);
    } else {
        func_001297A0(0x92, 0, 0);
        func_00205B30(0x22, 0);
    }
}
