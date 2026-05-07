#include "vu0.h"

void func_00243B30(void *p0, void *p1, void *p2, void *p3, void *p4, void *p5)
{
    VU0_MEM("lqc2 $vf4, 0x0($a2)");
    VU0_MEM("lqc2 $vf5, 0x30($a1)");
    VU0_MEM("lq $a3, 0x0($a1)");
    VU0_MEM("lq $t0, 0x10($a1)");
    VU0_MEM("lq $t1, 0x20($a1)");
    VU0_REG("vadd.xyz $vf5, $vf5, $vf4");
    VU0_MEM("sq $a3, 0x0($a0)");
    VU0_MEM("sq $t0, 0x10($a0)");
    VU0_MEM("sq $t1, 0x20($a0)");
    VU0_MEM("sqc2 $vf5, 0x30($a0)");
}
