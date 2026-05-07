#include "vu0.h"

void func_001183F0(void *p0, void *p1, void *p2)
{
    VU0_LOAD("lqc2 $vf1, 0x0($a1)");
    VU0_NOREORDER_BEGIN();
    VU0_MOVE("mfc1 $t0, $f12");
    VU0_MOVE("qmtc2.ni $t0, $vf2");
    VU0_NOREORDER_END();
    VU0_COMPUTE("vmulx.xyz $vf1, $vf1, $vf2x");
    VU0_STORE("sqc2 $vf1, 0x0($a0)");
    VU0_NOP();
}
