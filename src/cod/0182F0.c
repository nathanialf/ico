#include "vu0.h"

void func_001182F0(void *p0, void *p1, void *p2)
{
    VU0_MEM("lqc2 $vf1, 0x0($a1)");
    VU0_REG("vmul.xyz $vf3, $vf1, $vf1");
    VU0_REG("vmulax.w $ACC, $vf0, $vf3x");
    VU0_REG("vmadday.w $ACC, $vf0, $vf3y");
    VU0_REG("vmaddz.w $vf3, $vf0, $vf3z");
    VU0_REG("vrsqrt $Q, $vf0w, $vf3w");
    VU0_WAIT();
    VU0_REG("vmulq.xyz $vf1, $vf1, $Q");
    VU0_MEM("sqc2 $vf1, 0x0($a0)");
    VU0_NOP();
}
