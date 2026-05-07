#include "vu0.h"

void func_00243EC0(void *p0, void *p1, void *p2)
{
    VU0_MOVE("mfc1 $t0, $f12");
    VU0_MOVE("mfc1 $t1, $f13");
    VU0_LOAD("lqc2 $vf6, 0x0($a1)");
    VU0_MOVE("qmtc2.ni $t0, $vf4");
    VU0_MOVE("qmtc2.ni $t1, $vf5");
    VU0_COMPUTE("vmaxx.xyzw $vf6, $vf6, $vf4x");
    VU0_COMPUTE("vminix.xyzw $vf6, $vf6, $vf5x");
    VU0_STORE("sqc2 $vf6, 0x0($a0)");
}
