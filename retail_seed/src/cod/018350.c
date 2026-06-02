#include "vu0.h"

void func_00118350(void *p0, void *p1, void *p2, void *p3)
{
    VU0_LSV(lqc2, 1, 0x0, a1);
    VU0_LSV(lqc2, 2, 0x0, a2);
    VU0_V3OP_ACC(vopmula.xyz, 1, 2);
    VU0_V3OP(vopmsub.xyz, 3, 2, 1);
    VU0_V3OP(vsub.w, 3, 3, 3);
    VU0_LSV(sqc2, 3, 0x0, a0);
    VU0_NOP();
}
