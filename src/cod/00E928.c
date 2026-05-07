#include "vu0.h"

void func_0010E928(void *p0, void *p1, void *p2)
{
    VU0_MEM("lqc2 $vf14, 0x0($a0)");
    VU0_MEM("lqc2 $vf15, 0x0($a1)");
    VU0_REG("vmul.xyzw $vf15, $vf14, $vf15");
    VU0_REG("vaddy.x $vf15, $vf15, $vf15y");
    VU0_REG("vaddz.x $vf15, $vf15, $vf15z");
    VU0_REG("vaddw.x $vf15, $vf15, $vf15w");
    VU0_REG("qmfc2.ni $v0, $vf15");
    VU0_REG("mtc1 $v0, $f0");
    VU0_NOP();
}
