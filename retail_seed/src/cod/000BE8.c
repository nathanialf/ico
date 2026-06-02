#include "r5900.h"

extern void func_001002E0(void);

void func_00100BE8(void)
{
    func_001002E0();
    SYNC();
}
