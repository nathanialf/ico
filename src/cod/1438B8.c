#include "vu0.h"

void func_002438B8(void *p0, void *p1, void *p2, void *p3)
{
    VU0_LSV(lqc2, 4, 0x0, a1);
    VU0_LSV(lqc2, 5, 0x10, a1);
    VU0_LSV(lqc2, 6, 0x20, a1);
    VU0_LSV(lqc2, 7, 0x30, a1);
    VU0_LSV(lqc2, 8, 0x0, a2);
    VU0_V3OP_ACC_BC(vmulax.xyzw, 4, 8, x);
    VU0_V3OP_ACC_BC(vmadday.xyzw, 5, 8, y);
    VU0_V3OP_ACC_BC(vmaddaz.xyzw, 6, 8, z);
    VU0_V3OP_BC(vmaddw.xyzw, 9, 7, 8, w);
    VU0_LSV(sqc2, 9, 0x0, a0);
}
