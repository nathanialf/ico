#include "vu0.h"

void func_00118648(void *p0, void *p1, void *p2, void *p3)
{
    VU0_LSV(lqc2, 8, 0x0, a2);
    VU0_LSV(lqc2, 14, 0x0, a1);
    VU0_LSV(lqc2, 15, 0x10, a1);
    VU0_LSV(lqc2, 16, 0x20, a1);
    VU0_LSV(lqc2, 17, 0x30, a1);
    VU0_V3OP_ACC_BC(vmulax.xyzw, 14, 8, x);
    VU0_V3OP_ACC_BC(vmadday.xyzw, 15, 8, y);
    VU0_V3OP_ACC_BC(vmaddaz.xyzw, 16, 8, z);
    VU0_V3OP_BC(vmaddw.xyzw, 10, 17, 8, w);
    VU0_LSV(sqc2, 10, 0x0, a0);
    VU0_NOP();
}
