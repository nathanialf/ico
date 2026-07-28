#include "common.h"


#include "vu0.h"
void set_vertex(void *p0, void *p1, void *p2, void *p3)
{
    VU0_LSV(lqc2, 8, 0x0, a2);
    VU0_LSV(lqc2, 4, 0x0, a1);
    VU0_LSV(lqc2, 5, 0x10, a1);
    VU0_LSV(lqc2, 6, 0x20, a1);
    VU0_V3OP_ACC_BC(vmulax.xyzw, 4, 8, x);
    VU0_V3OP_ACC_BC(vmadday.xyzw, 5, 8, y);
    VU0_V3OP_BC(vmaddz.xyzw, 12, 6, 8, z);
    VU0_LSV(sqc2, 12, 0x0, a0);
    VU0_NOP();
}

INCLUDE_ASM("asm/nonmatchings/src/lightning", DrawLightning2);

INCLUDE_ASM("asm/nonmatchings/src/lightning", DrawLightningN);

int apply_m34(int *self, int *other) {
    return *(int *)((char *)self + 0x10) - *(int *)((char *)other + 0x10);
}

INCLUDE_ASM("asm/nonmatchings/src/lightning", DrawLightning);

INCLUDE_ASM("asm/nonmatchings/src/lightning", func_00199A08);

INCLUDE_ASM("asm/nonmatchings/src/lightning", func_00199A60);

INCLUDE_ASM("asm/nonmatchings/src/lightning", func_00199C30);

INCLUDE_ASM("asm/nonmatchings/src/lightning", func_0019A6E8);

