#include "vu0.h"

void func_00243930(void *p0, void *p1, void *p2, void *p3)
{
    VU0_LOAD("lqc2 $vf4, 0x0($a1)");
    VU0_LOAD("lqc2 $vf5, 0x0($a2)");
    VU0_COMPUTE("vopmula.xyz $ACC, $vf4, $vf5");
    VU0_COMPUTE("vopmsub.xyz $vf6, $vf5, $vf4");
    VU0_COMPUTE("vsub.w $vf6, $vf6, $vf6");
    VU0_STORE("sqc2 $vf6, 0x0($a0)");
}
