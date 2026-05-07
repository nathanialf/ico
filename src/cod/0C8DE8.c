#include "vu0.h"

void func_001C8DE8(void)
{
    VU0_NOREORDER_BEGIN();
    VU0_REG("mfc1 $t0, $f12");
    VU0_REG("qmtc2.ni $t0, $vf4");
    VU0_NOREORDER_END();
    VU0_REG("vrsqrt $Q, $vf0w, $vf4x");
    VU0_WAIT();
    VU0_NOREORDER_BEGIN();
    VU0_REG("cfc2.ni $v0, $vi22");
    VU0_REG("mtc1 $v0, $f0");
    VU0_NOREORDER_END();
}
