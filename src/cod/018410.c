#include "vu0.h"

void func_00118410(void *p0, void *p1, void *p2, void *p3)
{
    VU0_MEM("lqc2 $vf1, 0x0($a1)");
    VU0_MEM("lqc2 $vf2, 0x0($a2)");
    VU0_REG("vmulx.x $vf1, $vf1, $vf2x");
    VU0_REG("vmuly.y $vf1, $vf1, $vf2y");
    VU0_REG("vmulz.z $vf1, $vf1, $vf2z");
    VU0_MEM("sqc2 $vf1, 0x0($a0)");
    VU0_NOP();
}
