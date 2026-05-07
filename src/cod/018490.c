#include "vu0.h"

void func_00118490(void *p0, void *p1, void *p2, void *p3)
{
    VU0_NOREORDER_BEGIN();
    VU0_REG("mfc1 $t0, $f12");
    VU0_REG("qmtc2.ni $t0, $vf3");
    VU0_NOREORDER_END();
    VU0_MEM("lqc2 $vf1, 0x0($a1)");
    VU0_MEM("lqc2 $vf2, 0x0($a2)");
    VU0_REG("vsubx.w $vf8, $vf0, $vf3x");
    VU0_REG("vmulax.xyzw $ACC, $vf1, $vf3x");
    VU0_REG("vmaddw.xyzw $vf9, $vf2, $vf8w");
    VU0_MEM("sqc2 $vf9, 0x0($a0)");
    VU0_NOP();
}
