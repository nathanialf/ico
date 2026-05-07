#include "vu0.h"

void func_001180E0(void *p0, void *p1, void *p2)
{
    VU0_MEM("lqc2 $vf8, 0x0($a1)");
    VU0_REG("vmulax.xyzw $ACC, $vf4, $vf8x");
    VU0_REG("vmadday.xyzw $ACC, $vf5, $vf8y");
    VU0_REG("vmaddaz.xyzw $ACC, $vf6, $vf8z");
    VU0_REG("vmaddw.xyzw $vf10, $vf7, $vf8w");
    VU0_REG("vdiv $Q, $vf0w, $vf10w");
    VU0_WAIT();
    VU0_REG("vmulq.xyz $vf10, $vf10, $Q");
    VU0_MEM("sqc2 $vf10, 0x0($a0)");
    VU0_NOP();
}
