#include "matching.h"

extern void func_00193848(int a0);
extern void func_00193830(int a0);

void func_00231A98(volatile unsigned int a0)
{
    func_00193848(a0);
    VOLATILE_RELOAD_CALL(a0, func_00193830);
}
