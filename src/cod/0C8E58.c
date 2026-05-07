#include "vu0.h"

void func_001C8E58(void *p0)
{
    VU0_LOAD("lqc2 $vf4, 0x0($a0)");
    VU0_COMPUTE("vmul.xz $vf4, $vf4, $vf4");
    VU0_COMPUTE("vaddz.x $vf4, $vf4, $vf4z");
    VU0_MOVE("qmfc2.ni $v0, $vf4");
    VU0_MOVE("mtc1 $v0, $f0");
    VU0_NOP();
}
