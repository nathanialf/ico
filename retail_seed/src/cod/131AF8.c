#include "matching.h"

extern int func_0017B230(int a0);
extern void func_001A6E28(void *p);
extern void func_0017B258(int a0);
extern int D_0061C0D0[];

void func_00231AF8(void)
{
    if (func_0017B230(0x1D) != 0) {
        return;
    }
    func_001A6E28(D_0061C0D0);
    func_0017B258(0x165);
}

TRAILING_PAD_NOP();
