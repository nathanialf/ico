#include "vu0.h"

void func_00118320(void *p0, void *p1, void *p2)
{
    VU0_MEM("lqc2 $vf1, 0x0($a0)");
    VU0_MEM("lqc2 $vf2, 0x0($a1)");
    VU0_REG("vaddw.x $vf3, $vf0, $vf0w");
    VU0_REG("vmul.xyz $vf2, $vf1, $vf2");
    VU0_REG("vaddax.x $ACC, $vf0, $vf2x");
    VU0_REG("vmadday.x $ACC, $vf3, $vf2y");
    VU0_REG("vmaddz.x $vf2, $vf3, $vf2z");
    VU0_REG("qmfc2.ni $v0, $vf2");
    VU0_REG("mtc1 $v0, $f0");
    VU0_NOP();
}
