#include "vu0.h"

void func_00243EC0(void *p0, void *p1, void *p2)
{
    VU0_MFC1(t0, 12);
    VU0_MFC1(t1, 13);
    VU0_LSV(lqc2, 6, 0x0, a1);
    VU0_QMTC2_NI(t0, 4);
    VU0_QMTC2_NI(t1, 5);
    VU0_V3OP_BC(vmaxx.xyzw, 6, 6, 4, x);
    VU0_V3OP_BC(vminix.xyzw, 6, 6, 5, x);
    VU0_LSV(sqc2, 6, 0x0, a0);
}
