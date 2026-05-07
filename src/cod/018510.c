#include "vu0.h"

void func_00118510(void *p0, void *p1, void *p2)
{
    VU0_MEM("lqc2 $vf1, 0x0($a0)");
    VU0_MEM("lqc2 $vf2, 0x0($a1)");
    VU0_REG("vsub.xyzw $vf3, $vf1, $vf2");
    VU0_REG("vmul.xyz $vf3, $vf3, $vf3");
    VU0_REG("vmulax.w $ACC, $vf0, $vf3x");
    VU0_REG("vmadday.w $ACC, $vf0, $vf3y");
    VU0_REG("vmaddz.w $vf3, $vf0, $vf3z");
    VU0_WORD(0x4B8303BD);
    VU0_WAIT();
    VU0_NOREORDER_BEGIN();
    VU0_REG("cfc2.ni $v0, $vi22");
    VU0_REG("mtc1 $v0, $f0");
    VU0_NOREORDER_END();
}
