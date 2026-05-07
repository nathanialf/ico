#include "vu0.h"

void func_00118A68(void *p0, void *p1, void *p2, void *p3, void *p4, void *p5)
{
    VU0_REG("vrnext.x $vf1, $R");
    VU0_REG("vsubw.x $vf1, $vf1, $vf0w");
    VU0_REG("qmfc2.ni $a3, $vf1");
    VU0_REG("mtc1 $a3, $f0");
    VU0_NOP();
}
