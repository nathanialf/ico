#include "vu0.h"

void func_00118388(void *p0, void *p1, void *p2, void *p3)
{
    VU0_LSV(lqc2, 1, 0x0, a1);
    VU0_LSV(lqc2, 2, 0x0, a2);
    VU0_V3OP(vadd.xyz, 1, 1, 2);
    VU0_LSV(sqc2, 1, 0x0, a0);
    VU0_NOP();
}
