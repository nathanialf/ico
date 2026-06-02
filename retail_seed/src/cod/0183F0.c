#include "vu0.h"

void func_001183F0(void *p0, void *p1, void *p2)
{
    VU0_LSV(lqc2, 1, 0x0, a1);
    VU0_NOREORDER_BEGIN();
    VU0_MFC1(t0, 12);
    VU0_QMTC2_NI(t0, 2);
    VU0_NOREORDER_END();
    VU0_V3OP_BC(vmulx.xyz, 1, 1, 2, x);
    VU0_LSV(sqc2, 1, 0x0, a0);
    VU0_NOP();
}
