#include "vu0.h"

void func_00118A80(void *p0)
{
    VU0_REG("vrnext.x $vf1, $R");
    VU0_REG("vrnext.y $vf1, $R");
    VU0_REG("vrnext.z $vf1, $R");
    VU0_V3OP_BC(vsubw.xyz, 1, 1, 0, w);
    VU0_LSV(sqc2, 1, 0x0, a0);
    VU0_NOP();
}
