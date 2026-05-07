#include "vu0.h"

void func_001183D0(void *p0, void *p1, void *p2)
{
    VU0_MEM("lqc2 $vf1, 0x0($a1)");
    VU0_NOREORDER_BEGIN();
    VU0_REG("mfc1 $t0, $f12");
    VU0_REG("qmtc2.ni $t0, $vf2");
    VU0_NOREORDER_END();
    VU0_REG("vmulx.xyzw $vf3, $vf1, $vf2x");
    VU0_MEM("sqc2 $vf3, 0x0($a0)");
    VU0_NOP();
}
