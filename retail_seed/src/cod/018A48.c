#include "vu0.h"

void func_00118A48(void *p0, void *p1, void *p2, void *p3)
{
    VU0_NOREORDER_BEGIN();
    VU0_MFC1(a2, 12);
    VU0_QMTC2_NI(a2, 1);
    VU0_NOREORDER_END();
    VU0_V3OP_BC(vaddw.x, 2, 1, 0, w);
    VU0_V3OP(vadd.x, 1, 1, 1);
    VU0_REG("vrinit $R, $vf2x");
    VU0_REG("vrxor $R, $vf1x");
    VU0_NOP();
}
