#include "vu0.h"

void func_00243B30(void *p0, void *p1, void *p2, void *p3, void *p4, void *p5)
{
    VU0_LSV(lqc2, 4, 0x0, a2);
    VU0_LSV(lqc2, 5, 0x30, a1);
    VU0_LSGP(lq, a3, 0x0, a1);
    VU0_LSGP(lq, t0, 0x10, a1);
    VU0_LSGP(lq, t1, 0x20, a1);
    VU0_V3OP(vadd.xyz, 5, 5, 4);
    VU0_LSGP(sq, a3, 0x0, a0);
    VU0_LSGP(sq, t0, 0x10, a0);
    VU0_LSGP(sq, t1, 0x20, a0);
    VU0_LSV(sqc2, 5, 0x30, a0);
}
