#include "vu0.h"

void func_00118320(void *p0, void *p1, void *p2)
{
    VU0_LOAD("lqc2 $vf1, 0x0($a0)");
    VU0_LOAD("lqc2 $vf2, 0x0($a1)");
    VU0_COMPUTE("vaddw.x $vf3, $vf0, $vf0w");
    VU0_COMPUTE("vmul.xyz $vf2, $vf1, $vf2");
    VU0_COMPUTE("vaddax.x $ACC, $vf0, $vf2x");
    VU0_COMPUTE("vmadday.x $ACC, $vf3, $vf2y");
    VU0_COMPUTE("vmaddz.x $vf2, $vf3, $vf2z");
    VU0_MOVE("qmfc2.ni $v0, $vf2");
    VU0_MOVE("mtc1 $v0, $f0");
    VU0_NOP();
}
