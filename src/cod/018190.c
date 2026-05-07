#include "vu0.h"

void func_00118190(void)
{
    VU0_COMPUTE("vsub.xyzw $vf1, $vf0, $vf0");
    VU0_COMPUTE("vsubw.x $vf2, $vf0, $vf0w");
    VU0_COMPUTE("vaddx.y $vf14, $vf1, $vf5x");
    VU0_COMPUTE("vaddx.z $vf14, $vf1, $vf6x");
    VU0_COMPUTE("vaddy.x $vf15, $vf1, $vf4y");
    VU0_COMPUTE("vaddy.z $vf15, $vf1, $vf6y");
    VU0_COMPUTE("vaddz.x $vf16, $vf1, $vf4z");
    VU0_COMPUTE("vaddz.y $vf16, $vf1, $vf5z");
    VU0_COMPUTE("vmulx.xyz $vf17, $vf7, $vf2x");
    VU0_COMPUTE("vmove.yz $vf4, $vf14");
    VU0_COMPUTE("vmove.xz $vf5, $vf15");
    VU0_COMPUTE("vmove.xy $vf6, $vf16");
    VU0_COMPUTE("vmove.w $vf17, $vf0");
    VU0_COMPUTE("vmulax.xyzw $ACC, $vf4, $vf17x");
    VU0_COMPUTE("vmadday.xyzw $ACC, $vf5, $vf17y");
    VU0_COMPUTE("vmaddaz.xyzw $ACC, $vf6, $vf17z");
    VU0_COMPUTE("vmaddw.xyzw $vf7, $vf0, $vf17w");
    VU0_NOP();
}
