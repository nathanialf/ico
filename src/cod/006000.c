#include "vu0.h"

void func_00106000(void *p0)
{
    VU0_LOAD("lqc2 $vf4, 0x0($a0)");
    VU0_COMPUTE("vmul.xyz $vf4, $vf4, $vf4");
    VU0_COMPUTE("vaddy.x $vf4, $vf4, $vf4y");
    VU0_COMPUTE("vaddz.x $vf4, $vf4, $vf4z");
    VU0_WORD(0x4A0403BD);
    VU0_WAIT();
    VU0_NOREORDER_BEGIN();
    VU0_MOVE("cfc2.ni $v0, $vi22");
    VU0_MOVE("mtc1 $v0, $f0");
    VU0_NOREORDER_END();
}
