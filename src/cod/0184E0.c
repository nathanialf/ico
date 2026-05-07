#include "vu0.h"

void func_001184E0(void *p0)
{
    VU0_LOAD("lqc2 $vf3, 0x0($a0)");
    VU0_COMPUTE("vmul.xyz $vf3, $vf3, $vf3");
    VU0_COMPUTE("vmulax.w $ACC, $vf0, $vf3x");
    VU0_COMPUTE("vmadday.w $ACC, $vf0, $vf3y");
    VU0_COMPUTE("vmaddz.w $vf3, $vf0, $vf3z");
    VU0_WORD(0x4B8303BD);
    VU0_WAIT();
    VU0_NOREORDER_BEGIN();
    VU0_MOVE("cfc2.ni $v0, $vi22");
    VU0_MOVE("mtc1 $v0, $f0");
    VU0_NOREORDER_END();
}
