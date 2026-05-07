#include "vu0.h"

void func_00243BD8(void *p0)
{
    VU0_REG("vsub.xyzw $vf4, $vf0, $vf0");
    VU0_REG("vadd.w $vf4, $vf4, $vf0");
    VU0_REG("vmr32.xyzw $vf5, $vf4");
    VU0_REG("vmr32.xyzw $vf6, $vf5");
    VU0_REG("vmr32.xyzw $vf7, $vf6");
    VU0_MEM("sqc2 $vf4, 0x30($a0)");
    VU0_MEM("sqc2 $vf5, 0x20($a0)");
    VU0_MEM("sqc2 $vf6, 0x10($a0)");
    VU0_MEM("sqc2 $vf7, 0x0($a0)");
}
