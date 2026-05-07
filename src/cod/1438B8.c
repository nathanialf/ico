#include "vu0.h"

void func_002438B8(void *p0, void *p1, void *p2, void *p3)
{
    VU0_LOAD("lqc2 $vf4, 0x0($a1)");
    VU0_LOAD("lqc2 $vf5, 0x10($a1)");
    VU0_LOAD("lqc2 $vf6, 0x20($a1)");
    VU0_LOAD("lqc2 $vf7, 0x30($a1)");
    VU0_LOAD("lqc2 $vf8, 0x0($a2)");
    VU0_COMPUTE("vmulax.xyzw $ACC, $vf4, $vf8x");
    VU0_COMPUTE("vmadday.xyzw $ACC, $vf5, $vf8y");
    VU0_COMPUTE("vmaddaz.xyzw $ACC, $vf6, $vf8z");
    VU0_COMPUTE("vmaddw.xyzw $vf9, $vf7, $vf8w");
    VU0_STORE("sqc2 $vf9, 0x0($a0)");
}
