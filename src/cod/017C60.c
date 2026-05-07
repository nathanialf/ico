#include "vu0.h"

void func_00117C60(void)
{
    VU0_V2OP(vmove.xyzw, 7, 0);
    VU0_V2OP(vmr32.xyzw, 6, 7);
    VU0_V2OP(vmr32.xyzw, 5, 6);
    VU0_V2OP(vmr32.xyzw, 4, 5);
    VU0_REG("viaddi $vi15, $vi0, 0x0");
    VU0_NOP();
}
