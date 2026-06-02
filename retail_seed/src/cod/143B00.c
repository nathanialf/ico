#include "vu0.h"

void func_00243B00(void *p0, void *p1, void *p2, void *p3)
{
    VU0_LSV(lqc2, 4, 0x0, a1);
    VU0_LSV(lqc2, 5, 0x0, a2);
    VU0_V3OP(vmul.xyzw, 6, 4, 5);
    VU0_LSV(sqc2, 6, 0x0, a0);
}
