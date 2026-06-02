#include "vu0.h"

void func_001183B8(void *p0, void *p1, void *p2, void *p3)
{
    VU0_LSV(lqc2, 1, 0x0, a1);
    VU0_LSV(lqc2, 2, 0x0, a2);
    VU0_V3OP(vsub.xyz, 1, 1, 2);
    VU0_LSV(sqc2, 1, 0x0, a0);
    VU0_NOP();
}
