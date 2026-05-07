#include "vu0.h"

void func_001182F0(void *p0, void *p1, void *p2)
{
    VU0_LSV(lqc2, 1, 0x0, a1);
    VU0_V3OP(vmul.xyz, 3, 1, 1);
    VU0_V3OP_ACC_BC(vmulax.w, 0, 3, x);
    VU0_V3OP_ACC_BC(vmadday.w, 0, 3, y);
    VU0_V3OP_BC(vmaddz.w, 3, 0, 3, z);
    VU0_REG("vrsqrt $Q, $vf0w, $vf3w");
    VU0_WAIT();
    VU0_REG("vmulq.xyz $vf1, $vf1, $Q");
    VU0_LSV(sqc2, 1, 0x0, a0);
    VU0_NOP();
}
