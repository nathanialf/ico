#include "vu0.h"

void func_00243A68(void *p0, void *p1, void *p2)
{
    VU0_MEM("lqc2 $vf4, 0x0($a1)");
    VU0_NOREORDER_BEGIN();
    VU0_REG("mfc1 $t0, $f12");
    VU0_REG("qmtc2.ni $t0, $vf5");
    VU0_NOREORDER_END();
    VU0_REG("vdiv $Q, $vf0w, $vf5x");
    VU0_WAIT();
    VU0_REG("vmulq.xyzw $vf4, $vf4, $Q");
    VU0_MEM("sqc2 $vf4, 0x0($a0)");
}
