#include "vu0.h"

void func_00118350(void *p0, void *p1, void *p2, void *p3)
{
    VU0_MEM("lqc2 $vf1, 0x0($a1)");
    VU0_MEM("lqc2 $vf2, 0x0($a2)");
    VU0_REG("vopmula.xyz $ACC, $vf1, $vf2");
    VU0_REG("vopmsub.xyz $vf3, $vf2, $vf1");
    VU0_REG("vsub.w $vf3, $vf3, $vf3");
    VU0_MEM("sqc2 $vf3, 0x0($a0)");
    VU0_NOP();
}
