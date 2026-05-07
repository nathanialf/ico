#include "vu0.h"

void func_00118AA0(void *p0)
{
    VU0_COMPUTE("vrnext.xyz $vf1, $R");
    VU0_COMPUTE("vsubw.xyz $vf1, $vf1, $vf0w");
    VU0_STORE("sqc2 $vf1, 0x0($a0)");
    VU0_NOP();
}
