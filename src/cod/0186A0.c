#include "vu0.h"

void func_001186A0(void *p0)
{
    VU0_COMPUTE("vmove.xyzw $vf17, $vf0");
    VU0_COMPUTE("vmr32.xyzw $vf16, $vf17");
    VU0_COMPUTE("vmr32.xyzw $vf15, $vf16");
    VU0_COMPUTE("vmr32.xyzw $vf14, $vf15");
    VU0_STORE("sqc2 $vf14, 0x0($a0)");
    VU0_STORE("sqc2 $vf15, 0x10($a0)");
    VU0_STORE("sqc2 $vf16, 0x20($a0)");
    VU0_NOP();
}
