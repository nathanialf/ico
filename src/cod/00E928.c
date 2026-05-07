#include "vu0.h"

void func_0010E928(void *p0, void *p1, void *p2)
{
    VU0_LSV(lqc2, 14, 0x0, a0);
    VU0_LSV(lqc2, 15, 0x0, a1);
    VU0_V3OP(vmul.xyzw, 15, 14, 15);
    VU0_V3OP_BC(vaddy.x, 15, 15, 15, y);
    VU0_V3OP_BC(vaddz.x, 15, 15, 15, z);
    VU0_V3OP_BC(vaddw.x, 15, 15, 15, w);
    VU0_QMFC2_NI(v0, 15);
    VU0_MTC1(v0, 0);
    VU0_NOP();
}
