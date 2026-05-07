#include "vu0.h"

void func_00118AA0(void *p0)
{
    VU0_REG("vrnext.xyz $vf1, $R");
    VU0_V3OP_BC(vsubw.xyz, 1, 1, 0, w);
    VU0_LSV(sqc2, 1, 0x0, a0);
    VU0_NOP();
}
