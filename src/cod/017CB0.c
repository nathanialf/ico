#include "vu0.h"

void func_00117CB0(void *p0)
{
    VU0_LSV(lqc2, 8, 0x0, a0);
    VU0_V3OP_ACC_BC(vmulax.xyzw, 4, 8, x);
    VU0_V3OP_ACC_BC(vmadday.xyzw, 5, 8, y);
    VU0_V3OP_ACC_BC(vmaddaz.xyzw, 6, 8, z);
    VU0_V3OP_BC(vmaddw.xyzw, 7, 7, 8, w);
    VU0_NOP();
}
