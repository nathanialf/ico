#include "vu0.h"

void func_00118A48(void *p0, void *p1, void *p2, void *p3)
{
    VU0_NOREORDER_BEGIN();
    VU0_MOVE("mfc1 $a2, $f12");
    VU0_MOVE("qmtc2.ni $a2, $vf1");
    VU0_NOREORDER_END();
    VU0_COMPUTE("vaddw.x $vf2, $vf1, $vf0w");
    VU0_COMPUTE("vadd.x $vf1, $vf1, $vf1");
    VU0_COMPUTE("vrinit $R, $vf2x");
    VU0_COMPUTE("vrxor $R, $vf1x");
    VU0_NOP();
}
