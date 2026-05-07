#include "vu0.h"

void func_00117CD0(void *p0)
{
    VU0_LOAD("lqc2 $vf8, 0x0($a0)");
    VU0_COMPUTE("vmove.xyzw $vf7, $vf8");
    VU0_NOP();
}
