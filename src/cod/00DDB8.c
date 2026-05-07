#include "vu0.h"

void func_0010DDB8(void *p0, void *p1, void *p2, void *p3)
{
    VU0_LSV(lqc2, 11, 0x0, a1);
    VU0_LSV(lqc2, 12, 0x0, a2);
    VU0_V3OP(vmul.xyzw, 13, 11, 12);
    VU0_V3OP_BC(vaddy.x, 13, 13, 13, y);
    VU0_V3OP_BC(vaddz.x, 13, 13, 13, z);
    VU0_V3OP_BC(vsubx.w, 13, 13, 13, x);
    VU0_V3OP_BC(vmulw.xyz, 14, 12, 11, w);
    VU0_V3OP_BC(vmulw.xyz, 15, 11, 12, w);
    VU0_V3OP_ACC(vopmula.xyz, 12, 11);
    VU0_V3OP(vopmsub.xyz, 16, 11, 12);
    VU0_V3OP(vadd.xyz, 13, 14, 15);
    VU0_V3OP(vadd.xyz, 13, 13, 16);
    VU0_LSV(sqc2, 13, 0x0, a0);
    VU0_NOP();
}
