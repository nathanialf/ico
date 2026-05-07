#include "vu0.h"

void func_00118190(void)
{
    VU0_REG("vsub.xyzw $vf1, $vf0, $vf0");
    VU0_REG("vsubw.x $vf2, $vf0, $vf0w");
    VU0_REG("vaddx.y $vf14, $vf1, $vf5x");
    VU0_REG("vaddx.z $vf14, $vf1, $vf6x");
    VU0_REG("vaddy.x $vf15, $vf1, $vf4y");
    VU0_REG("vaddy.z $vf15, $vf1, $vf6y");
    VU0_REG("vaddz.x $vf16, $vf1, $vf4z");
    VU0_REG("vaddz.y $vf16, $vf1, $vf5z");
    VU0_REG("vmulx.xyz $vf17, $vf7, $vf2x");
    VU0_REG("vmove.yz $vf4, $vf14");
    VU0_REG("vmove.xz $vf5, $vf15");
    VU0_REG("vmove.xy $vf6, $vf16");
    VU0_REG("vmove.w $vf17, $vf0");
    VU0_REG("vmulax.xyzw $ACC, $vf4, $vf17x");
    VU0_REG("vmadday.xyzw $ACC, $vf5, $vf17y");
    VU0_REG("vmaddaz.xyzw $ACC, $vf6, $vf17z");
    VU0_REG("vmaddw.xyzw $vf7, $vf0, $vf17w");
    VU0_NOP();
}
