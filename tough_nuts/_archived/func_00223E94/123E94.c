#include "matching.h"

extern int func_0017B230(int a0);
extern void func_00203AA0(int a0);
extern void func_00205B30(int a0, int a1);

void func_00223E98(volatile int unused)
{
    while (func_0017B230(0xEA) == 0 || func_0017B230(0xEB) == 0) {
        func_00203AA0(1);
    }
    func_00205B30(4, 1);
    DEFEAT_TCO();
}
