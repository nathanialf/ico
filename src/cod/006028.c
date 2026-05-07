#include "vu0.h"

void func_00106028(void *p0)
{
    VU0_MEM("lqc2 $vf3, 0x0($a0)");
    VU0_REG("vmul.xyz $vf3, $vf3, $vf3");
    VU0_REG("vaddy.x $vf3, $vf3, $vf3y");
    VU0_REG("vaddz.x $vf3, $vf3, $vf3z");
    VU0_REG("qmfc2.ni $v0, $vf3");
    VU0_REG("mtc1 $v0, $f0");
    VU0_NOP();
}
