#include "vu0.h"

void func_00118110(void)
{
    VU0_COMPUTE("vsub.xyzw $vf1, $vf0, $vf0");
    VU0_COMPUTE("vaddx.y $vf14, $vf1, $vf5x");
    VU0_COMPUTE("vaddx.z $vf14, $vf1, $vf6x");
    VU0_COMPUTE("vaddx.w $vf14, $vf1, $vf7x");
    VU0_COMPUTE("vaddy.x $vf15, $vf1, $vf4y");
    VU0_COMPUTE("vaddy.z $vf15, $vf1, $vf6y");
    VU0_COMPUTE("vaddy.w $vf15, $vf1, $vf7y");
    VU0_COMPUTE("vaddz.x $vf16, $vf1, $vf4z");
    VU0_COMPUTE("vaddz.y $vf16, $vf1, $vf5z");
    VU0_COMPUTE("vaddz.w $vf16, $vf1, $vf7z");
    VU0_COMPUTE("vaddw.x $vf17, $vf1, $vf4w");
    VU0_COMPUTE("vaddw.y $vf17, $vf1, $vf5w");
    VU0_COMPUTE("vaddw.z $vf17, $vf1, $vf6w");
    VU0_COMPUTE("vmove.yzw $vf4, $vf14");
    VU0_COMPUTE("vmove.xzw $vf5, $vf15");
    VU0_COMPUTE("vmove.xyw $vf6, $vf16");
    VU0_COMPUTE("vmove.xyz $vf7, $vf17");
    VU0_NOP();
}
