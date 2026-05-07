#include "vu0.h"

void func_00117CB0(void *p0)
{
    VU0_LOAD("lqc2 $vf8, 0x0($a0)");
    VU0_COMPUTE("vmulax.xyzw $ACC, $vf4, $vf8x");
    VU0_COMPUTE("vmadday.xyzw $ACC, $vf5, $vf8y");
    VU0_COMPUTE("vmaddaz.xyzw $ACC, $vf6, $vf8z");
    VU0_COMPUTE("vmaddw.xyzw $vf7, $vf7, $vf8w");
    VU0_NOP();
}
