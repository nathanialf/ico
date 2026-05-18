#include "matching.h"
#include "vu0.h"

extern float func_00117C20(float x);

float func_0010E708(float *v)
{
    register float dot __asm__("$f12");
    VU0_LSV(lqc2, 14, 0x0, a0);
    VU0_LSV(lqc2, 15, 0x0, a0);
    VU0_V3OP(vmul.xyzw, 15, 14, 15);
    VU0_V3OP_BC(vaddy.x, 15, 15, 15, y);
    VU0_V3OP_BC(vaddz.x, 15, 15, 15, z);
    VU0_V3OP_BC(vaddw.x, 15, 15, 15, w);
    VU0_QMFC2_NI(v0, 15);
    VU0_MTC1(v0, 12);
    KEEP_LIVE_FP(dot);
    return func_00117C20(dot);
}
