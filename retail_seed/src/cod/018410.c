#include "vu0.h"

void func_00118410(void *p0, void *p1, void *p2, void *p3)
{
    VU0_LSV(lqc2, 1, 0x0, a1);
    VU0_LSV(lqc2, 2, 0x0, a2);
    VU0_V3OP_BC(vmulx.x, 1, 1, 2, x);
    VU0_V3OP_BC(vmuly.y, 1, 1, 2, y);
    VU0_V3OP_BC(vmulz.z, 1, 1, 2, z);
    VU0_LSV(sqc2, 1, 0x0, a0);
    VU0_NOP();
}
