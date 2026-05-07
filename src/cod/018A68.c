#include "vu0.h"

void func_00118A68(void *p0, void *p1, void *p2, void *p3, void *p4, void *p5)
{
    VU0_COMPUTE("vrnext.x $vf1, $R");
    VU0_COMPUTE("vsubw.x $vf1, $vf1, $vf0w");
    VU0_MOVE("qmfc2.ni $a3, $vf1");
    VU0_MOVE("mtc1 $a3, $f0");
    VU0_NOP();
}
