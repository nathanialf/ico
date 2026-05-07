#include "vu0.h"

void func_00243A88(void *p0, void *p1, void *p2)
{
    VU0_LOAD("lqc2 $vf4, 0x0($a1)");
    VU0_NOREORDER_BEGIN();
    VU0_MOVE("mfc1 $t0, $f12");
    VU0_MOVE("qmtc2.ni $t0, $vf5");
    VU0_NOREORDER_END();
    VU0_COMPUTE("vdiv $Q, $vf0w, $vf5x");
    VU0_WAIT();
    VU0_COMPUTE("vmulq.xyz $vf4, $vf4, $Q");
    VU0_STORE("sqc2 $vf4, 0x0($a0)");
}
