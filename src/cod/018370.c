#include "vu0.h"

void func_00118370(void *p0, void *p1, void *p2, void *p3)
{
    VU0_LOAD("lqc2 $vf1, 0x0($a1)");
    VU0_LOAD("lqc2 $vf2, 0x0($a2)");
    VU0_COMPUTE("vadd.xyzw $vf3, $vf1, $vf2");
    VU0_STORE("sqc2 $vf3, 0x0($a0)");
    VU0_NOP();
}
