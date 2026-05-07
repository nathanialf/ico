#include "vu0.h"

void func_00243950(void *p0, void *p1, void *p2)
{
    VU0_MEM("lqc2 $vf4, 0x0($a0)");
    VU0_MEM("lqc2 $vf5, 0x0($a1)");
    VU0_REG("vmul.xyz $vf5, $vf4, $vf5");
    VU0_REG("vaddy.x $vf5, $vf5, $vf5y");
    VU0_REG("vaddz.x $vf5, $vf5, $vf5z");
    VU0_REG("qmfc2.ni $v0, $vf5");
    VU0_REG("mtc1 $v0, $f0");
    VU0_NOP();
}
