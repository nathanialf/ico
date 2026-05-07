#include "vu0.h"

void func_00118448(void *p0, void *p1, void *p2)
{
    VU0_LOAD("lqc2 $vf1, 0x0($a1)");
    VU0_COMPUTE("vftoi0.xyzw $vf2, $vf1");
    VU0_STORE("sqc2 $vf2, 0x0($a0)");
    VU0_NOP();
}
