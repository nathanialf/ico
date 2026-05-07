#include "vu0.h"

void func_001183A0(void *p0, void *p1, void *p2, void *p3)
{
    VU0_MEM("lqc2 $vf1, 0x0($a1)");
    VU0_MEM("lqc2 $vf2, 0x0($a2)");
    VU0_REG("vsub.xyzw $vf3, $vf1, $vf2");
    VU0_MEM("sqc2 $vf3, 0x0($a0)");
    VU0_NOP();
}
