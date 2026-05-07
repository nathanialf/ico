#include "vu0.h"

void func_00117C40(void)
{
    VU0_COMPUTE("vmove.xyzw $vf7, $vf0");
    VU0_COMPUTE("vmr32.xyzw $vf6, $vf7");
    VU0_COMPUTE("vmr32.xyzw $vf5, $vf6");
    VU0_COMPUTE("vmr32.xyzw $vf4, $vf5");
    VU0_COMPUTE("viaddi $vi15, $vi0, 0x0");
    VU0_NOP();
}
