#include "vu0.h"

void func_00118578(void *p0, void *p1, void *p2)
{
    VU0_LOAD("lqc2 $vf1, 0x0($a0)");
    VU0_LOAD("lqc2 $vf2, 0x0($a1)");
    VU0_COMPUTE("vsub.xyzw $vf3, $vf1, $vf2");
    VU0_COMPUTE("vmul.xz $vf3, $vf3, $vf3");
    VU0_COMPUTE("vaddz.x $vf3, $vf3, $vf3z");
    VU0_WORD(0x4A0303BD);
    VU0_WAIT();
    VU0_NOREORDER_BEGIN();
    VU0_MOVE("cfc2.ni $v0, $vi22");
    VU0_MOVE("mtc1 $v0, $f0");
    VU0_NOREORDER_END();
}
