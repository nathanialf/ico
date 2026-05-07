#include "vu0.h"

void func_001C8EB0(void *p0, void *p1, void *p2, void *p3)
{
    VU0_LOAD("lqc2 $vf4, 0x0($a1)");
    VU0_LOAD("lqc2 $vf5, 0x0($a2)");
    VU0_NOREORDER_BEGIN();
    VU0_MOVE("mfc1 $t0, $f12");
    VU0_MOVE("qmtc2.ni $t0, $vf6");
    VU0_NOREORDER_END();
    VU0_COMPUTE("vmulx.xyz $vf5, $vf5, $vf6x");
    VU0_COMPUTE("vadd.xyz $vf4, $vf4, $vf5");
    VU0_STORE("sqc2 $vf4, 0x0($a0)");
    VU0_NOP();
}
