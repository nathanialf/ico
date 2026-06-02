#include "r5900.h"

extern void func_001002D0(void);

void func_00100BC8(void)
{
    func_001002D0();
    SYNC();
}
