#include "vu0.h"

void func_00118490(void *p0, void *p1, void *p2, void *p3)
{
    VU0_NOREORDER_BEGIN();
    VU0_MOVE("mfc1 $t0, $f12");
    VU0_MOVE("qmtc2.ni $t0, $vf3");
    VU0_NOREORDER_END();
    VU0_LOAD("lqc2 $vf1, 0x0($a1)");
    VU0_LOAD("lqc2 $vf2, 0x0($a2)");
    VU0_COMPUTE("vsubx.w $vf8, $vf0, $vf3x");
    VU0_COMPUTE("vmulax.xyzw $ACC, $vf1, $vf3x");
    VU0_COMPUTE("vmaddw.xyzw $vf9, $vf2, $vf8w");
    VU0_STORE("sqc2 $vf9, 0x0($a0)");
    VU0_NOP();
}
