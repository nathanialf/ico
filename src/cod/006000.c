#include "vu0.h"

void func_00106000(void *p0)
{
    VU0_MEM("lqc2 $vf4, 0x0($a0)");
    VU0_REG("vmul.xyz $vf4, $vf4, $vf4");
    VU0_REG("vaddy.x $vf4, $vf4, $vf4y");
    VU0_REG("vaddz.x $vf4, $vf4, $vf4z");
    VU0_WORD(0x4A0403BD);
    VU0_WAIT();
    VU0_NOREORDER_BEGIN();
    VU0_REG("cfc2.ni $v0, $vi22");
    VU0_REG("mtc1 $v0, $f0");
    VU0_NOREORDER_END();
}
