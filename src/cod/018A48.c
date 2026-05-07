#include "vu0.h"

void func_00118A48(void *p0, void *p1, void *p2, void *p3)
{
    VU0_NOREORDER_BEGIN();
    VU0_REG("mfc1 $a2, $f12");
    VU0_REG("qmtc2.ni $a2, $vf1");
    VU0_NOREORDER_END();
    VU0_REG("vaddw.x $vf2, $vf1, $vf0w");
    VU0_REG("vadd.x $vf1, $vf1, $vf1");
    VU0_REG("vrinit $R, $vf2x");
    VU0_REG("vrxor $R, $vf1x");
    VU0_NOP();
}
