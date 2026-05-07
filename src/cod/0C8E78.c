#include "vu0.h"

void func_001C8E78(void *p0, void *p1, void *p2, void *p3)
{
    VU0_LOAD("lqc2 $vf1, 0x0($a1)");
    VU0_LOAD("lqc2 $vf2, 0x0($a2)");
    VU0_COMPUTE("vsub.xyzw $vf4, $vf1, $vf2");
    VU0_COMPUTE("vmul.xyz $vf3, $vf4, $vf4");
    VU0_COMPUTE("vaddy.x $vf3, $vf3, $vf3y");
    VU0_COMPUTE("vaddz.x $vf3, $vf3, $vf3z");
    VU0_COMPUTE("vrsqrt $Q, $vf0w, $vf3x");
    VU0_STORE("sqc2 $vf4, 0x0($a0)");
    VU0_WAIT();
    VU0_NOREORDER_BEGIN();
    VU0_MOVE("cfc2.ni $v0, $vi22");
    VU0_MOVE("mtc1 $v0, $f0");
    VU0_NOREORDER_END();
}
