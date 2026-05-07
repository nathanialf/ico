#include "vu0.h"

void func_00105F90(void *p0, void *p1, void *p2, void *p3)
{
    VU0_LOAD("lqc2 $vf4, 0x0($a1)");
    VU0_LOAD("lqc2 $vf5, 0x0($a2)");
    VU0_COMPUTE("vsub.xyz $vf4, $vf4, $vf5");
    VU0_STORE("sqc2 $vf4, 0x0($a0)");
    VU0_NOP();
}
