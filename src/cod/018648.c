#include "vu0.h"

void func_00118648(void *p0, void *p1, void *p2, void *p3)
{
    VU0_MEM("lqc2 $vf8, 0x0($a2)");
    VU0_MEM("lqc2 $vf14, 0x0($a1)");
    VU0_MEM("lqc2 $vf15, 0x10($a1)");
    VU0_MEM("lqc2 $vf16, 0x20($a1)");
    VU0_MEM("lqc2 $vf17, 0x30($a1)");
    VU0_REG("vmulax.xyzw $ACC, $vf14, $vf8x");
    VU0_REG("vmadday.xyzw $ACC, $vf15, $vf8y");
    VU0_REG("vmaddaz.xyzw $ACC, $vf16, $vf8z");
    VU0_REG("vmaddw.xyzw $vf10, $vf17, $vf8w");
    VU0_MEM("sqc2 $vf10, 0x0($a0)");
    VU0_NOP();
}
