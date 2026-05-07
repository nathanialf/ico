#include "vu0.h"

void func_00117C60(void)
{
    VU0_REG("vmove.xyzw $vf7, $vf0");
    VU0_REG("vmr32.xyzw $vf6, $vf7");
    VU0_REG("vmr32.xyzw $vf5, $vf6");
    VU0_REG("vmr32.xyzw $vf4, $vf5");
    VU0_REG("viaddi $vi15, $vi0, 0x0");
    VU0_NOP();
}
