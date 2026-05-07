#include "vu0.h"

void func_0010DDB8(void *p0, void *p1, void *p2, void *p3)
{
    VU0_LOAD("lqc2 $vf11, 0x0($a1)");
    VU0_LOAD("lqc2 $vf12, 0x0($a2)");
    VU0_COMPUTE("vmul.xyzw $vf13, $vf11, $vf12");
    VU0_COMPUTE("vaddy.x $vf13, $vf13, $vf13y");
    VU0_COMPUTE("vaddz.x $vf13, $vf13, $vf13z");
    VU0_COMPUTE("vsubx.w $vf13, $vf13, $vf13x");
    VU0_COMPUTE("vmulw.xyz $vf14, $vf12, $vf11w");
    VU0_COMPUTE("vmulw.xyz $vf15, $vf11, $vf12w");
    VU0_COMPUTE("vopmula.xyz $ACC, $vf12, $vf11");
    VU0_COMPUTE("vopmsub.xyz $vf16, $vf11, $vf12");
    VU0_COMPUTE("vadd.xyz $vf13, $vf14, $vf15");
    VU0_COMPUTE("vadd.xyz $vf13, $vf13, $vf16");
    VU0_STORE("sqc2 $vf13, 0x0($a0)");
    VU0_NOP();
}
