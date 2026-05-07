#include "vu0.h"

void func_00118AA0(void *p0)
{
    VU0_REG("vrnext.xyz $vf1, $R");
    VU0_REG("vsubw.xyz $vf1, $vf1, $vf0w");
    VU0_MEM("sqc2 $vf1, 0x0($a0)");
    VU0_NOP();
}
