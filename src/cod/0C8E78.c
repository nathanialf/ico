#include "vu0.h"

void func_001C8E78(void *p0, void *p1, void *p2, void *p3)
{
    VU0_MEM("lqc2 $vf1, 0x0($a1)");
    VU0_MEM("lqc2 $vf2, 0x0($a2)");
    VU0_REG("vsub.xyzw $vf4, $vf1, $vf2");
    VU0_REG("vmul.xyz $vf3, $vf4, $vf4");
    VU0_REG("vaddy.x $vf3, $vf3, $vf3y");
    VU0_REG("vaddz.x $vf3, $vf3, $vf3z");
    VU0_REG("vrsqrt $Q, $vf0w, $vf3x");
    VU0_MEM("sqc2 $vf4, 0x0($a0)");
    VU0_WAIT();
    VU0_NOREORDER_BEGIN();
    VU0_REG("cfc2.ni $v0, $vi22");
    VU0_REG("mtc1 $v0, $f0");
    VU0_NOREORDER_END();
}
