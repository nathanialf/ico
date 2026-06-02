#include "vu0.h"

void func_001186A0(void *p0)
{
    VU0_V2OP(vmove.xyzw, 17, 0);
    VU0_V2OP(vmr32.xyzw, 16, 17);
    VU0_V2OP(vmr32.xyzw, 15, 16);
    VU0_V2OP(vmr32.xyzw, 14, 15);
    VU0_LSV(sqc2, 14, 0x0, a0);
    VU0_LSV(sqc2, 15, 0x10, a0);
    VU0_LSV(sqc2, 16, 0x20, a0);
    VU0_NOP();
}
