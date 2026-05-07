#include "vu0.h"

void func_00243EC0(void *p0, void *p1, void *p2)
{
    VU0_REG("mfc1 $t0, $f12");
    VU0_REG("mfc1 $t1, $f13");
    VU0_MEM("lqc2 $vf6, 0x0($a1)");
    VU0_REG("qmtc2.ni $t0, $vf4");
    VU0_REG("qmtc2.ni $t1, $vf5");
    VU0_REG("vmaxx.xyzw $vf6, $vf6, $vf4x");
    VU0_REG("vminix.xyzw $vf6, $vf6, $vf5x");
    VU0_MEM("sqc2 $vf6, 0x0($a0)");
}
