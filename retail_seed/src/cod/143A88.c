#include "vu0.h"

void func_00243A88(void *p0, void *p1, void *p2)
{
    VU0_LSV(lqc2, 4, 0x0, a1);
    VU0_NOREORDER_BEGIN();
    VU0_MFC1(t0, 12);
    VU0_QMTC2_NI(t0, 5);
    VU0_NOREORDER_END();
    VU0_REG("vdiv $Q, $vf0w, $vf5x");
    VU0_WAIT();
    VU0_REG("vmulq.xyz $vf4, $vf4, $Q");
    VU0_LSV(sqc2, 4, 0x0, a0);
}
