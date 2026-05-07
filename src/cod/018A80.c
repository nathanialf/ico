#include "vu0.h"

void func_00118A80(void *p0)
{
    VU0_COMPUTE("vrnext.x $vf1, $R");
    VU0_COMPUTE("vrnext.y $vf1, $R");
    VU0_COMPUTE("vrnext.z $vf1, $R");
    VU0_COMPUTE("vsubw.xyz $vf1, $vf1, $vf0w");
    VU0_STORE("sqc2 $vf1, 0x0($a0)");
    VU0_NOP();
}
