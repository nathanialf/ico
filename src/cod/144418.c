#include "vu0.h"

void func_00244418(void *p0, void *p1, void *p2, void *p3)
{
    VU0_LOAD("lqc2 $vf4, 0x0($a1)");
    VU0_LOAD("lqc2 $vf5, 0x0($a2)");
    VU0_NOREORDER_BEGIN();
    VU0_MOVE("mfc1 $t0, $f12");
    VU0_MOVE("qmtc2.ni $t0, $vf6");
    VU0_NOREORDER_END();
    VU0_COMPUTE("vmove.w $vf9, $vf4");
    VU0_COMPUTE("vaddw.x $vf7, $vf0, $vf0w");
    VU0_COMPUTE("vsub.x $vf8, $vf7, $vf6");
    VU0_COMPUTE("vmulax.xyz $ACC, $vf4, $vf6x");
    VU0_COMPUTE("vmaddx.xyz $vf9, $vf5, $vf8x");
    VU0_STORE("sqc2 $vf9, 0x0($a0)");
}
