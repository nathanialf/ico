#include "vu0.h"

void func_00106028(void *p0)
{
    VU0_LOAD("lqc2 $vf3, 0x0($a0)");
    VU0_COMPUTE("vmul.xyz $vf3, $vf3, $vf3");
    VU0_COMPUTE("vaddy.x $vf3, $vf3, $vf3y");
    VU0_COMPUTE("vaddz.x $vf3, $vf3, $vf3z");
    VU0_MOVE("qmfc2.ni $v0, $vf3");
    VU0_MOVE("mtc1 $v0, $f0");
    VU0_NOP();
}
