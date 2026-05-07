#include "vu0.h"

void func_00118A68(void *p0, void *p1, void *p2, void *p3, void *p4, void *p5)
{
    VU0_REG("vrnext.x $vf1, $R");
    VU0_V3OP_BC(vsubw.x, 1, 1, 0, w);
    VU0_QMFC2_NI(a3, 1);
    VU0_MTC1(a3, 0);
    VU0_NOP();
}
