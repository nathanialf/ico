#include "vu0.h"

void func_001184B8(void *p0, void *p1, void *p2, void *p3)
{
    VU0_NOREORDER_BEGIN();
    VU0_MFC1(t0, 12);
    VU0_QMTC2_NI(t0, 3);
    VU0_NOREORDER_END();
    VU0_LSV(lqc2, 1, 0x0, a1);
    VU0_LSV(lqc2, 2, 0x0, a2);
    VU0_V3OP_BC(vsubx.w, 8, 0, 3, x);
    VU0_V3OP_ACC_BC(vmulax.xyz, 1, 3, x);
    VU0_V3OP_BC(vmaddw.xyz, 1, 2, 8, w);
    VU0_LSV(sqc2, 1, 0x0, a0);
    VU0_NOP();
}
