#include "r5900.h"

extern void func_00100F18(int a0);

void func_0024FBD0(int a0, int a1, int a2)
{
    func_00100F18(a2);
    SYNC();
    EI();
}
