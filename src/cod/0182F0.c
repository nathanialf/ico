#include "vu0.h"

void func_001182F0(void *p0, void *p1, void *p2)
{
    VU0_LOAD("lqc2 $vf1, 0x0($a1)");
    VU0_COMPUTE("vmul.xyz $vf3, $vf1, $vf1");
    VU0_COMPUTE("vmulax.w $ACC, $vf0, $vf3x");
    VU0_COMPUTE("vmadday.w $ACC, $vf0, $vf3y");
    VU0_COMPUTE("vmaddz.w $vf3, $vf0, $vf3z");
    VU0_COMPUTE("vrsqrt $Q, $vf0w, $vf3w");
    VU0_WAIT();
    VU0_COMPUTE("vmulq.xyz $vf1, $vf1, $Q");
    VU0_STORE("sqc2 $vf1, 0x0($a0)");
    VU0_NOP();
}
