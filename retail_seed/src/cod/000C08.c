#include "r5900.h"

extern void func_001002F0(void);

void func_00100C08(void)
{
    func_001002F0();
    SYNC();
}
