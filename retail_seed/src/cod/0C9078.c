#include "matching.h"
#include "vu0.h"

int func_001C9078(void *a0, void *a1)
{
    int bits;
    int v0 = 0;
    VU0_LSV(lqc2, 1, 0x0, a0);
    VU0_LSV(lqc2, 2, 0x0, a1);
    VU0_V3OP(vmul.xyz, 3, 1, 2);
    VU0_V3OP_BC(vaddy.x, 3, 3, 3, y);
    VU0_V3OP_BC(vaddz.x, 3, 3, 3, z);
    VU0_V3OP_BC(vaddw.x, 3, 3, 2, w);
    VU0_QMFC2_NI(v0, 3);
    bits = v0;
    {
        register float f1 __asm__("$f1");
        register float f0 __asm__("$f0");
        VU0_MTC1(v0, 1);
        VU0_REG("mtc1 $0, $f0");
        if (f0 < f1) return 1;
    }
    return 0;
}
