#include "vu0.h"

void func_00243AA8(void *p0, void *p1, void *p2, void *p3)
{
    VU0_MEM("lqc2 $vf4, 0x0($a1)");
    VU0_MEM("lqc2 $vf5, 0x0($a2)");
    VU0_NOREORDER_BEGIN();
    VU0_REG("mfc1 $t0, $f12");
    VU0_REG("qmtc2.ni $t0, $vf6");
    VU0_NOREORDER_END();
    VU0_REG("vaddw.x $vf7, $vf0, $vf0w");
    VU0_REG("vsub.x $vf8, $vf7, $vf6");
    VU0_REG("vmulax.xyzw $ACC, $vf4, $vf6x");
    VU0_REG("vmaddx.xyzw $vf9, $vf5, $vf8x");
    VU0_MEM("sqc2 $vf9, 0x0($a0)");
}
