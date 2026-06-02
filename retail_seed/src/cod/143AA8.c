#include "vu0.h"

void func_00243AA8(void *p0, void *p1, void *p2, void *p3)
{
    VU0_LSV(lqc2, 4, 0x0, a1);
    VU0_LSV(lqc2, 5, 0x0, a2);
    VU0_NOREORDER_BEGIN();
    VU0_MFC1(t0, 12);
    VU0_QMTC2_NI(t0, 6);
    VU0_NOREORDER_END();
    VU0_V3OP_BC(vaddw.x, 7, 0, 0, w);
    VU0_V3OP(vsub.x, 8, 7, 6);
    VU0_V3OP_ACC_BC(vmulax.xyzw, 4, 6, x);
    VU0_V3OP_BC(vmaddx.xyzw, 9, 5, 8, x);
    VU0_LSV(sqc2, 9, 0x0, a0);
}
