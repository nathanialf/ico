#include "vu0.h"

void func_00118548(void *p0, void *p1, void *p2)
{
    VU0_LSV(lqc2, 1, 0x0, a0);
    VU0_LSV(lqc2, 2, 0x0, a1);
    VU0_V3OP(vsub.xyzw, 3, 1, 2);
    VU0_V3OP(vmul.xy, 3, 3, 3);
    VU0_V3OP_BC(vaddy.x, 3, 3, 3, y);
    VU0_WORD(0x4A0303BD);
    VU0_WAIT();
    VU0_NOREORDER_BEGIN();
    VU0_CFC2_NI(v0, 22);
    VU0_MTC1(v0, 0);
    VU0_NOREORDER_END();
}
