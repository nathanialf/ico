#include "vu0.h"

void func_00243BB8(void *p0, void *p1, void *p2)
{
    VU0_LOAD("lqc2 $vf4, 0x0($a1)");
    VU0_COMPUTE("vitof4.xyzw $vf5, $vf4");
    VU0_STORE("sqc2 $vf5, 0x0($a0)");
}
