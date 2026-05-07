#include "vu0.h"

void func_00243B30(void *p0, void *p1, void *p2, void *p3, void *p4, void *p5)
{
    VU0_LOAD("lqc2 $vf4, 0x0($a2)");
    VU0_LOAD("lqc2 $vf5, 0x30($a1)");
    VU0_LOAD("lq $a3, 0x0($a1)");
    VU0_LOAD("lq $t0, 0x10($a1)");
    VU0_LOAD("lq $t1, 0x20($a1)");
    VU0_COMPUTE("vadd.xyz $vf5, $vf5, $vf4");
    VU0_STORE("sq $a3, 0x0($a0)");
    VU0_STORE("sq $t0, 0x10($a0)");
    VU0_STORE("sq $t1, 0x20($a0)");
    VU0_STORE("sqc2 $vf5, 0x30($a0)");
}
