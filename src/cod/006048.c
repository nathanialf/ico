#include "matching.h"
#include "vu0.h"

extern void func_00243AE8(void *out, void *a, void *b);

float func_00106048(void *a, void *b)
{
    int local[4];
    register float result __asm__("$f0");
    func_00243AE8(local, a, b);
    VU0_LSV(lqc2, 4, 0x0, sp);
    VU0_V3OP(vmul.xyz, 4, 4, 4);
    VU0_V3OP_BC(vaddy.x, 4, 4, 4, y);
    VU0_V3OP_BC(vaddz.x, 4, 4, 4, z);
    VU0_WORD(0x4A0403BD);
    VU0_WAIT();
    VU0_CFC2_NI(v0, 22);
    VU0_MTC1(v0, 0);
    KEEP_LIVE_FP(result);
    return result;
}
