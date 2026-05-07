#include "vu0.h"

void func_00243AE8(void *p0, void *p1, void *p2, void *p3)
{
    VU0_MEM("lqc2 $vf4, 0x0($a1)");
    VU0_MEM("lqc2 $vf5, 0x0($a2)");
    VU0_REG("vsub.xyzw $vf6, $vf4, $vf5");
    VU0_MEM("sqc2 $vf6, 0x0($a0)");
}
