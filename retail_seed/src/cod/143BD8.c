#include "vu0.h"

void func_00243BD8(void *p0)
{
    VU0_V3OP(vsub.xyzw, 4, 0, 0);
    VU0_V3OP(vadd.w, 4, 4, 0);
    VU0_V2OP(vmr32.xyzw, 5, 4);
    VU0_V2OP(vmr32.xyzw, 6, 5);
    VU0_V2OP(vmr32.xyzw, 7, 6);
    VU0_LSV(sqc2, 4, 0x30, a0);
    VU0_LSV(sqc2, 5, 0x20, a0);
    VU0_LSV(sqc2, 6, 0x10, a0);
    VU0_LSV(sqc2, 7, 0x0, a0);
}
