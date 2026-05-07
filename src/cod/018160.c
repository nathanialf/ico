#include "vu0.h"

void func_00118160(void)
{
    VU0_REG("vsub.xyzw $vf1, $vf0, $vf0");
    VU0_REG("vaddx.y $vf14, $vf1, $vf5x");
    VU0_REG("vaddx.z $vf14, $vf1, $vf6x");
    VU0_REG("vaddy.x $vf15, $vf1, $vf4y");
    VU0_REG("vaddy.z $vf15, $vf1, $vf6y");
    VU0_REG("vaddz.x $vf16, $vf1, $vf4z");
    VU0_REG("vaddz.y $vf16, $vf1, $vf5z");
    VU0_REG("vmove.yz $vf4, $vf14");
    VU0_REG("vmove.xz $vf5, $vf15");
    VU0_REG("vmove.xy $vf6, $vf16");
    VU0_NOP();
}
