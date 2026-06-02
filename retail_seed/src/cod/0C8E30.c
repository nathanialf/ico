#include "vu0.h"

void func_001C8E30(void *p0)
{
    VU0_LSV(lqc2, 4, 0x0, a0);
    VU0_V3OP(vmul.xz, 4, 4, 4);
    VU0_V3OP_BC(vaddz.x, 4, 4, 4, z);
    VU0_REG("vrsqrt $Q, $vf0w, $vf4x");
    VU0_WAIT();
    VU0_NOREORDER_BEGIN();
    VU0_CFC2_NI(v0, 22);
    VU0_MTC1(v0, 0);
    VU0_NOREORDER_END();
}
