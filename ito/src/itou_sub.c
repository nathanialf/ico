#include "common.h"
#include "vu0.h"

void m33_to_quat(float *a0, float *a1) {
    a0[0] = -a1[0];
    a0[1] = -a1[1];
    a0[2] = -a1[2];
    a0[3] = a1[3];
}

void lw_pos_to_ico_pos(void *a0, void *a1, void *a2) {
    VU0_LSV(lqc2, 4, 0x0, 5);
    VU0_LSV(lqc2, 5, 0x10, 5);
    VU0_LSV(lqc2, 6, 0x20, 5);
    VU0_LSV(lqc2, 7, 0x30, 5);
    VU0_LSV(lqc2, 8, 0x0, 6);
    VU0_V3OP_ACC_BC(vmulax.xyzw, 4, 8, x);
    VU0_V3OP_ACC_BC(vmadday.xyzw, 5, 8, y);
    VU0_V3OP_ACC_BC(vmaddaz.xyzw, 6, 8, z);
    VU0_V3OP_BC(vmaddw.xyzw, 9, 7, 0, w);
    VU0_LSV(sqc2, 9, 0x0, 4);
    VU0_NOP();
}

extern void func_0023FED0(void *a0);
extern void func_00195B88(void *a0, void *a1);

void apply_matrix_w1(void *a0) {
    char buf[0x40];
    func_0023FED0(buf);
    func_00195B88(a0, buf);
}

INCLUDE_ASM("asm/aug6/nonmatchings/ito/src/itou_sub", ico_m33_to_quat);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/src/itou_sub", pbga_start);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/src/itou_sub", func_001962C0);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/src/itou_sub", func_00196D70);
