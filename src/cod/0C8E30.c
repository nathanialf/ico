#include "vu0.h"

void func_001C8E30(void *p0)
{
    VU0_MEM("lqc2 $vf4, 0x0($a0)");
    VU0_REG("vmul.xz $vf4, $vf4, $vf4");
    VU0_REG("vaddz.x $vf4, $vf4, $vf4z");
    VU0_REG("vrsqrt $Q, $vf0w, $vf4x");
    VU0_WAIT();
    VU0_NOREORDER_BEGIN();
    VU0_REG("cfc2.ni $v0, $vi22");
    VU0_REG("mtc1 $v0, $f0");
    VU0_NOREORDER_END();
}
