#include "vu0.h"

void func_001185D0(void *p0, void *p1, void *p2)
{
    VU0_LSV(lqc2, 14, 0x0, a1);
    VU0_LSV(lqc2, 15, 0x10, a1);
    VU0_LSV(lqc2, 16, 0x20, a1);
    VU0_LSV(lqc2, 17, 0x30, a1);
    VU0_LSV(lqc2, 24, 0x0, a2);
    VU0_LSV(lqc2, 25, 0x10, a2);
    VU0_LSV(lqc2, 26, 0x20, a2);
    VU0_LSV(lqc2, 27, 0x30, a2);
    VU0_V3OP_ACC_BC(vmulax.xyzw, 14, 24, x);
    VU0_V3OP_ACC_BC(vmadday.xyzw, 15, 24, y);
    VU0_V3OP_ACC_BC(vmaddaz.xyzw, 16, 24, z);
    VU0_V3OP_BC(vmaddw.xyzw, 24, 17, 24, w);
    VU0_V3OP_ACC_BC(vmulax.xyzw, 14, 25, x);
    VU0_V3OP_ACC_BC(vmadday.xyzw, 15, 25, y);
    VU0_V3OP_ACC_BC(vmaddaz.xyzw, 16, 25, z);
    VU0_V3OP_BC(vmaddw.xyzw, 25, 17, 25, w);
    VU0_V3OP_ACC_BC(vmulax.xyzw, 14, 26, x);
    VU0_V3OP_ACC_BC(vmadday.xyzw, 15, 26, y);
    VU0_V3OP_ACC_BC(vmaddaz.xyzw, 16, 26, z);
    VU0_V3OP_BC(vmaddw.xyzw, 26, 17, 26, w);
    VU0_V3OP_ACC_BC(vmulax.xyzw, 14, 27, x);
    VU0_V3OP_ACC_BC(vmadday.xyzw, 15, 27, y);
    VU0_V3OP_ACC_BC(vmaddaz.xyzw, 16, 27, z);
    VU0_V3OP_BC(vmaddw.xyzw, 27, 17, 27, w);
    VU0_LSV(sqc2, 24, 0x0, a0);
    VU0_LSV(sqc2, 25, 0x10, a0);
    VU0_LSV(sqc2, 26, 0x20, a0);
    VU0_LSV(sqc2, 27, 0x30, a0);
    VU0_NOP();
}
