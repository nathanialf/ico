#include "vu0.h"

void func_00243BC8(void *p0, void *p1, void *p2)
{
    VU0_MEM("lqc2 $vf4, 0x0($a1)");
    VU0_REG("vitof0.xyzw $vf5, $vf4");
    VU0_MEM("sqc2 $vf5, 0x0($a0)");
}
