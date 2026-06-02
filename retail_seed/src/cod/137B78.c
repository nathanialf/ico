#include "matching.h"

extern int func_0017B230(int x);
extern void func_001297A0(int x, int y, int z);
extern void func_00205B30(int x, int y);

void func_00237B78(void)
{
    if (func_0017B230(0x120) == 0) {
        func_001297A0(0x80, 0, 0);
        func_00205B30(4, 0);
    } else {
        func_001297A0(0x80, 0, -1);
        func_00205B30(4, 1);
    }
}
