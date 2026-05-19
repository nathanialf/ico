#include "matching.h"

extern int D_006349E0[];
extern int func_00100950(int a0, int *p);

int func_00101AA0(unsigned int a0, int a1, int a2)
{
    int local[4];
    local[0] = a0 & 0xFFFF;
    local[1] = a1;
    local[2] = a2;
    local[3] = (int)D_006349E0 | 0x20000000;
    return func_00100950(1, local);
}
