#include "vu0.h"

void func_00118388(void *p0, void *p1, void *p2, void *p3)
{
    VU0_LOAD("lqc2 $vf1, 0x0($a1)");
    VU0_LOAD("lqc2 $vf2, 0x0($a2)");
    VU0_COMPUTE("vadd.xyz $vf1, $vf1, $vf2");
    VU0_STORE("sqc2 $vf1, 0x0($a0)");
    VU0_NOP();
}
