#include "vu0.h"

void func_00243950(void *p0, void *p1, void *p2)
{
    VU0_LOAD("lqc2 $vf4, 0x0($a0)");
    VU0_LOAD("lqc2 $vf5, 0x0($a1)");
    VU0_COMPUTE("vmul.xyz $vf5, $vf4, $vf5");
    VU0_COMPUTE("vaddy.x $vf5, $vf5, $vf5y");
    VU0_COMPUTE("vaddz.x $vf5, $vf5, $vf5z");
    VU0_MOVE("qmfc2.ni $v0, $vf5");
    VU0_MOVE("mtc1 $v0, $f0");
    VU0_NOP();
}
