#include "vu0.h"

void func_00243950(void *p0, void *p1, void *p2)
{
    VU0_LSV(lqc2, 4, 0x0, a0);
    VU0_LSV(lqc2, 5, 0x0, a1);
    VU0_V3OP(vmul.xyz, 5, 4, 5);
    VU0_V3OP_BC(vaddy.x, 5, 5, 5, y);
    VU0_V3OP_BC(vaddz.x, 5, 5, 5, z);
    VU0_QMFC2_NI(v0, 5);
    VU0_MTC1(v0, 0);
    VU0_NOP();
}
