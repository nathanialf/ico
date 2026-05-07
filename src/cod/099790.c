#include "vu0.h"

void func_00199790(void *p0, void *p1, void *p2, void *p3)
{
    VU0_MEM("lqc2 $vf8, 0x0($a2)");
    VU0_MEM("lqc2 $vf4, 0x0($a1)");
    VU0_MEM("lqc2 $vf5, 0x10($a1)");
    VU0_MEM("lqc2 $vf6, 0x20($a1)");
    VU0_REG("vmulax.xyzw $ACC, $vf4, $vf8x");
    VU0_REG("vmadday.xyzw $ACC, $vf5, $vf8y");
    VU0_REG("vmaddz.xyzw $vf12, $vf6, $vf8z");
    VU0_MEM("sqc2 $vf12, 0x0($a0)");
    VU0_NOP();
}
